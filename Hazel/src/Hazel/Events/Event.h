//
// Created by 吴棋凡 on 2023/2/15.
//

#pragma once

#include "Hazel/Core/Core.h"
#include <sstream>
namespace Hazel {

// Events in Hazel are currently blocking, meaning when an event occurs it
// immediately gets dispatched and must be dealt with right then and there.
// For the future, a better strategy might be to buffer events in an event
// bus and process them during the "event" part of the update stage.

enum class EventType {
  NONE = 0,
  WINDOW_CLOSE,
  WINDOW_RESIZE,
  WINDOW_FOCUS,
  WINDOW_LOST_FOCUS,
  WINDOW_MOVED,  // window
  APP_TICK,
  APP_UPDATE,
  APP_RENDER,  // app
  KEY_PRESSED,
  KEY_RELEASED,
  KEY_TYPED,  // key
  MOUSE_BUTTON_PRESSED,
  MOUSE_BUTTON_RELEASED,
  MOUSE_MOVED,
  MOUSE_SCROLLED  // mouse
};

enum EventCategory {
  NONE = 0,
  EVENT_CATEGORY_APPLICATION = BIT(0),
  EVENT_CATEGORY_INPUT = BIT(1),
  EVENT_CATEGORY_KEYBOARD = BIT(2),
  EVENT_CATEGORY_MOUSE = BIT(3),
  EVENT_CATEGORY_MOUSE_BUTTON = BIT(4)
};

#define EVENT_CLASS_TYPE(type)                                                \
  static EventType GetStaticType() { return EventType::type; }                \
  virtual EventType GetEventType() const override { return GetStaticType(); } \
  virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
  virtual int GetCategoryFlags() const override { return category; }

class Event {
 public:
  virtual ~Event() = default;
  Event()=default;
  bool handled_ = false;

  virtual EventType GetEventType() const = 0;
  virtual const char* GetName() const = 0;
  virtual int GetCategoryFlags() const = 0;
  virtual std::string ToString() const { return GetName(); }
  bool IsInCategory(EventCategory category) const { return (GetCategoryFlags() & category) != 0; }
};

class EventDispatcher {
 public:
  explicit EventDispatcher(Event& event) : event_(event) {}

  // F will be deduced by the compiler
  template <typename T, typename F>
  bool Dispatch(const F& func) {
    if (event_.GetEventType() == T::GetStaticType()) {
      event_.handled_ |= func(static_cast<T&>(event_));
      return true;
    }
    return false;
  }

 private:
  Event& event_;
};

inline std::ostream& operator<<(std::ostream& ostream, const Event& event) { return ostream << event.ToString(); }

}  // namespace Hazel
