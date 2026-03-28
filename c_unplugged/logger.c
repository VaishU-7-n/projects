#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logger.h"

void logCommand(const char *cmd) {
    FILE *fp = fopen("log.txt", "a");
    if (!fp) return;

    time_t now = time(NULL);
    fprintf(fp, "[%s] %s\n", strtok(ctime(&now), "\n"), cmd);
    fclose(fp);
}

void showLog() {
    FILE *fp = fopen("log.txt", "r");
    if (!fp) {
        printf("No log file found.\n");
        return;
    }

    char line[256];
    printf("\n--- Command History ---\n");
    while (fgets(line, sizeof(line), fp))
        printf("%s", line);

    fclose(fp);
}

