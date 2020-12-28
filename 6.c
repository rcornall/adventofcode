#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int ans = 0;

    while (1) {
        char line[255];
        if (fgets(line, 255, stdin) == NULL) {
            fprintf(stderr, "Failed to fgets\n");
            return -1;
        }

        /* points to arrays of maps, assume max 10 ppl per test. */
        _Bool *maps[10] = {0};

        int unique = 0; /* count unique answers */
        int answers[255] = {0}; /* store unique answers */
        _Bool uniques[255] = {0}; /* cache if already stored. */

        /* build a map for each persons answers,
         * then check all maps contain the answer */
        int persons = 0;
        while (line[0] != '\n') {
            maps[persons] = malloc(255);
            _Bool *map = maps[persons];
            persons++;

            char tmp[255];
            sscanf(line, "%s", tmp);
            for (int i=0; i<strlen(tmp); i++) {
                if (!map[tmp[i]]) {
                    map[tmp[i]] = 1;

                    if (!uniques[tmp[i]]) {
                        uniques[tmp[i]] = 1;
                        answers[unique++] = tmp[i];
                    }
                }
            }

            if (fgets(line, 255, stdin) == NULL) {
                fprintf(stderr, "Failed to fgets\n");
                return -1;
            }
        }

        for (int i=0; i<unique; i++) {
            _Bool missing = 0;
            printf("ans %d\n", answers[i]);
            for (int j=0; j<persons; j++) {
                printf("%d\n", maps[j][answers[i]]);
                if (!maps[j][answers[i]]) {
                    missing = 1;
                    break;
                }
            }
            if (!missing)
                ans++;
        }

        /* for (int i=0; i<persons; i++) { */
            /* free(maps[i]); */
            /* maps[i] = NULL; */
        /* } */

        printf("ans: %d\n", ans);
    }
}
