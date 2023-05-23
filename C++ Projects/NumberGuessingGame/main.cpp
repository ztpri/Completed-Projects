#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    int userNum;
    int tries = 1;
    int randomNum;
    time_t t;

    // the best seed is a changing one, since time changes use time variable
    srand(time(&t));
    randomNum = (rand() % 91) + 10;

    cout << "What number, between 10 and 100, am I thinking of?" << endl;
    cin >> userNum;

    while(userNum != randomNum){
        if(userNum < randomNum){
            cout << "Too low! Guess again." << endl;
        }
        else if(userNum > randomNum){
            cout << "Too high! Guess again." << endl;
        }

        cin >> userNum;
        ++tries;
    }

    cout << "You guessed right! It took " << tries << " tries.";

    return 0;
}
