//
// Created by 吴棋凡 on 2023/2/15.
//

#pragma once

#include "Hazel/Events/Event.h"

namespace Hazel {

class WindowResizeEvent : public Event {
 public:
  WindowResizeEvent(unsigned int width, unsigned int height) : width_(width), height_(height) {}

  unsigned int GetWidth() const { return width_; }
  unsigned int GetHeight() const { return height_; }

  std::string ToString() const override {
    std::stringstream stringstream;
    stringstream << "WindowResizeEvent: " << width_ << ", " << height_;
    return stringstream.str();
  }

  EVENT_CLASS_TYPE(WINDOW_RESIZE)
  EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
 private:
  unsigned int width_, height_;
};

class WindowCloseEvent : public Event {
 public:
  WindowCloseEvent() = default;

  EVENT_CLASS_TYPE(WINDOW_CLOSE)
  EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
};

class AppTickEvent : public Event {
 public:
  AppTickEvent() = default;

  EVENT_CLASS_TYPE(APP_TICK)
  EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
};

class AppUpdateEvent : public Event {
 public:
  AppUpdateEvent() = default;

  EVENT_CLASS_TYPE(APP_UPDATE)
  EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
};

class AppRenderEvent : public Event {
 public:
  AppRenderEvent() = default;

  EVENT_CLASS_TYPE(APP_RENDER)
  EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
};
}  // namespace Hazel