#pragma once
#include "common.hpp"

namespace distream
{
    class Connection;
    class BaseEvent
    {
    private:

    public:
        eEventOp m_op;
        std::shared_ptr<Connection> m_owner;

        BaseEvent(std::shared_ptr<Connection> owner, json& data)
        {
            m_owner = owner;

            m_op = data.contains("op") ? data["op"].get<eEventOp>() : eEventOp::NONE;
        }
        BaseEvent(eEventOp op)
            : m_op(op)
        {
        }

        ~BaseEvent() = default;

        json to_json()
        {
            return json{
                { "op", m_op },
                { "d", json::object() }
            };
        }
    };
}