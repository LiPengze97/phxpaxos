/*
Tencent is pleased to support the open source community by making 
PhxPaxos available.
Copyright (C) 2016 THL A29 Limited, a Tencent company. 
All rights reserved.

Licensed under the BSD 3-Clause License (the "License"); you may 
not use this file except in compliance with the License. You may 
obtain a copy of the License at

https://opensource.org/licenses/BSD-3-Clause

Unless required by applicable law or agreed to in writing, software 
distributed under the License is distributed on an "AS IS" basis, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or 
implied. See the License for the specific language governing 
permissions and limitations under the License.

See the AUTHORS file for names of contributors. 
*/

#pragma once

#include <grpc++/grpc++.h>
#include "phxkv.grpc.pb.h"
#include "kv_paxos.h"
#include <iostream>
using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerCompletionQueue;
using grpc::ServerContext;
using grpc::Status;
namespace phxkv
{
    inline uint64_t get_time_us()
    {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
    }
    class PhxKVServiceImpl final
    {
    public:
        uint64_t pre_time = 0, cur_time;
        int cnt = 0;
        PhxKVServiceImpl(const phxpaxos::NodeInfo &oMyNode, const phxpaxos::NodeInfoList &vecNodeList,
                         const std::string &sKVDBPath, const std::string &sPaxosLogPath);

        int Init();
        void run(std::string sServerAddress);

    private:
        // Class encompasing the state and logic needed to serve a request.
        class CallData
        {
        public:
            uint64_t pre_time = 0, cur_time;

            // Take in the "service" instance (in this case representing an asynchronous
            // server) and the completion queue "cq" used for asynchronous communication
            // with the gRPC runtime.
            CallData(PhxKVServer::AsyncService *service, ServerCompletionQueue *cq, PhxKV *m_oPhxKV)
                : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), m_oPhxKV(m_oPhxKV)
            {
                // Invoke the serving logic right away.
                Proceed();
            }

            void Proceed()
            {
                if (status_ == CREATE)
                {
                    // Make this instance progress to the PROCESS state.
                    status_ = PROCESS;

                    // As part of the initial CREATE state, we *request* that the system
                    // start processing SayHello requests. In this request, "this" acts are
                    // the tag uniquely identifying the request (so that different CallData
                    // instances can serve different requests concurrently), in this case
                    // the memory address of this CallData instance.
                    service_->RequestPut(&ctx_, &request_, &responder_, cq_, cq_,
                                         this);
                    std::cout <<  "create state: " << std::endl;
                }
                else if (status_ == PROCESS)
                {
                    std::cout <<  "process state: " << std::endl;
                    // Spawn a new CallData instance to serve new clients while we process
                    // the one for this CallData. The instance will deallocate itself as
                    // part of its FINISH state.
                    new CallData(service_, cq_, m_oPhxKV);
                    bool master_flag = true;
                    // The actual processing.
                    std::string prefix("Hello ");
                    // reply_.set_message(prefix + request_.name());
                    if (!m_oPhxKV->IsIMMaster(request_.key()))
                    {
                        reply_.set_ret((int)PhxKVStatus::MASTER_REDIRECT);
                        uint64_t llMasterNodeID = m_oPhxKV->GetMaster(request_.key()).GetNodeID();
                        reply_.set_master_nodeid(llMasterNodeID);

                        PLImp("I'm not master, need redirect, master nodeid i saw %lu, key %s version %lu",
                              llMasterNodeID, request_.key().c_str(), request_.version());
                        master_flag = false;
                    }
                    if (master_flag)
                    {
                        // if (pre_time != 0)
                        // {
                        //     cur_time = get_time_us();
                        //     std::cout << "put interval: " << (cur_time - pre_time) / 1000 << std::endl;
                        //     PLImp("put interval: %lu", (cur_time - pre_time) / 1000);
                        // }
                        // pre_time = cur_time;
                        uint64_t kv_put_st = get_time_us();
                        PhxKVStatus status = m_oPhxKV->Put(request_.key(), request_.value(), request_.version());
                        std::cout <<  "process state put used: " << (get_time_us() - kv_put_st) / 1000 << std::endl;
                        reply_.set_ret((int)status);

                        PLImp("ret %d, key %s version %lu", reply_.ret(), request_.key().c_str(), request_.version());
                    }
                    // And we are done! Let the gRPC runtime know we've finished, using the
                    // memory address of this instance as the uniquely identifying tag for
                    // the event.
                    status_ = FINISH;
                    responder_.Finish(reply_, Status::OK, this);
                }
                else
                {
                    GPR_ASSERT(status_ == FINISH);
                    // Once in the FINISH state, deallocate ourselves (CallData).
                    delete this;
                }
            }

        private:
            // The means of communication with the gRPC runtime for an asynchronous
            // server.
            PhxKVServer::AsyncService *service_;
            // The producer-consumer queue where for asynchronous server notifications.
            ServerCompletionQueue *cq_;
            // Context for the rpc, allowing to tweak aspects of it such as the use
            // of compression, authentication, as well as to send metadata back to the
            // client.
            ServerContext ctx_;

            // What we get from the client.
            KVOperator request_;
            // What we send back to the client.
            KVResponse reply_;

            // The means to get back to the client.
            ServerAsyncResponseWriter<KVResponse> responder_;

            // Let's implement a tiny state machine with the following states.
            enum CallStatus
            {
                CREATE,
                PROCESS,
                FINISH
            };
            CallStatus status_; // The current serving state.
            PhxKV *m_oPhxKV;
        };
        PhxKV m_oPhxKV;
        void HandleRpcs()
        {
            // Spawn a new CallData instance to serve new clients.
            new CallData(&service_, cq_.get(), &m_oPhxKV);
            void *tag; // uniquely identifies a request.
            bool ok;
            while (true)
            {
                // Block waiting to read the next event from the completion queue. The
                // event is uniquely identified by its tag, which in this case is the
                // memory address of a CallData instance.
                // The return value of Next should always be checked. This return value
                // tells us whether there is any kind of event or cq_ is shutting down.
                GPR_ASSERT(cq_->Next(&tag, &ok));
                GPR_ASSERT(ok);
                uint64_t st_proceed = get_time_us();
                static_cast<CallData *>(tag)->Proceed();
                std::cout << cnt << " proceed used: " << (get_time_us() - st_proceed) / 1000 << std::endl;
                cur_time = get_time_us();
                if (pre_time != 0)
                {
                    std::cout << cnt++ << " put interval: " << (cur_time - pre_time) / 1000 << std::endl;
                }
                pre_time = cur_time;
            }
        }
        std::unique_ptr<ServerCompletionQueue> cq_;
        PhxKVServer::AsyncService service_;
        std::unique_ptr<Server> server_;
    };
    // This can be run in multiple threads if needed.
} // namespace phxkv
