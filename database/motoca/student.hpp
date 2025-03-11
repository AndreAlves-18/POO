#pragma once
#include <iostream>
#include <memory>
#include "fn.hpp"

class Pessoa{
    std::string nome{};
    int idade{0};
public:
    Pessoa(std::string nome = "", int idade = 0): nome(nome), idade(idade) {}
    std::string GetNome(){
        return this->nome;
    }
    int getidade(){
        return this->idade;
    }
    std::string str() const{
        return fn::format("{}:{}", this->nome, this->idade);
    }
};

class Motoca{
    int power{0};
    int time{0};
    std::shared_ptr<Pessoa> pessoa {nullptr};
public:
    Motoca(int power = 1): power(power){}

    void insert(std::shared_ptr<Pessoa> pessoa){
        if(this->pessoa == nullptr){
            this->pessoa = pessoa;
            return;
        }
        fn::write("fail: busy motorcycle");
    }
    void addtime(int valor){
        this->time += valor;
    }
    void dirigir(int valor){
        if(time == 0){
            fn::write("fail: buy time first");
            return;
        }
        if(valor > this->time){
            fn::print("fail: time finished after {} minutes\n", time);
            time = 0;
            return;
        }
        if(pessoa == nullptr){
            fn::write("fail: empty motorcycle");
            return;
        }
        if(this->pessoa->getidade() > 10){
            fn::write("fail: too old to drive");
            return;
        }
        this->time -= valor;
    }
    std::string pem() const{
        std::string som = "P";
        for(int i = 0; i < power; i++){
            som += "e";
        }
        return som += "m";
    }
    std::shared_ptr<Pessoa> remove (){
        if(pessoa == nullptr){
            fn::write("fail: empty motorcycle");
        }
        auto aux = this->pessoa;
        this->pessoa = nullptr;
        return aux;
    }
    std::string str() const{
        if(pessoa != nullptr){
            return fn::format("power:{}, time:{}, person:({})", this->power, this->time, pessoa->str());

        }
        return fn::format("power:{}, time:{}, person:(empty)", this->power, this->time);
    }
};




class Student {
    Motoca motoca;
public:

    void init(int power = 1) {
        (void) power;
        motoca = Motoca(power);
    }

    void enter(std::string name, int age) {
        (void) name;
        (void) age;
        auto person = std::make_shared<Pessoa>(name, age);
        motoca.insert(person);
    }

    void leave() {
        auto person = motoca.remove();
        fn::write(person == nullptr ? "---" : person->str());
    }

    void honk() const {
        fn::write(motoca.pem());
    }

    void buy(int time) {
        (void) time;
        motoca.addtime(time);
    }

    void drive(int time) {
        (void) time;
        motoca.dirigir(time);
    }

    void show() const {
        fn::write(motoca.str());
    }
};