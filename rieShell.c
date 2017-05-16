#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

#define MAXLENGTH_COM 100
#define MAX_ARG 7

static const char *FILE_PATH = "/root/linux/simCommand/";

void info_shell() {
    char *username, hostname[50], pwd[50], type;
    if (NULL == (username = getenv("USER"))) {
        perror("getenv");
        exit(EXIT_FAILURE);
    }
    if (NULL == getcwd(pwd, 50)){
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    if (-1 == gethostname(hostname, 50)) {
        perror("gethostname");
        exit(EXIT_FAILURE);
    }
    if (strcmp(username, "root") == 0) {
        type = '#';
    }
    else {
        type = '$';
    }
    
    printf("rieShell-[%s@%s %s]%c ", username, hostname, pwd, type);

}
int commandAnalyze(char *path, char *parameters[]) {

    char strInput[MAXLENGTH_COM];
    char *temp;
    int index, length;
    info_shell();
    fgets(strInput, MAXLENGTH_COM, stdin);
    char const delims[] = " ";
    temp = strtok(strInput, delims);
    index = 0;
    while (temp) {
        length = strlen(temp);
        parameters[index] = (char *) malloc(length+1);
        strcpy(parameters[index++], temp);
        temp = strtok(NULL, delims);
    }

    int i = strlen(parameters[index-1]);
    parameters[index-1][i-1] = 0;

    parameters[index] = (char *) malloc(4);
    parameters[index] = NULL;
    strcpy(path, FILE_PATH);
    strcat(path, parameters[0]);
    printf("path:%s\n", path);
    for (i = 0; i <= index; i++) {
         printf("%d-%s\n", i, parameters[i]);  
    }

    return index;
}


int main(int argc, char *argv[]) {

    pid_t pid;
    int status, length;
    char path[50];
    char *parameters[MAX_ARG];

    while(1) {
        length = commandAnalyze(path, parameters);
        if (strcmp(path, "/root/linux/simCommand/exit") == 0) {
            exit(EXIT_SUCCESS);
        }
        if ((pid = fork()) < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0) {
            waitpid(pid, &status, 0);
        }
        else {
            if (strcmp(path, "/root/linux/simCommand/cd") == 0) {
                if (length > 1) {
                    if (strcmp(parameters[1], "..") == 0) {
                        chdir("..");
                    }
                    else {
                        if (chdir(parameters[1]) != 0) {
                            perror("No such file");
                        }
                    }
                }
                else {
                    chdir("/root");
                }
            }
            else{
                if (execvp(path, parameters) == -1) {
                    printf("command not find\n");
                }   
            } 
        }
    }

    return 0;
}
