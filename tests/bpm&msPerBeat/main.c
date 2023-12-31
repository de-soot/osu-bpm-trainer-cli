#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <conio.h>
 
int main(void) {
    printf("BPM : ");
	double bpm = 120;
	scanf("%lf", &bpm);
	bpm += ( 2 * bpm * -(bpm < 0) ) + (bpm == 0); // bpm is never 0 or below

	printf("Time Signature (A/B) : ");
	double numerator, denominator;
	scanf("%lf/%lf", &numerator, &denominator);

	// numerator never below 0 and denominator never 0 or below
	numerator += ( 2 * numerator * -(numerator < 0) );
	denominator += ( 2 * denominator * -(denominator < 0) ) + (denominator == 0);

	double timeSignature = numerator / denominator;

	// bpm is 1/4th a whole note, so multiply it by 4 before multiplying with the time signature,
	// and 60000 is the amount of milliseconds in 1 second, so multipliying it by 4 gives 240000
	double msPerBeat = 240000 / bpm * timeSignature;

	printf("%lf", msPerBeat);

	_getch();
 
    return 0;
}
