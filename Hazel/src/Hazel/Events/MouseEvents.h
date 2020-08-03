#pragma once

#include "pch.h"
#include "Event.h"

namespace Hazel
{
    class HAZEL_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) : m_X{ x }, m_Y{ y } {}
        inline float GetX() const { return m_X; }
        inline float GetY() const { return m_Y; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << m_X << ", " << m_Y;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
            EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
    private:
        float m_X, m_Y;
    };

    class HAZEL_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset{ xOffset }, m_YOffset{ yOffset } {}
        inline float GetX() const { return m_XOffset; }
        inline float GetY() const { return m_YOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
            EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
    private:
        float m_XOffset, m_YOffset;
    };

    class HAZEL_API MouseButtonEvent : public Event
    {
    public:
        inline float GetMouseButton() const { return m_Button; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << GetName() << ": " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
    protected:
        MouseButtonEvent(int button) : m_Button{ button } {}
        int m_Button;
    };

    class HAZEL_API MousePressedEvent : public MouseButtonEvent
    {
    public:
        MousePressedEvent(int button) : MouseButtonEvent{ button } {}

        EVENT_CLASS_TYPE(MousePressed)
    };

    class HAZEL_API MouseReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseReleasedEvent(int button) : MouseButtonEvent{ button } {}

        EVENT_CLASS_TYPE(MouseReleased)
    };
}