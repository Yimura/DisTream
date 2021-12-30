#pragma once
#include "base_event.hpp"

namespace distream
{
    class AuthenticateEvent : public BaseEvent
    {
    private:
        std::string m_application_id = "";
        int m_shard_id;

    public:
        AuthenticateEvent(std::shared_ptr<Connection> owner, json& data)
            : BaseEvent(owner, data)
        {
            auto data_obj = data["d"];

            m_application_id = data_obj["application_id"];
            m_shard_id = data_obj["shard_id"];
        }
        ~AuthenticateEvent() = default;

        void execute()
        {
            m_owner->authenticate(m_application_id, m_shard_id);
        }
    };
    
}