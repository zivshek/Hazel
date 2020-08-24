#pragma once

#include "pch.h"
#include "Event.h"

namespace Hazel
{
    class  WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(uint width, uint height)
            : m_Width{ width }, m_Height{ height } {}

        inline uint GetWidth() const { return m_Width; }
        inline uint GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(EventCategory::Application)
    private:
        uint m_Width, m_Height;
    };

    class  WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
            EVENT_CLASS_CATEGORY(EventCategory::Application)
    };

    class  WindowFocusEvent : public Event
    {
    public:
        WindowFocusEvent() {}

        EVENT_CLASS_TYPE(WindowFocus)
            EVENT_CLASS_CATEGORY(EventCategory::Application)
    };

    class  WindowLostFocusEvent : public Event
    {
    public:
        WindowLostFocusEvent() {}

        EVENT_CLASS_TYPE(WindowLostFocus)
            EVENT_CLASS_CATEGORY(EventCategory::Application)
    };
}