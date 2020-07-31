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
			ss << GetName() << " " << m_X << ", " << m_Y;
			return ss.str();
		}
	private:
		float m_X, m_Y;
	};
}