#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

void show_all_processes() {
    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entry;

    printf("%-10s %s\n", "PID", "CMD");

    while ((entry = readdir(proc)) != NULL) {
        if (!isdigit(entry->d_name[0]))
            continue;

        char cmd_path[256];
        snprintf(cmd_path, sizeof(cmd_path), "/proc/%s/cmdline", entry->d_name);

        FILE *fp = fopen(cmd_path, "r");
        if (!fp) continue;

        char cmd[256];
        if (fgets(cmd, sizeof(cmd), fp) == NULL || strlen(cmd) == 0) {
            strcpy(cmd, "-");  // 명령어가 없을 경우
        }

        fclose(fp);

        printf("%-10s %s\n", entry->d_name, cmd);
    }

    closedir(proc);
}

int main() {
    show_all_processes();
    return 0;
}
