#include <stdio.h>
#include <sys/timeb.h>

int main() {
    struct _timeb timeBuffer;
    _ftime(&timeBuffer);
    printf("%lld", ( (timeBuffer.time * 1000) + (long long int)timeBuffer.millitm ));

    return 0;
}
