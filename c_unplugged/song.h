#ifndef SONG_H
#define SONG_H

struct Song {
    char title[100];
    char artist[100];
    struct Song *next;
};

void loadSongs(struct Song **head);
void listSongs(struct Song *head);
struct Song* findSong(struct Song *head, const char *title);

#endif
