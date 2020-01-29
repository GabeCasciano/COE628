#include <stdio.h>  //printf, fprintf
#include <stdlib.h> //EXIT_SUCCESS
#include <string.h> //strlen, strcmp
#define TOO_MANY_ARGS 2
#define TOO_FEW_ARGS 1

int main(int argc, char* argv[]) {
    //Default values:
    int exit_code = EXIT_SUCCESS;
    char * greeting = "Hello";
    char * person = "UNKNOWN";
    //Add code to change the exit_code depending on argc
    exit_code = ((argc>2)?2:((argc==2)?0:1));
    //Add code to change 'person' if one is given on command line
    if(exit_code==2){
        person = argv[2];
    }
    
    int len = strlen(argv[0]);
    char * last3 = argv[0] + len - 3; //last3 points to last 3 chars
    fprintf(stderr, "%s\n", argv[0]);
    fprintf(stderr, "%s\n", last3);
    
    char * temp = "bye";
    //Add code to change 'greeting' if last 3 chars of command are 'bye'
    if((exit_code == 0 || exit_code == 2) && strcmp(temp, argv[1]) == 0)
        greeting = temp;
    
    printf("%s %s\n", greeting, person);
    
    fprintf(stderr, "exit_code: %d\n", exit_code);
    
    return exit_code; //Could also say exit(exit_code)
}