#include <stdio.h>
#include <stdlib.h>
#include <sys/statvfs.h>
#include <mntent.h>

int main() {
    FILE *mnt = setmntent("/etc/mtab", "r");
    if (!mnt) {
        perror("setmntent");
        return 1;
    }

    struct mntent *ent;

    printf("%-20s %-10s %-10s %-10s %-10s %s\n", 
           "Filesystem", "Inodes", "IUsed", "IFree", "IUse%", "Mounted on");

    while ((ent = getmntent(mnt)) != NULL) {
        struct statvfs vfs;

        // 파일시스템의 inode 정보 수집
        if (statvfs(ent->mnt_dir, &vfs) != 0)
            continue;

        unsigned long total_inodes = vfs.f_files;
        unsigned long free_inodes = vfs.f_ffree;
        unsigned long used_inodes = total_inodes - free_inodes;

        // inode 사용률 계산
        int usage = (total_inodes > 0) ? (int)((double)used_inodes / total_inodes * 100) : 0;

        // 최종 출력
        printf("%-20s %-10lu %-10lu %-10lu %-9d%% %s\n",
               ent->mnt_fsname, total_inodes, used_inodes, free_inodes, usage, ent->mnt_dir);
    }

    endmntent(mnt);
    return 0;
}
