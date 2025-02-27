#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <net/if_arp.h>

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;

bool changemac(int8 *If, Mac mac);
Mac generatorMC(void);

struct s_mac {
    int64 addr:48;
};

typedef struct s_mac Mac;

Mac generatorMC() {
    int64 a, b;
    Mac mac;
    a = (long)random();
    b = (long)random();
    mac.addr = ((a * b) % 281474976710656);
    return mac;
}

bool changemac(int8 *If, Mac mac) {
    struct ifreq ir;
    int fd, ret;
    char *p;
    p = (char *)&mac;
    fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    assert(fd > 0);

    strncpy(ir.ifr_ifrn.ifrn.name, (char *)If, (IFNAMSIZ-1));
    ir.ifr_ifru.ifru_hwaddr.sa_family = ARPHRD_ETHER;
    memcpy(ir.ifr_ifru.ifru_hwaddr.sa_data, p, 6);

    ret = ioctl(fd, SIOCSIFHWADDR, &ir);
    close(fd);
    return (!ret) ? true : false;
}

int main(int argc, char *argv[]) {
    Mac mac;
    int8 *If;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s INTERFACE\n", argv[0]);
        return -1;
    } else {
        If = (int8 *)argv[1];
    }

    srand(getpid());
    mac = generatorMC();
    if (changemac(If, mac))
        printf("0x%llx\n", (long long)mac.addr);
    else
        assert_perror(errno);
    return 0;
}