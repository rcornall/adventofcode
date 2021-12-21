#include <unistd.h>
#include <stdio.h>
#include <math.h>

void printArr(int *arr, size_t size)
{
    printf("arr size %lu: ", size);
    for (int i = 0; i < size; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

int getSpot(char *fbs, int len)
{
    int spots = pow(2, len);
    int numbers[spots];
    for (int i=0; i < spots; i++) {
        numbers[i]=i;
    }

    // for navigating the array
    int *ptr = numbers;

    int size = spots;
    for (int i=0; i < len; i++) {
        if (fbs[i] == 'F' || fbs[i] == 'L') {
            ptr = ptr;
        } else {
            ptr = &ptr[size/2];
        }
        size = size/2;
    }

    return ptr[0];
}

int main()
{
    char in[10];
    int max = 0;
    int seats[128*8] = {0};
    int row, col;
    int seat;
    char *tmp;

    while (scanf("%10s", in) != EOF) {
        /* printf("%s\n", in); */

        row = getSpot(in, 7);
        tmp = &in[7];
        col = getSpot(tmp, 3);

        seat = (row*8) + col;

        // seat assigned.
        seats[seat]=1;

        if (seat > max)
            max=seat;
    }

    int ans = 0;
    for (int i=0; i<(128*8); i++) {
        if (seats[i] == 0) {
            if (seats[i-1] && seats[i+1]) {
                ans = i;
                break;
            }
        }
    }
    printf("max seatid: %d\n", max);
    printf("our seatid: %d\n", ans);
    return 0;
}
