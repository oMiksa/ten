#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int message;
int msg;
int main(int argc, char const *argv[]) {

    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(7780);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(2);
    }
    while (1)
    {
        scanf("%s", &message);

        send(sock, &message, sizeof(message), 0);

        //recv(sock, &msg, sizeof(msg), 0);

        //printf("%d\n", &msg);
    }
    close(sock);

    return 0;
}