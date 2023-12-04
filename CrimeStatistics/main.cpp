#include <iostream>
#include <vector>
#include <fstream>
#include "CrimeStatistic.h"

void loadStatistics(std::vector<CrimeStatistic*>* vector1);

void outWerten(std::vector<CrimeStatistic*>* vector1);

void howmany(std::vector<CrimeStatistic*>* vector1);

void mostPopularCrime(std::vector<CrimeStatistic*>* vector1);

void lawlessDistrict(std::vector<CrimeStatistic*>* vector1);

void multipleAdresses(std::vector<CrimeStatistic*>* vector1);

bool isEmptyOrWhitespace(std::string basicString);

//int main() {
//    std::vector<CrimeStatistic*> statistics;
//    loadStatistics(&statistics);
//    outWerten(&statistics);
//    for (CrimeStatistic* c: statistics) {
//        delete (c);
//    }
//    return 0;
//}

void outWerten(std::vector<CrimeStatistic*>* vector1) {
    howmany(vector1);
    mostPopularCrime(vector1);
    lawlessDistrict(vector1);
    multipleAdresses(vector1);
}

void multipleAdresses(std::vector<CrimeStatistic*>* vector1) {
    std::string previousAdresses;
    std::string doubleTrouble;
    for (CrimeStatistic* c: *vector1) {
        std::string adresse(*c->adress);
        if (previousAdresses.find(adresse) != std::string::npos) {
            doubleTrouble.append(adresse);
            doubleTrouble.append("  ");
        }
        previousAdresses.append(adresse);
        previousAdresses.append(" ; ; ");
    }
    std::cout << "I wish I could commit a crime here again: " << doubleTrouble << "\n";
}

struct thingsCounting {
    thingsCounting(std::string basicString, int i);

    std::string thing;
    int count;
};

thingsCounting::thingsCounting(std::string basicString, int i) {
    this->thing = basicString;
    this->count = i;
}

void lawlessDistrict(std::vector<CrimeStatistic*>* vector1) {
    std::vector<thingsCounting*> districts;
    for (CrimeStatistic* c: *vector1) {
        bool waspresent = false;
        for (thingsCounting* d: districts) {
            if (*c->district == d->thing) {
                d->count++;
                waspresent = true;
                break;
            }
        }
        if (!waspresent) {
            districts.push_back(new thingsCounting(*c->district, 1));
        }
    }
    int max = 0;
    std::vector<std::string> maxCrimeDistricts;
    for (thingsCounting* d: districts) {
        if (d->count > max) {
            max = d->count;
            maxCrimeDistricts.clear();
            maxCrimeDistricts.push_back(d->thing);
        } else if (d->count == max) {
            maxCrimeDistricts.push_back(d->thing);
        }
    }
    std::cout << "come visit these districts: ";
    for (std::string district: maxCrimeDistricts) {
        std::cout << district << " ; ";
    }
    std::cout << "\n";
    for (thingsCounting* t: districts) {
        delete (t);
    }
}

void mostPopularCrime(std::vector<CrimeStatistic*>* vector1) {
    std::vector<thingsCounting*> crimes;
    for (CrimeStatistic* c: *vector1) {
        bool waspresent = false;
        for (thingsCounting* d: crimes) {
            if (*c->crimedescr == d->thing) {
                d->count++;
                waspresent = true;
                break;
            }
        }
        if (!waspresent) {
            crimes.push_back(new thingsCounting(*c->crimedescr, 1));
        }
    }
    int max = 0;
    std::vector<std::string> maxNumberCrime;
    for (thingsCounting* d: crimes) {
        if (d->count > max) {
            max = d->count;
            maxNumberCrime.clear();
            maxNumberCrime.push_back(d->thing);
        } else if (d->count == max) {
            maxNumberCrime.push_back(d->thing);
        }
    }
    std::cout << "most popular crime: ";
    for (std::string district: maxNumberCrime) {
        std::cout << district << " ; ";
    }
    std::cout << "\n";
    for (thingsCounting* t: crimes) {
        delete (t);
    }
}

void howmany(std::vector<CrimeStatistic*>* vector1) {
    int total = 0;
    for (CrimeStatistic* c: *vector1) {
        total++;
    }
    std::cout << "total silly things in town: " << total;
    std::cout << "\n";
}

void loadStatistics(std::vector<CrimeStatistic*>* vector1) {
    bool firstline = true;
    std::string line;
    std::ifstream file("../ActuallyWorking.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (isEmptyOrWhitespace(line)) {
                continue;
            }
            if (firstline) {
                firstline = false;
                continue;
            }
            vector1->push_back(new CrimeStatistic(line));
        }
        file.close();
    } else {
        std::cout << "Error opening the file." << std::endl;
    }
}

bool isEmptyOrWhitespace(std::string basicString) {
    for (char c: basicString) {
        if (!(isspace(c) || isblank(c))) {
            return false;
        }
    }
    return true;
}
