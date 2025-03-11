#include "fn.hpp"
using namespace std;

struct Pessoa{
    string nome;
    Pessoa(string nome = "") : nome(nome) {}
};

class Budega{
    vector<shared_ptr<Pessoa>> caixas;
    list<shared_ptr<Pessoa>> fila;
public:
    Budega(int n_pessoas = 0){
        for(int i = 0; i < n_pessoas; i++){
            caixas.push_back(nullptr);
        }
    }
    string str(){
        stringstream ss;
        ss << "Caixas: [";
        for(size_t i = 0; i < caixas.size(); i++){
            if(caixas[i] == nullptr){
                ss << "-----";
            }else{
                ss << caixas[i]->nome;
            }
            if(i != caixas.size() - 1){
                ss << ", ";
            }
        }
        ss << "]\n";
        ss << "Espera: [";
        size_t cont = 0;
        for(auto elem : fila){
            ss << elem->nome;
            if(cont != fila.size() - 1){
                ss << ", ";
            }
            cont++;
        }
        ss << "]";

        return ss.str();
    }
    void chegar(shared_ptr<Pessoa> pessoa){
        fila.push_back(pessoa);
    }
    void chamarNoCaixa(int indice){
        if(indice < 0 || indice >= (int) caixas.size()){
            cout << "fail: caixa inexistente\n";
            return;
        }
        size_t i = fila.size();
        if(i == 0){
            cout << "fail: sem clientes\n";
            return;
        }
        if(caixas[indice] == nullptr){
            if(fila.empty()){
                return;
            }
            caixas[indice] = fila.front();
            fila.pop_front();
            return;
        }
        cout << "fail: caixa ocupado\n";
    }
    void finalizar(int indice){
        if(indice < 0 || indice >= (int) caixas.size()){
            cout << "fail: caixa inexistente\n";
            return;
        }
        if(caixas[indice] == nullptr){
            cout << "fail: caixa vazio\n";
            return;
        }
        caixas[indice] = nullptr;
    }

};


class Adapter {
    Budega budega;
public:
    void init(int qtd_caixas) {
        (void) qtd_caixas;
        budega = Budega(qtd_caixas);
    }
    void call(int indice) {
        (void) indice;
        budega.chamarNoCaixa(indice);
    }
    void finish(int indice) {
        (void) indice;
        budega.finalizar(indice);
    }
    void arrive(const std::string& nome) {
        budega.chegar(std::make_shared<Pessoa>(nome));
        (void) nome;
    }

    void show() {
        fn::write(budega.str());
    }
};

int main() {
    Adapter adp;

    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if      (args[0] == "end"   ) { break;                                          }
        else if (args[0] == "init"  ) { adp.init(+args[1]);                             }
        else if (args[0] == "call"  ) { adp.call(+args[1]);                             }
        else if (args[0] == "finish") { adp.finish(+args[1]);                           }
        else if (args[0] == "arrive") { adp.arrive(args[1]);                            }
        else if (args[0] == "show"  ) { adp.show();                          }
        else                          { fn::write("fail: comando invalido");            }
    }
}
