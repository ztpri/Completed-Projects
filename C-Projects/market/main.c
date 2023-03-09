// Zachary Price
// Program 3 - Fall 2020
// This program reads a data file that contains information about grocery purchases.
// A number of statistical analysis functions are called on the data retrieved from the file.
// The main() function is not particularly interesting, and is only provided for
// simple testing. The assignment is to implement the functions declared in groceryFile.h and stats.h.

#include <stdio.h>
#include <stdbool.h>

#include "groceryFile.h"
#include "stats.h"


int main() {
    FileInfo f;
    bool success = readFile("sample1.csv", &f);
    if (!success) {
        printf("Could not open file.\n");
        return 0;
    }
    printf("%d purchases\n", f.purchases);
    printf("%d members\n", f.members);
    printf("%d transactions\n", f.transactions);
    printf("%d items\n", f.items);
    printf("---\n");
    printf("Count(whole milk) = %d\n", countItem("whole milk", &f));
    printf("Count(whole milk,brown bread) = %d\n", countPair("whole milk", "brown bread", &f));
    printf("Support(whole milk) = %g\n", support("whole milk", &f));
    printf("Support(brown bread) = %g\n", support("brown bread", &f));
    printf("Confidence(whole milk -> brown bread) = %g\n", confidence("whole milk", "brown bread", &f));
    printf("Lift(whole milk -> brown bread) = %g\n", lift("whole milk", "brown bread", &f));
    printf("---\n");
    printf("Top 10 items: ");
    ItemCount items[10];
    int i, n;
    n = topItems(items, 10, &f);
    printf("(%d returned)\n", n);
    for (i=0; i < n; i++) {
        printf("%4d %s\n", items[i].count, items[i].item);
    }

    return 0;
}
