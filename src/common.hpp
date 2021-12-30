#pragma once

// Thread Pool
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <stack>
#include <thread>
#include <vector>
// Thread Pool nd

#include <csignal>

#include <fstream>

#include <map>

#include "nlohmann/json.hpp"

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

#include "core/enums.hpp"
#include "core/settings.hpp"

#include "util/logger.hpp"
#include "util/thread_pool.hpp"

namespace distream
{
    using namespace std::literals::chrono_literals;

    typedef websocketpp::server<websocketpp::config::asio> server;
    using websocketpp::connection_hdl;
    using websocketpp::lib::placeholders::_1;
    using websocketpp::lib::placeholders::_2;
    using websocketpp::lib::bind;

    using nlohmann::json;

    inline std::atomic<bool> g_running { true };
}