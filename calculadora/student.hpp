#pragma once
#include "../fn.hpp"

class Calculator {
private:
  int battery;
  int batteryMax;
  float display;
  bool checkBattery() {
    if(battery == 0)
      return false;
    return true;
  }
public:
  Calculator(int batteryMax = 0) :
  battery(0), batteryMax(batteryMax), display(0) {};

  void chargeBattery(int value) {
    if((this->battery + value) > this->batteryMax) {
      this->battery = this->batteryMax;
      return;
    }
    this->battery += value;
  }

  void sum(int a, int b) {
    if(!this->checkBattery()) {
      fn::print("fail: bateria insuficiente\n");
      return;
    }
    this->battery -= 1;
    this->display = a + b;
  }

  void division(int a, int b) {
    if(!this->checkBattery()) {
      fn::print("fail: bateria insuficiente\n");
      return;
    }
    if(b == 0) {
      fn::print("fail: divisao por zero\n");
      this->battery -= 1;
      return;
    }
    this->battery -= 1;
    this->display = (float) a / b;
  }

  std::string str() const {
    return fn::format("display = {%.2f}, battery = {}", this->display, this->battery); 
  }
};

class Student {
private:
    Calculator c;
public:
    void init() {
        this->c = Calculator(0);
    }
    void show() {
        std::cout << this->c.str() << std::endl;
    }
    void init(int batteryMax) {
        (void) batteryMax;
        this->c = Calculator(batteryMax);
    }
    void charge(int value) {
        (void) value;
        this->c.chargeBattery(value);
    }
    void sum(int a, int b) {
        (void) a;
        (void) b;
        this->c.sum(a, b);
    }
    void div(int num, int den) {
        (void) num;
        (void) den;
        this->c.division(num, den);
    }
};
