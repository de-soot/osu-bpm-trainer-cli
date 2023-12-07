#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>

int main(void) {
    LARGE_INTEGER startTick, currentTick, clockFrequency;
    QueryPerformanceCounter(&startTick);
	QueryPerformanceFrequency(&clockFrequency);

    double msTimeElapsed;

    do {
	    QueryPerformanceCounter(&currentTick);
        msTimeElapsed = (double)(currentTick.QuadPart - startTick.QuadPart) / (double)clockFrequency.QuadPart * 1000;
        printf("%lf\n", msTimeElapsed);
        Sleep(0); // sleeps until next frame
    } while(1);

    return 0;
}
