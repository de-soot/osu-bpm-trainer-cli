#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <time.h>

int main(void) {
	double bpm = 222.22, numerator = 3, denominator = 4, totalAccuracy = 72.7;
	long long unsigned int hitCount = 1337, misses = 1;

	FILE *saveFile = fopen("saves.csv", "a+");
	if(saveFile == NULL) { return 1; } // file not found

    printf("Save results ? (Y/N) : ");
	char save = 'y';
	scanf("%1s", &save);

	if(save == 'y' || save == 'Y') {
		time_t t;
		if( time(&t) == (time_t)(-1) ) { return 2; } // error getting time
		struct tm date;
		if (_gmtime64_s(&date, &t) != 0) { return 3; } // error getting date

		fprintf(saveFile, "%lf,%lf/%lf,%lf,%llu,%llu,%d-%02d-%02d %02d:%02d\n",
		bpm, numerator, denominator, totalAccuracy, hitCount, misses,
		date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min);
	}

	fclose(saveFile);

	return 0;
}
