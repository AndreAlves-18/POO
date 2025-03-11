#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <memory>

using namespace std;

class Veiculo {
protected:
    string id;
    string tipo;
    int horaEntrada;
public:
    Veiculo(string id = "0", string tipo = "null") :id(id), tipo(tipo){}
    void setEntrada(int horaEntrada) {
        this->horaEntrada = horaEntrada;
    }
    int getHoraEntrada() {
        return horaEntrada;
    }
    string getId() {
        return id;
    }
    string getTipo() {
        if(tipo == "bike"){
            return "Bike";
        }else if(tipo == "moto"){
            return "Moto";
        }else if(tipo == "carro"){
            return "Carro";
        }
        return "null";
    }
    virtual void cacularValor(int horaSaida) = 0;

    string toString(){
        std::stringstream ss;
        ss << std::setw(10) << std::setfill('_') << getTipo() << " : " 
           << std::setw(10) << std::setfill('_') << id << " : " 
           << horaEntrada;
        return ss.str();
    }
};

class Bike : public Veiculo {
    string id;
public:
    Bike(string id, string tipo) : Veiculo(id, tipo) {}
    virtual void cacularValor(int horaSaida) {
        (void)horaSaida;
        cout << "3.00";
    }
};

class Moto : public Veiculo {
    string id;
public:
    Moto(string id, string tipo) : Veiculo(id, tipo) {}
    virtual void cacularValor(int horaSaida) {
        //deixe com 2 casas decimais
        float aux = (horaSaida - horaEntrada)/20;
        cout << fixed << setprecision(2) << aux;
    }
};

class Carro : public Veiculo {
    string id;
public:
    Carro(string id, string tipo) : Veiculo(id, tipo) {}
    virtual void cacularValor(int horaSaida) {
        float aux = (horaSaida - horaEntrada)/10 >= 5 ? (horaSaida - horaEntrada)/10 : 5.0;
        cout << fixed << setprecision(2) << aux;    }
};

class Estacionamento {
    vector<Veiculo*> veiculos;
    int horaAtual {0};
public: 
    Estacionamento(int horaAtual = 0): horaAtual(horaAtual){}
    void estacionar(string tipo, string id) {
        if (tipo == "bike") {
            veiculos.push_back(new Bike(id, tipo));
        } else if (tipo == "moto") {
            veiculos.push_back(new Moto(id, tipo));
        } else if (tipo == "carro") {
            veiculos.push_back(new Carro(id, tipo));
        }
        veiculos.back()->setEntrada(horaAtual);
    }
    void PassarTempo(int tempo) {
        horaAtual += tempo;
    }
    void pagar(string id) {
        for (auto veiculo : veiculos) {
            if (veiculo->getId() == id) {
                
                cout << veiculo->getTipo() << " chegou " << to_string(veiculo->getHoraEntrada()) << 
                 " saiu "  << to_string(horaAtual) << ". Pagar R$ ";
                veiculo->cacularValor(horaAtual);
                cout << endl;
                return;
            }
        }
        cout << "fail: veiculo nao encontrado" << endl;
    }
    string str() {
        stringstream ss;
        for (auto veiculo : veiculos) {
            ss << veiculo->toString() << endl;
        }
        ss << "Hora atual: " << horaAtual;
        return ss.str();
    }
};


int main() {
    Estacionamento estacionamento;
    while (true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << endl;

        stringstream ss(line);
        ss >> cmd;

        if (cmd == "end") {
            break;
        } else if (cmd == "show") {
            cout << estacionamento.str() << endl;
        } else if (cmd == "estacionar") {
            string tipo, id;
            ss >> tipo >> id;
            estacionamento.estacionar(tipo, id);
        } else if (cmd == "tempo") {
            int tempo {};
            ss >> tempo;
            estacionamento.PassarTempo(tempo);
        } else if (cmd == "pagar") {
            string id;
            ss >> id;
            estacionamento.pagar(id);
        } else {
            cout << "fail: comando invalido" << endl;
        }
    }
}
