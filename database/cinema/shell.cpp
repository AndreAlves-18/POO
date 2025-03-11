#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
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

class Cliente {
public:
    string id;
    string telefone;
    Cliente(string id = "", string telefone = "") : id(id), telefone(telefone) {}
};

class Sala {
public:
    vector<shared_ptr<Cliente>> cadeiras;
    Sala(int qtd = 0) {
        for (int i = 0; i < qtd; i++) {
            cadeiras.push_back(nullptr);
        }
    }
    string toString() {
        vector<string> str;
        for (auto cliente : cadeiras) {
            if (cliente == nullptr) {
                str.push_back("-");
            } else {
                str.push_back(cliente->id + ":" + cliente->telefone);
            }
        }
        return "[" + map_join(str, [](string s) { return s; }, " ") + "]";
    }
    void reserva(string id, string telefone, int index) {
        if (index < 0 || index >= (int) cadeiras.size()) {
            cout << "fail: cadeira nao existe" << endl;
            return;
        }
        if (cadeiras[index] != nullptr) {
            cout << "fail: cadeira ja esta ocupada" << endl;
            return;
        }
        for (auto cliente : cadeiras) {
            if (cliente != nullptr && cliente->id == id) {
                cout << "fail: cliente ja esta no cinema" << endl;
                return;
            }
        }
        cadeiras[index] = make_shared<Cliente>(id, telefone);
    }
    void cancelar(string id) {
        for (int i = 0; i < (int) cadeiras.size(); i++) {
            if (cadeiras[i] != nullptr && cadeiras[i]->id == id) {
                cadeiras[i] = nullptr;
                return;
            }
        }
        cout << "fail: cliente nao esta no cinema" << endl;
    }
};


int main() {
    Sala sala;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;    
        } else if (cmd == "show") {
            cout << sala.toString() << endl;
        } else if (cmd == "init") {
            int qtd;
            ss >> qtd;
            sala = Sala(qtd);
        } else if (cmd == "reserve") {
            string id, phone;
            int index;
            ss >> id >> phone >> index;
            sala.reserva(id, phone, index);
        } else if (cmd == "cancel") {
            string id;
            ss >> id;
            sala.cancelar(id);
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
