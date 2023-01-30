// This is a coordinator for chaos testing control and reproduction.
// There is a strategy pool in the coordinator which will be used to manage all the chaos strategies.
// The coordinator also contains a set of orcales which are in charge of checking whether there are bugs in the system.
// Besides, during the reproduction process, the coordinator will send signals to each node.

// Developed by Fcorleone at 2022-12-01
#pragma once

#include <string>
#include <memory>
#include <vector>
#include "PhoenixHookPosition.h"

// #define PBFT_LOG(LEVEL) BCOS_LOG(LEVEL) << LOG_BADGE("CONSENSUS") << LOG_BADGE("PBFT")
#define PHOENIX_LOG(LEVEL) BCOS_LOG(LEVEL) << LOG_BADGE("PHOENIX") << LOG_BADGE("CHAOS")

// // Records all the strategy types
// enum StrategyType{
//     NETWORK_DELAY,
//     NETWORK_DROP,
//     NETWORK_DUPLICATE,
//     NETWORK_CORRUPT
// };

// Flags that indicates whether the strategy starts or ends
enum StrategyFlag{
    STRATEGYSTART,
    STRATEGYEND
};

// Signals that tell all the nodes how to act
enum Signal{
    RANDOMCHAOS, // this is the normal mode of phoenix, just randomly choose a chaos strategy.
    STOPCHAOS, // node under this mode will not perform any chaos testing
    DEFINITELYCHAOS, // node under this mode will perform chaos for 100% percent
};

// the struct of a phoenix strategy
class PhoenixStrategy{
public:
    using Ptr = std::shared_ptr<PhoenixStrategy>;
    PhoenixStrategy(
        std::string strategyId,
        std::string timeStamp,
        std::string node_id,
        std::string exec_cmd,
        HookPosition hookPosition);
    virtual ~PhoenixStrategy() = default;

    std::string getStrategyId();
    std::string getTimeStamp();
    // StrategyType getStrategyType();
    HookPosition getHookPosition();
    std::string getNodeId();
    std::string getExecCmd();

    void setStrategyId(std::string _strategyId);
    void setTimeStamp(std::string _timeStamp);
    void setNodeId(std::string _nodeId);
    void setExecCmd(std::string _execCmd);
    // void setStrategyType(StrategyType _strategyType);
    void setHookPosition(HookPosition _hookPosition);

protected:
    std::string strategyId;
    std::string timeStamp;
    std::string nodeId;
    std::string execCmd;
    // StrategyType strategyType;
    HookPosition hookPosition;
};

class PhoenixCoordinator{
public:
    using Ptr = std::shared_ptr<PhoenixCoordinator>;
    PhoenixCoordinator();
    PhoenixCoordinator(int t1, int t2);
    virtual ~PhoenixCoordinator() = default;
    void addToStrategyPool(std::shared_ptr<PhoenixStrategy> newStrategy);
    bool stopAllStrategies();
    void clearAllStrategies();
    std::shared_ptr<PhoenixStrategy> getStrategyById(std::string strategyId);
    std::vector<std::shared_ptr<PhoenixStrategy>> getStrategyPool();
    int getCurrentPhase();
    void setCurrentPhase(int newPhase);
    int getT1();
    void setT1(int newT1);
    int getT2();
    void setT2(int newT2);

    void fillStrategyPool(); // fill the strategy pool with the strategy files from each node

    // Write a signal to a file and all the nodes read the signal to act
    void writeSignal(std::string fileName, Signal signal);

protected:
    std::vector<std::shared_ptr<PhoenixStrategy>> strategyPool;
    int chaosPhase; // 0 indicates testing phase while 1 indicates checking phase
    int T1_testPhaseTime;
    int T2_checkPhaseTime;
};

// start the coordinator engine
void startCoordinator(std::shared_ptr<PhoenixCoordinator> phoenix);
bool performChecking();