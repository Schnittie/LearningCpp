//
// Created by laure on 22.11.2023.
//

#ifndef UNTITLED_CRIMESTATISTIC_H
#define UNTITLED_CRIMESTATISTIC_H


#include <string>
#include <iostream>
#include <ctime>
#include <string>

class SaleStatistic {
public:
    std::string* region;
    std::string* country;
    std::string* itemType;
    std::string* SalesChannel; //todo: make enum
    char* Priority; //todo: make enum
    tm* OrderDate;
    int* orderID;
    tm* shippDAte;
    int* UnitsSold;
    double * UnitPrice;
    double * UnitCost;
    double * TotalRevenue;
    double * TotalCost;
    double * TotalProfit;
public:
    explicit SaleStatistic(const std::string&);
    virtual ~SaleStatistic();
    void printStatistic();


    tm * stringToTm(std::string input);
};

#endif //UNTITLED_CRIMESTATISTIC_H
