#include <stdio.h>
#include <string.h>

struct passport {
    char* byr;
    char* iyr;
    char* eyr;
    char *hgt;
    char *hcl;
    char *ecl;
    char* pid;
    char* cid;
};

int main()
{
    int valid = 0;

    while (1) {
        struct passport p;

        char line[255];
        char *tmpline;
        if (fgets(line, 255, stdin) == NULL) {
            fprintf(stderr, "Failed to fgets\n");
            return -1;
        }

        int fields = 0;

        while (line[0] != '\n') {


            char key[4];
            char val[30] = {0};
            tmpline = line;
            while (sscanf(tmpline, "%3[^:]:%s", key,val) == 2) {
                /* key[3] = '\0'; */
                /* val[3] = '\0'; */
                printf("k,v: %s,%s\n", key, val);
                tmpline = tmpline + strlen(key) + strlen(val) + 2;
                printf("%lu %lu %d\n", strlen(key), strlen(val), 1);
                printf("tmpline: %s\n", tmpline);

                if (strcmp(key,"byr") == 0) {
                    fields++;
                    p.byr = strdup(val);
                } else if (strcmp(key,"iyr") == 0) {
                    fields++;
                    p.iyr = strdup(val);
                } else if (strcmp(key,"eyr") == 0) {
                    fields++;
                    p.eyr = strdup(val);
                } else if (strcmp(key,"hgt") == 0) {
                    fields++;
                    p.hgt = strdup(val);
                } else if (strcmp(key,"hcl") == 0) {
                    fields++;
                    p.hcl = strdup(val);
                } else if (strcmp(key,"ecl") == 0) {
                    fields++;
                    p.ecl = strdup(val);
                } else if (strcmp(key,"pid") == 0) {
                    fields++;
                    p.pid = strdup(val);
                } else if (strcmp(key,"cid") == 0) {
                    /* fields++; */
                    p.cid = strdup(val);
                }
            }

            if (fgets(line, 255, stdin) == NULL) {
                fprintf(stderr, "Failed to fgets\n");
                return -1;
            }
        }

        if (fields >= 7)
            valid++;

        printf("processed line: %s, valid: %d\n", line, valid);

        /* new line */
        printf("new line..\n");
    }

    printf("valid: %d\n", valid);

    return 0;
}
