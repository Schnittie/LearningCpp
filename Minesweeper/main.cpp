#include <iostream>
#include <memory>
#include <array>
#include <random>
#include <map>

void fillFieldWithMines(int field[16][16]);

void printField(int field[16][16]);

void fillFieldWithNumbers(int field[16][16]);

void fillTileWithNumbers(int field[16][16], int i, int j);


void fillState(std::unique_ptr<std::map<int, int>> state);

void printField(int field[16][16], std::map<int, int> *state);

void playGame(int field[16][16], std::map<int, int> *state);

bool lookat(int field[16][16], std::map<int, int> *state, int i, int j);

void reveal(int field[16][16], std::map<int, int> *state, int i, int j);

bool checkCoords(int k, int l);

bool getTwoNumbersFromUser(int *i, int *j);

void placeFlag(int field[16][16], std::map<int, int> *state, int i, int j);

bool gameWon(int field[16][16], std::map<int, int> *state, int i);

int getBombNr(int field[16][16]);

int main() {
    //std::unique_ptr<int[16][16]> field(int[16][16]);
    int field[16][16];
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            field[i][j] = 0;
        }
    }
    fillFieldWithMines(field);
    printField(field);
    fillFieldWithNumbers(field);
    printField(field);
    std::unique_ptr<std::map<int, int>> state = std::make_unique<std::map<int, int>>();
    //std::unique_ptr<std::map<int, int>> state(std::map<int, int>);
    //std::map<int, int> state;
    fillState(state);
    printField(field, &state);

    playGame(field, &state);
}

void playGame(int field[16][16], std::map<int, int> *state) {
    int i = 5;
    bool gaming = true;
    int j = 5;
    char des;

    while (gaming) {
        std::cout << "so, what do you wanna do now:  \n 1: place/remove flag \t 2: look beneath " << std::endl;
        std::cin.sync();
        std::cin >> des;
        int totalNrofBomb = getBombNr(field);
        switch (des) {
            case '1':
                while (!getTwoNumbersFromUser(&i, &j)) {}
                placeFlag(field, state, i, j);
                break;
            case '2':
                while (!getTwoNumbersFromUser(&i, &j)) {}
                gaming = lookat(field, state, i, j);
                break;

            default:
                std::cout << "\n please keep your inputs in line with the game";
        }
        if(gameWon(field, state, totalNrofBomb)){
            std::cout << "you won the game, congrats" << std::endl;
            gaming = false;
        }
    }

}

int getBombNr(int field[16][16]) {
    int bonbNr = 0;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (field[i][j]==-1){
                bonbNr++;
            }
        }
    }
    return bonbNr;
}

bool gameWon(int field[16][16], std::map<int, int> *state, int bombNr) {
    if ((*state)[-1]!=bombNr) return false;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (field[i][j]==-1){
                if ((*state)[i*100+j]!=2) return false;
            }
        }
    }
    return true;
}

void placeFlag(int field[16][16], std::map<int, int> *state, int i, int j) {
    switch (state->at(i * 100 + j)) {
        case 1:
            std::cout << "you can't place a flag on a number, silly" << std::endl;
            return;
        case 2:
            (*state)[i * 100 + j] = 0;
            (*state)[-1]--;
            printField(field, state);
            return;
        case 3:
            std::cout << "bruh you already know there's nothing here" << std::endl;
            return;
        case 0:
            (*state)[i * 100 + j] = 2;
            (*state)[-1]++;
            printField(field, state);
            return;
    }
}

bool getTwoNumbersFromUser(int *i, int *j) {
    std::cout << "please input the coordinates now... row then column" << std::endl;
    std::cin.sync();
    std::string input;
    //std::cin >> input;
    std::getline(std::cin, input);
    int currentInt = 0;
    int numberOfInts = 0;
    for (char c: input) {
        if (isdigit(c)) {
            if (numberOfInts == 3) {
                std::cout
                        << "there are too many numbers in there, please, keep your inputs in line with the game\n"
                        << std::endl;
                return false;
            }
            currentInt = currentInt * 10;
            currentInt = currentInt + (c - '0');
            if (currentInt > 16) {
                std::cout
                        << "there is a number in there larger than 16, please, keep your inputs in line with the game\n"
                        << std::endl;
                return false;
            }
        } else if (isspace(c)) {
            if (currentInt > 0) {
                (numberOfInts++ == 0 ? *i : *j) = currentInt;
                currentInt = 0;
            }
        } else {
            std::cout << "there is something: ( " << c
                      << " ) in there wich is neither a number nor a blank, please, keep your inputs in line with the game\n"
                      << std::endl;
            return false;
        }
    }
    if (currentInt > 0) {
        (numberOfInts++ == 0 ? *i : *j) = currentInt;
        currentInt = 0;
    }
    if (numberOfInts < 2) {
        std::cout
                << "there are too little numbers in there, please, keep your inputs in line with the game\n"
                << std::endl;
        return false;
    }
    (*i)--;
    (*j)--;
    return true;
}

bool lookat(int field[16][16], std::map<int, int> *state, int i, int j) {
    switch (state->at(i * 100 + j)) {
        case 1:
            //TODO what if visible and number
            return true;
        case 2:
            std::cout << "you can't look where you placed a flag" << std::endl;
            return true;
        case 3:
            std::cout << "bruh you already know there's nothing here" << std::endl;
            return true;
        case 0:
            if (field[i][j] == -1) {
                std::cout << "boom" << std::endl;
                printField(field);
                return false;
            }
            reveal(field, state, i, j);
            printField(field, state);
            return true;
    }

}

void reveal(int field[16][16], std::map<int, int> *state, int i, int j) {
    if (state->at(i * 100 + j) != 0)return;
    if (field[i][j] == -1)return;
    (*state)[i * 100 + j] = (field[i][j] > 0 ? 1 : 3);
    if (field[i][j] > 0)return;
    for (int k = i - 1; k <= i + 1; ++k) {
        for (int l = j - 1; l <= j + 1; ++l) {
            if (checkCoords(k, l)) {
                reveal(field, state, k, l);
            }
        }
    }

}

void printField(int field[16][16], std::map<int, int> *state) {
    std::cout << "\n";
    std::cout << "    1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 " << std::endl;
    for (int i = 0; i < 16; ++i) {
        std::cout << (i < 9 ? " " : "") << i + 1 << ' ';
        for (int j = 0; j < 16; ++j) {
            std::cout << '[';
            if ((*state)[i * 100 + j] == 0) {
                std::cout << "?]";
                continue;
            }
            if ((*state)[i * 100 + j] == 2) {
                std::cout << "F]";
                continue;
            }
            switch (field[i][j]) {
                case -1:
                    std::cout << 'X';
                    break;
                case 0:
                    std::cout << ' ';
                    break;
                default:
                    std::cout << field[i][j];
            }
            std::cout << ']';
        }
        std::cout << std::endl;
    }
}

void fillState(std::unique_ptr<std::map<int, int>> state) {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            state->insert({(i * 100 + j), 0});
        }
    }
    state->insert({-1,0});
}

void fillFieldWithNumbers(int field[16][16]) {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            fillTileWithNumbers(field, i, j);
        }
    }
}

void fillTileWithNumbers(int field[16][16], int i, int j) {
    int count = 0;
    if (field[i][j] == -1)return;
    for (int k = i - 1; k <= i + 1; ++k) {
        for (int l = j - 1; l <= j + 1; ++l) {
            if (checkCoords(k, l)) {
                if (field[k][l] == -1) {

                    count++;
                }
            }
        }
    }
    field[i][j] = count;
}

bool checkCoords(int k, int l) {
    return k >= 0 && l >= 0 && k < 16 && l < 16;
}

void printField(int field[16][16]) {
    std::cout << "    1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 " << std::endl;
    for (int i = 0; i < 16; ++i) {
        std::cout << (i < 9 ? " " : "") << i + 1 << ' ';
        for (int j = 0; j < 16; ++j) {
            std::cout << '[';
            switch (field[i][j]) {
                case -1:
                    std::cout << 'X';
                    break;
                case 0:
                    std::cout << ' ';
                    break;
                default:
                    std::cout << field[i][j];
            }
            std::cout << ']';
        }
        std::cout << std::endl;
    }
}

void fillFieldWithMines(int field[16][16]) {
    for (int i = 0; i < 3; ++i) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, 15);
        field[distribution(gen)][distribution(gen)] = -1;
    }
}
