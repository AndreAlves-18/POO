#include <iostream>
#include <sstream>
#include <memory>

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
             std::cout <<"Bateria cheia.\n";
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
            std::cout <<"Bateria Descarregada após : " << carga <<"\n";
            carga = 0;

            return;
        }
        carga -= valor;
    }
    std::string str(){
        std::stringstream ss;
        ss << "(" << carga << "/" << capacidade << ")";
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
        ss << "(Potencia " << potencia << ")";
        return ss.str();
    }
};

class Notebook{
    bool ligado = false;
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
            std::cout << "Notebook sem bateria e sem carregador.\n";
            return;
        }
        if(bateria != nullptr && bateria->getCarga() == 0){
            std::cout << "Bateria descarregada.\n";
            return;
        }
        std::cout << "Ligando\n";
        this->ligado = true;
    }
    void desligar(){
        if(this->ligado == false){
            std::cout << "Já está desligado\n";
            return;
        }
        std::cout << "Desligando\n";
        this->ligado = false;
    }
    void str(){
        if(this->ligado){
            if( bateria == nullptr && carregador == nullptr){
                std::cout << "Status: Ligado, Bateria: Nenhuma, Carregador: Desconectado\n";
                return;
            }
            if(bateria == nullptr){
                std::cout << "Status: Ligado, Bateria: Nenhuma, Carregador: " << carregador->str() <<'\n';
                return;
            }
            if(carregador == nullptr){
                std::cout << "Status: Ligado, Bateria: " << bateria->str() << ", Carregador: Desconectado\n";
                return;
            }
            std::cout << "Status: Ligado, Bateria: " << bateria->str() << ", Carregador: "  << carregador->str() <<'\n';
            return;
        }
        if(bateria == nullptr && carregador == nullptr){
            std::cout << "Status: Desligado, Bateria: Nenhuma, Carregador: Desconectado\n";
            return;
        }
        if(bateria == nullptr){
            std::cout << "Status: Desligado, Bateria: Nenhuma, Carregador: " << carregador->str() <<'\n';            
            return;
        }
        std::cout << "Status: Desligado, Bateria: " << bateria->str() << ", Carregador: Desconectado\n";
        return;
    }
    void usar(int valor){
        if(!this->ligado){
            std::cout <<"Ligue o notebook primeiro\n";
            return;
        }

        if(carregador == nullptr){
            if(valor >= bateria->getCarga()){
                ligado = false;
                bateria->descarregar(valor);
                return;
            }

            std::cout << "Usando por " << valor << " minutos\n";
            bateria->descarregar(valor);
            return;
        }
        
        if((valor * carregador->getPotencia()) >= (bateria->getCapacidade() - bateria->getCarga())){
            bateria->setCarga(bateria->getCapacidade());
            std::cout << "Bateria carregada em uso.\n";
            return;
        }
        bateria->setCarga(valor * carregador->getPotencia());
    }
    void setBateria(std::shared_ptr<Bateria> bat){
        bateria = bat;
    }
    void rmBateria(){
        bateria = nullptr;
        std::cout << "bateria removida\n";
        if (carregador == nullptr) {
            if (ligado) {
                ligado = false;
                std::cout << "Desligando\n";
            }
        }
    }
    void setCarregador(std::shared_ptr<Carregador> car){
        if(carregador != nullptr){
            std::cout << "Carregador já conectado\n";
            return;
        }
        carregador = car;
    }
    void rmCarregador(){
        carregador = nullptr;
        std::cout << "carregador removido\n";
        if (bateria == nullptr) {
            if (ligado) {
                ligado = false;
                std::cout << "Desligando\n";
            }
        }
    }
};
int main() {
    Notebook notebook;
    notebook.str();
    notebook.ligar();
    notebook.usar(10);
    
    std::cout << '\n';

    auto bateria = std::make_shared<Bateria>(50);
    std::cout << bateria->str() << '\n';
    notebook.setBateria(bateria);

    std::cout << '\n';

    notebook.str();
    notebook.ligar();
    notebook.str();
    notebook.usar(30);
    notebook.str();
    notebook.usar(30);
    notebook.str();
    
    std::cout << '\n';

    notebook.rmBateria();
    std::cout << bateria->str() << "\n";
    notebook.str();

    std::cout << '\n';

    auto carregador = std::make_shared<Carregador>(2);
    std::cout << carregador->str() << '\n';

    std::cout << '\n';

    notebook.setCarregador(carregador);
    notebook.str();
    notebook.ligar();
    notebook.str();

    std::cout << '\n';

    notebook.setBateria(bateria);
    notebook.str();
    notebook.usar(10);
    notebook.str();
    
}
