#include <logger.h>
#include <stdio.h>
#include <string.h>
#include <argp.h>

/*
* TODO: add the library argp so that error handling can be a bit better
*/

int main(int argc, char **argv){
    open_log();

    // if(argc < 3)
        // print_all_logs(FD);
    // 
    // else
        // if(strcmp("-P", argv[1]) == 0 || strcmp("--program", argv[1]) == 0)
            // print_logs_by_program(FD, argv[2]);

    struct argp argp;
    struct arguments args;

    argp_parse(&argp, argc, argv, 0, 0, &args);

    close_log();    
    return 0;
}