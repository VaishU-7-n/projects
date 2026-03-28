#ifndef ALBUM_H
#define ALBUM_H

#include "song.h"

struct Album {
    char name[100];
    struct Song *songs;
    struct Album *next;
};

void loadAlbums(struct Album **head);
void saveAlbums(struct Album *head);
void listAlbums(struct Album *head);
void addAlbum(struct Album **head, const char *name);
void addSongToAlbum(struct Album *head, const char *albumName, struct Song *song);

#endif

