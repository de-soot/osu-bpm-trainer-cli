#include <stdio.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <sys/timeb.h>

long long int msSystemTime() {
    struct _timeb timeBuffer;
    _ftime(&timeBuffer);
    return ( (timeBuffer.time * 1000) + (long long)timeBuffer.millitm );
}

void countdown(long unsigned int msPerCount) {
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

	printf("\r%s\r", "GO!");
	Sleep(msPerCount);
}

int main() {
	printf("BPM : ");
	float bpm;
	scanf("%f", &bpm);
	bpm += ( 2 * bpm * -(float)(bpm < 0) ) + (bpm == 0); // bpm is never below 0

	float timeSignature;
	{
		printf("Time Signature (A/B) : ");
		float numerator, denominator;
		scanf("%f/%f", &numerator, &denominator);
		timeSignature = numerator / denominator;
	}

	// bpm is 1/4th a whole note, so multiply it by 4 for the time signature
	// 60000 is the amount of milliseconds in 1 second, multiplied by 4 gives 240000
	long long int msPerBeat = (long long)trunc( (float)240000 / bpm * timeSignature );

	printf("Beat limit : ");
	long long int beatLimit;
	scanf("%lld", &beatLimit);

	printf("Press any key to start or press 'Q' to stop anytime\n");
	
	char keyPress = (char)_getch();

	countdown( (long unsigned)msPerBeat );

	long long int startTime = msSystemTime(), currentTime;
	long long int beatTime;
	long long int beatsSinceStart, beatsSinceStartPrevious;
	long long int hitTimeDiff;
	float hitAccuracy, totalAccuracy = 100;
	char earlyLate[8];
	float hitCount = 0;
	int misses = 0;
	int beatHit = 0;

	do {
		currentTime = msSystemTime();

		beatsSinceStart = (long long)trunc( (float)(currentTime - startTime) / (float)msPerBeat );
		beatTime = startTime + (long long)( (float)0.5 * (float)msPerBeat ) + (beatsSinceStart * msPerBeat);

		if( !beatHit && (beatsSinceStart != beatsSinceStartPrevious) ) {
			misses += 1;
			printf("MISS\n");
		}
		
		beatHit -= beatHit && (beatsSinceStart != beatsSinceStartPrevious);

		beatsSinceStartPrevious = beatsSinceStart;

		// gets key presses without stopping the program
		if( _kbhit() ) {
			keyPress = (char)_getch();
			beatHit = 1;
			++hitCount;

			hitTimeDiff = currentTime - beatTime;
			
			if(hitTimeDiff < 0) {
				strcpy(earlyLate, "EARLY");
			} else if(hitTimeDiff > 0) {
				strcpy(earlyLate, "LATE");
			} else {
				strcpy(earlyLate, "PERFECT");
			}

			// makes hitTimeDiff positive if negative
			hitTimeDiff += ( 2 * hitTimeDiff * -(hitTimeDiff < 0) );

			hitAccuracy = (float)(hitTimeDiff / msPerBeat);
			totalAccuracy = (totalAccuracy + hitAccuracy) / hitCount;

			printf("%lld ms %s\n", hitTimeDiff, earlyLate);
		}
	} while( (keyPress != 'q') && ( (beatsSinceStart < beatLimit) || (beatLimit <= 0) ) );

	printf("Press enter to exit the program or enter 'S' to save results : ");

	char save = (char)getchar();

	if(save == 's' || save == 'S') {
		// write stats in a .txt file where each line is a record
		// BPM : %f, Accuracy : %f, Total hit count : %d

		// read using
		// fscanf("BPM : %f, Time Signature : %f/%f Accuracy : %f, Total hit count : %d", &bpmFile, &totalAccuracyFile, &hitCountFile)

		// compare current accuracy with previous record's accuracies with the same BPM and Total hit count
		// and print personal best and current accuracy
	}

	return 0;
}
