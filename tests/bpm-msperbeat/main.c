#include <stdio.h>
#include <math.h>
#include <conio.h>
 
int main() {
    printf("BPM : ");
	int bpm;
	scanf("%d", &bpm);
	bpm += ( 2 * bpm * -(bpm < 0) ) + (bpm == 0); // bpm is never below 0
	printf("BPM : %d\n", bpm);

	long long int msPerBeat = (long long int)trunc(60000 / bpm);
	printf("Milliseconds Per Beat : %lld", msPerBeat);

	_getch();
 
    return 0;
}
