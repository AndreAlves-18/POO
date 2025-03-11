#include <iostream>
#include <list>
#include <sstream>
#include <memory>
using namespace std;


// Função auxiliar para mapear e juntar elementos de um container
template <typename CONTAINER, typename FUNC>
auto map_join(const CONTAINER& c, FUNC f, const string& sep = ", ") {
    stringstream ss;
    for (auto it = c.begin(); it != c.end(); ++it) {
        ss << (it != c.begin() ? sep : "");
        ss << f(*it);
    }
    return ss.str();
}

class Grafite{
    float calibre;
    string dureza;
    int tamanho;
public:
    Grafite(float calibre = 0, string dureza = "", int tamanho = 0) : calibre(calibre), dureza(dureza), tamanho(tamanho){}
    string str(){
        stringstream ss;
        ss << calibre << ":" << dureza << ":" << tamanho;
        return ss.str();
    }
    float getCalibre(){
        return this->calibre;
    }
    int getTamanho(){
        return this->tamanho;
    }
    void setTamanho(int valor){
        this->tamanho = valor;
    }
    int gasto(){
        if(dureza[0] == 'H'){
            return 1;
        }
        if(dureza[0] == '2'){
            return 2;
        }
        if(dureza[0] == '4'){
            return 4;
        }
        if(dureza[0] == '6'){
            return 6;
        }
        return 0;
    }
};
class Lapiseira{
    float calibre;
    shared_ptr<Grafite> ponta;
    list<shared_ptr<Grafite>> tambor;
public:
    Lapiseira(float calibre = 0) : calibre(calibre){}
    string str(){
        stringstream ss;
        auto lstr = [](auto x) {
            return x->str();
        };
        ss << "calibre: " << calibre << ", " << "bico: " << ( ponta != nullptr ? "[": "")
           << ( ponta != nullptr ? ponta->str(): "[]") << ( ponta != nullptr ? "]": "") << ", tambor: "
           << "<" <<( 0 == (int) tambor.size() ? "": "[") <<( 0 == (int) tambor.size() ? "": map_join(tambor, lstr, "][") )
           <<( 0 == (int) tambor.size() ? "": "]") << ">";
           return ss.str();
    }
    void inserir(shared_ptr<Grafite> grafite){
        
        if (calibre != grafite->getCalibre()){
            cout << "fail: calibre incompatível\n";
            return;
        }else {
            tambor.push_back(grafite);
        }
    }
    void pull(){
        if (tambor.size() == 0){
            cout << "fail: nao existe grafite\n";
            return;
        }
        if(ponta != nullptr){
            cout << "fail: ja existe grafite no bico\n";
            return;
        }
        ponta = tambor.front();
        tambor.pop_front();
    }
    void remover(){
        if (ponta == nullptr){
            cout << "fail: nao existe grafite no bico\n";
            return;
        }
        ponta = nullptr;
    }
    void escrever(){
        if (ponta == nullptr){
            cout << "fail: nao existe grafite no bico\n";
            return;
        }
        if(ponta->getTamanho() <= 10){
            cout << "fail: tamanho insuficiente\n";
            if(tambor.size() == 0){
                ponta = nullptr;
                return;
            }
            ponta = tambor.front();
            tambor.pop_front();
            return;
        }
        if((ponta->getTamanho() - 10) < ponta->gasto()){
            cout << "fail: folha incompleta\n";
            ponta->setTamanho(10);
            return;
        }
        ponta->setTamanho(ponta->getTamanho() - ponta->gasto());
        
    }
};

int main() {
    Lapiseira lapiseira;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;  
        }
        else if (cmd == "show") { 
            cout << lapiseira.str() << '\n';
        } 
        else if (cmd == "init") { 
            float calibre;
            ss >> calibre;
            lapiseira = Lapiseira(calibre);
        } 
        else if (cmd == "insert") { 
            float calibre;
            string dureza;
            int tamanho;
            ss >> calibre >> dureza >> tamanho;
            lapiseira.inserir(make_shared<Grafite>(calibre, dureza, tamanho));
        } 
        else if (cmd == "remove") { 
            lapiseira.remover();
        } 
        else if (cmd == "pull") { 
            lapiseira.pull();
        } 
        else if (cmd == "write") { 
            lapiseira.escrever();
        } 
        else {
            cout << "fail: comando invalido\n";
        }
    }
}
