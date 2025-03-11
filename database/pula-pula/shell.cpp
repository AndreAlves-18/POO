#include <iostream>
#include <memory>
#include <sstream>
#include <list>
using namespace std;

template<class CONTAINER, class FUNC>
string map_join(const CONTAINER& c, FUNC f, string sep) {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); it++) {
        ss << (it == c.begin() ? "" : sep);
        ss << f(*it);
    }
    return ss.str();
}

class Crianca {
    string nome;
    int idade;
public:
    Crianca(string nome = "", int idade = 0): nome(nome), idade(idade){}
    string str() const {
        stringstream ss;
        ss << nome << ":" << idade;
        return ss.str();
    }
    string gatnome() const {
        return nome;
    }
    int getidade() const {
        return idade;
    }
    void setnome(string nome) {
        this->nome = nome;
    }
    void setidade(int idade) {
        this->idade = idade;
    }
};


class Pupa_pula{
    list<shared_ptr<Crianca>> pulando;
    list<shared_ptr<Crianca>> esperando;
public:
    Pupa_pula() {}
    string str(){
        stringstream ss;
        auto lstr = [](auto x) {
            return x->str();
        };
        ss << "[" << map_join(esperando, lstr, ", ") << "]" << " => " 
           << "[" << map_join(pulando, lstr, ", ") << "]";
        return ss.str();
    }
    void chegar(shared_ptr<Crianca> crianca){
        esperando.push_front(crianca);
    }
    void entrar(){
        if(esperando.size() == 0){
            cout << "fail: nao tem ninguem na fila\n";
            return;
        }
        pulando.push_front(esperando.back());
        esperando.pop_back();
    }
    void tirar(){
        if(pulando.size() == 0){
            return;
        }
        esperando.push_front(pulando.back());
        pulando.pop_back();
    }
    void remover(string nome){
        for(auto it = esperando.begin(); it != esperando.end(); it++){
            if((*it)->gatnome() == nome){
                esperando.erase(it);
                return;
            }
        }
        for(auto it = pulando.begin(); it != pulando.end(); it++){
            if((*it)->gatnome() == nome){
                pulando.erase(it);
                return;
            }
        }
        cout << "fail: " << nome << " nao esta no pula-pula\n";
    }
};


int main() {
    Pupa_pula pupa_pula;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
            cout << pupa_pula.str() << '\n';
        } else if (cmd == "arrive") {
            string name;
            int age;
            ss >> name >> age;
            pupa_pula.chegar(make_shared<Crianca>(name, age));

        } else if (cmd == "enter") {
            pupa_pula.entrar();
        } else if (cmd == "leave") {
            pupa_pula.tirar();
        } else if (cmd == "remove") {
            string name;
            ss >> name;
            pupa_pula.remover(name);
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
