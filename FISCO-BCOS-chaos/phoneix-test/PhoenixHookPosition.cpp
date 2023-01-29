
#include "PhoenixHookPosition.h"

// enum HookPosition{
//     BEFORE_PREPREPARE,
//     BEFORE_PREPARE,
//     BEFORE_VIEWCHANGE,
//     BEFORE_RECOVER_RESPONSE,
//     BEFORE_CHECK_POINT,
//     BEFORE_BLOCK_REQUEST,
//     BEFORE_PEER_STATUS,
//     BEFORE_SYNC_STATUS,
//     BEFORE_TX_REQUEST
// };

std::string enumToString(HookPosition ele){
    switch(ele){
        case HookPosition::BEFORE_PREPREPARE:
            return "BEFORE_PREPREPARE";
        case HookPosition::BEFORE_PREPARE:
            return "BEFORE_PREPARE";
        case HookPosition::BEFORE_VIEWCHANGE:
            return "BEFORE_VIEWCHANGE";
        case HookPosition::BEFORE_RECOVER_RESPONSE:
            return "BEFORE_RECOVER_RESPONSE";
        case HookPosition::BEFORE_CHECK_POINT:
            return "BEFORE_CHECK_POINT";
        case HookPosition::BEFORE_BLOCK_REQUEST:
            return "BEFORE_BLOCK_REQUEST";
        case HookPosition::BEFORE_PEER_STATUS:
            return "BEFORE_PEER_STATUS";
        case HookPosition::BEFORE_SYNC_STATUS:
            return "BEFORE_SYNC_STATUS";
        case HookPosition::BEFORE_TX_REQUEST:
            return "BEFORE_TX_REQUEST";
        case HookPosition::BEFORE_BLOCK_SYNC:
            return "BEFORE_BLOCK_SYNC";
        default:
            return "BEFORE_PREPREPARE";
    }
}

HookPosition toEnum(std::string ele){
    if (ele == "BEFORE_PREPREPARE"){
        return HookPosition::BEFORE_PREPREPARE;
    }
    else if (ele == "BEFORE_PREPARE"){
        return HookPosition::BEFORE_PREPARE;
    }
    else if (ele == "BEFORE_VIEWCHANGE"){
        return HookPosition::BEFORE_VIEWCHANGE;
    }
    else if (ele == "BEFORE_RECOVER_RESPONSE"){
        return HookPosition::BEFORE_RECOVER_RESPONSE;
    }
    else if (ele == "BEFORE_CHECK_POINT"){
        return HookPosition::BEFORE_CHECK_POINT;
    }
    else if (ele == "BEFORE_BLOCK_REQUEST"){
        return HookPosition::BEFORE_BLOCK_REQUEST;
    }
    else if (ele == "BEFORE_PEER_STATUS"){
        return HookPosition::BEFORE_PEER_STATUS;
    }
    else if (ele == "BEFORE_SYNC_STATUS"){
        return HookPosition::BEFORE_SYNC_STATUS;
    }
    else if (ele == "BEFORE_TX_REQUEST"){
        return HookPosition::BEFORE_TX_REQUEST;
    }
    else if (ele == "BEFORE_BLOCK_SYNC"){
        return HookPosition::BEFORE_BLOCK_SYNC;
    }
    else{
        return HookPosition::BEFORE_PREPREPARE;
    }
}