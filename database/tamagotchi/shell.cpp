#include "fn.hpp" // https://raw.githubusercontent.com/senapk/cppaux/master/fn.hpp
#include <iostream>
#include <string>

class Tamagochi{
    int idade{0};
    int energia{0};
    int energiaMax{0};
    int limpeza{0};
    int limpezaMax{0};
    bool vivo {true};
public:
    Tamagochi(int enerMax = 0, int limMax = 0): energia(enerMax), energiaMax(enerMax), limpeza(limMax), limpezaMax(limMax){
        this->idade = 0;
        this->vivo = true;
    }
    int getIdade(){
        return this->idade;
    }
    int getEnergia(){
        return this->energia;
    }
    int getEnergiaMax(){
        return this->energiaMax;
    }
    int getLinpeza(){
        return this->limpeza;
    }
    int getLinpezaMax(){
        return this->limpezaMax;
    }
    bool getVida(){
        return this->vivo;
    }
    void setIdade(int valor){
        this->idade += valor;
    }
    void setEnergia(int valor){
        if((valor+energia) >= energiaMax){
            energia = energiaMax;
            return;
        }
        if((valor+energia) < 0){
            energia = 0;
            return;
        }
        this->energia += valor;
    }
    void setLimpeza(int valor){
        if((valor+limpeza) >= limpezaMax){
            limpeza = limpezaMax;
            return;
        }
        if((valor+limpeza) < 0){
            limpeza = 0;
            return;
        }
        this->limpeza += valor;
    }
    void morte(){
        vivo = false;
    }
};

class Jogo{
    Tamagochi tamagochi;
public:
    Jogo(Tamagochi tamagochi = 0): tamagochi(tamagochi){}

    std::string str(){
        return fn::format("E:{}/{}, L:{}/{}, I:{}", tamagochi.getEnergia(), tamagochi.getEnergiaMax(), tamagochi.getLinpeza(), 
                                                      tamagochi.getLinpezaMax(), tamagochi.getIdade());

    }
    void brincar(){
        if(tamagochi.getVida() == false){
            std::cout << "fail: pet esta morto\n";
            return;
        }
        tamagochi.setEnergia(-2);
        tamagochi.setLimpeza(-3);
        tamagochi.setIdade(1);
        if(tamagochi.getLinpeza() == 0){
            std::cout << "fail: pet morreu de sujeira\n";
            tamagochi.morte();
            return;
        }
        if(tamagochi.getEnergia() == 0){
            std::cout << "fail: pet morreu de fraqueza\n";
            tamagochi.morte();
            return;
        }

    }
    void dormir(){
        if(tamagochi.getVida() == false){
            std::cout << "fail: pet esta morto\n";
            return;
        }
        if((tamagochi.getEnergiaMax() - tamagochi.getEnergia()) < 5){
            std::cout << "fail: nao esta com sono\n";
            return;
        }
        tamagochi.setIdade(tamagochi.getEnergiaMax() - tamagochi.getEnergia());
        tamagochi.setEnergia(tamagochi.getEnergiaMax());
    }
    void tomarBanho(){
        if(tamagochi.getVida() == false){
            std::cout << "fail: pet esta morto\n";
            return;
        }
        tamagochi.setEnergia(-3);
        tamagochi.setLimpeza(tamagochi.getLinpezaMax());
        tamagochi.setIdade(2);
    }
};

class Adapter {
private:
    Jogo jogo;
public:
    void init(int energy, int clean) {
        (void) energy;
        (void) clean;
        this->jogo = Jogo(Tamagochi(energy, clean));
    }

    void show() {
        std::cout << this->jogo.str() << std::endl;
    }

    void play() {
        this->jogo.brincar();
    }

    void shower() {
        this->jogo.tomarBanho();
    }

    void eat() {
        // this->game.eat();
    }

    void sleep() {
        this->jogo.dormir();
    }
};


int main() {
    Adapter adp;
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');

        fn::write("$" + line);

        if      (args[0] == "end")    { break;                                       }
        else if (args[0] == "init")   { adp.init(+args[1], +args[2]);                }
        else if (args[0] == "show")   { adp.show();                                  }
        else if (args[0] == "play")   { adp.play();                                  }
        else if (args[0] == "sleep")  { adp.sleep();                                 }
        else if (args[0] == "shower") { adp.shower();                                }
        else                          { fn::write("fail: comando invalido");         }
    }
}
