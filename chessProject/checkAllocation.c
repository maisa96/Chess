#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

void checkAllocation(void* pointer) {
	if (pointer == NULL) {
		printf("Allocation failed!!");
		exit(1);
	}
}
void checkOpenFile(void* pointer) {
	if (pointer == NULL) {
		printf("failed open file!!");
		exit(1);
	}
}