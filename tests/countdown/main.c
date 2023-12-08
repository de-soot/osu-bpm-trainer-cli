#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
 
int main(void) {
	long unsigned int msPerCount = 250;
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

	return 0;
}
