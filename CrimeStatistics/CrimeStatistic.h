//
// Created by laure on 22.11.2023.
//

#ifndef UNTITLED_CRIMESTATISTIC_H
#define UNTITLED_CRIMESTATISTIC_H


#include <string>
#include <iostream>

class CrimeStatistic {
public:
    std::string* datetime;
    std::string* adress;
    std::string* district;
    std::string* beat;
    std::string* grod;
    std::string* crimedescr;
    std::string* ucr_ncic_code;
    std::string* latitute;
    std::string* longitute;
public:
    void print();
    CrimeStatistic(std::string);
    virtual ~CrimeStatistic();
};

#endif //UNTITLED_CRIMESTATISTIC_H
