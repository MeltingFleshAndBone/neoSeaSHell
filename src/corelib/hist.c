#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include "core.h"

#define HIST_FILE ".seashell.history"
#define MAX_HIST_SIZE 1000

static char **history = NULL;
static int hist_count = 0;
static int hist_size = 0;

void init_history(void) {
  history = malloc(MAX_HIST_SIZE * sizeof(char*));
  if (history == NULL) {
    perror("malloc");
    return;
  }

  struct passwd *pw = get_user_info();
  if (pw == NULL) {
    return;
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
        break;
      }
      hist_count++;
    }
    fclose(fp);
  }
  
  hist_size = MAX_HIST_SIZE;
}

void add_history(const char *cmd) {
  if (history == NULL) {
    return;
  }
  
  if (hist_count > 0 && strcmp(history[hist_count-1], cmd) == 0) {
    // Don't add duplicate of last command
    return;
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
    return;
  }
  hist_count++;
  
  // Write to history file
  struct passwd *pw = get_user_info();
  if (pw == NULL) {
    return;
  }

  char hist_path[1024];
  snprintf(hist_path, sizeof(hist_path), "%s/%s", pw->pw_dir, HIST_FILE);
  
  FILE *fp = fopen(hist_path, "w");
  if (fp == NULL) {
    perror("fopen");
    return;
  }
  
  for (int i = 0; i < hist_count; i++) {
    fprintf(fp, "%s\n", history[i]);
  }
  fclose(fp);
}

char *get_history(int index) {
  if (history == NULL || index < 0 || index >= hist_count) {
    return NULL;
  }
  return history[hist_count - index - 1];
}

void free_history() {
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
