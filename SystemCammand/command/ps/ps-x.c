#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

void show_processes_with_or_without_tty() {
    DIR *proc = opendir("/proc");
    if (!proc) {
        perror("opendir");
        exit(1);
    }

    struct dirent *entry;

    printf("%-6s %-6s %s\n", "PID", "TTY", "CMD");

    while ((entry = readdir(proc)) != NULL) {
        if (!isdigit(entry->d_name[0]))
            continue;

        char stat_path[256];
        snprintf(stat_path, sizeof(stat_path), "/proc/%s/stat", entry->d_name);

        FILE *stat_fp = fopen(stat_path, "r");
        if (!stat_fp) continue;

        int pid, tty_nr;
        char comm[256], state;
        // 필요한 앞부분 필드만 파싱
        fscanf(stat_fp, "%d %s %c", &pid, comm, &state);
        for (int i = 0; i < 3; i++) fscanf(stat_fp, "%*s"); // skip ppid, pgrp, session
        fscanf(stat_fp, "%d", &tty_nr);  // tty_nr
        fclose(stat_fp);

        char tty_str[16];
        if (tty_nr == 0)
            strcpy(tty_str, "?");  // TTY 없는 프로세스
        else
            strcpy(tty_str, "tty");  // 간단히 표시

        // cmdline 가져오기
        char cmd_path[256], cmd[256] = "-";
        snprintf(cmd_path, sizeof(cmd_path), "/proc/%s/cmdline", entry->d_name);
        FILE *cmd_fp = fopen(cmd_path, "r");
        if (cmd_fp) {
            if (fgets(cmd, sizeof(cmd), cmd_fp) == NULL || strlen(cmd) == 0)
                strcpy(cmd, "-");
            fclose(cmd_fp);
        }

        printf("%-6d %-6s %s\n", pid, tty_str, cmd);
    }

    closedir(proc);
}

int main() {
    show_processes_with_or_without_tty();
    return 0;
}
