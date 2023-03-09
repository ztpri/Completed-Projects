// Program 2 -- Boggle-ish
// An approximation of the Boggle game
// This game ONLY works with a 4x4 Boggle tray
//
// Usage:
//    When prompted, player enters an arbitrary random seed.
//    When prompted, player enters the number of seconds for timer.
//    Program prints letter grid and waits the specified number of seconds. Player writes down words.
//    When time expires, players enters words and collects points.
//    Player enters q to quit.
//
// Zachary Price, Section 602

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

unsigned int lfsrNext();                     // get next LFSR value
void seedRandom(unsigned int seed);          // initialize random number generator
unsigned int getRandom(unsigned int limit);  // return random number between 0 and limit-1
void permute(unsigned int values[], size_t size);

void shakeTray();   // "shake" Boggle dice and set up tray
void printTray();   // print tray in 4x4 grid
void startTimer(unsigned int seconds);      // count seconds
unsigned int scoreWord(const char word[]);  // check if word in grid and return score
bool findWord(const char word[]);           // check if word is in grid

// global variables
// justification
// (1) Values are needed by multiple functions.
// (2) Passing as arguments makes the function interfaces awkward and hard to use.
// (3) There's no need for keeping multiple local copies of these data structures.

unsigned int lfsr = 1;
unsigned int trayDice[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
char trayLetters[16] = {0};

const char dice[16][6] = {{'A', 'A', 'C', 'I', 'O', 'T'}, // die 0
                          {'A', 'H', 'M', 'O', 'R', 'S'}, // die 1
                          {'E', 'G', 'K', 'L', 'U', 'Y'}, // die 2
                          {'A', 'B', 'I', 'L', 'T', 'Y'}, // die 3
                          {'A', 'C', 'D', 'E', 'M', 'P'}, // die 4
                          {'E', 'G', 'I', 'N', 'T', 'V'}, // die 5
                          {'G', 'I', 'L', 'R', 'U', 'W'}, // die 6
                          {'E', 'L', 'P', 'S', 'T', 'U'}, // die 7
                          {'D', 'E', 'N', 'O', 'S', 'W'}, // die 8
                          {'A', 'C', 'E', 'L', 'R', 'S'}, // die 9
                          {'A', 'B', 'J', 'M', 'O', 'Q'}, // die 10
                          {'E', 'E', 'F', 'H', 'I', 'Y'}, // die 11
                          {'E', 'H', 'I', 'N', 'P', 'S'}, // die 12
                          {'D', 'K', 'N', 'O', 'T', 'U'}, // die 13
                          {'A', 'D', 'E', 'N', 'V', 'Z'}, // die 14
                          {'B', 'I', 'F', 'O', 'R', 'X'}  // die 15
};


// Boggle-ish main function
// (1) Gets random seed and timer duration from user
// (2) Set up letter tray
// (3) Run timer -- user writes down words
// (4) User provides list of words. Program checks and scores -- enter "q" to quit.
int main() {
    unsigned int seed;
    unsigned int seconds;
    printf("Enter a random seed: ");
    fflush(stdout);
    scanf("%i", &seed);
    seedRandom(seed);  // if zero, seed is ignored
    printf("Timer (seconds): ");
    fflush(stdout);
    scanf("%d", &seconds);

    shakeTray();
    printTray();
    startTimer(seconds);

    char word[18] = "";
    unsigned int total = 0;
    unsigned int score = 0;
    while (1) {
        // get word from user, at most 16 characters
        printf("Word: ");
        fflush(stdout);
        scanf("%17s", word);
        if (strcasecmp(word, "q") == 0) break;  // "q" means quit
        // convert to uppercase, to make comparisons easier
        // also, check for any non-letter characters, and report a score of zero
        bool justLetters = true;
        for (int i = 0; word[i] && (i < 17); i++) {
            if (isalpha(word[i])) word[i] = toupper(word[i]);
            else {
                justLetters = false;
                break;  // no need to look any further
            }
        }
        if (justLetters) score = scoreWord(word);
        else score = 0;
        total += score;
        printf("Word score = %d, Total score = %d\n", score, total);
    }
    printf("TOTAL: %d\n", total);
    return 0;
}

// lfsrNext -- function to advance an LFSR for pseudorandom number generation
// uses global variable (lfsr)
// code from: https://en.wikipedia.org/wiki/Linear-feedback_shift_register
unsigned int lfsrNext(void) {
    lfsr ^= lfsr >> 7;
    lfsr ^= lfsr << 9;
    lfsr ^= lfsr >> 13;
    return lfsr;
}

// startTimer -- counts from 0 to (seconds-1)
// prints dots and numbers to help user keep track of time
// prints a message when time expires
void startTimer(unsigned int seconds) {
    unsigned int t = 0;
    unsigned int display = 1;
    while (t++ < seconds) {
        sleep(1);  // do nothing for one second
        // when wakes up, print either a dot or a number
        if ((display % 5) == 0) printf(" %d ", display);
        else printf(".");
        fflush(stdout);
        // at the end of each minute, go to a new line
        if (display == 60) { printf("\n"); display = 0; }
        display++;
    }
    if (display != 1) printf("\n");
    printf("\nTIME'S UP!\n");
}


// ----------------------------------------------------------------
// Put your function definitions below this line.
// Do not change anything above the line.
// You can also add more function declarations, if needed.

void seedRandom(unsigned int seed){
    int debug;

    if(seed != 0){
        lfsr = seed;
    }
    else{}

    debug = lfsr;

    debug = debug;

    return;
}

unsigned int getRandom(unsigned int limit){
    int debug;
    int num;

    lfsr = lfsrNext();

    num = lfsr;

    while(num > (limit - 1)){
        num = num % limit;
    }

    debug = lfsr;

    debug = debug;

    return num;
}

void permute(unsigned int values[], size_t n){
    int j;
    int i;

    for(i = 1; i < n; ++i){
        j = getRandom(i);

        values[i] = values[j];
    }

    return;
}

void shakeTray(){
    return;
}

void printTray(){
    return;
}

bool findWord(const char *word){
    return 0;
}

unsigned int scoreWord(const char *word){
    int count = 0;
    int points = 0;
    int i;

    findWord(word);

    for(i = 0; *(word + i) != '\0'; ++i){
        count += 1;
    }

    if((count == 3) || (count == 4)){
        points = 1;
    }
    if(count == 5){
        points = 2;
    }
    if(count == 6){
        points = 3;
    }
    if(count == 7){
        points = 5;
    }
    if(count >= 8){
        points = 11;
    }

    return points;
}
