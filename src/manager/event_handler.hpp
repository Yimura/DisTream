#pragma once
#include "common.hpp"

namespace distream
{
    class Connection;
    class EventHandler
    {
    private:
        bool m_running;

        std::condition_variable m_action_cond;
        std::mutex m_event_lock;

        std::stack<std::pair<connection_hdl, json>> m_event_messages;

    public:
        EventHandler();
        ~EventHandler();

        void event_handler();
        void push_event(connection_hdl hdl, server::message_ptr message);

    private:
        void internal_handler(connection_hdl hdl, json data);

    };
    
}