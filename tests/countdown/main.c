#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
 
int main(void) {
	long unsigned int msPerCount = 250;
    char display[] = "3...";
	int counter = 3, i = 0, displayEmpty;

	PlaySound(TEXT("audio/count3s.wav"), NULL, SND_FILENAME | SND_ASYNC);
	
	do {
		printf("\r%s", display); // prints and moves cursor back to start of line to print over the previous one
		Sleep(msPerCount);

		displayEmpty = (i == 3);
		counter -= displayEmpty;
		display[3-i] = ' ';
		++i;
		i *= !displayEmpty; // resets i to 0 when display is empty
		
		if(!displayEmpty) continue;

		display[0] = (char)(counter + (int)'0');
		display[1] = '.';
		display[2] = '.';
		display[3] = '.';

		switch(counter) {
			case 1:
				PlaySound(TEXT("audio/count1s.wav"), NULL, SND_FILENAME | SND_ASYNC);
				break;
			case 2:
				PlaySound(TEXT("audio/count2s.wav"), NULL, SND_FILENAME | SND_ASYNC);
				break;
		}
	} while(counter > 0);

	printf("\r%s\n\n", "-----------------------------------------------------GO!-----------------------------------------------------");
	_getch();
	return 0;
}
