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
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	struct EventCategory
	{
		enum
		{
			None = 0,
			Application = 1 << 0,
			Input = 1 << 1,
			Keyboard = 1 << 2,
			Mouse = 1 << 3,
			MouseButton = 1 << 4
		};
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								   virtual EventType GetEventType() const override { return GetStaticType(); }\
								   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategory() const override { return category; }

	class HAZEL_API Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategory() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsCategory(Enum category) { return GetCategory() & category; }

	protected:
		bool m_Handled;
	};
}