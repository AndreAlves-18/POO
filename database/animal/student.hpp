#pragma once
#include "fn.hpp"

struct Animal{
    int idade;
    std::string especie;
    std::string barulho;

    Animal(std::string especie = "", std::string barrulho = ""){
        this-> especie = especie;
        this->barulho = barrulho;
        this-> idade = 0;
    }
    std::string str() const{
        return fn::format("{}:{}:{}", especie, idade, barulho);
    }
    void envelhecer(int qtd){
        this->idade += qtd;
        if( idade >= 4){
            fn::print("warning: {} morreu\n", especie);
            idade = 4;
        }
    }
    std::string fazerBarulho() const{
        if (idade == 0){
            return "---";
        }
        if (idade == 4){
            return "RIP";
        }
        return this->barulho;
    }
};

struct Student {
    Animal animal;
    Student(std::string especie = "", std::string barulho = "") {
        //ACT
        (void) especie;
        (void) barulho;
        animal = Animal(especie, barulho);
    }

    void grow(int idade) {
        (void) idade;
        animal.envelhecer(idade);
    }

    void noise() {
       
        std::cout << animal.fazerBarulho() << std::endl;
    }

    void show() {
       
        std::cout << animal.str() << std::endl;
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

