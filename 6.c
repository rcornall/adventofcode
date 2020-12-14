#include <stdio.h>
#include <string.h>

int main()
{
    int ans = 0;

    while (1) {
        char line[255];
        if (fgets(line, 255, stdin) == NULL) {
            fprintf(stderr, "Failed to fgets\n");
            return -1;
        }

        int unique = 0;
        _Bool map[255] = {0};

        while (line[0] != '\n') {
            char tmp[255];
            sscanf(line, "%s", tmp);
            for (int i=0; i<strlen(tmp); i++) {
                if (!map[tmp[i]]) {
                    map[tmp[i]] = 1;
                    unique++;
                }
            }

            if (fgets(line, 255, stdin) == NULL) {
                fprintf(stderr, "Failed to fgets\n");
                return -1;
            }
        }

        ans = ans + unique;

        printf("ans: %d\n", ans);
    }
}
