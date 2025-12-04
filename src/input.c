#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "input.h"
#include "raw_mode.h"
#include "trie.h"

// Access the global brain defined in main.c
extern TrieNode *g_history_root;

char *dumb_read(void) {
    int bufsize = 1024;
    int pos = 0;
    char *buffer = calloc(bufsize, 1);
    char c;
    char *last_ghost = NULL;

    // 1. Enter Raw Mode
    enable_raw_mode();

    while (1) {
        // 2. Read one character
        ssize_t nread = read(STDIN_FILENO, &c, 1);
        if (nread <= 0) break;

        if (c == '\r' || c == '\n') {
            // Enter key: Finish (raw mode sends \r, not \n)
            printf("\x1B[K\r\n");  // Clear line then newline
            break;
        } 
        else if (c == 127) { 
            // Backspace key
            if (pos > 0) {
                pos--;
                buffer[pos] = '\0';
                printf("\b \b");  // Erase character
                printf("\x1B[K");  // Clear rest of line (removes ghost)
            }
        }
        else if (c == '\t') {
            // TAB key: Accept the ghost suggestion!
            if (g_history_root && pos > 0) {
                char *best = getBestPrediction(g_history_root, buffer);
                if (best && strlen(best) > pos) {
                    // Clear ghost first
                    printf("\x1B[K");
                    // Print the remaining part
                    const char *rest = best + pos;
                    printf("%s", rest);
                    // Update buffer
                    strncpy(buffer, best, bufsize - 1);
                    buffer[bufsize - 1] = '\0';
                    pos = strlen(buffer);
                }
            }
        }
        else if (!iscntrl(c)) {
            // Normal character
            if (pos < bufsize - 1) {
                buffer[pos++] = c;
                buffer[pos] = '\0';
                printf("%c", c);
                printf("\x1B[K");  // Clear old ghost
            }
        } else {
            // Ignore other control characters
            continue;
        }

        // --- DRAW GHOST TEXT (only for normal chars and backspace) ---
        if (g_history_root && pos > 0 && (c != '\t')) {
            char *best = getBestPrediction(g_history_root, buffer);
            
            if (best && strlen(best) > pos) {
                const char *ghost = best + pos;
                size_t ghost_len = strlen(ghost);
                
                // Print ghost in dim gray
                printf("\x1B[38;5;240m%s\x1B[0m", ghost);
                // Move cursor back
                printf("\x1B[%zuD", ghost_len);
            }
        }
        
        fflush(stdout);  // Force immediate display
    }

    // 3. Restore Normal Mode
    disableRawMode();
    return buffer;
}