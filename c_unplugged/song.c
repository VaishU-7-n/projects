#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"

void loadSongs(struct Song **head) {
    FILE *fp = fopen("songs.txt", "r");
    if (!fp) {
        printf("Error: could not open songs.txt\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';

        struct Song *newSong = malloc(sizeof(struct Song));
        if (!newSong) continue;

        if (sscanf(line, " %[^,], %[^\n]", newSong->title, newSong->artist) == 2) {
            newSong->next = *head;
            *head = newSong;
        } else {
            free(newSong);
        }
    }
    fclose(fp);
}

void listSongs(struct Song *head) {
    printf("\n--- Song Library ---\n");
    for (struct Song *p = head; p; p = p->next)
        printf("Title: %s | Artist: %s\n", p->title, p->artist);
}

struct Song* findSong(struct Song *head, const char *title) {
    for (struct Song *p = head; p; p = p->next)
        if (strcasecmp(p->title, title) == 0)
            return p;
    return NULL;
}
