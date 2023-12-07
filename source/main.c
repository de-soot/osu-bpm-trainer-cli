#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>

double msClockTime(void) {
    LARGE_INTEGER clockFrequency;
    QueryPerformanceFrequency(&clockFrequency);

	LARGE_INTEGER currentTick;
	QueryPerformanceCounter(&currentTick);

    return (double)currentTick.QuadPart / (double)clockFrequency.QuadPart * 1000;
}

void countdown(long unsigned msPerCount) {
	char display[] = "3...";
	int counter = 3, i = 0, displayEmpty;

	do {
		printf("\r%s", display); // prints and moves cursor back to start of line to print over the previous one
		Sleep(msPerCount);

		displayEmpty = (i == 3);
		counter -= displayEmpty;

		display[3-i] = ' ';

		if(displayEmpty) {
			display[0] = (char)(counter + (int)'0');
			display[1] = '.';
			display[2] = '.';
			display[3] = '.';
		}

		++i;
		i *= !displayEmpty; // resets i to 0 when display is empty
	} while(counter > 0);

	printf("\r%s\n", "GO!");
}

int main(void) {
	printf("BPM : ");
	double bpm = 60;
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

	printf("Beat limit (0 == infinite): ");
	long long int beatLimit = 0;
	scanf("%lld", &beatLimit);

	printf("Press any key to start or press 'Q' to stop anytime\n");
	
	char keyPress = (char)_getch();

	countdown( (long unsigned)msPerBeat );

	double startTime = msClockTime(), currentTime, beatTime, hitTimeDiff, hitAccuracy, totalAccuracy = 100;
	long long int beatsSinceStart, beatsSinceStartPrevious, hitCount = 0, misses = 0, beatHit = 0;
	char* earlyLate;

	do {
		currentTime = msClockTime();

		beatsSinceStart = (long long int)trunc( (currentTime - startTime) / msPerBeat );
		beatTime = startTime + ( 0.5 * msPerBeat ) + ( (double)beatsSinceStart * msPerBeat );

		if( !beatHit && (beatsSinceStart != beatsSinceStartPrevious) ) {
			misses += 1;
			printf("MISS\n");
		}
		
		// if beatHit is 1 and there is a new beat, then reset beatHit to 0
		beatHit -= beatHit && (beatsSinceStart != beatsSinceStartPrevious);

		beatsSinceStartPrevious = beatsSinceStart;

		// gets key presses without stopping the program
		if( _kbhit() ) {
			keyPress = (char)_getch();
			beatHit = 1;
			++hitCount;

			hitTimeDiff = currentTime - beatTime;
			
			if(hitTimeDiff < 0) {
				earlyLate = "EARLY";
			} else if(hitTimeDiff > 0) {
				earlyLate = "LATE";
			} else {
				earlyLate = "PERFECT";
			}

			// makes hitTimeDiff positive if negative
			hitTimeDiff += ( 2 * hitTimeDiff * -(hitTimeDiff < 0) );

			hitAccuracy = (hitTimeDiff / msPerBeat);
			totalAccuracy = (totalAccuracy + hitAccuracy) / (double)hitCount;

			printf("%s - %lf ms\n", earlyLate, hitTimeDiff);
		}
	} while( (keyPress != 'q') && ( (beatsSinceStart < beatLimit) || (beatLimit <= 0) ) );

	printf("Save results ? (Y/N) : ");
	char save = 'y';
	scanf("%c", &save);

	if(save == 'y' || save == 'Y') {
		// write stats in a .csv file where each line is a record
		// compare current accuracy with previous record's accuracies with the same BPM and Total hit count
		// and print personal best and current accuracy
	}

	return 0;
}
