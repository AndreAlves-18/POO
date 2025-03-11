#include <iostream>
#include <sstream>
#include <memory>
#include <utility>
using namespace std;

class Bateria{
    int capacidade {0};
    int carga {0};
public:
    Bateria(int cap = 0): capacidade(cap), carga(cap){}

    int getCarga(){
        return this->carga;
    }
    int getCapacidade(){
        return this->capacidade;
    }
    void setCarga(int valor){
        if(valor < 0){
            std::cout <<"Valor invalido de carga.\n";
            return;
        }
        if((valor + carga) >= capacidade){
            carga = capacidade;
            return;
        }
        carga += valor;
    }
    void descarregar(int valor){
        if(valor < 0){
            std::cout <<"Valor invalido de uso.\n";
            return;
        }
        if(valor >= carga){
            std::cout <<"fail: descarregou\n";
            carga = 0;

            return;
        }
        carga -= valor;
    }
    std::string str(){
        std::stringstream ss;
        ss << carga << "/" << capacidade;
        return ss.str();
    }
};

class Carregador{
    int potencia{0};
public:
    Carregador (int valor = 0): potencia(valor){}
    int getPotencia(){
        return this->potencia;
    }
    void setPotencia(int valor){
        this->potencia = valor;
    }
    std::string str(){
        std::stringstream ss;
        ss << potencia << "W";
        return ss.str();
    }
};

class Notebook{
    bool ligado = false;
    int uso = 0;
    std::shared_ptr<Bateria> bateria {nullptr};
    std::shared_ptr<Carregador> carregador {nullptr};
public:
    Notebook(bool lig = false): ligado(lig){}
    bool estaligado(){
        return this->ligado;
    }
    void ligar(){
        if(this->ligado){
            std::cout << "Já está ligado\n";
            return;
        }
        if( bateria == nullptr && carregador == nullptr){
            std::cout << "fail: não foi possível ligar\n";
            return;
        }
        if(bateria != nullptr && bateria->getCarga() == 0){
            std::cout << "Bateria descarregada.\n";
            return;
        }
        this->ligado = true;
    }
    void desligar(){
        if(this->ligado == false){
            std::cout << "Já está desligado\n";
            return;
        }
        this->ligado = false;
    }
    void str(){
        if(this->ligado){
            if( bateria == nullptr && carregador == nullptr){
                std::cout << "Notebook: desligado\n";
                return;
            }
            if(bateria == nullptr){
                std::cout << "Notebook: ligado por " << uso << " min, Carregador " << carregador->str() <<'\n';
                return;
            }
            if(carregador == nullptr){
                std::cout << "Notebook: ligado por " << uso << " min, Bateria " << bateria->str() <<'\n';
                return;
            }
            std::cout << "Notebook: ligado por " << uso << " min, Carregador "  << carregador->str() << ", Bateria " << bateria->str() <<'\n';
            return;
        }
        if(bateria == nullptr && carregador == nullptr){
            std::cout << "Notebook: desligado\n";
            return;
        }
        if(bateria == nullptr){
            std::cout << "Notebook: desligado, Carregador " << carregador->str() <<'\n';            
            return;
        }
        std::cout << "Notebook: desligado, Bateria " << bateria->str()  <<'\n';
        return;
    }
    void usar(int valor){
        if(!this->ligado){
            std::cout <<"fail: desligado\n";
            return;
        }
        if (bateria == nullptr && carregador == nullptr) {
            std::cout << "fail: não há fonte de energia\n";
            ligado = false;
            return;
        }

        if(carregador == nullptr){
            if(valor >= bateria->getCarga()){
                if (bateria != nullptr) {
                    bateria->descarregar(bateria->getCarga());
                     uso += bateria->getCarga();
                }
                ligado = false;
                return;
            }
            bateria->descarregar(valor);
            uso += valor;
            return;
        }
        
        if (bateria != nullptr) {
            
            int cargaPossivel = valor * carregador->getPotencia();
            if (cargaPossivel >= (bateria->getCapacidade() - bateria->getCarga())) {
                bateria->setCarga(bateria->getCapacidade());
                uso += valor;
                return;
            }
            bateria->setCarga(cargaPossivel);
            uso += valor;
        } else {
            uso += valor;
        }


    }
    void setBateria(std::shared_ptr<Bateria> bat){
        bateria = bat;
    }
    void rmBateria(){
        if(bateria == nullptr){
            std::cout << "fail: Sem bateria\n";
            return;
        }
        std::cout << "Removido " << bateria->str() << "\n";
        bateria = nullptr;
    
        if (carregador == nullptr) {
            if (ligado) {
                ligado = false;
                
            }
        }
    }
    void setCarregador(std::shared_ptr<Carregador> car){
        if(carregador != nullptr){
            std::cout << "fail: carregador já conectado\n";
            return;
        }
        carregador = car;
    }
    void rmCarregador(){
        if(carregador == nullptr){
            std::cout << "fail: Sem carregador\n";
            return;
        }
        std::cout << "Removido " << carregador->str() << "\n";
        carregador = nullptr;
        if (bateria == nullptr) {
            if (ligado) {
                ligado = false;
            }
        }
    }
};


int main() {
    Notebook notebook;
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
            notebook.str();
        } 
        else if (cmd == "turn_on") {
            notebook.ligar();
        }
        else if (cmd == "turn_off") { 
            notebook.desligar();
        } 
        else if (cmd == "use") { 
            int minutes;
            ss >> minutes;
            notebook.usar(minutes);
        } 
        else if (cmd == "set_charger") {
            // CRIE UM OBJETO Charger E ATRIBUA AO NOTEBOOK
            int power;
            ss >> power;
            auto carregador = std::make_shared<Carregador>(power);
            notebook.setCarregador(carregador);
        } 
        else if (cmd == "rm_charger") {
            // REMOVA O CARREGADOR DO NOTEBOOK E IMPRIMA SE ELE EXISTIR
            notebook.rmCarregador();
            
        } 
        else if (cmd == "set_battery") {
            // CRIE UM OBJETO Bateria E ATRIBUA AO NOTEBOOK
            int capacity;
            ss >> capacity;
            auto bateria = std::make_shared<Bateria>(capacity);
            notebook.setBateria(bateria);
        } 
        else if (cmd == "rm_battery") {
            // REMOVA A BATERIA DO NOTEBOOK E IMPRIMA SE ELA EXISTIR
            notebook.rmBateria();
        } 
        else {
            cout << "fail: comando inválido\n";
        }
    }    
}
