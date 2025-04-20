#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "stats_function.h"

FILE *logfile = NULL;

void move_up(int lines) {
    printf("\033[%dA", lines);
}

void move_down(int lines) {
    printf("\033[%dB", lines);
}

void ctrlc_handler(int sig) {
    char c;
    printf("\nAre you sure you want to quit? (Y/N): ");
    c = getchar();
    if (c == 'Y' || c == 'y') {
        if (logfile) fclose(logfile);
        exit(0);
    }
}

void ctrlz_handler(int sig) {
    printf("\nCtrl-Z is disabled for this program.\n");
}

void set_signals_parent() {
    signal(SIGINT, ctrlc_handler);
    signal(SIGTSTP, ctrlz_handler);
}

void set_signals_child() {
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

void read_memory_info(int *fd, double prev_used, int graph_flag) {
    pid_t pid = fork();
    if (pid == 0) {
        set_signals_child();
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        get_memory_info(prev_used, graph_flag);
        exit(0);
    }
    else {
        close(fd[1]);
    }
}

void read_cpu_info(int *fd, int tdelay) {
    pid_t pid = fork();
    if (pid == 0) {
        set_signals_child();
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        calculate_cpu_use(tdelay);
        exit(0);
    }
    else {
        close(fd[1]);
    }
}

void read_user_info(int *fd) {
    pid_t pid = fork();
    if (pid == 0) {
        set_signals_child();
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        show_session_user();
        exit(0);
    }
    else {
        close(fd[1]);
    }
}

void show_sys_usage(int sample, int tdelay, int graph_flag) {
    double prev_used = 0;
    for (int i = 0; i < sample; ++i) {
        printf("\033[H\033[J");  // clear screen
        printf("System Snapshot %d/%d\n", i+1, sample);
        show_sys_info();

        int fd_mem[2], fd_cpu[2], fd_user[2];
        pipe(fd_mem); pipe(fd_cpu); pipe(fd_user);

        read_memory_info(fd_mem, prev_used, graph_flag);
        read_cpu_info(fd_cpu, tdelay);
        read_user_info(fd_user);

        char buf[1024];
        read(fd_mem[0], buf, sizeof(buf));
        printf("%s\n", buf);
        if (logfile) fprintf(logfile, "%s\n", buf);

        read(fd_cpu[0], buf, sizeof(buf));
        printf("%s\n", buf);
        if (logfile) fprintf(logfile, "%s\n", buf);

        read(fd_user[0], buf, sizeof(buf));
        printf("%s\n", buf);
        if (logfile) fprintf(logfile, "%s\n", buf);

        sleep(tdelay);
    }
}

void vertify_arg(int argc, char *argv[], int *sample, int *tdelay,
                 int *sys_flag, int *user_flag, int *sequential_flag,
                 int *graph_flag, int *sample_flag, int *tdelay_flag) {

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            printf("Usage: ./syswatch [--samples N] [--tdelay N] [--graphics] [--logfile FILE]\n");
            exit(0);
        }
        else if (strcmp(argv[i], "--samples") == 0 && i+1 < argc) {
            *sample = atoi(argv[++i]);
            *sample_flag = 1;
        }
        else if (strcmp(argv[i], "--tdelay") == 0 && i+1 < argc) {
            *tdelay = atoi(argv[++i]);
            *tdelay_flag = 1;
        }
        else if (strcmp(argv[i], "--graphics") == 0) {
            *graph_flag = 1;
        }
        else if (strcmp(argv[i], "--logfile") == 0 && i+1 < argc) {
            logfile = fopen(argv[++i], "w");
            if (!logfile) {
                perror("Could not open logfile");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int sample = 10, tdelay = 1;
    int sys_flag = 0, user_flag = 0, sequential_flag = 0;
    int graph_flag = 0, sample_flag = 0, tdelay_flag = 0;

    set_signals_parent();
    vertify_arg(argc, argv, &sample, &tdelay, &sys_flag, &user_flag,
                &sequential_flag, &graph_flag, &sample_flag, &tdelay_flag);

    show_sys_usage(sample, tdelay, graph_flag);

    if (logfile) fclose(logfile);
    return 0;
}
