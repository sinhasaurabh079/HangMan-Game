#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

class Hangman {
private:
    int maxTries;               
    int remainingTries;        
    char guessLetter;            
    string secretWord;
    vector<char> guessWord;

    // replaces dash with guessed letters 
    void replaceDashes() {
        guessWord.assign(secretWord.length(), '-');
    }

    // 
    void displayWord() const {
        for (char c : guessWord) {
            cout << c;
        }
        cout << endl;
    }

    int isGuessTrue(char letter) {
        int flag = 0;
        for (int i = 0; i < secretWord.length(); ++i) {
            if (secretWord[i] == letter) {
                if (guessWord[i] == secretWord[i]) {
                    flag = 2;
                } else {
                    guessWord[i] = secretWord[i];
                    flag = 1;
                }
            }
        }
        return flag;
    }

    void displayMan() const {
        string part[4];
        switch (remainingTries) {
        case 0:
            part[3] = "|";
        case 1:
            part[2] = "/|\\";
        case 2:
            part[1] = "/|\\";
        case 3:
            part[0] = "( )";
            break;
        }

        cout << "--------------\n";
        cout << "  |       " << part[3] << endl;
        cout << "  |       " << part[3] << endl;
        cout << "  |      " << part[0] << endl;
        cout << "  |      " << part[1] << endl;
        cout << "  |      " << part[2] << endl;
        cout << "  |\n";
        cout << "  |\n";
        cout << "--------------\n";
    }

public:
    Hangman(int maxTries) : maxTries(maxTries), remainingTries(maxTries) {}

    void displayGameDetails() const {
        cout << "\n"
                "        .-------------------------------------------------------------------------------.\n"
                "        |      _      _                                                                  |\n"
                "        |     | |    | |   __ _    _ __      __ _        /\\/\\      __ _    _ __          |\n"
                "        |     | |----| |  / _  |  |  _ \\    / _` |      /    \\    / _  |  |  _  \\        |\n"
                "        |     | |----| | | (_| |  | | | |  | (_| |     / /\\/\\ |  | (_| |  | | | |        |\n"
                "        |     |_|    |_|  \\_ _ |  |_| |_|   \\__, |     \\/    \\/   \\_ _ |  |_| |_|        |\n"
                "        |                                    |___/                                       |\n"
                "        .--------------------------------------------------------------------------------.\n";

        cout << "The purpose of this game is to guess an animal name, secretly chosen by the application\n\n";
        cout << "You have to guess one letter at a time and you can have " << maxTries << " wrong attempts\n\n";
        cout << "Enter a lower-case letter and don't forget to enter key after each guess\n\n";
        cout << "Let's play the game!\n\n";
    }

    void chooseSecretWord() {
        srand(time(NULL));

        string animals[] = {"puppy", "turtle", "rabbit", "raccoon", "kitten", "hamster",
                            "sheep", "turkey", "chicken", "horse", "chimpanzee", "kangaroo", "koala",
                            "elephant", "leopard", "hippopotamus", "giraffe", "crocodile", "alligator",
                            "hedgehog"};

        int randomIndex = rand() % 20;
        secretWord = animals[randomIndex];
        replaceDashes();
    }

    void playGame() {
        displayGameDetails();

        chooseSecretWord();

        cout << "Your guess word is:";
        displayWord();

        while (remainingTries != 0) {
            cout << "Enter your guess letter:" << endl;
            cin >> guessLetter;

            int guess = isGuessTrue(guessLetter);

            if (guess == 0) {
                remainingTries--;
                cout << "\nWhoops! That letter is not present in the word" << endl;
                displayMan();
            }
            if (guess == 1) {
                cout << "\nYay! You have found the letter" << endl;
            }
            if (guess == 2) {
                cout << "\nYou have already guessed this letter. Try something else!" << endl;
            }
            cout << "You can have " << remainingTries << " more wrong attempts" << endl;
            cout << "Your guess word is:";
            displayWord();
            cout << endl;

            if (secretWord == string(guessWord.begin(), guessWord.end())) {
                cout << "\nCongratulations! You won." << endl;
                return;
            }
        }
        if (secretWord != string(guessWord.begin(), guessWord.end())) {
            cout << "\nToo many guesses! You have been hanged." << endl;
            cout << "\nThe secret word was: " << secretWord << endl;
        }
    }
};

int main() {
    Hangman game(5);
    game.playGame();
    return 0;
}
