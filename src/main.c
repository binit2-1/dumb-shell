#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <linux/limits.h>

// Your modular headers
#include "banner.h"
#include "trie.h"
#include "input.h"
#include "raw_mode.h"


#include "execute.h"   
#include "splitline.h" 
#include "prompt.h"    

// --- GLOBAL: The Brain ---
// input.c needs access to this variable via 'extern' to show ghost text
TrieNode *g_history_root = NULL;

// --- Helper: Save to File (Persistence) ---
void save_to_history(const char *cmd) {
    // 1. Safety checks
    if (!cmd || strlen(cmd) == 0) return;
    
    // 2. Don't save 'predict' commands (avoids clutter)
    if (strncmp(cmd, "predict", 7) == 0) return;

    // 3. Construct path
    char path[PATH_MAX];
    char *home_directory = getenv("HOME");
    if(home_directory == NULL) return;

    snprintf(path, sizeof(path), "%s/.dumb_shell_history", home_directory);
    
    // 4. Append to file
    FILE *fp = fopen(path, "a");
    if (fp) {
        fprintf(fp, "%s\n", cmd);
        fclose(fp);
    }
}

// --- Helper: Load from File (Memory Init) ---
void loadHistory(TrieNode* root){
    char path[PATH_MAX];
    char *home_directory = getenv("HOME");
    if(home_directory == NULL) return;
    
    snprintf(path, sizeof(path), "%s/.dumb_shell_history", home_directory);
    
    FILE* file = fopen(path, "r");
    if(file == NULL) return; // First run, no history yet
    
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL){
        // Strip newline
        buffer[strcspn(buffer, "\n")] = 0; 
        // Feed the brain
        if (strlen(buffer) > 0) {
            insert(root, buffer);
        }
    }
    fclose(file);
}

// --- The Main Loop ---
void dumb_loop(void)
{
    char *line;
    char **args;
    int status;
    int last_status = 0;
    
    do
    {
        // 1. Print Prompt (Visuals)
        lsh_print_prompt(last_status);

        // 2. Read Input (The Interactive "Ghost Text" Reader)
        line = dumb_read(); 
        
        // 3. Save & Learn (Update Brain)
        char *line_for_history = strdup(line);
        save_to_history(line_for_history);
        
        if (g_history_root && strlen(line_for_history) > 0) {
            insert(g_history_root, line_for_history);
        }
        free(line_for_history);

        // 4. Parse & Execute (Logic)
        args = dumb_split_line(line);
        status = dumb_execute(args);

        last_status = status;

        // 5. Cleanup
        free(line);
        free(args);

    } while (status);
}

// --- Entry Point ---
int main(void)
{
    // 1. Initialize the Brain
    g_history_root = createNode();
    if (!g_history_root) {
        fprintf(stderr, "Failed to create history trie.\n");
        return 1;
    }

    // 2. Load past memories
    loadHistory(g_history_root);

    // 3. Start Shell
    print_banner();
    dumb_loop();

    // 4. Cleanup on exit
    freeTrie(g_history_root);
    
    return 0;
}