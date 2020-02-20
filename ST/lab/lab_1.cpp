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

#define N 5

pthread_mutex_t mut;

int sumator = 0;

struct st{
    int sock;
    char mass[1024];
};

void *ser_fn(void *s) {
    struct st *data = (struct st *)s;
    char buff[1024];
    int sock = data->sock;
    while (1) {
        pthread_mutex_lock(&mut);
        
        recv(sock, &buff, sizeof(buff), 0);
        printf("msg = %s\n", data->mass);
        printf("buff = %s\n", buff);
        for (int i = 0; i < 1024; i++)
            data->mass[i] = buff[i];
        sleep(10);
        //send(sock, &in, sizeof(int), 0);

        pthread_mutex_unlock(&mut);
    }
    close(sock);
    pthread_exit(0);
}

int main(int argc, char const *argv[]){
    pthread_mutex_init(&mut, 0);
    pthread_t* threads = (pthread_t*) malloc(N * sizeof(pthread_t));
    struct st *threadData = (struct st*) malloc(sizeof(struct st));


    int fd_socket, sock;
    struct sockaddr_in addrs;
    char buf[1024];
    int bytes_read;

    addrs.sin_family = AF_INET;
    addrs.sin_port = htons(7780);
    addrs.sin_addr.s_addr = inet_addr("127.0.0.1");

    if((fd_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("socket");
        exit(1);
    }
    if(bind(fd_socket, (struct sockaddr *)&addrs, sizeof(addrs)) < 0){
        perror("bind");
        exit(2);
    }
    listen(fd_socket, N);

    int i = 0;

    while(1)
    {
        sock = accept(fd_socket, NULL, NULL);//(struct sockaddr_in *)&cl, sizeof(cl));
        if(sock < 0){
            perror("accept");
            exit(3);
        }

        threadData->sock = sock;
        pthread_create(&(threads[i++]), NULL, ser_fn, threadData);
        
        //for(int i = 0; i < N; i++)
		//    pthread_join(threads[i], NULL);
            
    }
    close(fd_socket);
    return 0;
}