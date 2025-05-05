#pragma once

#include "Event.h"

#include <sstream>

namespace Hazel {
	
	class HAZEL_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		//构造函数为protected：仍为抽象类，别的类不能创建该类，只有子类可创建
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}
		int m_KeyCode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent : " << m_KeyCode << "( " << m_RepeatCount << "repeats)";
			return ss.str();
		}


		//static EventType GetStaticType() { return EventType::KeyPressed; }		// 运行时检查 事件是什么类型 且不一定为成员函数（不需要实例来查看）
		//virtual EventType GetEventType() const override { return GetStaticType(); }
		//virtual const char* GetName() const override { return "KeyPressed"; }

		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		int m_RepeatCount;
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent : " << m_KeyCode;
			return ss.str();
		}


		EVENT_CLASS_TYPE(KeyReleased)
	};
}