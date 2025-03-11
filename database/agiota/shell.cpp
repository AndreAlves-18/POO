#include <sstream>
#include <iostream>
#include "fn.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include <cmath>
using namespace std;

template <typename CONTAINER, typename FN>
string map_join(const CONTAINER& container, FN fn, string sep = ", ") {
    stringstream ss;
    for (auto it = container.begin(); it != container.end(); ++it) {
        ss << (it != container.begin() ? sep : "") << fn(*it);
    }
    return ss.str();
}

enum Label {
    GIVE, TAKE, PLUS
};

ostream &operator<<(ostream &os, Label label) {
    switch (label) {
        case GIVE: os << "give"; break;
        case TAKE: os << "take"; break;
        case PLUS: os << "plus"; break;
    }
    return os;
}

class Operacao{
    int id;
    string nome;
    Label label;
    int value;
public:
    Operacao(int id, string nome, Label label, int value){
        this->id = id;
        this->nome = nome;
        this->label = label;
        this->value = value;
    }
    string getNome() {
        return nome;
    }
    Label getLabel() {
        return label;
    }
    int getValue() {
        return value;
    }
    string str(){
        return "id:{} {}:{} {}" | fn::FORMAT(id, label, nome, value);
    }
   
};

class Cliente{
    string nome;
    int limite;
    vector<shared_ptr<Operacao>> operacoes;
public:
    Cliente(string nome= "", int limite = 0) : nome(nome), limite(limite) {}
    string getNome() {
        return nome;
    }
    int getLimite() {
        return limite;
    }
    int getBalance() {
        int balance = 0;
        for(auto& op : operacoes) {
            if(op->getLabel() == GIVE || op->getLabel() == PLUS) {
                balance += op->getValue();
            }
            else if(op->getLabel() == TAKE) {
                balance -= op->getValue();
            }
        }
        return balance;
    }
    void addOperacao(shared_ptr<Operacao> tr) {
        operacoes.push_back(tr);
    }
    vector<shared_ptr<Operacao>> getOperacoes() {
        return operacoes;
    }
    string str(){
        return "{} {}/{}" | fn::FORMAT(nome, getBalance(), limite);
    }
};

class Agiota{
    vector<Cliente> lista_viva;
    vector<Cliente> lista_morta;
    vector<shared_ptr<Operacao>> operacoes_vivos;
    vector<shared_ptr<Operacao>> operacoes_mortos;
    int nextOpId = 0;
public:
    Agiota() {}
    int procurar_cliente(string nome) {
        for(int i = 0; i < (int)lista_viva.size(); i++) {
            if(lista_viva[i].getNome() == nome) {
                return i;
            }
        }
        return -1;
    }
    void pushoperation (Cliente& cli, Label label, int value) {
        shared_ptr<Operacao> tr = make_shared<Operacao>(nextOpId, cli.getNome(), label, value);
        cli.addOperacao(tr);
        operacoes_vivos.push_back(tr);
        nextOpId++;
    }
    Cliente* getCliente(string nome) {
        int i = procurar_cliente(nome);
        if(i == -1) {
            cout << "fail: cliente nao existe\n";
            return nullptr;
        }
        return &lista_viva[i];
    }
    void addCliente(string nome, int limite) {
        if(procurar_cliente(nome) != -1) {
            cout << "fail: cliente ja existe\n";
            return;
        }
        lista_viva.push_back(Cliente(nome, limite));
        sort(lista_viva.begin(), lista_viva.end(), [](Cliente& a, Cliente& b) {
            return a.getNome() < b.getNome();
        });
    }
    void emprestar(string nome, int value) {
        Cliente* cli = getCliente(nome);
        if(cli == nullptr){
            return;
        }
        if(value > 0) {
            if(cli->getBalance() + value > cli->getLimite()) {
                cout << "fail: limite excedido\n";
                return;
            }
            pushoperation(*cli, GIVE, value);
        }
    }
    void cobrar(string nome, int value) {
        Cliente* cli = getCliente(nome);
        if(cli == nullptr){
            return;
        }
        if(value > 0) {
            if(cli->getBalance() - value < 0) {
                cout << "fail: valor excede o saldo\n";
                return;
            }
            pushoperation(*cli, TAKE, value);
        }
    }
    void matar(string nome) {
        int i = procurar_cliente(nome);
        if(i == -1) {
            cout << "fail: cliente nao existe\n";
            return;
        }
        Cliente cli = lista_viva[i];
        lista_viva.erase(lista_viva.begin() + i);
        lista_morta.push_back(cli);
        for(auto it = operacoes_vivos.begin(); it != operacoes_vivos.end();) {
            if((*it)->getNome() == nome) {
                operacoes_mortos.push_back(*it);
                it = operacoes_vivos.erase(it);
            }
            else {
                it++;
            }
        }
    }
    void juros(){
        for(auto& cli : lista_viva) {
            int balance = cli.getBalance();
            int juros = ceil(balance * 0.1);
            if(juros > 0) {
                pushoperation(cli, PLUS, juros);
            }
        }
        vector<string> a_remover;
        for (auto &cli : lista_viva) {
            if (cli.getBalance() > cli.getLimite()) {
                a_remover.push_back(cli.getNome());
            }
        }        
        for (const auto &nome : a_remover) {
            matar(nome);
        }
    }
    string str(){
        stringstream ss;
        for (auto& cli : lista_viva) 
            ss << ":) " << cli.str() << endl;
        for (auto& tr : operacoes_vivos)
            ss << "+ " << tr->str() << endl;
        for (auto& cli : lista_morta) 
            ss << ":( " << cli.str() << endl;
        for (auto& tr : operacoes_mortos) 
            ss << "- " << tr->str() << endl;
        return ss.str();
    }
    string strCli(string nome){
        stringstream ss;
        Cliente* cli = getCliente(nome);
        if(cli == nullptr) {
            return "";
        }
        ss << cli->str() << endl;
        for (auto& tr : cli->getOperacoes())
            ss << tr->str() << endl;
        return ss.str();
    }
};


int main() {
    Agiota agiota;
    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if(cmd == "end") {
            break;
        }
        else if(cmd == "addCli") {
            string name;
            int limite {};
            ss >> name >> limite;
            agiota.addCliente(name, limite);

        }
        else if(cmd == "show") {
            cout << agiota.str();
        }
        else if(cmd == "showCli") {
            string name;
            ss >> name;
            cout << agiota.strCli(name);
        }
        else if(cmd == "kill") {
            string name;
            ss >> name;
            agiota.matar(name);
        }
        else if(cmd == "give") {
            string name;
            int value;
            ss >> name >> value;
            agiota.emprestar(name, value);
        }
        else if(cmd == "take") {
            string name;
            int value;
            ss >> name >> value;
            agiota.cobrar(name, value);
        }
        else if(cmd == "plus") {
            agiota.juros();
        }
        else {
            cout << "fail: comando invalido\n";
        }
    }
}
