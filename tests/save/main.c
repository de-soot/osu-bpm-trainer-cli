#include <stdio.h>
#include <string.h>

int main() {
    printf("Save results ? (Y/N) : ");
	char save;
	scanf("%c", &save);

	if(save == 'y' || save == 'Y') {
		// write stats in a .txt file where each line is a record
		// compare current accuracy with previous record's accuracies with the same BPM and Total hit count
		// and print personal best and current accuracy
	}
}