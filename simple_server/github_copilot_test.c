//open main.c only using fopen
#include <stdio.h>
#include <string.h>

void open_file_example() {
    FILE *file = fopen("main.c", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
}

void main() {
    open_file_example();
}