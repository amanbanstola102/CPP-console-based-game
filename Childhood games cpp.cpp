#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Function to draw the hangman
void drawHangman(int lives) {
    switch (lives) {
        case 6:
            cout << " +---+" << endl;
            cout << " |   |" << endl;
            cout << "     |" << endl;
            cout << "     |" << endl;
            cout << "     |" << endl;
            cout << "     |" << endl;
            break;
        case 5:
            cout << " +---+" << endl;
            cout << " |   |" << endl;
            cout << " O   |" << endl;
            cout << "     |" << endl;
            cout << "     |" << endl;
            cout << "     |" << endl;
            break;
        case 4:
            cout << " +---+" << endl;
            cout << " |   |" << endl;
            cout << " O   |" << endl;
            cout << " |   |" << endl;
            cout << "     |" << endl;
            cout << "     |" << endl;
            break;
        case 3:
            cout << " +---+" << endl;
            cout << " |   |" << endl;
            cout << " O   |" << endl;
            cout << "/|   |" << endl;
            cout << "     |" << endl;
            cout << "     |" << endl;
            break;
        case 2:
            cout << " +---+" << endl;
            cout << " |   |" << endl;
            cout << " O   |" << endl;
            cout << "/|\\  |" << endl;
            cout << "     |" << endl;
            cout << "     |" << endl;
            break;
        case 1:
            cout << " +---+" << endl;
            cout << " |   |" << endl;
            cout << " O   |" << endl;
            cout << "/|\\  |" << endl;
            cout << "/    |" << endl;
            cout << "     |" << endl;
            break;
        case 0:
            cout << " +---+" << endl;
            cout << " |   |" << endl;
            cout << " O   |" << endl;
            cout << "/|\\  |" << endl;
            cout << "/ \\  |" << endl;
            cout << "     |" << endl;
            break;
    }
}

// Hangman Game
void playHangman() {
    string word;
    string guess;
    int lives = 6;
    string display;

    // Player 1 chooses the word
    cout << "Player 1, please enter a word: ";
    cin >> word;

    // Clear the console (optional, platform-dependent)
    system("clear"); // On Windows, use system("cls");

    // Initialize the display string
    for (int i = 0; i < word.length(); i++) {
        display += "_";
    }

    // Player 2 guesses the word
    while (lives > 0) {
        cout << "Player 2, please guess a letter: ";
        cin >> guess;

        // Check if the guess is correct
        if (word.find(guess) != string::npos) {
            cout << "Correct!" << endl;

            // Update the display string
            for (int i = 0; i < word.length(); i++) {
                if (word[i] == guess[0]) {
                    display[i] = guess[0];
                }
            }
        } else {
            cout << "Incorrect!" << endl;
            lives--;
        }

        // Draw the hangman
        drawHangman(lives);

        // Display the current state of the word
        cout << display << endl;

        // Check if the word has been guessed
        if (display.find("_") == string::npos) {
            cout << "Congratulations! You've guessed the word!" << endl;
            break;
        }
    }

    if (lives == 0) {
        cout << "Game Over! The word was: " << word << endl;
    }
}

// Raja-Rani Game
void shuffleRoles(vector<string>& roles) {
    random_shuffle(roles.begin(), roles.end());
}

void playRajaRani() {
    vector<string> roles = {"King", "Queen", "Minister", "Police", "Thief"};
    vector<string> players(5);
    vector<int> points(5, 0);

    // Input player names
    for (int i = 0; i < 5; i++) {
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> players[i];
    }

    for (int round = 1; round <= 10; round++) {
        shuffleRoles(roles);

        int policeIndex = -1;
        int thiefIndex = -1;

        for (int i = 0; i < roles.size(); i++) {
            if (roles[i] == "Police") policeIndex = i;
            if (roles[i] == "Thief") thiefIndex = i;
        }

        // Points assignment
        for (int i = 0; i < roles.size(); i++) {
            if (roles[i] == "King") points[i] += 1000;
            else if (roles[i] == "Queen") points[i] += 500;
            else if (roles[i] == "Minister") points[i] += 300;
            else if (roles[i] == "Police") {
                int guess;
                cout << "Round " << round << ": " << players[policeIndex] << " (Police), guess who the Thief is (0-4): ";
                cin >> guess;
                if (guess == thiefIndex) {
                    cout << "Correct! " << players[policeIndex] << " guessed the Thief (" << players[thiefIndex] << ")." << endl;
                    points[policeIndex] += 100;
                } else {
                    cout << "Incorrect! The Thief was " << players[thiefIndex] << "." << endl;
                    points[thiefIndex] += 100;
                }
            }
        }

        // Display round summary
        cout << "\nRound " << round << " Summary:\n";
        for (int i = 0; i < roles.size(); i++) {
            cout << players[i] << " is the " << roles[i] << " and has " << points[i] << " points." << endl;
        }
        cout << "---------------------------\n";
    }

    // Display final points
    cout << "\nFinal Points:\n";
    for (int i = 0; i < players.size(); i++) {
        cout << players[i] << ": " << points[i] << " points" << endl;
    }

    // Determine the winner
    int maxPoints = *max_element(points.begin(), points.end());
    vector<int> winners;
    for (int i = 0; i < points.size(); i++) {
        if (points[i] == maxPoints) {
            winners.push_back(i);
        }
    }

    if (winners.size() == 1) {
        cout << "The winner is " << players[winners[0]] << " with " << maxPoints << " points!" << endl;
    } else {
        cout << "It's a tie between: ";
        for (int i = 0; i < winners.size(); i++) {
            cout << players[winners[i]] << " ";
        }
        cout << "with " << maxPoints << " points!" << endl;
    }
}

int main() {
    int choice;
    cout << "Choose a game to play:\n";
    cout << "1. Hangman\n";
    cout << "2. Raja-Rani\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            playHangman();
            break;
        case 2:
            playRajaRani();
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }

    return 0;
}
