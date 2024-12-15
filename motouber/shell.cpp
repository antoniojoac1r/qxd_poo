#define __MEMORY //enable print for shared_ptr
#include "fn.hpp"
#include <utility>

class Person {
private:
  std::string name;
  int money;
public:
  Person(std::string name = "", int money = 0) : 
    name(name), money(money) {}

  auto getName() const { return this->name; }

  auto getMoney() const { return this->money; }

  void setMoney(int m) {
    this->money = m;
  }

  std::string str() const {
    return fn::format("{}:{}", this->name, this->money);
  }
};

inline std::ostream& operator<<(std::ostream& os, const Person& p) {
  return os << p.str();
}

class Uber {
private:
  int km;
  std::shared_ptr<Person> driver;
  std::shared_ptr<Person> pass;
public:
  Uber() : km(0) {}

  auto getDriver() const { return this->driver; }

  auto getPass() const { return this->pass; }

  auto getKm() const { return this->km; }

  void setDriver(std::shared_ptr<Person> p) {
    this->driver = p;
  }

  void setPass(std::shared_ptr<Person> p) {
    this->pass = p;
  }

  void setKm(int km) {
    this->km = km;
  }

  std::shared_ptr<Person> leave() {
    if (this->pass == nullptr) 
      return nullptr;
    fn::print("{}\n", this->pass);
    return std::exchange(this->pass, nullptr);
  }
    
  std::string str() const {
    std::string tmp { fn::format("Cost: {}", this->km) };
    /*return fn::format("Cost: {}, Driver: {}, Passenger: {}\n", this->km, this->driver, this->pass);*/
    if(this->driver == nullptr)
      tmp += ", Driver: None";
    else
      tmp += fn::format(", Driver: {}", this->driver);
    if(this->pass == nullptr)
      tmp += ", Passenger: None\n";
    else
      tmp += fn::format(", Passenger: {}\n", this->pass);
    return tmp;
  }
};

inline std::ostream& operator<<(std::ostream& os, const Uber& u) {
  return os << u.str();
}

class Adapter {
  Uber uber;
public:
  void setDriver(std::string name, int money) {
    uber.setDriver(std::make_shared<Person>(name, money));
  }
  void setPass(std::string name, int money) {
    uber.setPass(std::make_shared<Person>(name, money));
  }
  void drive(int d) {
    if(this->uber.getDriver() == nullptr) {
      fn::write("fail: no driver");
      return;
    }
    this->uber.setKm(this->uber.getKm() + d);
  }

  void leavePass() {
    auto p = this->uber.getPass();
    if(p->getMoney() < this->uber.getKm()) {
      fn::write("fail: Passenger does not have enough money");
      p->setMoney(0);
      this->uber.getDriver()->setMoney(this->uber.getDriver()->getMoney() + this->uber.getKm());
      this->uber.setKm(0);
    }
    this->uber.leave();
  }

  void show() {
    std::cout << this->uber;
  }
};

int main() {
  Adapter adp;
  while (true) {
    fn::write("$", "");
    auto line = fn::input();
    auto args = fn::split(line, ' ');
    fn::write(line);

    if      (args[0] == "end")       { break;                                  }
    else if (args[0] == "setDriver") { adp.setDriver(args[1], +args[2]);       }
    else if (args[0] == "setPass")   { adp.setPass(args[1], +args[2]);         }
    else if (args[0] == "drive")     { adp.drive(+args[1]);                    }
    else if (args[0] == "leavePass") { adp.leavePass();                        }
    else if (args[0] == "show")      { adp.show();                             }
    else                             { fn::write("fail: command not found\n"); }
  }
}
