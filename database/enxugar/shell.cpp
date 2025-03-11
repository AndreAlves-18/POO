#include "fn.hpp"
class Toalha{
    std::string cor {};
    std::string tamanho {};
    int umidade {0};
public:
    Toalha(std::string cor = "", std::string tamanho = ""): cor(cor), tamanho(tamanho){
        
    }
    void enxugar(int valor){
        if(valor >= (pegarMaximoUmidade() - umidade)){
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
            std::cout << "sim\n";
            return true;
        }
        std::cout << "nao\n";
        return false;
        
    }
    void str() const{
        fn::print("Cor: {}, Tamanho: {}, Umidade: {}\n", cor, tamanho, umidade);
     }
 };

class Adapter {
    Toalha toalha;
public:
    Adapter() {}

    void criar(const std::string& cor, const std::string& tamanho) {
        (void) cor;
        (void) tamanho;
        Toalha toa(cor, tamanho);
        toalha = toa;
    }

    void enxugar(int quantidade) {
        (void) quantidade;
        toalha.enxugar(quantidade);
    }

    void seca() {
        toalha.estaSeca();
    }

    void torcer() {
        toalha.torcer();
    }

    void mostrar() const {
        toalha.str();
    }
};

int main() {
    Adapter adapter;
    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "end"    ) { break;                           }
        else if (args[0] == "criar"  ) { adapter.criar(args[1], args[2]); }
        else if (args[0] == "enxugar") { adapter.enxugar(+args[1]);       }
        else if (args[0] == "seca"   ) { adapter.seca();                  }
        else if (args[0] == "torcer" ) { adapter.torcer();                }
        else if (args[0] == "mostrar") { adapter.mostrar();               }
        else                           { fn::write("comando invalido");   }
    }
}
