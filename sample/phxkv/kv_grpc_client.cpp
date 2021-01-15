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

#include "kv_grpc_client.h"
#include "phxpaxos/options.h"
#include <iostream>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace phxpaxos;
using namespace std;

namespace phxkv
{

    PhxKVClient ::PhxKVClient(std::shared_ptr<Channel> channel, int msg_num)
        : stub_(PhxKVServer::NewStub(channel)), msg_num(msg_num)
    {
    }

    void PhxKVClient ::AsyncCompleteRpc()
    {
        void *got_tag;
        bool ok = false;

        // Block until the next result is available in the completion queue "cq".
        while (cq_.Next(&got_tag, &ok))
        {
            // The tag in this example is the memory location of the call object
            AsyncClientCall *call = static_cast<AsyncClientCall *>(got_tag);

            // Verify that the request was completed successfully. Note that "ok"
            // corresponds solely to the request for updates introduced by Finish().
            GPR_ASSERT(ok);

            if (call->status.ok())
            {
                KVResponse oResponse = call->response;
                if (oResponse.ret() == static_cast<int>(PhxKVStatus::MASTER_REDIRECT))
                {
                    if (oResponse.master_nodeid() != phxpaxos::nullnode)
                    {
                        std::cout << "NOT MASTER RESTART!!" << std::endl;
                    }
                }
                else
                {
                    send_receive_time_keeper[cnt * 2 + 1] = get_time_us();
                    std::cout << oResponse.ret() << " is 0 means " << cnt << "success" << std::endl;
                }
                cnt++;
            }
            else
            {
                std::cout << "RPC failed" << std::endl;
            }

            // Once we're complete, deallocate the call object.
            delete call;
            if (cnt == msg_num)
            {
                std::ofstream file("./small_trace_all_sf_for_each_msg_phxkv.csv");
                if (file)
                {
                    file << "enter_time,complete_time\n";
                    for (int i = 0; i < cnt; i++)
                    {
                        file << send_receive_time_keeper[i * 2] << "," << send_receive_time_keeper[i * 2 + 1] << "\n";
                    }
                }
                file.close();
                break;
            }
        }
    }

    void PhxKVClient ::NewChannel(const uint64_t llNodeID)
    {
        NodeInfo oNodeInfo(llNodeID);

        //for test multi node in one machine, each node have difference grpc_port.
        //but normally, every node's grpc_port is same, so you just set your grpc_port.
        //if you change paxos_port/grpc_port's relation, you must modify this line.
        int iGrpcPort = oNodeInfo.GetPort() + 10000;

        char sAddress[128] = {0};
        snprintf(sAddress, sizeof(sAddress), "%s:%d", oNodeInfo.GetIP().c_str(), iGrpcPort);

        string sServerAddress = sAddress;

        printf("%s %s\n", __func__, sAddress);

        stub_.reset(nullptr);

        stub_ = PhxKVServer::NewStub(grpc::CreateChannel(sServerAddress,
                                                         grpc::InsecureChannelCredentials()));
    }

    void PhxKVClient ::Put(
        const std::string &sKey,
        const std::string &sValue,
        const uint64_t llVersion,
        const int iDeep)
    {
        if (iDeep > 3)
        {
            cout << "iDeep > 3, exiting!" << endl;
            exit(-1);
        }

        KVOperator oRequest;
        oRequest.set_key(sKey);
        oRequest.set_value(sValue);
        oRequest.set_version(llVersion);
        oRequest.set_operator_(KVOperatorType_WRITE);

        // Call object to store rpc data
        AsyncClientCall *call = new AsyncClientCall;

        // stub_->PrepareAsyncSayHello() creates an RPC object, returning
        // an instance to store in "call" but does not actually start the RPC
        // Because we are using the asynchronous API, we need to hold on to
        // the "call" instance in order to get updates on the ongoing RPC.
        call->response_reader =
            stub_->PrepareAsyncPut(&call->context, oRequest, &cq_);
        // StartCall initiates the RPC call
        call->response_reader->StartCall();
        send_receive_time_keeper[send_cnt * 2] = get_time_us();
        send_cnt++;
        // Request that, upon completion of the RPC, "reply" be updated with the
        // server's response; "status" with the indication of whether the operation
        // was successful. Tag the request with the memory address of the call object.
        call->response_reader->Finish(&call->response, &call->status, (void *)call);
    }

    int PhxKVClient ::GetLocal(
        const std::string &sKey,
        std::string &sValue,
        uint64_t &llVersion)
    {
        KVOperator oRequest;
        oRequest.set_key(sKey);
        oRequest.set_operator_(KVOperatorType_READ);

        KVResponse oResponse;
        ClientContext context;
        Status status = stub_->GetLocal(&context, oRequest, &oResponse);

        if (status.ok())
        {
            sValue = oResponse.data().value();
            llVersion = oResponse.data().version();
            return oResponse.ret();
        }
        else
        {
            return static_cast<int>(PhxKVStatus::FAIL);
        }
    }

    int PhxKVClient ::GetLocal(
        const std::string &sKey,
        const uint64_t minVersion,
        std::string &sValue,
        uint64_t &llVersion)
    {
        int ret = GetLocal(sKey, sValue, llVersion);
        if (ret == 0)
        {
            if (llVersion < minVersion)
            {
                return static_cast<int>(PhxKVStatus::VERSION_NOTEXIST);
            }
        }

        return ret;
    }

    int PhxKVClient ::Delete(
        const std::string &sKey,
        const uint64_t llVersion,
        const int iDeep)
    {
        KVOperator oRequest;
        oRequest.set_key(sKey);
        oRequest.set_version(llVersion);
        oRequest.set_operator_(KVOperatorType_DELETE);

        KVResponse oResponse;
        ClientContext context;
        Status status = stub_->Delete(&context, oRequest, &oResponse);

        if (status.ok())
        {
            if (oResponse.ret() == static_cast<int>(PhxKVStatus::MASTER_REDIRECT))
            {
                if (oResponse.master_nodeid() != phxpaxos::nullnode)
                {
                    NewChannel(oResponse.master_nodeid());
                    return Delete(sKey, llVersion, iDeep + 1);
                }
                else
                {
                    return static_cast<int>(PhxKVStatus::NO_MASTER);
                }
            }

            return oResponse.ret();
        }
        else
        {
            return static_cast<int>(PhxKVStatus::FAIL);
        }
    }

    int PhxKVClient ::GetGlobal(
        const std::string &sKey,
        std::string &sValue,
        uint64_t &llVersion,
        const int iDeep)
    {
        if (iDeep > 3)
        {
            return static_cast<int>(PhxKVStatus::FAIL);
        }

        KVOperator oRequest;
        oRequest.set_key(sKey);
        oRequest.set_operator_(KVOperatorType_READ);

        KVResponse oResponse;
        ClientContext context;
        Status status = stub_->GetGlobal(&context, oRequest, &oResponse);

        if (status.ok())
        {
            if (oResponse.ret() == static_cast<int>(PhxKVStatus::MASTER_REDIRECT))
            {
                if (oResponse.master_nodeid() != phxpaxos::nullnode)
                {
                    NewChannel(oResponse.master_nodeid());
                    return GetGlobal(sKey, sValue, llVersion, iDeep + 1);
                }
                else
                {
                    return static_cast<int>(PhxKVStatus::NO_MASTER);
                }
            }

            sValue = oResponse.data().value();
            llVersion = oResponse.data().version();

            return oResponse.ret();
        }
        else
        {
            return static_cast<int>(PhxKVStatus::FAIL);
        }
    }

} // namespace phxkv
