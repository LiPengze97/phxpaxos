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
#include <iostream>
#include <fstream>
#include <sstream>
#include <strings.h>
#include <tuple>
#include <unistd.h>
#include <thread>
#include <vector>
#include <map>

using namespace std;
using namespace phxkv;
std::map<uint64_t, uint64_t> sf_arrive_time_map;

inline uint64_t get_time_us()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}

// void Put(uint64_t message_index, PhxKVClient &oPhxKVClient, const string &sKey, const string &sValue, const uint64_t llVersion)
// {
//     int ret = oPhxKVClient.Put(sKey, sValue, llVersion);
//     if (ret == 0)
//     {
//         // printf("Put ok, key %s value %s version %lu\n",
//         //    sKey.c_str(), sValue.c_str(), llVersion);
//         if ((message_index + 1) % 10000 == 0)
//         {
//             sf_arrive_time_map[message_index] = get_time_us();

//         }
//         printf("Put ok%lu\n", message_index+1);

//     }
//     else if (ret == -11)
//     {
//         printf("Put version conflict, key %s value %s version %lu\n",
//                sKey.c_str(), sValue.c_str(), llVersion);
//         exit(-11);
//     }
//     else
//     {
//         printf("Put fail, ret %d, key %s value %s version %lu\n",
//                ret, sKey.c_str(), sValue.c_str(), llVersion);
//         exit(-22);
//     }
// }

void GetGlobal(PhxKVClient &oPhxKVClient, const string &sKey)
{
    string sReadValue;
    uint64_t iReadVersion = 0;
    int ret = oPhxKVClient.GetGlobal(sKey, sReadValue, iReadVersion);
    if (ret == 0)
    {
        printf("GetGlobal ok, key %s value %s version %lu\n",
               sKey.c_str(), sReadValue.c_str(), iReadVersion);
    }
    else if (ret == 1)
    {
        printf("GetGlobal key %s not exist, version %lu\n", sKey.c_str(), iReadVersion);
    }
    else if (ret == 101)
    {
        printf("GetGlobal no master\n");
    }
    else
    {
        printf("GetGlobal fail, ret %d key %s\n", ret, sKey.c_str());
    }
}

void GetLocal(PhxKVClient &oPhxKVClient, const string &sKey)
{
    string sReadValue;
    uint64_t iReadVersion = 0;
    int ret = oPhxKVClient.GetLocal(sKey, sReadValue, iReadVersion);
    if (ret == 0)
    {
        printf("GetLocal ok, key %s value %s version %lu\n",
               sKey.c_str(), sReadValue.c_str(), iReadVersion);
    }
    else if (ret == 1)
    {
        printf("GetLocal key %s not exist, version %lu\n", sKey.c_str(), iReadVersion);
    }
    else
    {
        printf("GetLocal fail, ret %d key %s\n", ret, sKey.c_str());
    }
}

void Delete(PhxKVClient &oPhxKVClient, const string &sKey, const uint64_t llVersion)
{
    int ret = oPhxKVClient.Delete(sKey, llVersion);
    if (ret == 0)
    {
        printf("Delete ok, key %s version %lu\n",
               sKey.c_str(), llVersion);
    }
    else if (ret == -11)
    {
        printf("Delete version conflict, key %s version %lu\n",
               sKey.c_str(), llVersion);
    }
    else
    {
        printf("Delete fail, ret %d key %s\n", ret, sKey.c_str());
    }
}

void usage(char **argv)
{
    printf("%s <server address ip:port> <put> <key> <value> <version>\n", argv[0]);
    printf("%s <server address ip:port> <getlocal> <key>\n", argv[0]);
    printf("%s <server address ip:port> <getglobal> <key>\n", argv[0]);
    printf("%s <server address ip:port> <delete> <key> <version>\n", argv[0]);
}

inline uint64_t randomize_key(uint64_t &in)
{
    static uint64_t random_seed = get_time_us();
    uint64_t x = (in ^ random_seed);
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
}

int main(int argc, char **argv)
{
    // if (argc < 4)
    // {
    //     usage(argv);
    //     return -2;
    // }

    // string sServerAddress = argv[1];

    // PhxKVClient oPhxKVClient(grpc::CreateChannel(
    //             sServerAddress, grpc::InsecureChannelCredentials()));

    // string sFunc = argv[2];
    // string sKey = argv[3];

    // if (sFunc == "put")
    // {
    //     if (argc < 6)
    //     {
    //         usage(argv);
    //         return -2;
    //     }

    //     string sValue = argv[4];
    //     uint64_t llVersion = strtoull(argv[5], NULL, 10);
    //     Put(oPhxKVClient, sKey, sValue, llVersion);
    // }
    // else if (sFunc == "getlocal")
    // {
    //     GetLocal(oPhxKVClient, sKey);
    // }
    // else if (sFunc == "getglobal")
    // {
    //     GetGlobal(oPhxKVClient, sKey);
    // }
    // else if (sFunc == "delete")
    // {
    //     if (argc < 5)
    //     {
    //         usage(argv);
    //         return -2;
    //     }

    //     uint64_t llVersion = strtoull(argv[4], NULL, 10);
    //     Delete(oPhxKVClient, sKey, llVersion);
    // }
    // else
    // {
    //     usage(argv);
    // }
    std::ifstream inFile("/root/lpz/icdcs_cascade/cascade/trace_09_20_small.csv", std::ios::in);
    std::string lineStr;
    getline(inFile, lineStr);
    uint64_t message_index = 0;
    const uint64_t max_distinct_objects = 517295;
    // int num_msg = 517293;
    int num_msg = 687;
    string sServerAddress = "10.0.0.4:21111";
    PhxKVClient oPhxKVClient(grpc::CreateChannel(
                                 sServerAddress, grpc::InsecureChannelCredentials()),
                             num_msg);

    uint64_t llVersion = 0;

    int msg_size = 8192 - 128;

    uint64_t start_time = get_time_us();
    uint64_t end_time = 0;
    char *payload = static_cast<char *>(malloc(msg_size));
    for (int i = 0; i < msg_size; i++)
    {
        payload[i] = '0' + (i % 10);
    }
    string sValue = payload;

    sleep(3.1);
    std::thread a = std::thread(&PhxKVClient::AsyncCompleteRpc, &oPhxKVClient);
    printf("lets go\n");
    /** fix number **/
    // for (int i = 0; i < num_msg; i++)
    // {
    //     oPhxKVClient.Put(std::to_string(i), sValue, llVersion);
    // }
    // printf("done\n");
    // a.join();
    // end_time = get_time_us() - start_time;
    // printf("%lld\n", end_time);
    // printf("joined\n");

    /** trace **/
    
    while (getline(inFile, lineStr))
    {
        std::vector<std::string> fields;
        std::stringstream ss(lineStr);
        std::string str;
        while (getline(ss, str, ','))
        {
            fields.push_back(str);
        }
        int timestamp = atoi(fields[1].c_str());
        // cout << "time: " << timestamp << endl;
        // sleep(timestamp);
        int file_size = atoi(fields[0].c_str());

        if (file_size < msg_size)
        {
            char *tmp_payload = static_cast<char *>(malloc(file_size));
            for (int i = 0; i < file_size; i++)
            {
                tmp_payload[i] = '0' + (i % 10);
            }
            // Put(message_index, oPhxKVClient, std::to_string(randomize_key(message_index) % max_distinct_objects), sValue, llVersion);
            // Put(message_index, oPhxKVClient, std::to_string(message_index), tmp_payload, llVersion);
            oPhxKVClient.Put(std::to_string(message_index), tmp_payload, llVersion);
            message_index++;
            // if ((message_index - 1) == 510000)
            // {
            //     end_time = get_time_us();
            // }
            // if ((message_index + 1) % 10000 == 0)
            // {
            //     printf("msg %lu sent", message_index + 1);
            // }
        }
        else
        {
            while (file_size > msg_size)
            {
                // Put(message_index, oPhxKVClient, std::to_string(randomize_key(message_index) % max_distinct_objects), sValue, llVersion);
                // Put(message_index, oPhxKVClient, std::to_string(message_index), sValue, llVersion);
                oPhxKVClient.Put(std::to_string(message_index), sValue, llVersion);
                file_size -= msg_size;
                message_index++;
                // if ((message_index - 1) == 510000)
                // {
                //     end_time = get_time_us();
                // }
                // if ((message_index + 1) % 10000 == 0)
                // {
                //     printf("msg %lu sent", message_index + 1);
                // }
            }
            if (file_size > 0)
            {
                // Put(message_index, oPhxKVClient, std::to_string(randomize_key(message_index) % max_distinct_objects), sValue, llVersion);
                char *tmp_payload = static_cast<char *>(malloc(file_size));
                for (int i = 0; i < file_size; i++)
                {
                    tmp_payload[i] = '0' + (i % 10);
                }
                // Put(message_index, oPhxKVClient, std::to_string(message_index), sValue, llVersion);
                oPhxKVClient.Put(std::to_string(message_index), tmp_payload, llVersion);
                message_index++;
                // if ((message_index - 1) == 510000)
                // {
                //     end_time = get_time_us();
                // }
                // if ((message_index + 1) % 10000 == 0)
                // {
                //     printf("msg %lu sent", message_index + 1);
                // }
            }
        }
    }
    
    printf("done\n");
    a.join();
    end_time = get_time_us() - start_time;
    printf("%lld\n", end_time);
    printf("joined\n");
    
    // printf("duration %lu\n", end_time - start_time);

    // std::ofstream file("./sf_arrive_time.csv");
    // if(file) {
    //     file << "stability frontier,arrive time\n";
    //     file << start_time << ",-1\n";
    //     for(std::map<uint64_t, uint64_t>::iterator iter = sf_arrive_time_map.begin(); iter != sf_arrive_time_map.end(); iter++) {
    //         file << iter->first << "," << iter->second << "\n";
    //     }
    // }
    return 0;
}
