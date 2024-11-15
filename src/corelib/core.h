#ifndef _CORE_H_
#define _CORE_H_

void terminal_mode_switch(int mode); 

int split(char *buffer, char *dest[]);

int expand(char *buffer[]);
struct passwd *get_user_info();

int proc_manager(char *buffer);

void print_handle(int type);

void init_history(void);
void add_history(const char *cmd);
char *get_history(int index);
void free_history(void);


#endif // !_CORE_H_

