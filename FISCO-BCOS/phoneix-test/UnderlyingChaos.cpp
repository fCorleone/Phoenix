// Library for underlying chaos strategies of Phoenix
// Developed by Fcorleone at 2022-11-14

#include "UnderlyingChaos.h"
#include <json/json.h>
#include <boost/throw_exception.hpp>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>
#include <sys/fcntl.h>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);

// Network related stategies
void network_delay(int duration, int offset, string net_interface, int port, string node_id, HookPosition hookPosition){
    // std::cout << "We are now in the network_delay, ";
    int chaos_probability = getProbability(); // get the chaos probability controled by the coordinator
    // std::cout << "the chaos probability is :" << chaos_probability << std::endl;
    if(dis(gen) < (float)(chaos_probability * 1.0 / 100.0)){
        char network_cmd[100];
        sprintf(network_cmd, "blade create network delay --time %d --offset %d --interface %s --local-port %d",duration, offset, net_interface.c_str(), port);
        // std::cout << "The exec cmd is " << network_cmd << std::endl;
        std::string chaos_result = executeCMD(network_cmd);
        Json::Value json_result;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(chaos_result, json_result);
        // std::cout << "The exec res is " << chaos_result << std::endl;
        // std::cout << "The exec json res is " << json_result << std::endl;
        // The result is like: {"code":200,"success":true,"result":"35719a3de188df83"}
        if(json_result["code"].asInt() == 200 && json_result["success"].asString() == "true"){
            // This indicates that the json is parsed successfully and the chaos is starting successfully
            string chaos_id = json_result["result"].asString();
            // write strategies to files
            writeStrategy("/tmp/phoenix/PHOENIX_HOOK_" + node_id + ".txt", std::time(0), node_id, hookPosition, chaos_id, network_cmd);
            // writeIdToPool("/tmp/PHOENIX_STRATEGY_POOL.txt", chaos_id + "\n");
            // return chaos_id;
        }
        else{
            // panic here because the chaos-blade has some errors.
            BOOST_THROW_EXCEPTION(std::runtime_error{"Network delay chaos starting error!"});
        }
    }
}

// Stop network delay strategies
bool stop_chaos_blade_strategy(string chaos_id){
    char network_stop_cmd[100];
    sprintf(network_stop_cmd, "blade destroy %s --force-remove",chaos_id.c_str());
    std::string chaos_result = executeCMD(network_stop_cmd);
    Json::Value json_result;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(chaos_result, json_result);
    // The result is like: {"code":200,"success":true,"result":{"target":"network","action":"delay","flags":{"interface":"eth0","local-port":"30300","offset":"0","time":"200"},"ActionProcessHang":false}}
    if(json_result["code"].asInt() == 200 && json_result["success"].asString() == "true"){
        // This indicates that the json is parsed successfully and the chaos is starting successfully
        return true;
    }
    else{
        return false;
    }
}

void network_drop_packets(int percent, string net_interface, int port, string node_id, HookPosition hookPosition){
    // std::cout << "We are now in the network_drop_packets, ";
    int chaos_probability = getProbability(); // get the chaos probability controled by the coordinator
    // std::cout << "the chaos probability is :" << chaos_probability << std::endl;
    if(dis(gen) < (float)(chaos_probability * 1.0 / 100.0)){
        char network_cmd[100];
        sprintf(network_cmd, "blade create network loss --percent %d --interface %s --local-port %d",percent, net_interface.c_str(), port);
        // std::cout << "The exec cmd is " << network_cmd << std::endl;
        std::string chaos_result = executeCMD(network_cmd);
        Json::Value json_result;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(chaos_result, json_result);
        // std::cout << "The exec res is " << chaos_result << std::endl;
        // std::cout << "The exec json res is " << json_result << std::endl;
        // The result is like: {"code":200,"success":true,"result":"35719a3de188df83"}
        if(json_result["code"].asInt() == 200 && json_result["success"].asString() == "true"){
            // This indicates that the json is parsed successfully and the chaos is starting successfully
            string chaos_id = json_result["result"].asString();
            // write strategies to files
            writeStrategy("/tmp/phoenix/PHOENIX_HOOK_" + node_id + ".txt", std::time(0), node_id, hookPosition, chaos_id, network_cmd);
            // writeIdToPool("/tmp/PHOENIX_STRATEGY_POOL.txt", chaos_id + "\n");
        }
        else{
            std::cout << "Network drop failure" << std::endl;
            // panic here because the chaos-blade has some errors.
            BOOST_THROW_EXCEPTION(std::runtime_error{"Network packets drop chaos starting error!"});
        }
    }
}

void network_reorder_packets(int correlation, int percent, string net_interface, int port, string node_id, HookPosition hookPosition){
    // std::cout << "We are now in the network_reorder_packets, ";
    int chaos_probability = getProbability(); // get the chaos probability controled by the coordinator
    // std::cout << "the chaos probability is :" << chaos_probability << std::endl;
    if(dis(gen) < (float)(chaos_probability * 1.0 / 100.0)){
        char network_cmd[100];
        sprintf(network_cmd, "blade create network reorder --correlation %d --percent %d --interface %s  --local-port %d", correlation, percent, net_interface.c_str(), port);
        // std::cout << "The exec cmd is " << network_cmd << std::endl;
        std::string chaos_result = executeCMD(network_cmd);
        Json::Value json_result;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(chaos_result, json_result);
        // std::cout << "The exec res is " << chaos_result << std::endl;
        // std::cout << "The exec json res is " << json_result << std::endl;
        // The result is like: {"code":200,"success":true,"result":"35719a3de188df83"}
        if(json_result["code"].asInt() == 200 && json_result["success"].asString() == "true"){
            // This indicates that the json is parsed successfully and the chaos is starting successfully
            string chaos_id = json_result["result"].asString();
            // write strategies to files
            writeStrategy("/tmp/phoenix/PHOENIX_HOOK_" + node_id + ".txt", std::time(0), node_id, hookPosition, chaos_id, network_cmd);
            // writeIdToPool("/tmp/PHOENIX_STRATEGY_POOL.txt", chaos_id + "\n");
        }
        else{
            // panic here because the chaos-blade has some errors.
            BOOST_THROW_EXCEPTION(std::runtime_error{"Network packets duplicate chaos starting error!"});
        }
    }
}

void network_corrupt_packets(int percent, string net_interface, int port, string node_id, HookPosition hookPosition){
    // std::cout << "We are now in the network_corrupt_packets, " ;
    int chaos_probability = getProbability(); // get the chaos probability controled by the coordinator
    // std::cout << "the chaos probability is :" << chaos_probability << std::endl;
    if(dis(gen) < (float)(chaos_probability * 1.0 / 100.0)){
        char network_cmd[100];
        sprintf(network_cmd, "blade create network corrupt --percent %d --interface %s  --local-port %d", percent, net_interface.c_str(), port);
        std::cout << "The exec cmd is " << network_cmd << std::endl;
        std::string chaos_result = executeCMD(network_cmd);
        Json::Value json_result;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(chaos_result, json_result);
        // std::cout << "The exec res is " << chaos_result << std::endl;
        // std::cout << "The exec json res is " << json_result << std::endl;
        // The result is like: {"code":200,"success":true,"result":"35719a3de188df83"}
        if(json_result["code"].asInt() == 200 && json_result["success"].asString() == "true"){
            // This indicates that the json is parsed successfully and the chaos is starting successfully
            string chaos_id = json_result["result"].asString();
            // write strategies to files
            writeStrategy("/tmp/phoenix/PHOENIX_HOOK_" + node_id + ".txt", std::time(0), node_id, hookPosition, chaos_id, network_cmd);
            // writeIdToPool("/tmp/PHOENIX_STRATEGY_POOL.txt", chaos_id + "\n");
        }
        else{
            // panic here because the chaos-blade has some errors.
            BOOST_THROW_EXCEPTION(std::runtime_error{"Network packets corrupt chaos starting error!"});
        }
    }
}

void network_duplicate_packets(int percent, string net_interface, int port, string node_id, HookPosition hookPosition){
    // std::cout << "We are now in the network_duplicate_packets, ";
    int chaos_probability = getProbability(); // get the chaos probability controled by the coordinator
    // std::cout << "the chaos probability is :" << chaos_probability << std::endl;
    if(dis(gen) < (float)(chaos_probability * 1.0 / 100.0)){
        char network_cmd[100];
        sprintf(network_cmd, "blade create network duplicate --percent %d --interface %s  --local-port %d", percent, net_interface.c_str(), port);
        // std::cout << "The exec cmd is " << network_cmd << std::endl;
        std::string chaos_result = executeCMD(network_cmd);
        Json::Value json_result;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(chaos_result, json_result);
        // std::cout << "The exec res is " << chaos_result << std::endl;
        // std::cout << "The exec json res is " << json_result << std::endl;
        // The result is like: {"code":200,"success":true,"result":"35719a3de188df83"}
        if(json_result["code"].asInt() == 200 && json_result["success"].asString() == "true"){
            // This indicates that the json is parsed successfully and the chaos is starting successfully
            string chaos_id = json_result["result"].asString();
            // write strategies to files
            writeStrategy("/tmp/phoenix/PHOENIX_HOOK_" + node_id + ".txt", std::time(0), node_id, hookPosition, chaos_id, network_cmd);
            // writeIdToPool("/tmp/PHOENIX_STRATEGY_POOL.txt", chaos_id + "\n");
        }
        else{
            // panic here because the chaos-blade has some errors.
            BOOST_THROW_EXCEPTION(std::runtime_error{"Network packets corrupt chaos starting error!"});
        }
    }
}

void clear_block_data(string node_id, HookPosition hookPosition){
    int chaos_probability = getProbability(); // get the chaos probability controled by the coordinator
    if(dis(gen) < (float)(chaos_probability * 1.0 / 100.0)){
        srand(time(NULL));
        int nonce = rand() % 3;
        std::string chaos_id;
        std::string chaos_result;
        switch(nonce){
        case 0:
            char clear_data_cmd1[100];
            sprintf(clear_data_cmd1, "sudo rm -rf /data/chaos/fisco/nodes/127.0.0.1/node7/data/*");
            chaos_result = executeCMD(clear_data_cmd1);
            chaos_id = "111111111";
            writeStrategy("/tmp/phoenix/PHOENIX_HOOK_" + node_id + ".txt", std::time(0), node_id, hookPosition, chaos_id, clear_data_cmd1);
            break;
        case 1:
            char clear_data_cmd2[100];
            sprintf(clear_data_cmd2, "sudo rm -rf /data/chaos/fisco/nodes/127.0.0.1/node8/data/*");
            chaos_result = executeCMD(clear_data_cmd2);
            chaos_id = "222222222";
            writeStrategy("/tmp/phoenix/PHOENIX_HOOK_" + node_id + ".txt", std::time(0), node_id, hookPosition, chaos_id, clear_data_cmd2);
            break;
        case 2:
            char clear_data_cmd3[100];
            sprintf(clear_data_cmd3, "sudo rm -rf /data/chaos/fisco/nodes/127.0.0.1/node9/data/*");
            chaos_result = executeCMD(clear_data_cmd3);
            chaos_id = "333333333";
            writeStrategy("/tmp/phoenix/PHOENIX_HOOK_" + node_id + ".txt", std::time(0), node_id, hookPosition, chaos_id, clear_data_cmd3);
            break;
    }
    }
}

std::string executeCMD(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL){
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

// void executeCMD(const char *cmd, char *result)   
// {   
//     char buf_ps[1024];   
//     char ps[1024]={0};   
//     FILE *ptr;   
//     strcpy(ps, cmd);   
//     if((ptr=popen(ps, "r"))!=NULL)   
//     {   
//         while(fgets(buf_ps, 1024, ptr)!=NULL)   
//         {   
//            strcat(result, buf_ps);   
//            if(strlen(result)>1024)   
//                break;   
//         }   
//         pclose(ptr);   
//         ptr = NULL;   
//     }   
//     else  
//     {   
//         printf("popen %s error", ps);   
//     }   
// }  

void writeStrategy(string info_file, long int timeStamp, string node_id, HookPosition hookPosition, string strategy_id, string exec_cmd){
    ofstream MyFile;
    MyFile.open(info_file, std::ios_base::app);
    MyFile << timeStamp << "," << node_id << "," << enumToString(hookPosition)<< "," << strategy_id << "," << exec_cmd << std::endl;
    MyFile.close();
}

// void writeIdToPool(string pool_file, string node_id){
//     // here we need to write file in parallel, so please add a lock
//     int fd = open(pool_file.c_str(), O_RDWR, 777);

//     // lock the file
//     struct flock lock = {};
//     lock.l_type = F_WRLCK;
//     lock.l_whence = SEEK_SET;
//     lock.l_start = 0;
//     lock.l_len = 0;

//     lock.l_pid = getpid();
//     if (fcntl(fd, F_SETLKW, &lock) == -1) {
//         perror("fcntl");
//     }

//     // write the file
//     int res = write(fd, node_id.c_str(), strlen(node_id.c_str()));

//     // unlock the file
//     lock.l_type = F_UNLCK;
//     if (fcntl(fd, F_SETLKW, &lock) == -1) {
//         perror("fcntl");
//     }

// }

int getProbability(){
    ifstream MyFile("/tmp/PHOENIX_CHAOS_SIGNAL.txt");
    std::string signal;
    getline(MyFile, signal);
    std::stringstream test(signal);
    std::string segment;
    std::vector<std::string> seglist;
    while(std::getline(test, segment, ':'))
    {
        seglist.push_back(segment);
    }
    std::string probablity = seglist[1]; 
    // std::cout << "Read Signal probablity:" << probablity << std::endl;
    int res = stoi(probablity);
    return res;
}

void randomNetworkChaos(int p2pPort, string node_id, HookPosition hookPosition){
    srand(time(NULL));
    int nonce = rand() % 5;
    // std::cout << "The nonce for this round is:" << nonce << std::endl;
    // std::cout << "Current hook position is:" << enumToString(hookPosition) << std::endl;
    switch(nonce){
        case 0:
            network_delay(3000,100,"eth0",p2pPort,node_id,hookPosition);
            break;
        case 1:
            network_drop_packets(80,"eth0",p2pPort,node_id,hookPosition);
            break;
        case 2:
            network_reorder_packets(80, 80, "eth0", p2pPort, node_id,hookPosition);
            break;
        case 3:
            network_corrupt_packets(80,"eth0", p2pPort, node_id,hookPosition);
            break;
        case 4:
            network_duplicate_packets(80,"eth0", p2pPort, node_id,hookPosition);
            break;
        // case 5:
        //     clear_block_data(node_id,hookPosition);
        //     break;
    }
}

// TODO:
// 1. writeIdtoPool #Done#
// 2. more instrumentation #Done#
// 3. each instrumentation randomly choose one strategy #Done#
// 4. reproduction 
// 5. coordinator的strategypool的填充 #Done#
// 6. coordinator的stop chaos的重写 #Done#
// 7. resilience checking #Done#