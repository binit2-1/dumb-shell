#include <stdio.h>
#include "banner.h"

// --- Define colors  ---
#define KNRM  "\x1B[0m"   // Reset
#define KBLU  "\x1B[34m"  // Blue
#define KGRN  "\x1B[32m"  // Green
#define KCYN  "\x1B[36m"  // Cyan
#define KYEL  "\x1B[33m"  // Yellow
#define KGRY  "\x1B[90m"  // Dark Gray

void print_banner(void) {
    printf("\n\n\n");
    // --- Print the new ASCII banner in blue ---
    printf(KBLU);
    printf("██╗      ██████╗  █████╗ ██████╗ ███████╗██╗  ██╗   ██╗      █████╗ ██╗     ██╗██╗   ██╗███████╗\n");
    printf("╚██╗     ██╔══██╗██╔══██╗██╔══██╗██╔════╝██║  ╚██╗ ██╔╝     ██╔══██╗██║     ██║██║   ██║██╔════╝\n");
    printf(" ╚██╗    ██████╔╝███████║██████╔╝█████╗  ██║   ╚████╔╝█████╗███████║██║     ██║██║   ██║█████╗  \n");
    printf(" ██╔╝    ██╔══██╗██╔══██║██╔══██╗██╔══╝  ██║    ╚██╔╝ ╚════╝██╔══██║██║     ██║╚██╗ ██╔╝██╔══╝  \n");
    printf("██╔╝     ██████╔╝██║  ██║██║  ██║███████╗███████╗██║        ██║  ██║███████╗██║ ╚████╔╝ ███████╗\n");
    printf("╚═╝      ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝╚═╝        ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝  ╚══════╝\n");
    printf("                                                                                    \n");

    // --- Reset to normal, then print the sub-heading in a different color ---
    printf(KNRM "\n"); // Reset color
    printf(KYEL "Welcome to dumb-shell!" KNRM); // Yellow for the title
    printf(KGRY " (made by a dumb developer) " KNRM); // Gray for the joke
    printf("Type 'help' for commands.\n\n");
    printf(KNRM); // Final reset, just in case
}