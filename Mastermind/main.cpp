#include <iostream>
#include <random>

void fourRandomChars(char *drawnColours);

char getColourFromint(int distribution);

class combination {
    char *comb;
public:
    ~combination();

    combination();

    combination(char c[4]);

    void print();

    bool compare(combination *);

    void evaluate(combination *);

};

combination *getCombignationFromUser();

combination::combination() {
    this->comb = new char[4];
    fourRandomChars(this->comb);
}

combination::combination(char c[4]) {
    this->comb = c;
}

combination::~combination() {
    delete[] this->comb;
}

void combination::print() {
    for (int i = 0; i < 4; ++i) {
        std::cout << comb[i];
    }
    std::cout << std::endl;
}

bool combination::compare(combination *other) {
    for (int i = 0; i < 4; ++i) {
        if (this->comb[i] != other->comb[i]) {
            return false;
        }
    }
    return true;
}

void combination::evaluate(combination *other) {
    bool blackChars[4] = {false, false, false, false};
    bool whiteChars[4] = {false, false, false, false};
    for (int i = 0; i < 4; ++i) {
        if (this->comb[i] == other->comb[i]) {
            std::cout << "s"<< std::endl;
            blackChars[i] = true;
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (this->comb[i] == other->comb[j] && !blackChars[i] && !blackChars[j] && !whiteChars[i] &&
                !whiteChars[j]) {
                std::cout << "w" << std::endl;
                //whiteChars[i] = true;
                //whiteChars[j] = true;
            }

        }
    }
}

int main() {
    combination *solution = new combination();
    //solution->print();
    combination *p = getCombignationFromUser();
    while (!solution->compare(p)) {
        std::cout << "wrong" << std::endl;
        solution->evaluate(p);
        p = getCombignationFromUser();
    }
    std::cout << "right" << std::endl;
    delete solution;
    delete p;
    return 0;
}


combination *getCombignationFromUser() {
    int numberChars = 0;
    char *in = new char[4];
    while (numberChars < 4) {
        std::string templ = "rgbskm";
        std::cout << "please input your combination now... \n" << std::endl;
        std::string input;
        std::getline(std::cin, input);
        for (char c: input) {
            if (templ.find(c) != std::string::npos) {
                in[numberChars++] = c;
            } else if (isspace(c)) {

            } else {
                std::cout << "there is something: ( " << c
                          << " ) in there wich is neither a number nor a blank, please, keep your inputs in line with the game\n"
                          << std::endl;
                numberChars = 0;
                break;
            }
        }
    }
    return new combination(in);
}

void fourRandomChars(char *drawnColours) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 6);
    for (int i = 0; i < 4; ++i) {
        drawnColours[i] = getColourFromint(distribution(gen));
    }

}

char getColourFromint(int distribution) {
    switch (distribution) {
        case 1:
            return 'r';
        case 2:
            return 'g';
        case 3:
            return 'b';
        case 4:
            return 's';
        case 5:
            return 'k';
        case 6:
            return 'm';
        default:
            std::cout << "\n boa alda was willste denn mit dem kack, mach mal ernst hier ey";
            return 'r';
    }
}
