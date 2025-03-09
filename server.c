#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct sockaddr_in server_addr, client_addr;
    long addr;
    
    /* start server */
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(sfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(sfd, 5);

    int len = sizeof(client_addr);
    int conn_fd = accept(sfd, (struct sockaddr*)&client_addr, &len);
    
    printf("Enter address to read: ");
    scanf("%lx", &addr);
    send(conn_fd, (char*)&addr, sizeof(addr), 0);

    char received;
    for (int i = 0; i < 20; i++) {
        recv(conn_fd, &received, 1, 0);
        printf("%x ", received);
    }
    printf("\n");

    close(sfd);
}