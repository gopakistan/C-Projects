/* time_client.c - main */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>

#define BUFSIZE 64

int main(int argc, char *argv[])
{
    char *host = "localhost"; /* host to use if none supplied */
    char *service = "3000";
    char pdu[101]; /* 1 char = type, rest =data*/
    char data[100];
    char filename[100];
    int options = O_RDWR | O_APPEND;
    int file, i;
    struct hostent *phe; /* pointer to host information entry */
    struct sockaddr_in sin; /* an Internet endpoint address */
    int s, n, type; /* socket descriptor and socket type */
    off_t offset;

    switch (argc) {
        case 1:
            host = "localhost";
            break;
        case 3:
            service = argv[2];
            /* FALL THROUGH */
        case 2:
            host = argv[1];
            break;
        default:
            fprintf(stderr, "usage: UDPtime [host [port]]\n");
            exit(1);
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;

    /* Map service name to port number */
    sin.sin_port = htons((u_short)atoi(service));

    if (phe = gethostbyname(host)) {
        memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
    } else if ((sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE) {
        fprintf(stderr, "Can't get host entry \n");
        exit(1);
    }

    /* Allocate a socket */
    s = socket(PF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        fprintf(stderr, "Can't create socket \n");
        exit(1);
    }

    /* Connect the socket */
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        fprintf(stderr, "Can't connect to %s %s \n", host, service);
        exit(1);
    }

    while (1) {
        //pdu[0] = 'C';
        strcpy(pdu, "C");
        printf("Enter file name:\n");
        n = read(0, filename, 100); //READ FILENAME
        //filename[n-1]='\0';
        strcat(pdu, filename); //ADD C TO FILENAME
        printf("What you entered: ");
        write(1, pdu, n+1);
        write(s, pdu, n+1); //SEND FILENAME
        n = read(s, pdu, 101); //READ FILE DATA
        printf("filedata: ");
        for (i = 0; i < n; i++) {
            printf("%c", pdu[i]);
        }
        if (pdu[0] == 'E') { //CHECK ERROR
            printf("Error\n");
            continue;
        }
        file = open(filename, O_CREAT, 0644);
        close(file);
        file = open(filename, O_RDWR | O_APPEND, 0644); //IF NO ERROR -> CREATE FILE

        while (pdu[0] == 'D') { //read until all data from desired file is received
            for (i = 0; i < n - 1; i++) {
                pdu[i] = pdu[i+1];
            }

            pdu[n] = '\0';

            write(file, pdu, strlen(pdu)-1);
            n = read(s, pdu, 101);
            printf("%s", pdu);

        }
        //if we get here, that means type == F
        for (i = 0; i < n - 1; i++) {
            pdu[i] = pdu[i+1];
        }
        //pdu[n-1] = '\n';
        pdu[n] = '\0';
        write(file, pdu, n-1);
        close(file);
    }

    close(s);
    exit(0);
}
