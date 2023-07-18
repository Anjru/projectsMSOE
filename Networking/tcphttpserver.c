#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>

//Sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>

#include <arpa/inet.h>

#define SIZE 8000
#define BACKLOG 10  // Passed to listen()

void report(struct sockaddr_in *serverAddress);

int main(void)
{

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8001);
    serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress));

    int listening = listen(serverSocket, BACKLOG);

    if (listening < 0) {
        printf("Error: The server is not listening.\n");
        return 1;
    }

    report(&serverAddress);
    int clientSocket;

    while(1) {
        clientSocket = accept(serverSocket, NULL, NULL);
        char* httpHeader = malloc(SIZE);
        char* buffer = malloc(SIZE);
        memset(buffer, 0, SIZE);
	    int bytes_read;
        char* request = malloc(SIZE);
        memset(request, 0, SIZE);

        buffer[0] = '\0';
        bytes_read = read(clientSocket,buffer,999);
        buffer[bytes_read] = '\0';

        int indexCounter = 0;
        while(buffer[indexCounter + 5] != ' ')
        {
            request[indexCounter] = buffer[indexCounter + 5];
            indexCounter++;
        }

        free(buffer);
        if(strcmp(request, "") == 0)
        {
            request = "index.html";
        }

        FILE *htmlData = fopen(request, "r");
        
        struct stat sb;
        stat(request, &sb);
        
        char* responseData = malloc(sb.st_size);
        if(htmlData == NULL)
        {
            memset(httpHeader, 0, SIZE);
            strcat(httpHeader, "HTTP/1.1 404 NOT FOUND\r\n\r\n");
        } else {
            memset(httpHeader, 0, SIZE);
            memset(responseData, 0, sb.st_size);
            if(strstr(request, ".jpg")) {
                sprintf(httpHeader, "HTTP/1.1 200 OK\r\nContent-Type: image/jpeg\r\nContent-Length: %ld\r\n\r\n", sb.st_size);
            } else {
                sprintf(httpHeader, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %ld\r\n\r\n", sb.st_size); 
            }
            fseek(htmlData, 0, SEEK_SET);
            fread(responseData, sizeof(char), sb.st_size + 1, htmlData);
        }

        write(clientSocket, httpHeader, strlen(httpHeader));
        write(clientSocket, responseData, sb.st_size);
        close(clientSocket);
    }
    return 0;
}

void report(struct sockaddr_in *serverAddress)
{
    char hostBuffer[INET6_ADDRSTRLEN];
    char serviceBuffer[NI_MAXSERV];
    socklen_t addr_len = sizeof(*serverAddress);
    int err = getnameinfo((struct sockaddr *) serverAddress, addr_len, hostBuffer,
        sizeof(hostBuffer), serviceBuffer, sizeof(serviceBuffer), NI_NUMERICHOST);

    if (err != 0) {
        printf("It's not working!!\n");
    }

    printf("\n\n\tServer listening on http://%s:%s\n", hostBuffer, serviceBuffer);
}