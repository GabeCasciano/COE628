#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>

#define MAX_COMMANDS 2

typedef struct COMMAND{
    bool amp_flag, pipe_flag, isParent;
    char ** args;
}command_t, *command;

pid_t pid;
command commands;

command parse_command (command com){
    const char * delim_char = " ";
    char* arg[100];
    char * input = (char *)malloc(strlen(com->args[0]));
    char * temp_str_1 = (char *)malloc(strlen(input));
    char * temp_str_2 = (char *)malloc(strlen(input));
    char * pch = strchr(input, '&');
    int amp_pos = pch-input+1;
    
    if(amp_pos != 0){
        memcpy(temp_str_1, input, amp_pos-1);
        memcpy(temp_str_2, &input[amp_pos+1], strlen(input)-amp_pos);
        strcat(temp_str_1, temp_str_2);
        memcpy(input, temp_str_1, strlen(input));
        
    }
}

command flag_substring(char * input, command com){
    int pipe_pos;
    char * temp_str_1, * temp_str_2, * pch;
    
    
    temp_str_1 = (char *)malloc(strlen(input));
    temp_str_2 = (char *)malloc(strlen(input));
    
    pch = strchr(input, '|');
    pipe_pos = pch-input+1;
    
    if(pipe_pos != 0){
        memcpy(temp_str_1, input, pipe_pos-1);
        memcpy(temp_str_2, &input[pipe_pos+1], strlen(input)-pipe_pos);
        com[0].amp_flag = true;
        memcpy(com[1].args[0], temp_str_2, strlen(temp_str_2));
        com[1].isParent = false;
    }
    
    memcpy(com[0].args[0], temp_str_1, strlen(temp_str_1));
    com[0].isParent = true;
    return com;
    
}

char * read_stdin(){
    char buffer;
    char * input_string = (char*)malloc(1);
    char * temp;
    int input_len = 0;
    
    while((buffer = getchar()) != '\n'){ 
        temp = (char*)malloc(input_len);
        memcpy(temp, input_string, input_len);
        input_len++;
        input_string = (char *)malloc(input_len);// I know I coul use realloc, but i prefer to do it this way
        memcpy(input_string, temp, input_len);
        input_string[input_len-1] = buffer;
    }
    
    return input_string;
}

bool execute(command com){
    
}

int main(){
    commands = (command)malloc(MAX_COMMANDS);
    
    for(;;){
        printf("Simple Shell>");
        flag_substring(read_stdin(), commands);
        while(commands->args[0] != NULL){
            parse_command(commands);
            execute(commands);
            commands++;
        }
        
    }
    return 0;
}
