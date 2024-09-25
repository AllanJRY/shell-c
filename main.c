#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>

const int MAX_CMD_LINE_LEN = 1024;
const int MAX_CMD_LEN      = 32;

int read_cmd(char* cmd_line, int max_cmd_len, char* out_cmd) {
    int i;
    for(i = 0; i < max_cmd_len; ++i) {
        if (cmd_line[i] == ' ' || cmd_line[i] == '\n') {
            out_cmd[i] = '\0';
            break;
        }
        out_cmd[i] = cmd_line[i] | 0x60; // to lower case, but only working for ASCII char.
    }
    return i;
}

bool str_eq(char* str, char* o_str) {
    for(int i = 0; str[i] != '\0' || o_str[i] != '\0'; ++i) {
        if(str[i] != o_str[i]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    bool exit = false;

    const char* path_env = getenv("PATH");
    printf("path: %s\n", path_env);

    char cwd[PATH_MAX] = "";
    getcwd(cwd, sizeof(cwd));
    printf("working dir: %s\n", cwd);


    
    while (!exit) {
        printf("> ");

        char cmd_line[MAX_CMD_LINE_LEN];
        fgets(cmd_line, sizeof(cmd_line), stdin);

        char cmd[MAX_CMD_LEN];
        int cmd_len = read_cmd(cmd_line, sizeof(cmd), cmd);

        // TODO : read args proc

        if(str_eq(cmd, "exit")) {
            exit = true;
        } else if(str_eq(cmd, "echo")) {
            for(int i = cmd_len + 1; cmd_line[i] != '\n'; ++i) {
                printf("%c", cmd_line[i]);
            }
            printf("\n");
        } else {
            printf("%s not found. \n", cmd);
        }
    }
    
    return 1;
}

