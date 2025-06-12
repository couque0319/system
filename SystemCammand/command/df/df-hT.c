#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <mntent.h>
#include <string.h>

void human_readable(unsigned long long size, char *out) {
    const char *units[] = {"B", "K", "M", "G", "T"};
    int i = 0;
    double s = (double)size;

    while (s >= 1024 && i < 4) {
        s /= 1024;
        i++;
    }

    sprintf(out, "%.1f%s", s, units[i]);
}

int main() {
    FILE *mnt = setmntent("/etc/mtab", "r");
    if (!mnt) {
        perror("setmntent");
        return 1;
    }

    struct mntent *ent;

    printf("%-20s %-10s %-10s %-10s %-10s %s\n", 
           "Filesystem", "Type", "Size", "Used", "Avail", "Mounted on");

    while ((ent = getmntent(mnt)) != NULL) {
        struct statvfs vfs;

        // 파일시스템 사용량 정보 수집
        if (statvfs(ent->mnt_dir, &vfs) != 0)
            continue;

        unsigned long long total = vfs.f_blocks * vfs.f_frsize;
        unsigned long long avail = vfs.f_bavail * vfs.f_frsize;
        unsigned long long used = total - avail;

        char total_str[16], used_str[16], avail_str[16];
        human_readable(total, total_str);
        human_readable(used, used_str);
        human_readable(avail, avail_str);

        // 최종 출력
        printf("%-20s %-10s %-10s %-10s %-10s %s\n", 
               ent->mnt_fsname, ent->mnt_type, total_str, used_str, avail_str, ent->mnt_dir);
    }

    endmntent(mnt);
    return 0;
}
