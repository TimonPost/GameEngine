#pragma once
#include "epch.h"
#include "Event.h"

namespace Engine
{
	class ENGINE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) {}

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return"MouseMoved"; }
		virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
	private:
		float m_MouseX, m_MouseY;
	};

	class ENGINE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return"MouseScrolled"; }
		virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }
	private:
		float m_XOffset, m_YOffset;
	};

	class ENGINE_API MouseButtonEvent : public Event
	{
	public:
		int GetMouseButton() const { return m_Button; }
		virtual int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton; }
	
	protected:
		MouseButtonEvent(const int button)
			: m_Button(button) {}

		int m_Button;
	};

	class ENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return"MouseButtonPressed"; }
	};

	class ENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return"MouseButtonReleased"; }
	};
}
