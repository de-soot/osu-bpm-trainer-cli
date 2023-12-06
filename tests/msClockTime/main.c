#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>

int main() {
    LARGE_INTEGER startTick, currentTick, clockFrequency;
    QueryPerformanceCounter(&startTick);
	QueryPerformanceFrequency(&clockFrequency);

    double msTimeElapsed;

    do {
	    QueryPerformanceCounter(&currentTick);
        msTimeElapsed = (double)( (currentTick.QuadPart - startTick.QuadPart) / clockFrequency.QuadPart * 1000 );
        printf("%lf", msTimeElapsed);
        Sleep(1000);
    } while(1);

    return 0;
}
