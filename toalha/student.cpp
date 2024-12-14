#include <iostream>

class Towel {
private:
    std::string color;
    std::string size;
    int wetness;
public:
    Towel(std::string color = "", std::string size = "") :
    color(color), size(size), wetness(0) {}

    std::string getColor() const {
        return this->color;
    }

    std::string getSize() const {
        return this->size;
    }

    int getWetness() const {
        return this->wetness;
    }

    void setColor(std::string newColor) {
        this->color = newColor;
    }

    void setSize(std::string newSize) {
        this->size = newSize;
    }

    void setWetness(int newWetness) {
        this->wetness = newWetness;
    }

    int getMaxWetness() {
        if(this->size == "P")
            return 10;
        if(this->size == "M")
            return 20;
        if(this->size == "G")
            return 30;
        return 0;
    }

    void dry(int amount) {
        if((this->wetness + amount) > getMaxWetness()) {
            std::cout << "msg: toalha encharcada" << std::endl;
            return;
        }
        this->wetness += amount;
    }

    void wringOut() {
        this->wetness = 0;
    }

    std::string isDry() {
        return (this->wetness == 0) ? "true" : "false";
    }

    void show() {
        std::cout << this->color << " " << this->size << " " << this->wetness << std::endl;
    }
};


int main() {
    Towel towel("Azul", "P");
    towel.show(); //  # Azul P 0
    towel.dry(5);
    towel.show();  // # Azul P 5
    std::cout << towel.isDry() << std::endl; // # False
    towel.dry(5);
    towel.show();  // # Azul P 10
    towel.dry(5); // # msg: toalha encharcada
    towel.show();  // # Azul P 10

    towel.wringOut();
    towel.show();  // # Azul P 0 */

    towel = Towel("Verde", "G");
    std::cout << towel.isDry() << std::endl; // # True
    towel.dry(30);
    towel.show();  // # Verde G 30
    std::cout << towel.isDry() << std::endl; //  # False
    towel.dry(1);  // # msg: toalha encharcada 
}