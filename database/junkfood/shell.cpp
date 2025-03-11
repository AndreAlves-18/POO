#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

class Espiral{
    string nome;
    int qtd;
    double preco;
public:
    Espiral(string nome, int qtd, double preco) : nome(nome), qtd(qtd), preco(preco) {}
    string get_nome(){ 
        return nome; 
    }
    int get_qtd(){ 
        return qtd; 
    }
    double get_preco(){ 
        return preco; 
    }
    void set_nome(string nome) { 
        this->nome = nome; 
    }
    void set_qtd(int qtd) { 
        this->qtd = qtd; 
        }
    void set_preco(double preco) { 
        this->preco = preco; 
    }
    string str(){
        stringstream ss;
        ss << "[" << setw(8) << setfill(' ') << nome
           << " : " << qtd << " U : " << fixed << setprecision(2) << preco << " RS]";
        return ss.str();
    }
};
class Maquina {
    vector<Espiral> espirais;
    double saldo;
    double lucro;
public:
    Maquina(int n_espirais = 0){
        espirais = vector<Espiral>(n_espirais, 
                   Espiral("empty", 0, 0));
        saldo = 0;
        lucro = 0;
    }

    
    string str() {
        stringstream ss;
        ss << "saldo: " << fixed << setprecision(2) << saldo << endl;
        for (size_t i = 0; i < espirais.size(); i++) {
            ss << i << " " << espirais[i].str() << endl;
        }
        string saida = ss.str();
        saida.pop_back();
        return saida;
    }
    void setProduto(int index, string nome, int qtd, double preco){
        if (index < 0 || index >= (int) espirais.size()) {
            cout << "fail: indice nao existe\n";
            return;
        }
        espirais[index] = Espiral(nome, qtd, preco);
    }
    void limpar(int index){
        if (index < 0 || index >= (int) espirais.size()) {
            cout << "fail: indice nao existe\n";
            return;
        }
        espirais[index] = Espiral("empty", 0, 0);
    }
    void dinheiro(double value){
        saldo += value;
    }
    double troco() {
        double troco = saldo;
        saldo = 0;
        return troco;
    }
    void comprar(int index){
        if (index < 0 || index >= (int) espirais.size()) {
            cout << "fail: indice nao existe\n";
            return;
        }
        if (espirais[index].get_qtd() == 0) {
            cout << "fail: espiral sem produtos\n";
            return;
        }
        if (saldo < espirais[index].get_preco()) {
            cout << "fail: saldo insuficiente\n";
            return;
        }
        saldo -= espirais[index].get_preco();
        espirais[index].set_qtd(espirais[index].get_qtd() - 1);
        lucro += espirais[index].get_preco();
        cout << "voce comprou um " << espirais[index].get_nome() << endl;
    }

};


template<typename CONTAINER, typename FUNC>
string map_join(const CONTAINER& cont, FUNC func, string delim) {
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++) {
        ss << (it == cont.begin() ? "" : delim);
        ss << func(*it);
    }
    return ss.str();
}


int main() {
    Maquina maquina;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        try {
            if (cmd == "show") {
                // IMPRIMIR
                cout << maquina.str() << '\n';
            } else if (cmd == "init") {
                int n_espirais {};
                ss >> n_espirais;
                maquina = Maquina(n_espirais);
            } else if (cmd == "limpar") {
                int indice {};
                ss >> indice;
                maquina.limpar(indice);
            } else if (cmd == "dinheiro") {
                int value {};
                ss >> value;
                maquina.dinheiro(value);
            } else if (cmd == "comprar") {
                int index {};
                ss >> index;
                maquina.comprar(index);
            } else if (cmd == "set") {
                int index {};
                string name;    
                int qtd {};
                double price {};
                ss >> index >> name >> qtd >> price;
                maquina.setProduto(index, name, qtd, price);
            } else if (cmd == "troco") {
                auto troco = maquina.troco();
                cout << "voce recebeu " 
                     << fixed << setprecision(2) << troco
                     << " RS" << '\n';
            } else if (cmd == "end") {
                break;
            } else {
                cout << "comando invalido" << endl;
            }
        } catch (const char* e) {
            cout << e << endl;
        }
    }
}
