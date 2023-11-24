//
// Created by laure on 22.11.2023.
//

#include "CrimeStatistic.h"
CrimeStatistic::CrimeStatistic(std::string input) {
    std::string strings[9];
    for (int i = 0; i < 9; ++i) {
        strings[i] = "";
    }
    int i = 0;
    for (char c: input) {
        if (c == ','){
            i++;
        } else{
            strings[i] += c;
        }
    }
    this->datetime = new std::string(strings[0]);
    this->adress = new std::string(strings[1]);
    this->district = new std::string(strings[2]);
    this->beat = new std::string(strings[3]);
    this->grod = new std::string(strings[4]);
    this->crimedescr = new std::string(strings[5]);
    this->ucr_ncic_code = new std::string(strings[6]);
    this->latitute = new std::string(strings[7]);
    this->longitute = new std::string(strings[8]);
}

void CrimeStatistic::print() {
    std::cout << "datetime: "<< *datetime << " thing: "<< *district <<" adress: "<< *adress <<" beat: "
              << *beat <<" grod: "<< *grod <<" crimedescr: "<< *crimedescr <<" ucr_ncic_code: "<< *ucr_ncic_code <<" latitute: "
              << *latitute <<" longitute: "<< *longitute << "\n";
}

CrimeStatistic::~CrimeStatistic() {
    delete[] datetime;
    delete[] district;
    delete[] adress;
    delete[] beat;
    delete[] grod;
    delete[] crimedescr;
    delete[] ucr_ncic_code;
    delete[] latitute;
    delete[] longitute;
}