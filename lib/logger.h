#include <stdio.h>
#include <sqlite3.h>

#define FD "/var/log/logger.db"
enum levels {INFO, WARNING, ERROR};


int open_log();
int write_log(char *prog_name, int log_type, char *log_text);
int print_logs(char *program_name);
int close_log();