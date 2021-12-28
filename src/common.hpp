#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <stack>
#include <thread>
#include <vector>

#include <csignal>

#include <iostream>

#include <map>

#include "util/logger.hpp"
#include "util/thread_pool.hpp"

namespace distream
{
    using namespace std::literals::chrono_literals;

    inline std::atomic<bool> g_running { true };
}