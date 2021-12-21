#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int valid = 0;

    while (1) {
        char line[255];
        if (fgets(line, 255, stdin) == NULL) {
            fprintf(stderr, "Failed to fgets\n");
            return -1;
        }

        int fields = 0;
        char *tmpline;

        /* becoming painful in C.. */
        while (line[0] != '\n') {
            char key[4];
            char val[30] = {0};
            tmpline = line;
            while (sscanf(tmpline, "%3[^:]:%29s", key,val) == 2) {
                tmpline = tmpline + strlen(key) + strlen(val) + 2;

                if (strcmp(key,"byr") == 0) {
                    char *end;
                    unsigned long l = strtol(val, &end, 10);
                    if (l >= 1920 && l <= 2002)
                        fields++;
                } else if (strcmp(key,"iyr") == 0) {
                    char *end;
                    unsigned long l = strtol(val, &end, 10);
                    if (l >= 2010 && l <= 2020)
                        fields++;
                } else if (strcmp(key,"eyr") == 0) {
                    char *end;
                    unsigned long l = strtol(val, &end, 10);
                    if (l >= 2020 && l <= 2030)
                        fields++;
                } else if (strcmp(key,"hgt") == 0) {
                    char *end;
                    unsigned long l = strtol(val, &end, 10);
                    if (strchr(val, 'c') != NULL) {
                        if (l >= 150 && l <= 193)
                            fields++;
                    } else if (strchr(val, 'i') != NULL) {
                        if (l >= 59 && l <= 76)
                            fields++;
                    }
                } else if (strcmp(key,"hcl") == 0) {
                    if (val[0] == '#') {
                        fields++;
                        for (int i=1; i<strlen(val);  i++) {
                            if ((val[i] >= 48 && val[i] <= 57) ||
                                (val[i] >= 97 && val[i] <= 102))
                            {
                                continue;
                            } else {
                                fields--;
                                break;
                            }
                        }
                    }
                } else if (strcmp(key,"ecl") == 0) {
                    if (strcmp(val, "amb") == 0 ||
                        strcmp(val, "blu") == 0 ||
                        strcmp(val, "brn") == 0 ||
                        strcmp(val, "gry") == 0 ||
                        strcmp(val, "grn") == 0 ||
                        strcmp(val, "hzl") == 0 ||
                        strcmp(val, "oth") == 0)
                    {
                        fields++;
                    }
                } else if (strcmp(key,"pid") == 0) {
                    if (strlen(val) == 9) {
                        fields++;
                        for (int i=0; i<strlen(val); i++) {
                            if ((val[i] < 48 && val[i] > 57))
                            {
                                fields--;
                                break;
                            }
                        }
                    }
                } else if (strcmp(key,"cid") == 0) {
                    /* fields++; */
                }
            }

            if (fgets(line, 255, stdin) == NULL) {
                fprintf(stderr, "Failed to fgets\n");
                return -1;
            }
        }

        if (fields >= 7)
            valid++;

        printf("valid: %d\n", valid);
    }

    printf("valid: %d\n", valid);

    return 0;
}
