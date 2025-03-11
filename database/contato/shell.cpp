#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

template <class CONTAINER, class FUNC>
string map_join(const CONTAINER &cont, FUNC func, string sep = " ")
{
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++)
    {
        ss << (it == cont.begin() ? "" : sep) << func(*it);
    }
    return ss.str();
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

int main(){
    Contato contato;
    while (true)
    {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end")
        {
            break;
        }
        else if (cmd == "init")
        {
            string name;
            ss >> name;
            contato = Contato(name);
        }
        else if (cmd == "add")
        {
            string id;
            string number;
            ss >> id >> number;
            contato.addFone(id, number);
        }
        else if (cmd == "rm")
        {
            int index{};
            ss >> index;
            contato.apagar(index);
        }
        else if (cmd == "tfav")
        {
            contato.favoritar();
        }
        else if (cmd == "show")
        {
            cout << contato.toString() << endl;
        }
        else
        {
            cout << "fail: comando invalido" << endl;
        }
    }
}
