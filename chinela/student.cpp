#include "fn.hpp"

class Chinela {
private:
  int tamanho;
public:
  Chinela(int tamanho = 0) :
  tamanho(tamanho) {}

  int getTamanho() const { return this->tamanho; };

  void setTamanho(int t) {
    if(t < 20 || t > 50 || t % 2 != 0) {
      fn::print("msg: error tamanho {} invalido!\nTente novamente\n", t);
      return;
    }
    this->tamanho = t;
    return;
  }
};

int main() {
  Chinela c;
  while(c.getTamanho() == 0) {
    fn::write("Digite seu tamanho de chinela");
    auto line = fn::split(fn::input());
    c.setTamanho(+line[0]);
  }
  fn::print("Parabens, você comprou uma chinela tamanho {}\n", c.getTamanho());
}
