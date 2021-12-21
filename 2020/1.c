#include <stdio.h>
#include <stdlib.h>

int main()
{
    int array[2020];
    _Bool map[2020];

    int entry;
    int size=0;
    while (scanf("%d", &entry) != EOF) {
        /* printf("%d\n", entry); */
        array[size++] = entry;
        map[entry]=1;
    }

    for (int j=0; j < size-1; j++) {
        int other = 2020-array[j];
        if (map[other]) {
            printf("ans1: %d\n", array[j] * other);
            break;
        }
    }

    // part2
    for (int i=0; i < size-1; i++) {
        for (int j=size-1; j >= 0; j--) {
            int other = 2020 - (array[i] + array[j]);
            if (other >= 0 && map[other]) {
                printf("ans2: %d\n", array[i] * array[j] * other);
                exit(0);
            }
        }
    }

    return 0;
}
