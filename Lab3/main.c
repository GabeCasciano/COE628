/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: gabriel
 *
 * Created on February 5, 2020, 2:05 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

pid_t pid;


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

char ** parse_input(char * input){
    const char * delim_char = " ";
    char* arg[100];
    char * temp = (char *)malloc(strlen(input));
    int index = 0;
    int flag = strchr(input, '&');
    
    temp = strtok(input, delim_char);
    
    while(temp != NULL){
        arg[index] = (char *)malloc(strlen(temp));
        arg[index] = temp;
        index++;
        temp = strtok(NULL, delim_char);
    }
        
    arg[index+1] = NULL;
    
    pid = fork();
    if(pid == 0){ // child
        execvp(arg[0], arg);
        exit(0);
    }
    else
        wait(NULL);
}

int main()
{
    for(;;){
        printf("Your Command>");    
        parse_input(read_stdin());
    }
        
    return 0;
}