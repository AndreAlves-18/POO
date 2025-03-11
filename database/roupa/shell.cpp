#include "fn.hpp"

class Camisa{
std::string tamanho {};
public:
    Camisa(std::string valor = ""): tamanho(valor){}
    void setTamanho(std::string valor){
        if( valor == "PP" ||  valor == "P" ||  valor == "M" ||  valor == "G" ||  valor == "GG" ||  valor == "XG"){
            this->tamanho = valor;
            return;
        }
        std::cout << "fail: Valor inválido, tente PP, P, M, G, GG ou XG\n";
    }
    std::string getTamanho(){
        return this->tamanho;
    }
    void str(){
        if(tamanho == ""){
            fn::write("size: ()");
            return;
        }
        fn::print("size: ({})\n", tamanho);
    }
};

class Adapter {
    Camisa camisa;
public:
    Adapter() {
    }
    void size(const std::string& size) {
        (void) size;
        camisa.setTamanho(size);
    }
    void show() {
        camisa.str();
    }
};

int main() {
    Adapter adapter;
    while (true) {
        fn::write("$", "");
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write(line);

        if      (args[0] == "end")  { break;                         }
        else if (args[0] == "size") { adapter.size(args[1]);         }
        else if (args[0] == "show") { adapter.show();                }
        else                        { fn::write("Comando inválido"); }
    }
}