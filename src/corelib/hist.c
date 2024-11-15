#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include "core.h"
#include "../include/status.h"

#define HIST_FILE ".seashell.history"
#define MAX_HIST_SIZE 1000

static char **history = NULL;
static int hist_count = 0;
static int hist_size = 0;

int init_history(void) {
  /* Initialize command history
   * Allocates memory for history array and loads existing history from ~/.seashell.history
   * History is limited to MAX_HIST_SIZE entries
   * Returns: STAT_SUCCESS on success, STAT_MEMALLOCERR on allocation failure,
   *         STAT_HISTORYERR on other errors */

  history = malloc(MAX_HIST_SIZE * sizeof(char*));
  if (history == NULL) {
    perror("malloc");
    return STAT_MEMALLOCERR;
  }

  struct passwd *pw = get_user_info();
  if (pw == NULL) {
    return STAT_HISTORYERR;
  }

  char hist_path[1024];
  snprintf(hist_path, sizeof(hist_path), "%s/%s", pw->pw_dir, HIST_FILE);
  
  // Try to read existing history file
  FILE *fp = fopen(hist_path, "r");
  if (fp != NULL) {
    char line[1024];
    while (fgets(line, sizeof(line), fp) && hist_count < MAX_HIST_SIZE) {
      // Remove newline
      line[strcspn(line, "\n")] = 0;
      
      history[hist_count] = strdup(line);
      if (history[hist_count] == NULL) {
        perror("strdup");
        fclose(fp);
        return STAT_MEMALLOCERR;
      }
      hist_count++;
    }
    fclose(fp);
  }
  
  hist_size = MAX_HIST_SIZE;
  return STAT_SUCCESS;
}

int add_history(const char *cmd) {
  /* Add a command to the history
   * Adds the given command to the history array and writes all history to disk
   * Will not add duplicates of the last command
   * If history is full, removes oldest entry
   * Params:
   *   cmd: Command string to add to history
   * Returns: STAT_SUCCESS on success, STAT_HISTORYERR on failure */

  if (history == NULL) {
    return STAT_HISTORYERR;
  }
  
  if (hist_count > 0 && strcmp(history[hist_count-1], cmd) == 0) {
    // Don't add duplicate of last command
    return STAT_SUCCESS;
  }
  
  if (hist_count >= hist_size) {
    // History full, remove oldest entry
    free(history[0]);
    memmove(&history[0], &history[1], (hist_size-1) * sizeof(char*));
    hist_count--;
  }
  
  history[hist_count] = strdup(cmd);
  if (history[hist_count] == NULL) {
    perror("strdup");
    return STAT_MEMALLOCERR;
  }
  hist_count++;
  
  // Write to history file
  struct passwd *pw = get_user_info();
  if (pw == NULL) {
    return STAT_HISTORYERR;
  }

  char hist_path[1024];
  snprintf(hist_path, sizeof(hist_path), "%s/%s", pw->pw_dir, HIST_FILE);
  
  FILE *fp = fopen(hist_path, "w");
  if (fp == NULL) {
    perror("fopen");
    return STAT_HISTORYERR;
  }
  
  for (int i = 0; i < hist_count; i++) {
    fprintf(fp, "%s\n", history[i]);
  }
  fclose(fp);
  return STAT_SUCCESS;
}

char *get_history(int index) {
  /* Get a command from history by index
   * Returns the command at the given index, counting backwards from most recent
   * Index 0 is the most recent command
   * Params:
   *   index: History index to retrieve (0 = most recent)
   * Returns: Command string at index, or NULL if invalid index */

  if (history == NULL || index < 0 || index >= hist_count) {
    return NULL;
  }
  return history[hist_count - index - 1];
}

void free_history() {
  /* Free all history memory
   * Frees the history array and all command strings
   * Resets history tracking variables
   * Returns: void */

  if (history != NULL) {
    for (int i = 0; i < hist_count; i++) {
      free(history[i]);
    }
    free(history);
    history = NULL;
    hist_count = 0;
    hist_size = 0;
  }
}
