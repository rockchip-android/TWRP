#include <errno.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>

//add by lili@vamrs.com for adj userdata
#define MAX_PATH_LEN 512

/* returns basename and keeps dirname in the @path */
static char *stripoff_last_component(char *path)
{
    char *p = strrchr(path, '/');

    if (!p)
        return NULL;
    *p = '\0';
    return ++p;

}

int run(const char *filename, char *const argv[])
{
    struct stat s;
    int status;
    pid_t pid;

    if (stat(filename, &s) != 0) {
        fprintf(stderr, "cannot find '%s'", filename);
        return -1;
    }

    printf("executing '%s'\n", filename);

    pid = fork();

    if (pid == 0) {
        setpgid(0, getpid());
        /* execute */
        execv(filename, argv);
        fprintf(stderr, "can't run %s (%s)\n", filename, strerror(errno));
        /* exit */
        _exit(0);
    }

    if (pid < 0) {
        fprintf(stderr, "failed to fork and start '%s'\n", filename);
        return -1;
    }

    if (-1 == waitpid(pid, &status, WCONTINUED | WUNTRACED)) {
        fprintf(stderr, "wait for child error\n");
        return -1;
    }

    if (WIFEXITED(status)) {
        printf("executed '%s' done\n", filename);
    }

    printf("executed '%s' return %d\n", filename, WEXITSTATUS(status));
    return 0;
}

int adj_userdata(const char* blk_device){

    struct stat st = {0};
    /*char real_block[MAX_PATH_LEN] = {0};
    if(readlink(blk_device, real_block, MAX_PATH_LEN -1) < 0){
        printf("%s\n", "read link error");
        return -1;
    }

    printf("real_block path:%s\n", real_block);*/

    if(stat(blk_device, &st) != 0){
        printf("stat error %s\n", blk_device);
        return -1;
    }

    char devPath[MAX_PATH_LEN] = {0};
    int len = snprintf(devPath, MAX_PATH_LEN, "/sys/dev/block/%d:%d", major(st.st_rdev), 0);
    if(len <= 0){
        printf("%s\n", "snprintf error");
        return -1;
    }

    char realDevPath[MAX_PATH_LEN] = {0};
    if(readlink(devPath, realDevPath, MAX_PATH_LEN -1) < 0){
        printf("%s\n", "readlink error");
        return -1;
    }

    char* name = stripoff_last_component(realDevPath);

    if(!name){
        printf("%s\n", "stripoff_last_component error");
        return -1;
    }

    printf("dev name:%s\n", name);

    const char* parted_path = "/sbin/parted";
    char* part_num;
    char* dev_path;
    len = asprintf(&part_num, "%d", minor(st.st_rdev));
    if(len <= 0){
        printf("%s\n", "part_num snprintf error");
        return -1;
    }
    len = asprintf(&dev_path, "/dev/block/%s", name);
    if(len <= 0){
        printf("%s\n","dev_path snprintf error");
        return -1;
    }

    const char* const f2fs_argv[] = {"/sbin/parted", "-s", dev_path, "resizepart", part_num, "100%", NULL};
    int result = run(parted_path, (char* const*)f2fs_argv);
    // int result = exec_cmd(f2fs_argv);
    free(part_num);
    free(dev_path);
    return result;
}