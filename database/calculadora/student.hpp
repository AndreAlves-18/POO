#pragma once
#include "fn.hpp"

struct Calculadora{
    int bateria;
    int bateriaMax;
    float display;
    
    Calculadora(int qtd){
        this->bateria = 0;
        this->bateriaMax = qtd;
        this->display = 0;
    }
    std::string toString(){
        return fn::format("display = {%.2f}, battery = {}", display, bateria);
    }
    void carrega_bateria(int qtd){
        if((bateria + qtd) > bateriaMax){
            this->bateria = bateriaMax;
            return;
        }
        this->bateria += qtd;
    }
    void sum(int a, int b){
        if(bateria > 0){
            display = a + b;
            bateria--;
            return;
        }
        std::cout << "fail: bateria insuficiente\n";
    }
    void div(float a, float b){
        if(b == 0){
            std::cout << "fail: divisao por zero\n";
            bateria--;
            return;
        }
        if(bateria > 0){
            display = a / b;
            bateria--;
            return;
        }
        std::cout << "fail: bateria insuficiente\n";
    }
};


class Student {
    Calculadora c;
public:
    Student() : c(0){
    }
    void show() {
        std::cout << c.toString() << std::endl;
    }
    void init(int batteryMax) {
        c = Calculadora(batteryMax);
       // (void) batteryMax;
    }
    void charge(int value) {
         c.carrega_bateria(value);
        // // ACT!
        //(void) value;
    }
    void sum(int a, int b) {
         c.sum(a, b);
        // // ACT!
        //  (void) a;
        //  (void) b;
    }
    void div(int num, int den) {
        c.div(num, den);
        // // ACT!
        //  (void) num;
        //  (void) den;
    }
};