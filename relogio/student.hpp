#pragma once
#include "../fn.hpp"

class Time {
private:
  int HH;
  int MM;
  int SS;
public:
  Time(int HH = 0, int MM = 0, int SS = 0) :
  HH(HH), MM(MM), SS(SS) {};

  int getHH() { return this->HH; }

  int getMM() { return this->MM; }

  int getSS() { return this->SS; }

  void setHour(int value) {
    if(value > 23) {
      fn::print("fail: hora invalida\n");
      return;
    }
    this->HH = value;
  }

  void setMinute(int value) {
    if(value > 59) {
      fn::print("fail: minuto invalido\n");
      return;
    }
    this->MM = value;
  }

  void setSecond(int value) {
    if(value > 59) {
      fn::print("fail: segundo invalido\n");
      return;
    }
    this->SS = value;
  }

  void nextSecond() {
    if((getSS() + 1) == 60) {
      this->SS = 0;
      if((getMM() + 1) == 60){ 
        this->MM = 0;
        if((getHH() + 1) == 24) {
          this->HH = 0;
          return;
        } else {
          this->HH += 1;
          return;
        }
      } else {
        this->MM += 1;
        return;
      }
    }
    this->SS += 1;
  }

  std::string str() const {
    return fn::format("{%02d}:{%02d}:{%02d}", this->HH, this->MM, this->SS);
  }
};

inline std::ostream& operator<<(std::ostream& os, const Time& time) {
  return os << time.str();
}

class Student {
private:
    Time time;

public:
    void init(int hour = 0, int minute = 0, int second = 0) {
        (void) hour;
        (void) minute;
        (void) second;
        this->time = Time(hour, minute, second);
    }

    void setHour(int hour) {
        (void) hour;
        this->time.setHour(hour);
    }

    void setMinute(int minute) {
        (void) minute;
        this->time.setMinute(minute);
    }
    void setSecond(int second) {
        (void) second;
        this->time.setSecond(second);
    }

    void nextSecond() {
        this->time.nextSecond();
    }
    
    void show() {
         fn::write(time);
    }
};
