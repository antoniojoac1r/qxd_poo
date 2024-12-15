#include "fn.hpp"
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

class Battery {
private:
  int carga;
  int capacidade;
public:
  Battery(int capacidade = 0) :
    carga(capacidade), capacidade(capacidade) {}

  int getCarga() const { return this->carga; }

  int getCapacidade() const { return this->capacidade; }

  void setCarga(int newCarga) {
    this->carga = newCarga;
  }

  void setCapacidade(int newCapacidade) {
    this->capacidade = newCapacidade;
  }

  std::string str() const {
    return fn::format("({}/{})", this->carga, this->capacidade);
  }
};

inline std::ostream& operator<<(std::ostream& os, const Battery& b) {
  return os << b.str();
}

class Carregador {
private:
  int potencia;
public:
  Carregador(int potencia = 0) :
    potencia(potencia) {}

  int getPotencia() const {
    return this->potencia;
  }

  std::string str() const {
    return fn::format("(Potencia {})", this->potencia);
  }
};

inline std::ostream& operator<<(std::ostream& os, const Carregador& c) {
  return os << c.str();
}

class Notebook {
private:    
  std::shared_ptr<Battery> battery;
  std::shared_ptr<Carregador> carregador;
  bool ligado = false;
  std::string estaLigado() const {
    if(this->ligado)
      return "Ligado";
    return "Desligado";
  }
public:
  Notebook() {}

  std::shared_ptr<Battery> rmBateria() {
    if(this->battery == nullptr) {
      fn::print("msg: não existe bateria\n");
      return nullptr;
    }
    return std::exchange(this->battery, nullptr);
  }

  void setBateria(std::shared_ptr<Battery> b) {
    this->battery = b;
  }

  void setCarregador(std::shared_ptr<Carregador> c) {
    this->carregador = c;
  }

  void ligar() {
    if(this->battery == nullptr && this->carregador == nullptr) {
      fn::print("msg: não foi possível ligar\n");
      return;
    }
    fn::print("msg: notebook ligado\n");
    this->ligado = true;
  }

  void usar(int timeToUse) {
    if(!this->ligado) {
      fn::print("msg: notebook desligado\n");
      return;
    }
    if(this->carregador != nullptr) {
      if((this->battery->getCarga() + (timeToUse * this->carregador->getPotencia())) > this->battery->getCapacidade()) {
        this->battery->setCarga(this->battery->getCapacidade());
        fn::print("msg: Notebook utilizado com sucesso\n");
        return;
      }
      this->battery->setCarga(this->battery->getCarga() + (timeToUse * this->carregador->getPotencia()));
      fn::print("msg: Notebook utilizado com sucesso\n");
      return;
    }
    if((this->battery->getCarga() - timeToUse) <= 0) {
      fn::print("msb: Usando por {} minutos, notebook descarregou\n", this->battery->getCarga());
      this->battery->setCarga(0);
      this->ligado = false;
      return;
    }
    fn::print("msg: Usando por {} minutos\n", timeToUse);
    this->battery->setCarga((this->battery->getCarga() - timeToUse));
  }

  std::string str() const {
    std::string tmp{ fn::format("msg: Status: {}", this->estaLigado())};
    if(this->battery != nullptr) {
      tmp += fn::format(", Bateria: {}", this->battery);
    } else {
      tmp += fn::format(", Bateria: Nenhuma");
    }
    if(this->carregador != nullptr) {
      tmp += fn::format(", Carregador: {}\n", this->carregador);
    } else {
      tmp += fn::format(", Carregador: Desconectado\n");
    }
    return tmp;
  }
};

inline std::ostream& operator<<(std::ostream& os, const Notebook& n) {
  return os << n.str();
}

int main() {
  Notebook n;
  std::cout << n;
  n.ligar();
  n.usar(10);
  auto b = std::make_shared<Battery>(50);
  std::cout << *b << std::endl;
  n.setBateria(b);
  std::cout << n;
  n.ligar();
  std::cout << n;
  n.usar(30);
  std::cout << n;
  n.usar(30);
  std::cout << n;
  n.rmBateria();
  std::cout << *b << std::endl;
  std::cout << n;
  auto c = std::make_shared<Carregador>(2);
  std::cout << *c << std::endl;
  n.setCarregador(c);
  std::cout << n;
  n.ligar();
  std::cout << n;
  n.setBateria(b);
  std::cout << n;
  n.usar(10);
  std::cout << n;
}
