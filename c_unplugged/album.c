#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "album.h"

void addAlbum(struct Album **head, const char *name) {
    struct Album *newAlbum = malloc(sizeof(struct Album));
    strcpy(newAlbum->name, name);
    newAlbum->songs = NULL;
    newAlbum->next = *head;
    *head = newAlbum;
    printf("Album '%s' added.\n", name);
}

void addSongToAlbum(struct Album *head, const char *albumName, struct Song *song) {
    for (struct Album *a = head; a; a = a->next) {
        if (strcasecmp(a->name, albumName) == 0) {
            struct Song *newSong = malloc(sizeof(struct Song));
            *newSong = *song;
            newSong->next = a->songs;
            a->songs = newSong;
            printf("Added '%s' to album '%s'.\n", song->title, albumName);
            return;
        }
    }
    printf("Album '%s' not found.\n", albumName);
}

void listAlbums(struct Album *head) {
    for (struct Album *a = head; a; a = a->next) {
        printf("\nAlbum: %s\n", a->name);
        struct Song *s = a->songs;
        while (s) {
            printf("  - %s by %s\n", s->title, s->artist);
            s = s->next;
        }
    }
}

void saveAlbums(struct Album *head) {
    FILE *fp = fopen("albums.txt", "w");
    if (!fp) return;

    for (struct Album *a = head; a; a = a->next) {
        fprintf(fp, "#ALBUM %s\n", a->name);
        for (struct Song *s = a->songs; s; s = s->next)
            fprintf(fp, "%s, %s\n", s->title, s->artist);
        fprintf(fp, "#END\n");
    }
    fclose(fp);
}

void loadAlbums(struct Album **head) {
    FILE *fp = fopen("albums.txt", "r");
    if (!fp) return;

    char line[256];
    struct Album *current = NULL;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';

        if (strncmp(line, "#ALBUM", 6) == 0) {
            struct Album *newAlbum = malloc(sizeof(struct Album));
            sscanf(line, "#ALBUM %[^\n]", newAlbum->name);
            newAlbum->songs = NULL;
            newAlbum->next = *head;
            *head = newAlbum;
            current = newAlbum;
        } else if (strncmp(line, "#END", 4) == 0) {
            current = NULL;
        } else if (current) {
            struct Song *newSong = malloc(sizeof(struct Song));
            sscanf(line, " %[^,], %[^\n]", newSong->title, newSong->artist);
            newSong->next = current->songs;
            current->songs = newSong;
        }
    }
    fclose(fp);
}
