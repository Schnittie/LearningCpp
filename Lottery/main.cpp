#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

std::string TICKET;
std::string LOTTERY;
std::string LADY;
std::string UPPER_TICKET;
std::string LOWER_TICKET;
std::string UPPER_RESULT;
std::string MIDDLE_RESULT;
std::string LOWER_RESULT;


void printLotteryText();

bool getSevenNumbersFromUser(int sevenNumbers[7]);

void replaceTicketWithX(int *numbers);

void lotteryDraw(int *drawnNumbers);

void sevenRandomNumbers(int *pInt);

void getWinningLine(std::string *basicString, int i, int *pInt);

bool numbersArentUniqe(int *ints);

void resetTicket();

void initASCIIArt();

int main() {
    initASCIIArt();
    bool cont = true;
    while (cont) {
        resetTicket();
        printLotteryText();
        int sevenNumbers[7];
        while (!getSevenNumbersFromUser(sevenNumbers)) {
            int i = 0;
            for (int p: sevenNumbers) {
                sevenNumbers[i++] = 0;
            }
        }
        replaceTicketWithX(sevenNumbers);
        std::cout << "You have filled out your Ticket!\n"
                     "May the odds be ever in your favour\n" << std::endl;
        std::cout << UPPER_TICKET << std::endl;
        std::cout << TICKET << std::endl;
        std::cout << LOWER_TICKET << std::endl;
        std::cout << "\n\n" << std::endl;
        std::cout << "The numbers will be drawn now..." << std::endl;
        std::cout << std::endl;
        int drawnNumbers[7];
        lotteryDraw(drawnNumbers);
        int correctGuesses = 0;
        for (int drawn: drawnNumbers) {
            for (int given: sevenNumbers) {
                if (drawn == given) {
                    correctGuesses++;
                }
            }
        }
        std::cout << "\n\n" << std::endl;
        if (correctGuesses == 0) {
            std::cout
                    << "Very sorry, but you didn't get anything right this time, you should try again though\nEveryone is a winner on Eros"
                    << std::endl;
        } else if (correctGuesses < 7) {
            std::cout << "You got a total number of " << correctGuesses
                      << " right.\nThat's impressive, try again for an even better score\nEveryone is a winner on Eros"
                      << std::endl;
        } else if (correctGuesses == 7) {
            std::cout
                    << "JACKPOT JACKPOT JACKPOT congratulations. Try again and double your winnings?\nEveryone is a winner on Eros"
                    << std::endl;
        } else {
            std::cout << "this shouldn't be possible" << std::endl;
        }
        char tryAgain;

        std::cout
                << "\nTry again?(y|N)" << std::endl;
        std::cin >> tryAgain;
        cont = (tryAgain == 'y');
    }
    return 0;
}

void lotteryDraw(int *drawnNumbers) {
    std::string ignored;
    std::string winningLine;
    sevenRandomNumbers(drawnNumbers);
    std::cout << LADY << std::endl;
    std::cout << UPPER_RESULT << std::endl;
    std::cout << MIDDLE_RESULT << std::endl;
    std::cout << MIDDLE_RESULT << std::endl;
    std::cout << MIDDLE_RESULT << std::endl;
    std::cout << LOWER_RESULT << std::endl;
    for (int i = 0; i < sizeof drawnNumbers - 1; ++i) {
        getWinningLine(&winningLine, i + 1, drawnNumbers);
        std::cout << "are you ready to see the next number?" << std::endl;
        std::cin >> ignored;
        std::cout << LADY << std::endl;
        std::cout << UPPER_RESULT << std::endl;
        std::cout << MIDDLE_RESULT << std::endl;
        std::cout << winningLine << std::endl;
        std::cout << MIDDLE_RESULT << std::endl;
        std::cout << LOWER_RESULT << std::endl;
    }


}

void getWinningLine(std::string *winningLine, int howMany, int *drawn) {
    *winningLine = "";
    for (int i = 0; i < sizeof drawn - 1; ++i) {
        *winningLine += "| ";
        if (i < howMany) {
            if (drawn[i] > 9) {
                *winningLine += std::to_string(drawn[i]);
            } else {
                *winningLine += " ";
                *winningLine += std::to_string(drawn[i]);
            }
        } else {
            *winningLine += "  ";
        }
        *winningLine += " | ";
    }
}

void sevenRandomNumbers(int *drawnNumbers) {
    do {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(1, 49);
        for (int i = 0; i < 7; ++i) {
            drawnNumbers[i] = distribution(gen);
        }
    } while (numbersArentUniqe(drawnNumbers));
}

void replaceTicketWithX(int *numbers) {
    for (int i = 0; i < sizeof(numbers); ++i) {
        int numbrOfBracket = 0;
        for (int j = 0; j < TICKET.size(); ++j) {
            if (TICKET[j] == '[') {
                if (++numbrOfBracket == numbers[i]) {
                    TICKET[j + 1] = ' ';
                    TICKET[j + 2] = ' ';
                    TICKET[j + 3] = 'X';
                    TICKET[j + 4] = ' ';
                    break;
                }
            }
        }
    }
}

bool getSevenNumbersFromUser(int sevenNumbers[7]) {
    std::cout << "please input your numbers now... \n" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    int currentInt = 0;
    int numberOfInts = 0;
    for (char c: input) {
        if (isdigit(c)) {
            if (numberOfInts == 7) {
                std::cout
                        << "there are too many numbers in there, please, keep your inputs in line with the game\n"
                        << std::endl;
                return false;
            }
            currentInt = currentInt * 10;
            currentInt = currentInt + (c - '0');
            if (currentInt > 49) {
                std::cout
                        << "there is a number in there larger than 49, please, keep your inputs in line with the game\n"
                        << std::endl;
                return false;
            }
        } else if (isspace(c)) {
            if (currentInt > 0) {
                sevenNumbers[numberOfInts++] = currentInt;
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
        sevenNumbers[numberOfInts++] = currentInt;
    }
    if (numberOfInts < 7) {
        std::cout
                << "there are too little numbers in there, please, keep your inputs in line with the game\n"
                << std::endl;
        return false;
    }
    if (numbersArentUniqe(sevenNumbers)) {
        std::cout
                << "there duplicate numbers in there, please, keep your inputs in line with the game\n"
                << std::endl;
        return false;
    }
    return true;
}

bool numbersArentUniqe(int *ints) {
    for (int i = 0; i < sizeof ints; ++i) {
        for (int j = 0; j < sizeof ints; ++j) {
            if (i != j && ints[i] == ints[j]) {
                return true;
            }
        }
    }
    return false;
}


void printLotteryText() {
    std::cout << "\n \n " << std::endl;
    std::cout << LOTTERY << std::endl;
    std::cout << "\n \n " << std::endl;
    std::cout << "Welcome to the ultimate test of luck and intuition!\n"
                 "Get ready to embark on a thrilling journey where fortunes can change in the blink of an eye.\n"
                 "It's time to unveil the magic of your own destiny by choosing your seven, yes, seven, lucky numbers!"
              << std::endl;
    std::cout << "\n \n " << std::endl;
    std::cout << "here's your ticket" << std::endl;
    std::cout << UPPER_TICKET << std::endl;
    std::cout << TICKET << std::endl;
    std::cout << LOWER_TICKET << std::endl;
    std::cout << "now... which seven numbers will you choose? " << std::endl;
}

//ASCII ART:
void initASCIIArt() {
    LOTTERY = "$$\\                   $$\\       $$\\                                   \n"
              "$$ |                  $$ |      $$ |                                  \n"
              "$$ |       $$$$$$\\  $$$$$$\\   $$$$$$\\    $$$$$$\\   $$$$$$\\  $$\\   $$\\ \n"
              "$$ |      $$  __$$\\ \\_$$  _|  \\_$$  _|  $$  __$$\\ $$  __$$\\ $$ |  $$ |\n"
              "$$ |      $$ /  $$ |  $$ |      $$ |    $$$$$$$$ |$$ |  \\__|$$ |  $$ |\n"
              "$$ |      $$ |  $$ |  $$ |$$\\   $$ |$$\\ $$   ____|$$ |      $$ |  $$ |\n"
              "$$$$$$$$\\ \\$$$$$$  |  \\$$$$  |  \\$$$$  |\\$$$$$$$\\ $$ |      \\$$$$$$$ |\n"
              "\\________| \\______/    \\____/    \\____/  \\_______|\\__|       \\____$$ |\n"
              "                                                            $$\\   $$ |\n"
              "                                                            \\$$$$$$  |\n"
              "                                                             \\______/ \n"
              "";
    LADY = "\n"
           "                             ,---')\n"
           "                            (  -_-(\n"
           "                            ) .__/ )\n"
           "                          _/ _/_( /        _.---._\n"
           "                         (__/ _ _) ,-._   /  o    \\\n"
           "                           //)__(\\/,-` |_| O  o o O|\n"
           "                       _\\\\///==o=\\'      |O o  o O |\n"
           "                        `-' \\    /        \\O o   o/\n"
           "                             )___\\         `'-.-\\\\\n"
           "                            / ,\\ \\       ____)_(____\n"
           "                           / /  \\ \\     '--..---,,--'\n"
           "                          /()    >()        \\\\_//   \n"
           "                          |\\_\\   |\\_\\       /,-.\\";
    UPPER_TICKET = "_______________________________________________________________________________";
    LOWER_TICKET = "-------------------------------------------------------------------------------";
    UPPER_RESULT = "______ ______ ______ ______ ______ ______ ______";
    LOWER_RESULT = "------ ------ ------ ------ ------ ------ ------";
    MIDDLE_RESULT= "|    | |    | |    | |    | |    | |    | |    |";
}

void resetTicket() {
    TICKET = "[  1 ] [  2 ] [  3 ] [  4 ] [  5 ] [  6 ] [  7 ] [  8 ] [  9 ] [ 10 ]\n"
             "[ 11 ] [ 12 ] [ 13 ] [ 14 ] [ 15 ] [ 16 ] [ 17 ] [ 18 ] [ 19 ] [ 20 ]\n"
             "[ 21 ] [ 22 ] [ 23 ] [ 24 ] [ 25 ] [ 26 ] [ 27 ] [ 28 ] [ 29 ] [ 30 ]\n"
             "[ 31 ] [ 32 ] [ 33 ] [ 34 ] [ 35 ] [ 36 ] [ 37 ] [ 38 ] [ 39 ] [ 40 ]\n"
             "[ 41 ] [ 42 ] [ 43 ] [ 44 ] [ 45 ] [ 46 ] [ 47 ] [ 48 ] [ 49 ]";
}

