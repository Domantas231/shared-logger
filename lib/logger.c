#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <time.h>
#include <string.h>

#include "logger.h"

sqlite3 *DB = NULL;

static char log_types[3][10] = {"INFO", "WARNING", "ERROR"};

static int create_db(){
    char *err;

    char *table = "CREATE TABLE Logs IF NOT EXISTS("
                        "id INTEGER PRIMARY KEY,"
                        "program_name TEXT NOT NULL,"
                        "log_type TEXT NOT NULL,"
                        "log_text TEXT NOT NULL,"
                        "timestamp TEXT NOT NULL )";

    int rc = sqlite3_exec(DB, table, NULL, NULL, &err);
    if(rc != SQLITE_OK){
        printf("Can't create table/database: %s \n", err);
        return 1;
    }

    return 0;
}

int open_log(){
    if(sqlite3_open(FD, &DB) != SQLITE_OK){
        printf("Failed to OPEN database.");
        return 1;
    }

    create_db();

    return 0;
}

int close_log(){
    if(sqlite3_close(DB) != SQLITE_OK){
        printf("Failed to CLOSE database.");
        return 1;
    }

    return 0;
}

static int print_res(sqlite3_stmt *res){
    while(sqlite3_step(res) != SQLITE_DONE){ 
        printf("%d %s %s %s %s", sqlite3_column_int(res, 0), 
        sqlite3_column_text(res, 1), sqlite3_column_text(res, 2), 
        sqlite3_column_text(res, 3), sqlite3_column_text(res, 4));
    }

    return 0;
}

static int curr_time(char current[], int n){
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(current, n, "%Y-%m-%d %H:%M:%S\n", timeinfo);

    return 0;
}
 
int write_log(char *prog_name, int level, char *log_text){
    char *err;

    char time[26];
    curr_time(time, 26);

    char *temp = "INSERT INTO Logs (program_name, log_type, log_text, timestamp) VALUES";

    char query[128];
    snprintf(query, 128, "%s('%s', '%s', '%s', '%s')", temp, prog_name, log_types[level], log_text, time);

    int rc = sqlite3_exec(DB, query, NULL, NULL, &err);
    if(rc != SQLITE_OK){
        printf("Can't insert new log: %s \n", err);
        return 1;
    }
    return 0;
}

int print_logs(char *program_name){
    sqlite3_stmt *res;

    char *query = NULL;

    if(program_name != NULL){
        char *temp = "SELECT * FROM Logs WHERE program_name=";
        char query[64];
        sprintf(query, "%s'%s'", temp, program_name);
    }
    else
        query = "SELECT * FROM Logs";

    sqlite3_prepare_v3(DB, query, -1, 0, &res, 0);
    print_res(res);
    return 0;
}