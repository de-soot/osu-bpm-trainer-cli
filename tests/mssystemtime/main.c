#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <sys/timeb.h>

int main() {
    struct _timeb timeBuffer;
    _ftime(&timeBuffer);
    printf("%lf", (double)( (timeBuffer.time * 1000) + (long long)timeBuffer.millitm ));

    return 0;
}
