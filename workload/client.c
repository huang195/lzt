#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main(int argc, char const *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hostname>\n", argv[0]);
        return 1;
    }

    // Set stdout and stderr to be line-buffered
    setvbuf(stdout, NULL, _IOLBF, 0);
    setvbuf(stderr, NULL, _IOLBF, 0);

    // Get the server hostname from the command line arguments
    const char *hostname = argv[1];

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    // Get the server address by hostname
    if ((server = gethostbyname(hostname)) == NULL) {
        fprintf(stderr, "No such host: %s\n", hostname);
        return -1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    while (1) {
        // Create a message with the current time
        time_t t;
        time(&t);
        snprintf(message, BUFFER_SIZE, "Hello from client at %s", ctime(&t));

        // Send a message to the server
        send(sock, message, strlen(message), 0);
        printf("Message sent: %s\n", message);

        // Read the server's response
        int valread = read(sock, buffer, BUFFER_SIZE);
        if (valread > 0) {
            printf("Server: %s\n", buffer);
        } else if (valread == 0) {
            // Server closed the connection
            printf("Server disconnected\n");
            close(sock);
            return 0;
        } else {
            perror("read");
            close(sock);
            return -1;
        }

        // Sleep for 1 second
        sleep(1);
    }

    close(sock);
    return 0;
}

