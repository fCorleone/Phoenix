/*
 *  Copyright (C) 2021 FISCO BCOS.
 *  SPDX-License-Identifier: Apache-2.0
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * @file RateLimiterManager.cpp
 * @author: octopus
 * @date 2022-06-30
 */

#include "bcos-gateway/Common.h"
#include "bcos-utilities/BoostLog.h"
#include <bcos-gateway/libratelimit/RateLimiterManager.h>

using namespace bcos;
using namespace bcos::gateway;
using namespace bcos::gateway::ratelimiter;

const std::string RateLimiterManager::TOTAL_OUTGOING_KEY = "total-outgoing-key";

RateLimiterInterface::Ptr RateLimiterManager::getRateLimiter(const std::string& _rateLimiterKey)
{
    std::shared_lock lock(x_rateLimiters);
    auto it = m_rateLimiters.find(_rateLimiterKey);
    if (it != m_rateLimiters.end())
    {
        return it->second;
    }

    return nullptr;
}

bool RateLimiterManager::registerRateLimiter(
    const std::string& _rateLimiterKey, RateLimiterInterface::Ptr _rateLimiter)
{
    std::unique_lock lock(x_rateLimiters);
    auto result = m_rateLimiters.try_emplace(_rateLimiterKey, _rateLimiter);

    RATELIMIT_MGR_LOG(INFO) << LOG_BADGE("registerRateLimiter")
                            << LOG_KV("rateLimiterKey", _rateLimiterKey)
                            << LOG_KV("result", result.second);
    return result.second;
}

bool RateLimiterManager::removeRateLimiter(const std::string& _rateLimiterKey)
{
    RATELIMIT_MGR_LOG(INFO) << LOG_BADGE("removeRateLimiter")
                            << LOG_KV("rateLimiterKey", _rateLimiterKey);

    std::unique_lock lock(x_rateLimiters);
    return m_rateLimiters.erase(_rateLimiterKey) > 0;
}

RateLimiterInterface::Ptr RateLimiterManager::getGroupRateLimiter(const std::string& _group)
{
    if (!m_rateLimiterConfig.enableGroupRateLimit)
    {
        return nullptr;
    }

    const std::string& rateLimiterKey = _group;

    auto rateLimiter = getRateLimiter(rateLimiterKey);
    if (rateLimiter != nullptr)
    {
        return rateLimiter;
    }

    // rete limiter not exist, create it
    int64_t groupOutgoingBwLimit = -1;

    auto it = m_rateLimiterConfig.group2BwLimit.find(_group);
    if (it != m_rateLimiterConfig.group2BwLimit.end())
    {
        groupOutgoingBwLimit = it->second;
    }
    else if (m_rateLimiterConfig.groupOutgoingBwLimit > 0)
    {
        groupOutgoingBwLimit = m_rateLimiterConfig.groupOutgoingBwLimit;
    }

    if (groupOutgoingBwLimit > 0)
    {
        RATELIMIT_MGR_LOG(INFO) << LOG_BADGE("getGroupRateLimiter")
                                << LOG_DESC("group rate limiter not exist")
                                << LOG_KV("rateLimiterKey", rateLimiterKey)
                                << LOG_KV("groupOutgoingBwLimit", groupOutgoingBwLimit)
                                << LOG_KV("enableDistributedRatelimit",
                                       m_rateLimiterConfig.enableDistributedRatelimit);

        if (m_rateLimiterConfig.enableDistributedRatelimit)
        {
            // create ratelimiter
            rateLimiter = m_rateLimiterFactory->buildRedisDistributedRateLimiter(
                m_rateLimiterFactory->toTokenKey(_group), groupOutgoingBwLimit, 1,
                m_rateLimiterConfig.enableDistributedRateLimitCache,
                m_rateLimiterConfig.distributedRateLimitCachePercent);
        }
        else
        {
            // create ratelimiter
            rateLimiter = m_rateLimiterFactory->buildTokenBucketRateLimiter(groupOutgoingBwLimit);
        }

        registerRateLimiter(_group, rateLimiter);
    }

    return rateLimiter;
}

RateLimiterInterface::Ptr RateLimiterManager::getConnRateLimiter(const std::string& _connIP)
{
    if (!m_rateLimiterConfig.enableConRateLimit)
    {
        return nullptr;
    }

    const std::string& rateLimiterKey = _connIP;

    auto rateLimiter = getRateLimiter(rateLimiterKey);
    if (rateLimiter != nullptr)
    {
        return rateLimiter;
    }

    int64_t connOutgoingBwLimit = -1;

    auto it = m_rateLimiterConfig.ip2BwLimit.find(_connIP);
    if (it != m_rateLimiterConfig.ip2BwLimit.end())
    {
        connOutgoingBwLimit = it->second;
    }
    else if (m_rateLimiterConfig.connOutgoingBwLimit > 0)
    {
        connOutgoingBwLimit = m_rateLimiterConfig.connOutgoingBwLimit;
    }

    if (connOutgoingBwLimit > 0)
    {
        RATELIMIT_MGR_LOG(INFO) << LOG_BADGE("getConnRateLimiter")
                                << LOG_DESC("conn rate limiter not exist")
                                << LOG_KV("rateLimiterKey", rateLimiterKey)
                                << LOG_KV("connOutgoingBwLimit", connOutgoingBwLimit);

        // create ratelimiter
        rateLimiter = m_rateLimiterFactory->buildTokenBucketRateLimiter(connOutgoingBwLimit);

        registerRateLimiter(rateLimiterKey, rateLimiter);
    }

    return rateLimiter;
}