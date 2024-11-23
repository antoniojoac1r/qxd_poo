#pragma once
#include "../fn.hpp"

struct Animal {
  std::string especie;
  std::string barulho;
  int stage;
  Animal(std::string especie = "", std::string barulho = "") :
  especie(especie), barulho(barulho), stage(0){};

  std::string fazerBarulho() const {
    if(stage == 0)
      return "---";
    if(stage == 4)
      return "RIP";
    return this->barulho;
  }

  void envelhecer(int level) {
        stage += level;
        if (stage >= 4) {
            fn::print("warning: {} morreu\n", especie);
            stage = 4;
        }
  }

  std::string str() const {
    return fn::format("{}:{}:{}", this->especie, this->stage, this->barulho);
  }

};

inline std::ostream& operator<<(std::ostream& os, const Animal& animal) {
    return os << animal.str();
}

struct Student {
    Animal animal;
    void init(std::string especie = "", std::string barulho = "") {
        (void) especie;
        (void) barulho;
        animal = Animal(especie, barulho);
    }

    void grow(int level) {
        (void) level;
        animal.envelhecer(level);
    }

    void noise() {
        std::cout << animal.fazerBarulho() << std::endl;
    }

    void show() {
        std::cout << animal.str() << std::endl;
    }
};
