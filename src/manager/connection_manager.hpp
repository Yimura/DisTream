#pragma once
#include "common.hpp"

namespace distream
{
    class Connection; // Forward Declare Connection
    class EventHandler; // Forward Declare EventHandler
    class ConnectionManager : public server
    {
    private:
        uint16_t m_port;

        std::map<connection_hdl, std::shared_ptr<Connection>, std::owner_less<>> m_conn_list;
        std::unique_ptr<EventHandler> m_event_handler;
    public:
        ConnectionManager(uint16_t port = 8888);
        ~ConnectionManager();

        std::shared_ptr<Connection> get_client(connection_hdl hdl);

        // events
        void on_open(connection_hdl hdl);
        void on_close(connection_hdl hdl);
        void on_message(connection_hdl hdl, server::message_ptr msg);

        // methods
        void start();
        void destroy();
    };
    

    inline ConnectionManager* g_conn_mgr{};
}