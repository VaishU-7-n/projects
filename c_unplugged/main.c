#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "song.h"
#include "album.h"
#include "playlist.h"
#include "logger.h"

int main() {
    struct Song *library = NULL;
    struct Album *albums = NULL;
    struct PlaylistNode *playlist = NULL;
    struct PlaylistNode *current = NULL;

    loadSongs(&library);
    loadAlbums(&albums);

    char cmd[100];
    printf("Welcome to C-Unplugged! Type 'help' for commands.\n");

    while (1) {
        printf("\nC-Unplugged> ");
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strcspn(cmd, "\n")] = '\0';
        logCommand(cmd);

        if (strcasecmp(cmd, "help") == 0) {
            printf("Commands:\n");
            printf("  list_songs\n  list_albums\n  add_album <name>\n  add_song <song> <album>\n");
            printf("  show_log\n  add_to_playlist <song>\n  show_playlist\n  play_next\n  exit\n");
        }
        else if (strcasecmp(cmd, "list_songs") == 0)
            listSongs(library);
        else if (strcasecmp(cmd, "list_albums") == 0)
            listAlbums(albums);
        else if (strncmp(cmd, "add_album ", 10) == 0)
            addAlbum(&albums, cmd + 10);
        else if (strncmp(cmd, "add_song ", 9) == 0) {
            char songName[100], albumName[100];
            if (sscanf(cmd + 9, "%[^,], %[^\n]", songName, albumName) == 2) {
                struct Song *s = findSong(library, songName);
                if (s) addSongToAlbum(albums, albumName, s);
                else printf("Song not found.\n");
            } else printf("Usage: add_song <song>, <album>\n");
        }
        else if (strncmp(cmd, "add_to_playlist ", 16) == 0) {
            struct Song *s = findSong(library, cmd + 16);
            if (s) {
                addToPlaylist(&playlist, s);
                if (!current) current = playlist;
            } else printf("Song not found.\n");
        }
        else if (strcasecmp(cmd, "show_playlist") == 0)
            showPlaylist(playlist);
        else if (strcasecmp(cmd, "play_next") == 0)
            playNext(&current);
        else if (strcasecmp(cmd, "show_log") == 0)
            showLog();
        else if (strcasecmp(cmd, "exit") == 0) {
            saveAlbums(albums);
            printf("Goodbye!\n");
            break;
        }
        else printf("Unknown command. Type 'help' for help.\n");
    }
    return 0;
}
