#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "fn.hpp"

class Grafite{
    float G_calibre {0};
    std::string dureza;
    int tamanho {0};
public:
    Grafite(float calibre = 0, std::string dureza = "", int tamanho = 0):G_calibre(calibre), dureza(dureza), tamanho(tamanho){}
    std::string str(){
        return fn::format("[{}:{}:{}]", G_calibre, dureza, tamanho);
    }
    float GetCalibre(){
        return this->G_calibre;
    }
    std::string GetDureza (){
        return this->dureza;
    }
    int GetTamanho(){
        return this->tamanho;
    }
    void SetDureza(std::string valor){
        this->dureza = valor;
    }
    void SetTamanho(int valor){
        this->tamanho = valor;
    }
    void SetTamanhoSub(int valor){
        this->tamanho -= valor;
    }
    void SetCalibre(float valor){
        this->G_calibre = valor;
    }
    int gasto(){
        if(dureza[0] == 'H'){
            return 1;
        }
        if(dureza[0] == '2'){
            return 2;
        }
        if(dureza[0] == '4'){
            return 4;
        }
        if(dureza[0] == '6'){
            return 6;
        }
        return 0;
    }
};

class Lapiseira{
    float L_calibre {0};
    std::shared_ptr<Grafite> grafite {nullptr};
public:
    Lapiseira(float calibre = 0.5): L_calibre(calibre){
        this->L_calibre = calibre;
    }
    std::string str(){
        if (grafite == nullptr){
            return fn::format("calibre: {}, grafite: null", L_calibre);
        }
        return fn::format("calibre: {}, grafite: {}", L_calibre, grafite->str());
    }
    void inserir(std::shared_ptr<Grafite>  grafitee ){
        if(L_calibre != grafitee->GetCalibre()){
            fn::write("fail: calibre incompativel");
            return;
        }
        if(grafite != nullptr){
            fn::write("fail: ja existe grafite");
            return;
        }
        grafite = grafitee;
    }
    void remove(){
        grafite = nullptr;
        return;
    }
    void escrever(){
        if(grafite == nullptr){
            fn::write("fail: nao existe grafite");
            return;
        }
        if(grafite->GetTamanho() <= 10){
            fn::write("fail: tamanho insuficiente");
            return;
        }
        if((grafite->GetTamanho() - 10) < grafite->gasto()){
            fn::write("fail: folha incompleta");
            grafite->SetTamanho(10);
            return;
        }
        if(grafite->GetTamanho() > 10){
            grafite->SetTamanhoSub(grafite->gasto());
            return;
        }
        
    }
};

class Student {
private:
    Lapiseira lapiseira;
public:
    Student(float thickness): lapiseira(thickness){
        (void) thickness;
    };
    
    void insert(float thickness, std::string hardness, int length) {
        (void) thickness;
        (void) hardness;
        (void) length;
        lapiseira.inserir(std::make_shared<Grafite>(thickness, hardness, length));
    }

    void remove() {
        lapiseira.remove();
    }

    void writePage() {
        lapiseira.escrever();
    }


    void show() {
        fn::write(lapiseira.str());
    }
};
