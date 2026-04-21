#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock = 0;
    struct sockaddr_in server_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Erro na criacao do socket\n");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;


    bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(sock, 5);

    int addrlen = sizeof(server_addr);
    int connection = accept(sock, (struct sockaddr *)&server_addr, (socklen_t*)&addrlen);


    char message[1024];
    char buffer[1024];
    
    while (1){
        read(connection, buffer, 1024);
        printf("server: %s\n", buffer);
        
        printf("escreva a msg: ");
        fgets(message, 1024, stdin);
        send(connection, message, strlen(message), 0);
        if(strcmp(message, "exit\n") == 0){
            break;
        }
        
    }
    close(connection);
    close(sock);
    return 0;
    
}