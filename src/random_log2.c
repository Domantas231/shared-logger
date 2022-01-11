#include <logger.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include <unistd.h>

#define FD "var/log/logger.db"

int initialize_rand(){
    time_t t;
    srand((unsigned) time(&t));

    return 0;
}

int send_rand_logs(char *program_name){
    while(1){
        char msg[20];
        sprintf(msg, "%d", rand() % 120 + 120);
        add_log(FD, program_name, 1, msg);
        sleep(10);
    }

    return 0;
}

int main(int argc, char **argv){
    create_db(FD);

    initialize_rand();
    send_rand_logs(argv[0]);

    return 0;
}