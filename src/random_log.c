#include <logger.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sqlite3.h>
#include <unistd.h>

int initialize_rand(){
    time_t t;
    srand((unsigned) time(&t));

    return 0;
}

int send_rand_logs(char *program_name){
    while(1){
        char msg[20];
        sprintf(msg, "%d", rand() % 120);
        write_log(program_name, WARNING, msg);

        sleep(10);
    }

    return 0;
}

int main(int argc, char **argv){
    open_log();

    initialize_rand();
    send_rand_logs(argv[0]);

    close_log();
    return 0;
}