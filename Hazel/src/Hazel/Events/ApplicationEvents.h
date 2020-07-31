#pragma once

#include "pch.h"
#include "Event.h"

namespace Hazel
{
	class HAZEL_API WindowResizeEvent : public Event 
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width{ width }, m_Height{ height } {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << GetName() << ": " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategory::Application)
	private:
		unsigned int m_Width, m_Height;
	};

	class HAZEL_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategory::Application)
	};

	class HAZEL_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() {}

		EVENT_CLASS_TYPE(WindowFocus)
		EVENT_CLASS_CATEGORY(EventCategory::Application)
	};

	class HAZEL_API WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() {}

		EVENT_CLASS_TYPE(WindowLostFocus)
		EVENT_CLASS_CATEGORY(EventCategory::Application)
	};
}