#include <iostream>
#include <sstream>

class Chinela{
int tamanho {0};
public:
    Chinela(){ 
        this->tamanho = 0;
    }
    int getTamanho(){
        return this->tamanho;
    }
    void setTamanho(int valor){
        if(valor < 20 || valor > 50){
            std::cout << "Valor invalodo!, digite novamente.\n";
            return;
        }
        if((valor % 2) == 1){
            std::cout << "Valor invalodo!, digite novamente.\n";
            return;
        }
        tamanho = valor;
        return;
    }
};

int main() {
    Chinela chinela;
    while (chinela.getTamanho() == 0){
        std::cout << "Digite seu tamanho de chinela\n";
        int tamanho;
        std::cin >> tamanho;
        chinela.setTamanho(tamanho);
    }
    std::cout << "Parabens, você comprou uma chinela tamanho " << chinela.getTamanho() << '\n';

}