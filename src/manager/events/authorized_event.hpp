#pragma once
#include "base_event.hpp"

namespace distream
{
    class AuthorizedEvent : public BaseEvent
    {
    private:
        /* data */
    public:
        AuthorizedEvent(/* args */)
            : BaseEvent(eEventOp::AUTHORIZED)
        {

        }
        ~AuthorizedEvent() = default;

        json to_json()
        {
            return BaseEvent::to_json();
        }
    };
    
}