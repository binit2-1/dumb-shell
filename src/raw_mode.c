#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "raw_mode.h"

struct termios orig_termios;

void die(const char *s) {
    perror(s);
    exit(1);
}

// 1. Function to Restore Terminal (Must be separate!)
void disable_raw_mode(void) {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
        die("tcsetattr");
    }
}

// Wrapper to match header declaration
void disableRawMode(void) {
    disable_raw_mode();
}

// 2. Function to Enable Raw Mode
void enable_raw_mode(void) {
    // Save current settings
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
        die("tcgetattr");
    }
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;

    // Input Flags
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

    // Output Flags
    raw.c_oflag &= ~(OPOST);

    // Control Flags
    raw.c_cflag |= (CS8);

    // Local Flags (ECHO off, Canonical off)
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    // Control Chars - immediate response
    raw.c_cc[VMIN] = 1;  // Wait for at least 1 character
    raw.c_cc[VTIME] = 0; // No timeout - immediate return

    // Apply
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
        die("tcsetattr");
    }
}