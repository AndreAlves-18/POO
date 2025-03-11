#include "fn.hpp"

struct Car{
    int pass;
    int passMax;
    int gas;
    int gasMas;
    int Km;

    Car (){
        pass = 0;
        passMax = 2;
        gas = 0;
        gasMas = 100;
        Km = 0;
    }
    void enter(){
        if(pass < passMax){
            pass++;
            return;
        }
        fn::print("fail: limite de pessoas atingido\n");
        return;
    }
    void leave(){
        if(pass > 0){
            pass--;
            return;
        }
        fn::print("fail: nao ha ninguem no carro\n");
        return;
    }
    void fuel(int qtd){
        if((qtd + gas) > 100){
            gas = 100;
            return;
        }
        gas += qtd;
    }
    void drive(int qtd){
        bool aux = true;
        if(pass == 0){
            fn::print("fail: nao ha ninguem no carro\n");
            return;
        }
        if(gas == 0){
            fn::print("fail: tanque vazio\n");
            return;
        }
        if((gas - qtd) > 0){
            gas -= qtd;
            aux = false;
        }
        if(qtd <= gas){
            Km += qtd;
        }
        
        if(qtd > gas){
            Km += gas;
            fn::print("fail: tanque vazio apos andar {} km\n", gas);
            gas = 0;
            return;
        }
        if(((gas - qtd) <= 0) && aux){
            gas = 0;
        }
    }
    std::string toString(){
        return fn::format("pass: {}, gas: {}, km: {}", pass, gas, Km);
    }
};

struct Student {
    Car car;
    Student() {}

    void enter() {
        car.enter();
    }
    void leave() {
        car.leave();
    }
    void fuel(int q) {
        car.fuel(q);
        (void) q;
    }
    void drive(int q) {
        car.drive(q);
        (void) q;
    }
    void show() {
        std::cout << car.toString() << std::endl;
    }
};

struct Debug {
    // Se a variável debug for true, os testes não serão executados
    // Apenas o conteúdo do método run() será executado
    // Você pode usar isso para testar seu código manualmente
    static const bool debug = false;
    static void run() {
        std::cout << "Debug ativado" << std::endl;
    }
};
