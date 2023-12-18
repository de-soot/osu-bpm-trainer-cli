#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <conio.h>

int main(void) {
    long long unsigned int hitCount = 16, misses = 2;
    double bpm = 128, numerator = 1, denominator = 8, totalAccuracy = 4;

    printf("\n---------------------------------------------------RESULTS---------------------------------------------------\n\n=============================================================================================================\n| BPM : %lf | Time Signature : %lf/%lf | Accuracy : %lf | Hit count : %llu | Misses : %llu |\n=============================================================================================================\n",
		bpm, numerator, denominator, totalAccuracy, hitCount, misses);

    _getch();

    return 0;
}
