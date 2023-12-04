//
// Created by laure on 22.11.2023.
//

#include "SaleStatistic.h"
#include <string>

SaleStatistic::SaleStatistic(const std::string &input) {

    std::string strings[14];
    for (int i = 0; i < 13; ++i) {
        strings[i] = "";
    }
    int i = 0;
    for (char c: input) {
        if (c == ',') {
            i++;
        } else {
            strings[i] += c;
        }
    }
    this->region = new std::string(strings[0]);
    this->country = new std::string(strings[1]);
    this->itemType = new std::string(strings[2]);
    this->SalesChannel = new std::string(strings[3]);
    this->Priority = new char(strings[4][0]);;
    this->OrderDate = stringToTm(strings[5]);
    this->orderID = new int(stoi(strings[6]));
    this->shippDAte = stringToTm(strings[7]);
    this->UnitsSold = new int(stoi(strings[8]));
    this->UnitPrice = new double(stod(strings[9]));
    this->UnitCost = new double(stod(strings[10]));
    this->TotalRevenue = new double(stod(strings[11]));
    this->TotalCost = new double(stod(strings[12]));
    this->TotalProfit = new double(stod(strings[13]));

}

void SaleStatistic::printStatistic() {
    std::cout << " , " << *region
              << " , " << *country
              << " , " << *itemType
              << " , " << *SalesChannel
              << " , " << *Priority
              << " , " << (*OrderDate).tm_mday << '/' << (*OrderDate).tm_mon << '/' << (*OrderDate).tm_year
              << " , " << *orderID
              << " , " << (*shippDAte).tm_mday << '/' << (*shippDAte).tm_mon << '/' << (*shippDAte).tm_year
              << " , " << *UnitsSold
              << " , " << *UnitPrice
              << " , " << *UnitCost
              << " , " << *TotalRevenue
              << " , " << *TotalCost
              << " , " << *TotalProfit << std::endl;
}

SaleStatistic::~SaleStatistic() {
    delete region;
    delete country;
    delete itemType;
    delete SalesChannel;
    delete Priority;
    delete OrderDate;
    delete orderID;
    delete shippDAte;
    delete UnitsSold;
    delete UnitPrice;
    delete UnitCost;
    delete TotalRevenue;
    delete TotalCost;
    delete TotalProfit;
}


tm *SaleStatistic::stringToTm(std::string input) {
    //6/27/2010
    int day = 0;
    int month = 0;
    int year = 0;
    int currentInt = 0;
    for (char c: input) {
        if (isspace(c)) {
            continue;
        } else if (isdigit(c)) {
            currentInt = currentInt * 10;
            currentInt = currentInt + (c - '0');
        } else if (c == '/') {
            if (day == 0) {
                day = currentInt;
            } else if (month == 0) {
                month = currentInt;
            }
            currentInt = 0;
        }
    }
    year = currentInt;
    tm t;
    t.tm_mday = day;
    t.tm_mon = month;
    t.tm_year = year;
    return new tm(t);

}


