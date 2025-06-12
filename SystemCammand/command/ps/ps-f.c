#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <pwd.h>

void show_full_processes() {
    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entry;

    printf("%-10s %-6s %-6s %s\n", "UID", "PID", "PPID", "CMD");

    while ((entry = readdir(proc)) != NULL) {
        if (!isdigit(entry->d_name[0]))
            continue;

        char path[256];
        char status_path[256], cmdline_path[256];
        snprintf(status_path, sizeof(status_path), "/proc/%s/status", entry->d_name);
        snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%s/cmdline", entry->d_name);

        FILE *status_fp = fopen(status_path, "r");
        FILE *cmd_fp = fopen(cmdline_path, "r");
        if (!status_fp || !cmd_fp) {
            if (status_fp) fclose(status_fp);
            if (cmd_fp) fclose(cmd_fp);
            continue;
        }

        char line[256];
        int uid = -1, pid = -1, ppid = -1;
        while (fgets(line, sizeof(line), status_fp)) {
            if (strncmp(line, "Uid:", 4) == 0) {
                sscanf(line, "Uid:\t%d", &uid);
            } else if (strncmp(line, "Pid:", 4) == 0) {
                sscanf(line, "Pid:\t%d", &pid);
            } else if (strncmp(line, "PPid:", 5) == 0) {
                sscanf(line, "PPid:\t%d", &ppid);
            }
        }

        char *username = "?";
        struct passwd *pw = getpwuid(uid);
        if (pw) username = pw->pw_name;

        char cmdline[256];
        if (fgets(cmdline, sizeof(cmdline), cmd_fp) == NULL) {
            strcpy(cmdline, "-");
        }

        printf("%-10s %-6d %-6d %s\n", username, pid, ppid, cmdline);

        fclose(status_fp);
        fclose(cmd_fp);
    }

    closedir(proc);
}

int main() {
    show_full_processes();
    return 0;
}
