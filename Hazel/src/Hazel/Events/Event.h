#pragma once

#include "Hazel/Core.h"

#include <string>
#include <functional>

namespace Hazel {
	//Evtnts in Hazel are currently blocking , when an event occurs it
	//immediately gets dispached and must be dealt with right then an there.
	//For the future , a better strategy might be to buffer events in an event
	// bus anda process them during the "event" part of the update stage.


	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication		 = BIT(0),
		EventCategoryInput				 = BIT(1),
		EventCategoryKeyboard			 = BIT(2),
		EventCategoryMouse				 = BIT(3),
		EventCategoryMouseButton		 = BIT(4),
	};

//为了实现 Event 内的3个pure函数
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)	virtual int GetCategoryFlags() const override { return category; } 


	class HAZEL_API Event
	{
		friend class EventDispatcher;
	public:
		bool m_Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName();  }		//for Debug
	
	//filter事件类型
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		//bool m_Handled = false;		//事件处理标志	分层处理事件
	};


// T:可以是任何事件
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;	//返回bool 接受T&
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		//用不同的事件函数多次调用Dispatch函数
		//现在无法保证 T的类型安全（T不一定传入事件）
		template<typename T>
		bool Dispatch(EventFn<T> func)		//检查当前尝试调度的事件类型时候与此模板参数匹配
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	//方便log Event类
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}