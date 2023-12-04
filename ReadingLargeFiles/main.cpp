#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "SaleStatistic.h"

std::vector<SaleStatistic *> statistics;

void loadStatistics(std::vector<SaleStatistic *> *vector1);

bool isEmptyOrWhitespace(const std::string &basicString);

void profitsPer();

void profitsPerRegion();

void getProfitsPerRegion(const std::string &region);

void profitsPerCountry();

void profitsPerType();

void profitsPerChannel();

void getProfitsPerCountry(std::string basicString);

void getProfitsPerType(std::string basicString);

void getProfitsPerChannel(std::string basicString);

void itemTypePerRegion();

void itemPerRegionAbsolute(std::string type);

void itemPerRegionPercent(std::string basicString);

void favoritePerCountry();

void getFavoritePerCountry(std::string country);

void onlineByCountry();

void onlineByCountryAbsolute(std::string county);

void onlineByCountryPercent(std::string basicString);

int main() {
    loadStatistics(&statistics);
    //outWerten(&statistics);
    char des = 'd';
    while (des != 'e') {
        // Baue intelligente Datenstrukturen, um die Daten im Speicher zu halten
        //• Das System soll die folgenden Abfragen unterstützen und per Menü anbieten
        //• Total profit pro Region, Country, Item Type oder Sales Channel
        //• Wie oft wurde ein Item Type in den Regionen verkauft? Absolut und prozentual
        //• Welcher Item Type ist der beliebteste in Land X?
        //• Wie oft wurde in Land X Online oder Offline bestellt (insgesamt, prozentual)?
        //• Weitere nach Langeweile 😉
        //• Nutzt erstmal die Sample Datei mit 100 Einträgen und wechselt dann auf die mit 15.000.000 Einträgen
        std::cout << "\nso, what do you wanna do now:  \n e: end search \n 1: total profit per... " <<
                  "\n 2: item type per region .. \n 3: favorite Item type of country..." <<
                  "\n 4: how often were purchases from country ... online" << std::endl;
        std::cin.sync();
        std::cin >> des;
        switch (des) {
            case 'e':
                break;
            case '1':
                profitsPer();
                break;
            case '2':
                itemTypePerRegion();
                break;
            case '3':
                favoritePerCountry();
                break;
            case '4':
                onlineByCountry();
                break;
            default:
                std::cout << "\n waht";
        }
    }
    for (SaleStatistic *c: statistics) {
        delete (c);
    }
    return 0;
}

void onlineByCountry() {
//• Wie oft wurde in Land X Online oder Offline bestellt (insgesamt, prozentual)?
    std::string input;
    std::cout << "enter Country" << std::endl;
    std::cin.sync();
    std::cin >> input;
    input.erase(input.find_last_not_of(" \n\r\t") + 1);

    char des;
    std::cout << "1: Absolute  \n 2: Procentual" << std::endl;
    std::cin.sync();
    std::cin >> des;
    switch (des) {
        case '1':
            onlineByCountryAbsolute(input);
            break;
        case '2':
            onlineByCountryPercent(input);
            break;
        default:
            std::cout << "\n waht";
    }

}

void onlineByCountryPercent(std::string country) {
    int onlineItems = 0;
    int offlineItems = 0;
    double totalItems = 0;
    for (SaleStatistic *s: statistics) {
        if (*s->country != country) {
            continue;
        }
        totalItems += *s->UnitsSold;
        if (*s->SalesChannel == "Offline") offlineItems += *s->UnitsSold;
        else onlineItems += *s->UnitsSold;
    }
    if (totalItems == 0) {
        std::cout << "Either the country wasn't found or there wasn't sold anything there" << std::endl;
    }
    std::cout << "in the country: " << country << " " << (offlineItems / totalItems) * 100 << "% were sold offline and "
              << (onlineItems / totalItems) * 100 << "% were sold online" << std::endl;

}

void onlineByCountryAbsolute(std::string country) {
    int onlineItems = 0;
    int offlineItems = 0;
    for (SaleStatistic *s: statistics) {
        if (*s->country != country) {
            continue;
        }
        if (*s->SalesChannel == "Offline") offlineItems += *s->UnitsSold;
        else onlineItems += *s->UnitsSold;
    }
    if (onlineItems + offlineItems == 0) {
        std::cout << "Either the country wasn't found or there wasn't sold anything there" << std::endl;
    }
    std::cout << "in the country: " << country << " " << offlineItems << " were sold offline and " << onlineItems
              << " were sold online" << std::endl;
}

void favoritePerCountry() {
    //• Welcher Item Type ist der beliebteste in Land X?
    std::string input;
    std::cout << "enter Country" << std::endl;
    std::cin.sync();
    std::cin >> input;
    input.erase(input.find_last_not_of(" \n\r\t") + 1);
    getFavoritePerCountry(input);
}

void getFavoritePerCountry(std::string country) {
    std::map<std::string, int> itemToNumberMap;
    for (SaleStatistic *s: statistics) {
        if (*s->country != country) {
            continue;
        }
        auto it = itemToNumberMap.find(*s->itemType);
        if (it != itemToNumberMap.end()) {
            it->second += *s->UnitsSold;
        } else {
            itemToNumberMap.insert({*s->itemType, *s->UnitsSold});
        }
    }
    int maxItemNumber = 0;
    std::string favItems;
    if (itemToNumberMap.empty()) {
        std::cout << "Either the Country wasn't found or there were no Items sold there" << std::endl;
        return;
    }
    for (const auto &i: itemToNumberMap) {
        if (i.second == maxItemNumber) favItems += (" , " + i.first);
        else if (i.second < maxItemNumber) continue;
        else if (i.second > maxItemNumber) favItems = i.first;
    }
    std::cout << "The favorite item(s) was/ were: " << favItems << std::endl;
}

void itemTypePerRegion() {
    //• Wie oft wurde ein Item Type in den Regionen verkauft? Absolut und prozentual
    std::string input;
    std::cout << "enter Item Type" << std::endl;
    std::cin.sync();
    std::cin >> input;
    input.erase(input.find_last_not_of(" \n\r\t") + 1);

    char des;
    std::cout << "1: Absolute  \n 2: Procentual" << std::endl;
    std::cin.sync();
    std::cin >> des;
    switch (des) {
        case '1':
            itemPerRegionAbsolute(input);
            break;
        case '2':
            itemPerRegionPercent(input);
            break;
        default:
            std::cout << "\n waht";
    }

}

void itemPerRegionPercent(std::string type) {
    std::map<std::string, int> regionToNumberMap;
    double totalOfItem = 0;
    for (SaleStatistic *s: statistics) {
        if (*s->itemType != type) {
            continue;
        }
        totalOfItem += *s->UnitsSold;
        auto it = regionToNumberMap.find(*s->region);
        if (it != regionToNumberMap.end()) {
            it->second += *s->UnitsSold;
        } else {
            regionToNumberMap.insert({*s->region, *s->UnitsSold});
        }
    }
    if (regionToNumberMap.empty()) {
        std::cout << "Either the Item wasn't found or it wasn't sold anywhere" << std::endl;
        return;
    }
    for (const auto &i: regionToNumberMap) {
        double percent = (i.second / totalOfItem) * 100;
        std::cout << i.first << ": " << percent << "%" << std::endl;
    }
}

void itemPerRegionAbsolute(std::string type) {
    std::map<std::string, int> regionToNumberMap;
    for (SaleStatistic *s: statistics) {
        if (*s->itemType != type) {
            continue;
        }
        auto it = regionToNumberMap.find(*s->region);
        if (it != regionToNumberMap.end()) {
            it->second += *s->UnitsSold;
        } else {
            regionToNumberMap.insert({*s->region, *s->UnitsSold});
        }
    }
    if (regionToNumberMap.empty()) {
        std::cout << "Either the Item wasn't found or it wasn't sold anywhere" << std::endl;
        return;
    }
    for (const auto &i: regionToNumberMap) {
        std::cout << i.first << ": " << i.second << std::endl;
    }
}

void profitsPer() {
    //• Total profit pro Region, Country, Item Type oder Sales Channel
    char des;
    std::cout << "total Profit per what:  \n 1: Region" <<
              "\n 2: Country \n 3: Item Type" <<
              "\n 4: Sales Channel" << std::endl;
    std::cin.sync();
    std::cin >> des;
    switch (des) {
        case '1':
            profitsPerRegion();
            break;
        case '2':
            profitsPerCountry();
            break;
        case '3':
            profitsPerType();
            break;
        case '4':
            profitsPerChannel();
            break;
        default:
            std::cout << "\n waht";
    }
}

void profitsPerChannel() {
    char input;
    std::string Channel;
    std::cout << "enter Channel for the prophet: \n 1: Online \n 2: offline" << std::endl;
    std::cin.sync();
    std::cin >> input;
    switch (input) {
        case '1':
            Channel = "Online";
            break;
        case '2':
            Channel = "Offline";
            break;
        default:
            std::cout << "\n waht";
            return;
    }
    getProfitsPerChannel(Channel);
}

void getProfitsPerChannel(std::string Channel) {
    double profits = 0;
    for (SaleStatistic *s: statistics) {
        if (*s->SalesChannel == Channel) {
            profits += *s->TotalProfit;
        }
    }
    if (profits == 0) {
        std::cout << "Either the Channel wasn't found or it didn't make any profits" << std::endl;
        return;
    }
    std::cout << "total profits in " << Channel << " are: " << profits << std::endl;
}

void profitsPerType() {
    std::string input;
    std::cout << "enter type of which you want your profit" << std::endl;
    std::cin.sync();
    std::cin >> input;
    input.erase(input.find_last_not_of(" \n\r\t") + 1);
    getProfitsPerType(input);
}

void getProfitsPerType(std::string type) {
    double profits = 0;
    for (SaleStatistic *s: statistics) {
        if (*s->itemType == type) {
            profits += *s->TotalProfit;
        }
    }
    if (profits == 0) {
        std::cout << "Either the Type wasn't found or it didn't make any profits" << std::endl;
        return;
    }
    std::cout << "total profits in " << type << " are: " << profits << std::endl;
}

void profitsPerCountry() {
    std::string input;
    std::cout << "enter Country where you want your profit" << std::endl;
    std::cin.sync();
    std::cin >> input;
    input.erase(input.find_last_not_of(" \n\r\t") + 1);
    getProfitsPerCountry(input);
}

void getProfitsPerCountry(std::string country) {
    double profits = 0;
    for (SaleStatistic *s: statistics) {
        if (*s->country == country) {
            profits += *s->TotalProfit;
        }
    }
    if (profits == 0) {
        std::cout << "Either the Country wasn't found or it didn't make any profits" << std::endl;
        return;
    }
    std::cout << "total profits in " << country << " are: " << profits << std::endl;
}

void profitsPerRegion() {
    //• Total profit pro Region, Country, Item Type oder Sales Channel
    std::string input;
    std::cout << "enter Region where you want your profit" << std::endl;
    std::cin.sync();
    std::cin >> input;
    input.erase(input.find_last_not_of(" \n\r\t") + 1);
    getProfitsPerRegion(input);
}

void getProfitsPerRegion(const std::string &region) {
    double profits = 0;
    for (SaleStatistic *s: statistics) {
        if (*s->region == region) {
            profits += *s->TotalProfit;
        }
    }
    if (profits == 0) {
        std::cout << "Either the Region wasn't found or it didn't make any profits" << std::endl;
        return;
    }
    std::cout << "total profits in " << region << "are: " << profits << std::endl;
}

void loadStatistics(std::vector<SaleStatistic *> *vector1) {
    bool firstline = true;
    std::string line;
    std::ifstream file("../beeegRecords.txt");
    //std::ifstream file("../smallRecords.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (isEmptyOrWhitespace(line)) {
                continue;
            }
            if (firstline) {
                firstline = false;
                continue;
            }
            vector1->push_back(new SaleStatistic(line));
        }
        file.close();
    } else {
        std::cout << "Error opening the file." << std::endl;
    }
}

bool isEmptyOrWhitespace(const std::string &basicString) {
    for (char c: basicString) {
        if (!(isspace(c) || isblank(c))) {
            return false;
        }
    }
    return true;
}
