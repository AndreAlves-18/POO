#include <iostream>
class Camisa{
std::string tamanho {};
public:
    Camisa(std::string valor = ""): tamanho(valor){}
    void setTamanho(std::string valor){
        if( valor == "PP" ||  valor == "P" ||  valor == "M" ||  valor == "G" ||  valor == "GG" ||  valor == "XG"){
            this->tamanho = valor;
            return;
        }
        std::cout << "Valor invalido, digite novamente.\n";
        std::cout << "Os valores válidos são 'PP', 'P', 'M' , 'G', 'GG' e 'XG'.\n";
    }
    std::string getTamanho(){
        return this->tamanho;
    }
};
int main() {
    Camisa camisa;
    while (camisa.getTamanho() == ""){
        std::cout << "Informe um tamanho de camisa\n";
        std::string tamanho;
        std::cin >> tamanho;
        camisa.setTamanho(tamanho);
    }
    std::cout << "Parabens, você comprou uma camisa tamanho " << camisa.getTamanho() << '\n';
}