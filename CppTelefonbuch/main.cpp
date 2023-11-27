#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>


[[maybe_unused]] typedef struct phoneBookEntry {
    std::string givenName;
    std::string surname;
    std::string number;
} phoneBookEntry_t;


void search(const std::vector<phoneBookEntry*> &s);

void machweg(std::vector<phoneBookEntry*> s);

std::vector<phoneBookEntry*> getVectorOfPhonebook();

void writePhonebook(std::vector<phoneBookEntry*> vector1);

phoneBookEntry* newEntry() {
    std::string firstName;
    std::string lastName;
    std::string numb;
    std::cout << "\n gib mal den vornamen von neue eintrag";
    std::cin >> firstName;
    std::cout << "gib mal lastname";
    std::cin >> lastName;
    std::cout << "gib mal numner";
    std::cin >> numb;
    phoneBookEntry* p = new phoneBookEntry;
    p->givenName = firstName;
    p->surname = lastName;
    p->number = numb;
    return p;
}

void printPhoneBook(const std::vector<phoneBookEntry*> &s) {
    for (phoneBookEntry* entry: s) {
        std::cout << "surname: " << entry->surname << " firsname: " << entry->givenName << " number: " << entry->number
                  << std::endl;
    }
}

int main() {
    std::vector<phoneBookEntry*> s = getVectorOfPhonebook();
    char des = 'a';
    while (des) {
        std::cout
                << "\n hau mal raus jetzt was ich mache soll \n n: neuw entr \n e: end programm\n p: print\n s: search";
        std::cin >> des;
        switch (des) {
            case 'n':
                s.push_back(newEntry());
                break;
            case 'p':
                printPhoneBook(s);
                break;
            case 'e':
                writePhonebook(s);
                machweg(s);
                des = 0;
                break;
            case 's':
                search(s);
                break;
            default:
                std::cout << "\n boa alda was willste denn mit dem kack, mach mal ernst hier ey";
        }
    }
    return 0;
}

void writePhonebook(std::vector<phoneBookEntry*> s) {
    std::ofstream outFile("phonebook", std::ios::binary);
    for (phoneBookEntry* entry: s) {
        std::string p =
                "surname: " + entry->surname + " firsname: " + entry->givenName + " number: " + entry->number + "\n";
        outFile << p;
    }
    outFile.close();
}

std::vector<phoneBookEntry*> getVectorOfPhonebook() {
    std::vector<phoneBookEntry*> s;
    std::ifstream inFile("students.data", std::ios::binary);
    phoneBookEntry hatBecokesEntry;
    inFile.read((char*) &hatBecokesEntry, sizeof(phoneBookEntry));
    s.push_back(&hatBecokesEntry);
    return s;
}

void machweg(std::vector<phoneBookEntry*> s) {
    for (phoneBookEntry* entry: s) {
        delete entry;
    }
}

void search(const std::vector<phoneBookEntry*> &s) {
    std::string name;
    std::cout << "\n gib mal den name den du suchst: ";
    std::cin >> name;
    for (phoneBookEntry* entry: s) {
        if (name == entry->surname || name == entry->givenName) {
            std::cout << "surname: " << entry->surname << " firsname: " << entry->givenName << " number: "
                      << entry->number << std::endl;
        }
    }
    std::cout << "mehr hab ich nicht, sorry" << std::endl;
}
