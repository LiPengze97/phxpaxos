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

#include <iostream>
#include <memory>
#include <fstream>
#include <string>

#include <grpc++/grpc++.h>

#include "phxkv.grpc.pb.h"

#include "def.h"

using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
namespace phxkv
{

    class PhxKVClient
    {
    public:
        int cnt = 0;
        int send_cnt = 0;
        uint64_t *send_receive_time_keeper = static_cast<uint64_t *>(malloc(sizeof(uint64_t) * 520000 * 2));
        explicit PhxKVClient(std::shared_ptr<grpc::Channel> channel, int msg_num);
        int msg_num = -1;
        void NewChannel(const uint64_t llNodeID);

        void Put(
            const std::string &sKey,
            const std::string &sValue,
            const uint64_t llVersion,
            const int iDeep = 0);

        int GetLocal(
            const std::string &sKey,
            std::string &sValue,
            uint64_t &llVersion);

        int GetLocal(
            const std::string &sKey,
            const uint64_t minVersion,
            std::string &sValue,
            uint64_t &llVersion);

        int Delete(
            const std::string &sKey,
            const uint64_t llVersion,
            const int iDeep = 0);

        int GetGlobal(
            const std::string &sKey,
            std::string &sValue,
            uint64_t &llVersion,
            const int iDeep = 0);

        void AsyncCompleteRpc();
        // timing unit.
        inline uint64_t get_time_us()
        {
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
        }
        struct AsyncClientCall
        {
            // Container for the data we expect from the server.
            KVResponse response;

            // Context for the client. It could be used to convey extra information to
            // the server and/or tweak certain RPC behaviors.
            ClientContext context;

            // Storage for the status of the RPC upon completion.
            Status status;

            std::unique_ptr<ClientAsyncResponseReader<KVResponse>> response_reader;
        };

    private:
        CompletionQueue cq_;

        std::unique_ptr<PhxKVServer::Stub> stub_;
    };
} // namespace phxkv
