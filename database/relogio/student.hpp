#pragma once
#include "fn.hpp"

class Relogio {
    int hora;
    int min;
    int seg;
public:
    Relogio(int h = 0, int m = 0, int s = 0): hora(0), min(0), seg(0){
        this->SetHora(h);
        this->SetMin(m);
        this->SetSeg(s);
    }
    std::string ToString(){
        std::string saida = fn::format("{%02d}:{%02d}:{%02d}", hora, min, seg);
        return saida;
    }
    void SetHora(int value){
        if(value < 0 or value > 23){
            std::cout << "fail: hora invalida\n";
            return;
        }
        this->hora = value;
    }
    void SetMin(int value){
        if(value < 0 or value > 59){
            std::cout << "fail: minuto invalido\n";
            return;
        }
        this->min = value;
    }
    void SetSeg(int value){
        if(value < 0 or value > 59){
            std::cout << "fail: segundo invalido\n";
            return;
        }
        this->seg = value;
        
    }
    int GetHora() const{
        return this->hora;
    }
    int GetMin() const{
        return this->min;
    }
    int GetSeg() const{
        return this->seg;
    }
    void IncSeg (){
        if(seg >= 0 && seg < 59){
            seg++;
            return;
        }
        if(min >= 0 && min < 59){
            min++;
            seg = 0;
            return;
        }
        if(hora >= 0 && hora < 23){
            hora++;
            min = 0;
            seg = 0;
            return;
        }
        hora = 0;
        min = 0;
        seg = 0;
    }

};


class Student {
private:
    Relogio relogio;

public:
    void init(int hour = 0, int minute = 0, int second = 0) {
        (void) hour;
        (void) minute;
        (void) second;
        this->relogio = Relogio(hour, minute, second);
    }
    void setHour(int hour) {
        (void) hour;
         this->relogio.SetHora(hour);
    }

    void setMinute(int minute) {
        (void) minute;
        this->relogio.SetMin(minute);
    }
    void setSecond(int second) {
        (void) second;
        this->relogio.SetSeg(second);
    }

    void nextSecond() {
        this->relogio.IncSeg();
    }
    
    void show() {
        fn::write(relogio.ToString());
    }
};