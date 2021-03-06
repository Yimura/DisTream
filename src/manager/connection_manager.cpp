#include "connection.hpp"
#include "connection_manager.hpp"
#include "event_handler.hpp"

namespace distream
{
    ConnectionManager::ConnectionManager(uint16_t port)
        : m_port(port)
    {
        m_event_handler = std::make_unique<EventHandler>();

        this->clear_access_channels(websocketpp::log::alevel::all);
        this->clear_error_channels(websocketpp::log::alevel::all);

        this->init_asio();
        this->set_reuse_addr(true);

        this->set_validate_handler(bind(&ConnectionManager::on_validation, this, _1));
        this->set_open_handler(bind(&ConnectionManager::on_open, this, _1));
        this->set_close_handler(bind(&ConnectionManager::on_close, this, _1));
        this->set_message_handler(bind(&ConnectionManager::on_message, this, _1, _2));
    
        g_conn_mgr = this;
    }

    ConnectionManager::~ConnectionManager()
    {
        g_conn_mgr = nullptr;

        // destroying our event handler will stop execution of the internal thread
        m_event_handler.reset();

        this->destroy();
    }

    std::shared_ptr<Connection> ConnectionManager::get_client(connection_hdl hdl)
    {
        if (auto it = m_conn_list.find(hdl); it != m_conn_list.end())
            return std::move(it->second);
        return nullptr;
    }

    void ConnectionManager::on_open(connection_hdl hdl)
    {
        g_log->verbose("CONN_MGR", "New client connection");

        auto conn = std::make_shared<Connection>(hdl);

        this->m_conn_list.insert({ hdl, std::move(conn) });
    }

    void ConnectionManager::on_close(connection_hdl hdl)
    {
        this->m_conn_list.erase(hdl);

        g_log->verbose("CONN_MGR", "Client connection closed");
    }

    void ConnectionManager::on_message(connection_hdl hdl, server::message_ptr msg)
    {
        m_event_handler->push_event(hdl, msg);
    }

    bool ConnectionManager::on_validation(connection_hdl hdl)
    {
        return this->get_con_from_hdl(hdl)->get_request_header("Authorization") == g_settings->server.password;
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

        for (auto conn_pair : m_conn_list)
        {
            auto conn = this->get_con_from_hdl(conn_pair.first);

            conn->close(1001, "");
        }

        this->stop();
    }
}