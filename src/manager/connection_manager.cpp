#include "connection.hpp"
#include "connection_manager.hpp"

namespace distream
{
    ConnectionManager::ConnectionManager(uint16_t port)
        : m_port(port)
    {
        this->clear_access_channels(websocketpp::log::alevel::all);
        this->clear_error_channels(websocketpp::log::alevel::all);

        this->init_asio();
        this->set_reuse_addr(true);

        this->set_open_handler(bind(&ConnectionManager::on_open, this, _1));
        this->set_close_handler(bind(&ConnectionManager::on_close, this, _1));
        this->set_message_handler(bind(&ConnectionManager::on_message, this, _1, _2));
    
        g_conn_mgr = this;
    }

    ConnectionManager::~ConnectionManager()
    {
        g_conn_mgr = nullptr;

        this->destroy();
    }

    void ConnectionManager::on_open(connection_hdl hdl)
    {
        auto conn = std::make_unique<Connection>();

        this->m_conn_list.insert({ hdl, std::move(conn) });
    }

    void ConnectionManager::on_close(connection_hdl hdl)
    {
        this->m_conn_list.erase(hdl);
    }

    void ConnectionManager::on_message(connection_hdl hdl, server::message_ptr msg)
    {

    }

    void ConnectionManager::start()
    {
        this->listen(this->m_port);
        this->start_accept();
        this->run();
    }

    void ConnectionManager::destroy()
    {
        this->stop_listening();
        this->stop();
    }
}