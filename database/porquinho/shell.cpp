#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <utility>
#include <iomanip>
#include <memory>
using namespace std;

template <typename CONTAINER, typename FN>
string map_join(const CONTAINER& container, FN fn, string sep = ", ", string prefix = "[", string suffix = "]") {
    stringstream ss;
    for (auto it = container.begin(); it != container.end(); ++it) {
        ss << (it != container.begin() ? sep : "") << fn(*it);
    }
    return prefix + ss.str() + suffix;
}

class Moeda {
    string nome;
    float valor;
    int tamanho;
public:
    Moeda(string nome = "") : nome(nome){
        if(nome == "5"){
            tamanho = 0;
            valor = 0.05;
        }
        else if(nome == "10"){
            tamanho = 1;
            valor = 0.10;
        }
        else if(nome == "25"){
            tamanho = 2;
            valor = 0.25;
        }
        else if(nome == "50"){
            tamanho = 3;
            valor = 0.50;
        }
        else if(nome == "100"){
            tamanho = 4;
            valor = 1;
        }

    }
    int getTamanho() {
        return tamanho;
    }
    float getValor() {
        return valor;
    }
    string toString() {
        stringstream ss;
        ss << fixed << setprecision(2) << valor << ":" << tamanho;
        return ss.str();
    }
};

class Item {
    string nome;
    int tamanho;
public:
    Item(string nome = "", int tamanho = 0) : nome(nome), tamanho(tamanho) {}
    int getTamanho() {
        return tamanho;
    }
    string toString() {
        stringstream ss;
        ss << nome << ":" << tamanho;
        return ss.str();
    }
};
class Porquinho {
    bool quebrado = false;
    int volumeMax;
    int volumeAtual = 0;
    float dinheiro = 0;
    list<Moeda> moedas;
    list<Item> itens;
public:
    Porquinho(int volumeMax = 0) : volumeMax(volumeMax) {}
    void adicionarMoeda(Moeda moeda) {
        if (quebrado) {
            cout << "fail: the pig is broken\n";
            return;

        }
        if (volumeAtual + moeda.getTamanho() > volumeMax) {
            cout << "fail: the pig is full\n";
            return;
        }
        moedas.push_back(moeda);
        volumeAtual += moeda.getTamanho();
        dinheiro += moeda.getValor();
    }
    void adicionarItem(Item item) {
        if (quebrado) {
            cout << "fail: the pig is broken\n";
            return;
        }
        if (volumeAtual + item.getTamanho() > volumeMax) {
            cout  << "fail: the pig is full\n";
            return;
        }
        itens.push_back(item);
        volumeAtual += item.getTamanho();
    }
    void quebrar() {
        quebrado = true;
        volumeAtual = 0;
    }
    void extrairMoedas() {
        if (quebrado) {
            cout << map_join(moedas, [](Moeda m) { return m.toString(); }) << endl;
            dinheiro = 0;
            volumeAtual = 0;
            moedas.clear();
            return;
        }
        cout << "fail: you must break the pig first\n" << "[]\n";

    }
    void extrairItens() {
        if (quebrado) {
            cout << map_join(itens, [](Item i) { return i.toString(); }) << endl;
            volumeAtual = 0;
            itens.clear();
            return;
        }
        cout << "fail: you must break the pig first\n" << "[]\n";
    }
    string toString() {
        ostringstream ss;
        ss << fixed << setprecision(2) << dinheiro;
        return string("state=") + (quebrado ? "broken" : "intact") + 
               " : coins=" + map_join(moedas, [](Moeda m) { return m.toString(); }) +
               " : items=" + map_join(itens, [](Item i) { return i.toString(); }) + 
               " : value=" + ss.str() + 
               " : volume=" + to_string(static_cast<int>(volumeAtual)) + "/" + to_string(static_cast<int>(volumeMax));

    }
};
int main() {
    Porquinho porquinho;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "init") {
            int volumeMax;
            ss >> volumeMax;
            porquinho = Porquinho(volumeMax);
        } else if (cmd == "show") {
            cout << porquinho.toString() << endl;
        } else if (cmd == "break") {
            porquinho.quebrar();
        } else if (cmd == "addCoin") {
            string label;
            ss >> label;
            porquinho.adicionarMoeda(Moeda(label));
        } else if (cmd == "addItem") {
            string label;
            int volume;
            ss >> label >> volume;
            porquinho.adicionarItem(Item(label, volume));
        } else if (cmd == "extractItems") {
            // Obtenha os itens com o método extractItems
            // e imprima os itens obtidos
            porquinho.extrairItens();
        } else if (cmd == "extractCoins") {
            // Obtenha as moedas com o método extractCoins
            // e imprima as moedas obtidas
            porquinho.extrairMoedas();
        } else {
            cout << "fail: invalid command\n";
        }
    }
}