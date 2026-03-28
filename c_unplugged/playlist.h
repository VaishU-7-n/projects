#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"

struct PlaylistNode {
    struct Song *song;
    struct PlaylistNode *next;
};

void addToPlaylist(struct PlaylistNode **head, struct Song *song);
void playNext(struct PlaylistNode **current);
void showPlaylist(struct PlaylistNode *head);

#endif

