#include "common.hpp"
#include "manager/connection_manager.hpp"

using namespace distream;

void signal_handler(int signal)
{
    std::cout << "\r";
    g_log->info("SIGNAL", "Received termination signal, shutting down...");

    g_running = false;
}

int main()
{
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    auto logger_instance = std::make_unique<Logger>(Logger::LogLevel::Verbose);

    g_log->info("MAIN", "Starting DisTream...");

    auto settings_instance = std::make_unique<Settings>();
    g_log->verbose("MAIN", "Initialized Settings");

    auto thread_pool_instance = std::make_unique<ThreadPool>(512);
    g_log->verbose("MAIN", "Initialized ThreadPool");

    auto conn_mgr_instance = std::make_unique<ConnectionManager>();
    g_log->verbose("MAIN", "Initialized ConnectionManager");
    g_thread_pool->push([]
    {
        g_conn_mgr->start();
    });

    while (g_running)
        std::this_thread::sleep_for(100ms);

    conn_mgr_instance.reset();
    g_log->verbose("MAIN", "Connection manager uninitialized");

    thread_pool_instance->destroy();
    g_log->verbose("MAIN", "Destroyed thread pool");

    thread_pool_instance.reset();
    g_log->verbose("MAIN", "Thread pool uninitialized");

    settings_instance.reset();
    g_log->verbose("MAIN", "Settings uninitialized");

    g_log->info("MAIN", "Farewell!!!");
    logger_instance.reset();

    return 0;
}