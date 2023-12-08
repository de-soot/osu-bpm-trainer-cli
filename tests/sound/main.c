#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>

int main(void) {
    PlaySound(TEXT("metronome.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    _getch();

    return 0;
}
