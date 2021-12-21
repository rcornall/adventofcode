#include <stdio.h>

int main()
{
    char in[30];
    int trees=0;

    int index1=0;
    int index1d2=0;
    int index3=0;
    int index5=0;
    int index7=0;

    int trees1=0;
    int trees1d2=0;
    int trees3=0;
    int trees5=0;
    int trees7=0;

    scanf("%s", in); // skip first line

    int i=1;
    while(scanf("%s", in) != EOF) {
        index1 = ( index1 + 1 ) % 31;
        index3 = ( index3 + 3 ) % 31;
        index5 = ( index5 + 5 ) % 31;
        index7 = ( index7 + 7 ) % 31;

        if (in[index1] == '#') {
            /* printf("found tree 1: %d, %s\n", index1, in); */
            trees1++;
        }
        if (in[index3] == '#') {
            /* printf("found tree 3: %d, %s\n", index3, in); */
            trees3++;
        }
        if (in[index5] == '#') {
            /* printf("found tree 5: %d, %s\n", index5, in); */
            trees5++;
        }
        if (in[index7] == '#') {
            /* printf("found tree 7: %d, %s\n", index7, in); */
            trees7++;
        }

        printf("i %d\n", i);
        /* printf("%s\n", in); */
        if (i++%2 != 0)
        {
            printf("skipping\n");
            continue;
        }

        index1d2 = ( index1d2 + 1 ) % 31;
        if (in[index1d2] == '#') {
            printf("found tree 1d2: %d, %s\n", index1d2, in);
            trees1d2++;
        }
    }

    printf("%d\n", (trees1 * trees3 * trees5 * trees7 * trees1d2));

    return 0;
}
