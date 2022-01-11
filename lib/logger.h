#include <stdio.h>
#include <sqlite3.h>

int add_log(char *fd, char *prog_name, int log_type, char *log_text);
int print_logs_by_program(char *fd, char *program_name);
int print_all_logs(char *fd);
int create_db(char *fd);
int delete_db(char *fd);