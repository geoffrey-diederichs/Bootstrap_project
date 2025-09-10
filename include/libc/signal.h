#ifndef SIGNAL_H
#define SIGNAL_h

struct sigaction {
    void (*sa_handler)(int);
    unsigned long sa_flags;
    void (*sa_restorer)(void);
    unsigned long long sa_mask;
};

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

#endif