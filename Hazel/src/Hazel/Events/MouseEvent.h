//
// Created by 吴棋凡 on 2023/2/15.
//

#pragma once

#include "Hazel/Core/MouseCodes.h"
#include "Hazel/Events/Event.h"
namespace Hazel {

class MouseMovedEvent : public Event {
public:
  MouseMovedEvent(const float x_position, const float y_position) : m_mouse_x_(x_position), m_mouse_y_(y_position) {}

  float GetX() const { return m_mouse_x_; }
  float GetY() const { return m_mouse_y_; }

  std::string ToString() const override {
    std::stringstream stringstream;
    stringstream << "MouseMovedEvent: " << m_mouse_x_ << ", " << m_mouse_y_;
    return stringstream.str();
  }

  EVENT_CLASS_TYPE(MOUSE_MOVED)
  EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)
private:
  float m_mouse_x_, m_mouse_y_;
};

class MouseScrolledEvent : public Event {
public:
  MouseScrolledEvent(const float x_offset, const float y_offset) : m_x_offset_(x_offset), m_y_offset_(y_offset) {}

  float GetXOffset() const { return m_x_offset_; }
  float GetYOffset() const { return m_y_offset_; }

  std::string ToString() const override {
    std::stringstream stringstream;
    stringstream << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
    return stringstream.str();
  }

  EVENT_CLASS_TYPE(MOUSE_SCROLLED)
  EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT)
private:
  float m_x_offset_, m_y_offset_;
};

class MouseButtonEvent : public Event {
public:
  MouseCode GetMouseButton() const { return m_button_; }

  EVENT_CLASS_CATEGORY(EVENT_CATEGORY_MOUSE | EVENT_CATEGORY_INPUT | EVENT_CATEGORY_MOUSE_BUTTON)
protected:
  explicit MouseButtonEvent(const MouseCode button) : m_button_(button) {}

  MouseCode m_button_;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
  explicit MouseButtonPressedEvent(const MouseCode button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream stringstream;
    stringstream << "MouseButtonPressedEvent: " << m_button_;
    return stringstream.str();
  }

  EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESSED)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
  explicit MouseButtonReleasedEvent(const MouseCode button) : MouseButtonEvent(button) {}

  std::string ToString() const override {
    std::stringstream stringstream;
    stringstream << "MouseButtonReleasedEvent: " << m_button_;
    return stringstream.str();
  }

  EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASED)
};

} // namespace Hazel