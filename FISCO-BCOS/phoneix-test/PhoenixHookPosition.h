// Store all the hook position of phoenix
// Developed by Fcorleone at 2022-12-01

#include <string>
#pragma once

// Records all the Hook positions
enum HookPosition{
    BEFORE_PREPREPARE,
    BEFORE_PREPARE,
    BEFORE_VIEWCHANGE,
    BEFORE_RECOVER_RESPONSE,
    BEFORE_CHECK_POINT,
    BEFORE_BLOCK_REQUEST,
    BEFORE_PEER_STATUS,
    BEFORE_SYNC_STATUS,
    BEFORE_TX_REQUEST,
    BEFORE_BLOCK_SYNC
};

std::string enumToString(HookPosition ele);

HookPosition toEnum(std::string ele);