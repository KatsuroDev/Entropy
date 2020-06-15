#pragma once

namespace Entropy {

    // All event types supported by the application
    enum class EventType
    {
    	None = 0,
    	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    	AppTick, AppUpdate, AppRender,
    	KeyPressed, KeyReleased, KeyTyped,
    	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    #define BIT(x) (1 << x)

    enum EventCategory
    {
    	None = 0,
    	EventCategoryApplication    = BIT(0),
    	EventCategoryInput          = BIT(1),
    	EventCategoryKeyboard       = BIT(2),
    	EventCategoryMouse          = BIT(3),
    	EventCategoryMouseButton    = BIT(4)
    };

    // An event by itself is abstract
    class Event
    {
    public:
        bool Handled = false;

        // Virtual methods
        virtual EventType GetType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category)
    	{
    		return GetCategoryFlags() & category;
    	}
    };

    // Dispatches (throws) events
    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {
        }

        template<typename T, typename Func>
        bool Dispatch(const Func& func)
        {
            if (m_Event.GetType() == T::GetStaticType())
            {
                m_Event.Handled = func((T&)m_Event);
                return true;
            }

            return false;
        }

    private:
        Event& m_Event;
    };
}
