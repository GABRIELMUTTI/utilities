#pragma once

#include "../../eventqueue/event/EventArgs.hpp"

namespace utl
{
    class IEventQueue
    {
        public:
            virtual void flush() = 0;
            virtual void send(EventArgs* event) = 0;
    };
}
