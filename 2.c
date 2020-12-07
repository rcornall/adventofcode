#include <stdio.h>

int main()
{
    int min, max;
    char letter;
    char password[30];

    int baddies = 0;
    int nopasswords = 0;
    int valid = 0;
    while (scanf("%d-%d %c: %s", &min, &max, &letter, password) != EOF) {
        nopasswords++;
        int count = 0;
        for (int i=0; i<30; i++) {
            if (password[i] == '\0') {
                if (count < min)
                    baddies++;
                break;
            }

            if (password[i] == letter) {
                count++;
                if (count > max) {
                    baddies++;
                    break;
                }
            }
        }


        // part 2
        if ((password[min-1] == letter) ^ (password[max-1] == letter)) {
            valid++;
        }
    }

    printf("ans: %d\n", nopasswords-baddies);
    printf("ans2: %d\n", valid);


    return 0;
}
