#include <logger.h>
#include <stdio.h>
#include <string.h>

#define FD "var/log/logger.db"

int main(int argc, char **argv){
    create_db(FD);

    if(argc < 3)
        print_all_logs(FD);

    else
        if(strcmp("-P", argv[1]) == 0 || strcmp("--program", argv[1]) == 0)
            print_logs_by_program(FD, argv[2]);
        
    return 0;
}