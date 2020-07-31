#pragma once

#include "pch.h"
#include "Hazel/Core.h"

namespace Hazel
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MousePressed, MouseReleased, MouseMoved, MouseScrolled
	};

	enum class EventCategory
	{
		None = 0,
		Application = 1 << 0,
		Input = 1 << 1,
		Keyboard = 1 << 2,
		Mouse = 1 << 3,
		MouseButton = 1 << 4
	};

	int operator|(EventCategory a, EventCategory b) { return static_cast<int>(a) | static_cast<int>(b); }
	int operator&(EventCategory a, EventCategory b) { return static_cast<int>(a) & static_cast<int>(b); }
	int operator|(int a, EventCategory b) { return a | static_cast<int>(b); }
	int operator|(EventCategory a, int b) { return static_cast<int>(a) | b; }
	int operator&(int a, EventCategory b) { return a & static_cast<int>(b); }
	int operator&(EventCategory a, int b) { return static_cast<int>(a) & b; }

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								   virtual EventType GetEventType() const override { return GetStaticType(); }\
								   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategory() const override { return static_cast<int>(category); }

	class HAZEL_API Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategory() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsCategory(EventCategory category) { return GetCategory() & category; }

	protected:
		bool m_Handled;
	};
}