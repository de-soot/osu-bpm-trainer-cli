#include <stdio.h>
#include <math.h>
#include <conio.h>
 
int main() {
    printf("BPM : ");
	double bpm = 60;
	scanf("%lf", &bpm);
	bpm += ( 2 * bpm * -(bpm < 0) ) + (bpm == 0); // bpm is never 0 or below

	printf("%lf", bpm);

	double timeSignature;
	{
		printf("Time Signature (A/B) : ");
		double numerator, denominator;
		scanf("%lf/%lf", &numerator, &denominator);

		// numerator and denominator and never 0 or below
		numerator += ( 2 * numerator * -(numerator < 0) ) + (numerator == 0);
		denominator += ( 2 * denominator * -(denominator < 0) ) + (denominator == 0);

		timeSignature = numerator / denominator;
	}

	printf("%lf", timeSignature);

	// bpm is 1/4th a whole note, so multiply it by 4 before multiplying with the time signature,
	// and 60000 is the amount of milliseconds in 1 second, so multipliying it by 4 gives 240000
	double msPerBeat = 240000 / bpm * timeSignature;

	printf("%lf", msPerBeat);

	_getch();
 
    return 0;
}
