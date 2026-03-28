#include <stdio.h>
#include <stdlib.h>
#include "playlist.h"

void addToPlaylist(struct PlaylistNode **head, struct Song *song) {
    struct PlaylistNode *newNode = malloc(sizeof(struct PlaylistNode));
    newNode->song = song;

    if (!*head) {
        *head = newNode;
        newNode->next = *head;
    } else {
        struct PlaylistNode *temp = *head;
        while (temp->next != *head)
            temp = temp->next;
        temp->next = newNode;
        newNode->next = *head;
    }
    printf("Added '%s' to playlist.\n", song->title);
}

void playNext(struct PlaylistNode **current) {
    if (!*current) {
        printf("Playlist empty.\n");
        return;
    }
    *current = (*current)->next;
    printf("Now playing: %s by %s\n", (*current)->song->title, (*current)->song->artist);
}

void showPlaylist(struct PlaylistNode *head) {
    if (!head) {
        printf("Playlist empty.\n");
        return;
    }
    struct PlaylistNode *temp = head;
    do {
        printf("%s by %s\n", temp->song->title, temp->song->artist);
        temp = temp->next;
    } while (temp != head);
}
