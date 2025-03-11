#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

class Conta{
    int id;
    int saldo;
public:
    Conta(int id = 0): id(id){ saldo = 0; }
    void deposito(int value){
        if(value < 0){
            cout << "fail: invalid value\n";
            return;
        }
        saldo += value;
    }
    void saque(int value){
        if(value < 0){
            cout << "fail: invalid value\n";
            return;
        }
        if(saldo < value){
            cout << "fail: insufficient balance\n";
            return;
        }
        saldo -= value;
    }
    void taxa(int value){
        if(value < 0){
            cout << "fail: invalid value\n";
            return;
        }
        saldo -= value;
    }
    string toString(){
        stringstream ss;
        ss << "account:" << id << " balance:" << saldo /*<< " saldo:" << fixed << setprecision(2) << saldo*/;
        return ss.str();
    }
};

template<typename CONTAINER, typename FUNC>
string join(const CONTAINER& cont, FUNC func, const string& delim) {
    stringstream ss;
    for (auto it = cont.begin(); it != cont.end(); it++) {
        ss << (it == cont.begin() ? "" : delim) << func(*it);
    }
    return ss.str();
}

int main() {
    Conta conta;
    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        
        if (cmd == "end") {
            break;
        }
        else if (cmd == "init") {
            int number{};
            ss >> number;
            conta = Conta(number);
        }
        else if (cmd == "show") {
            // TODO
            cout << conta.toString() << endl;
        }
        else if (cmd == "deposit") {
            float value{};
            ss >> value;
            conta.deposito(value);
        }
        else if (cmd == "withdraw") {
            float value{};
            ss >> value;
            conta.saque(value);
        }
        else if (cmd == "fee") {
            float value{};
            ss >> value;
            conta.taxa(value);
        }
        else if (cmd == "extract") {
            // int qtd{};
            // ss >> qtd;
            // cout << conta.extrato(qtd) << endl;
        }
        else if (cmd == "reverse") {
            // int index{};
            // while(ss >> index) {
            // }
        }
        else {
            cout << "fail: invalid command\n";
        }
    }
    return 0;
}
