#include "common.hpp"
#include "connection.hpp"
#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

namespace distream
{
    typedef websocketpp::server<websocketpp::config::asio> server;

    using websocketpp::connection_hdl;
    using websocketpp::lib::placeholders::_1;
    using websocketpp::lib::placeholders::_2;
    using websocketpp::lib::bind;

    class ConnectionManager : public server
    {
    private:
        uint16_t m_port;

        std::map<connection_hdl, std::unique_ptr<Connection>, std::owner_less<>> m_conn_list;
    public:
        ConnectionManager(uint16_t port = 8888);
        ~ConnectionManager();

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