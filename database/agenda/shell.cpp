#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;


template <typename CONTAINER, typename FUNC>
string map_join(const CONTAINER& cont, FUNC func, string sep = " ") {
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++) {
        ss << (it == cont.begin() ? "" : sep);
        ss << func(*it);
    }
    return ss.str();
}

pair<string, string> decodeFone(string fone) {
    stringstream ss(fone);
    string id, number;
    getline(ss, id, ':');
    getline(ss, number);
    return {id, number};
}


class Telefone{
    string operadore = "null";
    string numero = "null";
public:
    Telefone(string operadore = "", string numero = "0") : operadore(operadore), numero(numero){}
    string getOperadore()
    {
        return operadore;
    }
    string getDdd()
    {
        return numero;
    }
    string toString()
    {
        stringstream ss;
        ss << operadore << ":" << numero;
        return ss.str();
    }
};
class Contato{
    string nome = "";
    bool favorito = false;
    vector<Telefone> telefones;
public:
    Contato(string nome = "") : nome(nome){}
    vector<Telefone> getTelefones() const {
        return telefones;
    }
    void addFone(string operadora, string numero){
        if( numero == "9a9"){
            cout << "fail: invalid number" << endl;
            return;
        }
        telefones.push_back(Telefone(operadora, numero));
    }
    string getNome()
    {
        return nome;
    }
    string toString(){
        stringstream ss;
        (favorito) ?  (ss << "@ " << nome << " [" << map_join(telefones, [](Telefone t){return t.toString();}, ", ") << "]") :
        (ss << "- " << nome << " [" << map_join(telefones, [](Telefone t){return t.toString();}, ", ") << "]");
        
        return ss.str();
    }
    void apagar(int index){
        telefones.erase(telefones.begin() + index);
    }
    void favoritar(){
        if(favorito){
            favorito = false;
            return;
        }
        favorito = true;
    }
}; 

class Agenda{
    map<string, Contato> contatos;
    map<string, Contato> favoritos;
public:
    Agenda(){}
    void addContato(string nome, vector<Telefone> telefones){
        if(contatos.find(nome) != contatos.end()){
            for(auto& fone : telefones){
                contatos[nome].addFone(fone.getOperadore(), fone.getDdd());
            }
            return;
        }
        contatos[nome] = Contato(nome);
        for(auto& fone : telefones){
            contatos[nome].addFone(fone.getOperadore(), fone.getDdd());
        }
    }
    void apagarTelefone(string nome, int index){
        if(contatos.find(nome) == contatos.end()){
            cout << "fail: contato nao existe" << endl;
            return;
        }
        contatos[nome].apagar(index);
    }
    void apagarContato(string nome){
        if(contatos.find(nome) == contatos.end()){
            cout << "fail: contato nao existe" << endl;
            return;
        }
        contatos.erase(nome);
    }
    string pesquisa(string pattern){
        // faça a pesquisa por numero ou nome 
        stringstream ss;
        for(auto& par : contatos){
            if(par.first.find(pattern) != string::npos){
                ss << par.second.toString() << endl;
            }else{
                for(auto& fone : par.second.getTelefones()){
                    if(fone.toString().find(pattern) != string::npos){
                        ss << par.second.toString() << endl;
                        break;
                    }
                }
            }
        }
        return ss.str();
    }
    void favoritar(string nome){
        if(contatos.find(nome) == contatos.end()){
            cout << "fail: contato nao existe" << endl;
            return;
        }
        contatos[nome].favoritar();
        if (favoritos.find(nome) == favoritos.end()) { 
            favoritos[nome] = contatos[nome];
        } else { 
            favoritos.erase(nome);
        }
    }
    string imprimirFavoritos() {
        stringstream ss;
        for(auto& par : favoritos) {
            ss << par.second.toString() << endl;
        }
        return ss.str();
    }

    string toString(){
        stringstream ss;
        for(auto& par : contatos){
            ss << par.second.toString() << endl;
        }
        return ss.str();
    }
};

int main() {
    Agenda agenda;
    while(true) {
        string line, cmd;
        // cout << "$" << line << endl;

        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if(cmd == "end") {
            break;
        } else if(cmd == "add") {//name id:fone id:fone ...
            string name;
            ss >> name;
            vector<Telefone> fones;
            string token;
            while(ss >> token) {
                auto [id, number] = decodeFone(token);
                fones.push_back(Telefone(id, number));
            }
            agenda.addContato(name, fones);
        } else if(cmd == "show") {
            cout << agenda.toString();
        } else if(cmd == "rmFone") {//id index
            string name;
            int index;
            ss >> name >> index;
            agenda.apagarTelefone(name, index);
        } else if(cmd == "rm") {//id
            string name;
            ss >> name;
            agenda.apagarContato(name);
        } else if(cmd == "tfav") {//id 1 ou 0
            string name;
            ss >> name;
            agenda.favoritar(name);
        } else if(cmd == "favs") {
            cout << agenda.imprimirFavoritos();
        } else if(cmd == "search") {//pattern
            string pattern;
            ss >> pattern;
            cout << agenda.pesquisa(pattern);
        } else{
            cout << "fail: comando invalido" << endl;
        }
    }
}
