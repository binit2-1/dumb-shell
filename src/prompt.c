#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h> // For WEXITSTATUS

// --- Add these colors (or make sure they are at the top of your file) ---
#define KNRM  "\x1B[0m"   // Reset
#define KRED  "\x1B[31m"  // Red
#define KGRN  "\x1B[32m"  // Green
#define KYEL  "\x1B[33m"  // Yellow
#define KBLU  "\x1B[34m"  // Blue
#define KGRY  "\x1B[90m"  // Bright Black (Gray) - good for separators

// --- Nerd Font Icons ---
#define ICON_PROMPT "\u276F" // ❯ (Heavy arrow prompt)

/**
 * @brief Prints the custom shell prompt.
 * Format: : username > path > time )
 */
void lsh_print_prompt(int last_status) {
    
    // --- 1. Get Username ---
    char *user = getenv("USER");
    if (user == NULL) {
        user = "user"; // Fallback
    }

    // --- 2. Get CWD (and shorten it to ~) ---
    char cwd[1024];
    char display_path[1024];
    char *home_dir = getenv("HOME");

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        if (home_dir && strncmp(cwd, home_dir, strlen(home_dir)) == 0) {
            // It's in the home directory, replace with "~"
            snprintf(display_path, sizeof(display_path), "~%s", &cwd[strlen(home_dir)]);
        } else {
            // Not in home dir, just copy the full path
            strncpy(display_path, cwd, sizeof(display_path));
        }
    } else {
        // Error getting CWD
        strncpy(display_path, "???", sizeof(display_path));
    }


    // --- 3. Get Current Time (HH:MM) ---
    char time_str[16];
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    strftime(time_str, sizeof(time_str), "%H:%M", local_time);


    // --- 4. Print the Info String (without the final prompt char) ---
    printf("%s: %s%s %s%s %s%s %s%s %s%s %s", 
           KGRY,            // Gray ":"
           KGRN, user,      // Green username
           KGRY, ICON_PROMPT,  // Gray separator
           KBLU, display_path, // Blue path
           KGRY, ICON_PROMPT,  // Gray separator
           KYEL, time_str,  // Yellow time
           KNRM             // Reset color
    );

    // --- 5. Print the final prompt character (smart status) ---
    if (WEXITSTATUS(last_status) == 0) {
        // Last command was a success
        printf(KGRN "%s " KNRM, ICON_PROMPT);
    } else {
        // Last command failed
        printf(KRED "%s " KNRM, ICON_PROMPT);
    }
    
    // Force output to display before raw mode
    fflush(stdout);
}

