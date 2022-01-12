#include <logger.h>
#include <stdio.h>
#include <string.h>
#include <argp.h>

char doc[] = "A simple program that prints the contents of a log file. \n"
             "Use -p to specify a program.";   

struct arguments {
    char *program_name;
};

struct argp_option options[] = {
    {"program", 'p', 0, 0, "Print only given program name logs"},
    { 0 }
};

error_t parse_opt (int key, char *arg, struct argp_state *state){
    struct arguments *args = state->input;
    
    switch(key){
        case 'p':
            args->program_name = arg;
            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

struct argp argp = {options, parse_opt, NULL, doc};

/*
* TODO: add the library argp so that error handling can be a bit better
*/

int main(int argc, char **argv){
    open_log();

    struct arguments args;

    args.program_name = NULL;
    argp_parse(&argp, argc, argv, 0, 0, &args);

    print_logs(args.program_name);

    close_log();    
    return 0;
}