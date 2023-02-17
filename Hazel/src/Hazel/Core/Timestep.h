//
// Created by 吴棋凡 on 2023/2/16.
//

#pragma once

namespace Hazel {

class Timestep
{
public:
  explicit Timestep(float time = 0.0f)
      : time_(time)
  {
  }

  explicit operator float() const { return time_; }

  float GetSeconds() const { return time_; }
  float GetMilliseconds() const { return time_ * 1000.0f; }
private:
  float time_;
};

}