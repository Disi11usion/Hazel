//
// Created by 吴棋凡 on 2023/2/15.
//
#pragma once

#include "Hazel/Events/Event.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel {

class KeyEvent : public Event {
public:
  KeyCode GetKeyCode() const { return key_code_; }

  EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT)
protected:
  explicit KeyEvent(const KeyCode keycode) : key_code_(keycode) {}

  KeyCode key_code_;
};

class KeyPressedEvent : public KeyEvent {
public:
  explicit KeyPressedEvent(const KeyCode keycode, bool is_repeat = false) : KeyEvent(keycode), is_repeat_(is_repeat) {}

  bool IsRepeat() const { return is_repeat_; }

  std::string ToString() const override {
    std::stringstream stringstream;
    stringstream << "KeyPressedEvent: " << key_code_ << " (repeat = " << is_repeat_ << ")";
    return stringstream.str();
  }

  EVENT_CLASS_TYPE(KEY_PRESSED)
private:
  bool is_repeat_;
};

class KeyReleasedEvent : public KeyEvent {
public:
  explicit KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream stringstream;
    stringstream << "KeyReleasedEvent: " << key_code_;
    return stringstream.str();
  }

  EVENT_CLASS_TYPE(KEY_RELEASED)
};

class KeyTypedEvent : public KeyEvent {
public:
  explicit KeyTypedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

  std::string ToString() const override {
    std::stringstream stringstream;
    stringstream << "KeyTypedEvent: " << key_code_;
    return stringstream.str();
  }

  EVENT_CLASS_TYPE(KEY_TYPED)
};
} // namespace Hazel