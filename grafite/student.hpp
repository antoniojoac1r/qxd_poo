#pragma once
#include <string>
#include <utility>
#include <memory>
#include "../fn.hpp"

struct Lead {
private:
  double thickness;
  std::string hardness;
  int length;
public:
  Lead(float thickness = 0, std::string hardness = "", int length = 0) : 
    thickness(thickness), hardness(hardness), length(length) {
  }

  double getThickness() const { return this->thickness; }

  std::string getHardness() const { return this->hardness; }

  int getLenght() const { return this->length; }

  void setLenght(int value) { this->length = value; }

  int usagePerSheet() {
    if(this->hardness == "HB")
      return 1;
    if(this->hardness == "2B")
      return 2;
    if(this->hardness == "4B")
      return 4;
    return 6;
  }

  std::string str() const {
    return fn::format("[{}:{}:{}]", this->thickness, this->hardness, this->length);
  }
};

inline std::ostream& operator<<(std::ostream& os, const Lead& lead) {
  return os << lead.str();
}

class Pencil {
private:
  double thickness;
  std::shared_ptr<Lead> lead;
public:
  Pencil(float thickness) : 
    thickness(thickness), lead(nullptr) { }

  bool hasLead() {
    if(this->lead != nullptr)
      return true;
    return false;
  }

  void insert(std::shared_ptr<Lead> lead) {
    if(hasLead()) {
      fn::print("fail: ja existe grafite\n");
      return;
    }
    if(lead->getThickness() != this->thickness) {
      fn::print("fail: calibre incompativel\n");
      return;
    }
    this->lead = lead;
  }

  std::shared_ptr<Lead> remove() {
    if (this->lead == nullptr) {
      fn::print("fail: nao existe grafite\n");
      return nullptr;
    }
    return std::exchange(this->lead, nullptr);
  }

  void writePage() {
    if(!hasLead()) {
      fn::print("fail: nao existe grafite\n");
      return;
    }
    if(this->lead->getLenght() == 10) {
      fn::print("fail: tamanho insuficiente\n");
      return;
    }
    if((this->lead->getLenght() - this->lead->usagePerSheet()) < 10) {
      fn::print("fail: folha incompleta\n");
      this->lead->setLenght(10);
      return;
    }
    this->lead->setLenght(this->lead->getLenght() - this->lead->usagePerSheet());
  }

  std::string str() const {
    return fn::format("calibre: {}, grafite: {}", this->thickness, this->lead);
  }
};

inline std::ostream& operator<<(std::ostream& os, const Pencil& pencil) {
  return os << pencil.str();
}

class Student {
private:
  Pencil pencil;
public:
  Student(double thickness = 0) : pencil(thickness) {
    (void) thickness;
  };

  void insert(double thickness, std::string hardness, int length) {
    (void) thickness;
    (void) hardness;
    (void) length;
    pencil.insert(std::make_shared<Lead>(thickness, hardness, length));
  }

  void remove() {
    pencil.remove();
  }

  void writePage() {
    pencil.writePage();
  }

  void show() {
    fn::write(pencil);
  }
};
