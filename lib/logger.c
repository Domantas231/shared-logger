#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <time.h>
#include <string.h>

#include "logger.h"
#define FD "var/log/logger.db"

char log_types[3][10] = {"info", "Warning", "ERROR"};

int print_res(sqlite3_stmt *res){
    while(sqlite3_step(res) != SQLITE_DONE){ 
        printf("%d %s %s %s %s", sqlite3_column_int(res, 0), 
        sqlite3_column_text(res, 1), sqlite3_column_text(res, 2), 
        sqlite3_column_text(res, 3), sqlite3_column_text(res, 4));
    }

    return 0;
}

int curr_time(char current[], int n){
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(current, n, "%Y-%m-%d %H:%M:%S\n", timeinfo);

    return 0;
}
 
int add_log(char *fd, char *prog_name, int log_type, char *log_text){
    sqlite3 *db;
    sqlite3_open(fd, &db);
    char *err;

    char time[26];
    curr_time(time, 26);

    char *temp = "INSERT INTO Logs (program_name, log_type, log_text, timestamp) VALUES";

    char querry[128];
    snprintf(querry, 128, "%s%s'%s', '%s', '%s', '%s'%s", temp, "(", prog_name, log_types[log_type], log_text, time, ")");

    int rc = sqlite3_exec(db, querry, NULL, NULL, &err);
    if(rc != SQLITE_OK){
        printf("Can't insert new log: %s \n", err);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int print_logs_by_program(char *fd, char *program_name){
    sqlite3 *db;
    sqlite3_open(fd, &db);

    sqlite3_stmt *res;

    char *temp = "SELECT * FROM Logs WHERE program_name=";
    char querry[64];
    sprintf(querry, "%s'%s'", temp, program_name);

    int rc = sqlite3_prepare_v3(db, querry, -1, 0, &res, 0);

    print_res(res);

    sqlite3_close(db);
    return 0;
}

int print_all_logs(char *fd){
    sqlite3 *db;
    sqlite3_open(fd, &db);
    sqlite3_stmt *res;

    char *querry = "SELECT * FROM Logs";
    sqlite3_prepare_v3(db, querry, -1, 0, &res, 0);

    print_res(res);

    sqlite3_close(db);
    return 0;
}

int create_db(char *fd){
    sqlite3 *db;
    sqlite3_open(fd, &db);

    char *err;

    char *table = "CREATE TABLE Logs ("
                        "id INTEGER PRIMARY KEY,"
                        "program_name TEXT NOT NULL,"
                        "log_type TEXT NOT NULL,"
                        "log_text TEXT NOT NULL,"
                        "timestamp TEXT NOT NULL )";

    int rc = sqlite3_exec(db, table, NULL, NULL, &err);
    if(rc != SQLITE_OK){
        printf("Can't create table/database: %s \n", err);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}

int delete_db(char *fd){
    sqlite3 *db;
    sqlite3_open(fd, &db);

    char *err;

    int rc = sqlite3_exec(db, "DROP DATABASE Logs", NULL, NULL, &err);
    if(rc != SQLITE_OK){
        printf("Can't delete the database: %s \n", err);
        return 1;
    }

    return 0;
}