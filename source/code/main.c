#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>

double msClockTime(void) {
    LARGE_INTEGER clockFrequency;
    QueryPerformanceFrequency(&clockFrequency);
	LARGE_INTEGER currentTick;
	QueryPerformanceCounter(&currentTick);
    return (double)currentTick.QuadPart / (double)clockFrequency.QuadPart * 1000;
}

void countdown(const long unsigned int msPerCount) {
	char display[] = "3...";
	int counter = 3, i = 0, displayEmpty;

	PlaySound(TEXT("audio/count3s.wav"), NULL, SND_FILENAME | SND_ASYNC);
	
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

			if		(counter == 2) { PlaySound(TEXT("audio/count2s.wav"), NULL, SND_FILENAME | SND_ASYNC); }
			else if (counter == 1) { PlaySound(TEXT("audio/count1s.wav"), NULL, SND_FILENAME | SND_ASYNC); }
		}

		++i;
		i *= !displayEmpty; // resets i to 0 when display is empty
	} while(counter > 0);

	printf("\r%s\n\n", "-----------------------------------------------------GO!-----------------------------------------------------");
}

int main(void) {
	printf("BPM : ");
	double bpm = 120;
	scanf("%lf", &bpm);
	bpm += ( 2 * bpm * -(bpm < 0) ) + (bpm == 0); // bpm never 0 or below

	printf("Time Signature (A/B) : ");
	double numerator, denominator;
	scanf("%lf/%lf", &numerator, &denominator);

	// numerator never below 0 and denominator never 0 or below
	numerator += ( 2 * numerator * -(numerator < 0) );
	denominator += ( 2 * denominator * -(denominator < 0) ) + (denominator == 0);

	double timeSignature = numerator / denominator;

	// bpm is 1/4th a whole note, so multiply it by 4 before multiplying with the time signature.
	// 60000 is the amount of milliseconds in 1 second, so multipliying it by 4 gives 240000
	double msPerBeat = 240000 / bpm * timeSignature;

	printf("Beat limit : ");
	long long unsigned int beatLimit = 0;
	scanf("%llu", &beatLimit);

	printf("Play along with a metronome ? (Y/N) : ");
	char metronome = 'y';
	scanf("%1s", &metronome);

	printf("Play along with music ? (Y/N) : ");
	char music = 'y';
	scanf("%1s", &music);

	printf("Press any key to start or press 'Q' to stop anytime\n");
	
	char keyPress = (char)_getch();

	countdown( (long unsigned int)msPerBeat );

	double startTime = msClockTime(), currentTime, beatTime, hitTimeDiff, hitAccuracy, totalAccuracy = 100;
	long long unsigned int beatsSinceStart, beatsSinceStartPrevious = 0, hitCount = 0, misses = 0, beatHit = 0;
	char *earlyLate;

	if(music == 'y' || music == 'Y') { PlaySound(TEXT("audio/music.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); }

	do {
		currentTime = msClockTime();
		beatsSinceStart = (long long unsigned int)trunc( (currentTime - startTime) / msPerBeat );
		beatTime = startTime + ( msPerBeat * 0.5 ) + ( (double)beatsSinceStart * msPerBeat );

		if( (beatsSinceStart != beatsSinceStartPrevious) && !beatHit ) { misses += 1; printf("MISS\n"); }
		if( (currentTime >= beatTime - 0.01) && (currentTime <= beatTime + 0.01) && (metronome == 'y' || metronome == 'Y') )
			{ PlaySound(TEXT("audio/metronome.wav"), NULL, SND_FILENAME | SND_ASYNC); }
		
		// if beatHit is 1 and there is a new beat, then reset beatHit to 0
		beatHit -= beatHit && (beatsSinceStart != beatsSinceStartPrevious);

		beatsSinceStartPrevious = beatsSinceStart;

		// gets key presses without stopping the program
		if( _kbhit() ) {
			PlaySound(TEXT("audio/hitsound.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
	} while( (keyPress != 'q') && ( (beatsSinceStart < beatLimit) || (beatLimit == 0) ) );

	// display results
	printf("\n---------------------------------------------------RESULTS---------------------------------------------------\n\n=============================================================================================================\n| BPM : %lf | Time Signature : %lf/%lf | Accuracy : %lf | Hit count : %llu | Misses : %llu |\n=============================================================================================================\n",
		bpm, numerator, denominator, totalAccuracy, hitCount, misses);

	// saves results
	FILE *saveFile = fopen("saves.csv", "a+");
	if(saveFile == NULL) { return 1; } // if file not found

	time_t t;
	if( time(&t) == (time_t)(-1) ) { return 2; } // if error getting time
	struct tm date;
	if (_gmtime64_s(&date, &t) != 0) { return 3; } // if error getting date

	fprintf(saveFile, "%lf,%lf/%lf,%lf,%llu,%llu,%d-%02d-%02d %02d:%02d\n",
	bpm, numerator, denominator, totalAccuracy, hitCount, misses,
	date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min);

	// Find personal best in saves.csv with the same (bpm * timeSignatures), then compare accuracy with current results.
	// If current results are better, print previous best and "New Personal Best!".

	fclose(saveFile);

	_getch();

	return 0;
}
