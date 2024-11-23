#include "../fn.hpp"

struct Car {
  int pass;
  int passMax;
  int gas;
  int gasMax;
  int km;

  Car() : pass(0), passMax(2), gas(0), gasMax(100), km(0) {};

  void enter() {
    if(pass >= passMax) {
      fn::print("fail: limite de pessoas atingido\n");
      return;
    }
    this->pass += 1;
  }

  void leave() {
    if(this->pass == 0) {
      fn::print("fail: nao ha ninguem no carro\n");
      return;
    }
    this->pass -= 1;
  }

  void fuel(int value) {
    if((this->gas + value) > this->gasMax) {
      this->gas = 100;
      return;
    }
    this->gas += value;
  }

  void drive(int value) {
    if(this->pass == 0) {
      fn::print("fail: nao ha ninguem no carro\n");
      return;
    }
    if(this->gas == 0) {
      fn::print("fail: tanque vazio\n");
      return;
    }
    if(value > this->gas) {
      fn::print("fail: tanque vazio apos andar {} km\n", this->gas);
      this->gas = 0;
      return;
    }
    this->gas -= value;
  }

  std::string str() const {
    return fn::format("pass: {}, gas: {}, km: {}", this->pass, this->gas, this->km);
  }
};

inline std::ostream& operator<<(std::ostream& os, const Car& car) {
  return os << car.str();
}

struct Student {
    Car car;
    Student() {}

    void enter() {
        this->car.enter();
    }
    void leave() {
        this->car.leave();
    }
    void fuel(int q) {
        this->car.fuel(q);
        (void) q;
    }
    void drive(int q) {
        this->car.drive(q);
        (void) q;
    }
    void show() {
        std::cout << this->car.str() << std::endl;
    }
};
