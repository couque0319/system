#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>

int show_pid = 0, show_ppid = 0, show_cmd = 0, show_uid = 0;

void parse_format(const char *fmt) {
    char fmt_copy[128];
    strncpy(fmt_copy, fmt, sizeof(fmt_copy));
    fmt_copy[sizeof(fmt_copy) - 1] = '\0';

    char *token = strtok(fmt_copy, ",");
    while (token) {
        if (strcmp(token, "pid") == 0) show_pid = 1;
        else if (strcmp(token, "ppid") == 0) show_ppid = 1;
        else if (strcmp(token, "cmd") == 0) show_cmd = 1;
        else if (strcmp(token, "uid") == 0) show_uid = 1;
        token = strtok(NULL, ",");
    }
}

void print_header() {
    if (show_uid) printf("%-10s ", "UID");
    if (show_pid) printf("%-6s ", "PID");
    if (show_ppid) printf("%-6s ", "PPID");
    if (show_cmd) printf("%s", "CMD");
    printf("\n");
}

void show_selected_fields() {
    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entry;

    print_header();

    while ((entry = readdir(proc)) != NULL) {
        if (!isdigit(entry->d_name[0])) continue;

        char status_path[256], cmdline_path[256];
        snprintf(status_path, sizeof(status_path), "/proc/%s/status", entry->d_name);
        snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%s/cmdline", entry->d_name);

        FILE *status_fp = fopen(status_path, "r");
        if (!status_fp) continue;

        int uid = -1, pid = -1, ppid = -1;
        char line[256];
        while (fgets(line, sizeof(line), status_fp)) {
            if (strncmp(line, "Uid:", 4) == 0)
                sscanf(line, "Uid:\t%d", &uid);
            else if (strncmp(line, "Pid:", 4) == 0)
                sscanf(line, "Pid:\t%d", &pid);
            else if (strncmp(line, "PPid:", 5) == 0)
                sscanf(line, "PPid:\t%d", &ppid);
        }
        fclose(status_fp);

        char cmd[256] = "-";
        FILE *cmd_fp = fopen(cmdline_path, "r");
        if (cmd_fp) {
            if (fgets(cmd, sizeof(cmd), cmd_fp) == NULL || strlen(cmd) == 0) {
                strcpy(cmd, "-");
            }
            fclose(cmd_fp);
        }

        if (show_uid) printf("%-10d ", uid);
        if (show_pid) printf("%-6d ", pid);
        if (show_ppid) printf("%-6d ", ppid);
        if (show_cmd) printf("%s", cmd);
        printf("\n");
    }

    closedir(proc);
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "-o") != 0) {
        fprintf(stderr, "Usage: %s -o [pid,ppid,cmd,uid]\n", argv[0]);
        return 1;
    }

    parse_format(argv[2]);
    show_selected_fields();

    return 0;
}
