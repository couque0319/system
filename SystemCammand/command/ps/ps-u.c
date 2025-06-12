#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>

void show_user_processes() {
    uid_t current_uid = getuid();  // 현재 사용자 UID

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

        char status_path[256];
        snprintf(status_path, sizeof(status_path), "/proc/%s/status", entry->d_name);

        FILE *status_fp = fopen(status_path, "r");
        if (!status_fp) continue;

        int uid = -1;
        char line[256];

        while (fgets(line, sizeof(line), status_fp)) {
            if (strncmp(line, "Uid:", 4) == 0) {
                sscanf(line, "Uid:\t%d", &uid);
                break;
            }
        }

        fclose(status_fp);

        if (uid != current_uid)
            continue;

        char cmd_path[256], cmd[256];
        snprintf(cmd_path, sizeof(cmd_path), "/proc/%s/cmdline", entry->d_name);
        FILE *cmd_fp = fopen(cmd_path, "r");
        if (!cmd_fp) continue;

        if (fgets(cmd, sizeof(cmd), cmd_fp) == NULL || strlen(cmd) == 0) {
            strcpy(cmd, "-");
        }

        fclose(cmd_fp);

        printf("%-10s %s\n", entry->d_name, cmd);
    }

    closedir(proc);
}

int main() {
    show_user_processes();
    return 0;
}
