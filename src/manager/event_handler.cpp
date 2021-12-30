#include "connection.hpp"
#include "connection_manager.hpp"
#include "event_handler.hpp"
#include "events/authenticate_event.hpp"

namespace distream
{
    EventHandler::EventHandler()
        : m_running(true)
    {
        g_thread_pool->push([this]
        {
            this->event_handler();
        });
    }

    EventHandler::~EventHandler()
    {
        m_running = false;

        m_action_cond.notify_all();
    }

    void EventHandler::event_handler()
    {
        for (; m_running; )
        {
            std::unique_lock<std::mutex> lock(m_event_lock);

            m_action_cond.wait(lock, [this]
            {
                return !m_event_messages.empty() || !m_running;
            });
            
            if (!m_running) break;
            if (m_event_messages.empty()) continue;

            auto data = std::move(m_event_messages.top());
            m_event_messages.pop();

            // release immediately as we don't need to lock anymore
            m_event_lock.unlock();

            connection_hdl hdl = data.first;
            json payload = data.second;

            try
            {
                this->internal_handler(hdl, payload);
            }
            catch(const std::exception& e)
            {
                g_log->error("EVENT_HANDLER", "Error occured while handling event: %s", e.what());
            }
        }

        g_log->warning("EVENT_HANDLER", "Handler thread has stopped.");
    }

    void EventHandler::internal_handler(connection_hdl hdl, json data)
    {
        auto owner = g_conn_mgr->get_client(hdl);
        auto base_event = BaseEvent(owner, data);

        if (!owner->is_authenticated())
        {
            if (base_event.m_op != eEventOp::AUTHENTICATE) return;

            AuthenticateEvent(
                owner,
                data
            ).execute();

            return;
        }

        switch (base_event.m_op)
        {
        case eEventOp::VOICE_CONNECT:
            

            break;
        
        default:
            break;
        }
    }

    void EventHandler::push_event(connection_hdl hdl, server::message_ptr message)
    {
        g_thread_pool->push([this, hdl, message]
        {
            {
                std::lock_guard<std::mutex> lock_guard(m_event_lock);

                json data = json::parse(message->get_payload());
                m_event_messages.push({ hdl, std::move(data) });
            }
            // lock went out of scope, thus it has unlocked and we can notify our handler

            m_action_cond.notify_one();
        });
    }
}