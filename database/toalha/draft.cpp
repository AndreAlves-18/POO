#include <iostream>
#include <sstream>
class Toalha{
    std::string cor {};
    std::string tamanho {};
    int umidade {0};
public:
    Toalha(std::string cor = "", std::string tamanho = ""): cor(cor), tamanho(tamanho){
        this->umidade = 0;
    }
    void enxugar(int valor){
        if(valor == (pegarMaximoUmidade() - umidade)){
            umidade = pegarMaximoUmidade();
            return;
        }
        if(valor > (pegarMaximoUmidade() - umidade)){
            umidade = pegarMaximoUmidade();
            std::cout << "toalha encharcada\n";
            return;
        }
        umidade += valor;
    }
    void torcer(){
        this->umidade = 0;
    }
    int pegarMaximoUmidade(){

        if( tamanho == "P" || tamanho == "p"){
            return 10;
        }
        if( tamanho == "M" || tamanho == "m"){
            return 20;
        }
        if( tamanho == "G" || tamanho == "g"){
            return 30;
        }
        return 0;
    }
    bool estaSeca(){
        if(umidade == 0){
            std::cout << "True\n";
            return true;
        }
        std::cout << "False\n";
        return false;
        
    }
    void str(){
        std::cout << cor << " " << tamanho << " " << umidade << '\n';
     }
 };

int main() {
    Toalha toalha("Azul", "P");
    toalha.str();

    toalha.enxugar(5);
    toalha.str();
    toalha.estaSeca();
    toalha.enxugar(5);
    toalha.str();  
    toalha.enxugar(5); 
    toalha.str();  

    toalha.torcer();
    toalha.str();  

    toalha = Toalha("Verde", "G");
    toalha.estaSeca(); 
    toalha.enxugar(30);
    toalha.str();  
    toalha.estaSeca(); 
    toalha.enxugar(1); 
    }
