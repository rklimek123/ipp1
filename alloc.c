#include <stdlib.h>

//Validates if memory has been successfully allocated to a pointer.
void validateAlloc(void *ptr) {
    if (ptr == NULL) {
        perror("Blad alokacji pamieci\n");
        exit(1);
    }
}

//Allocate memory for a string to a given pointer and validate allocation.
void allocateAndValidateStr(char **baseStr, int targetLength) {
    *baseStr = (char *)malloc(targetLength * sizeof(char));
    validateAlloc(*baseStr);
}

//Reallocate memory for a string to a certain length and validate allocation.
void reallocateAndValidateStr(char **baseStr, int targetLength) {
    *baseStr = (char *)realloc(*baseStr, targetLength * sizeof(char));
    validateAlloc(*baseStr);
}

int main() {
    return 0;
}