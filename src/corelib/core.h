#ifndef _CORE_H_
#define _CORE_H_

void terminal_mode_switch(int mode); 

int split(char *buffer, char *dest[]);

int expand(char *buffer[]);

int proc_manager(char *buffer);

void print_handle(int type);

#endif // !_CORE_H_

