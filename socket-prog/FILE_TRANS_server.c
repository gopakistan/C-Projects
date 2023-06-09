#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <time.h>
#include <strings.h>
#include <fcntl.h>

#define BUFLEN 100 /* buffer length */

int main(int argc, char *argv[]) {
    struct sockaddr_in fsin; /* the from address of a client */
    char *service = "3000"; /* service name or port number */
    char buf[100]; /* "input" buffer; any size > 0 */
    char pts[101];
    int sock, n; /* server socket */
    time_t now; /* current time */
    int alen; /* from-address length */
    struct sockaddr_in sin; /* an Internet endpoint address         */
    int s, type; /* socket descriptor and socket type    */
    u_short portbase = 0; /* port base, for non-root servers */

    switch (argc) {
        case 1:
            break;
        case 2:
            service = argv[1];
            break;
        default:
            fprintf(stderr, "usage: time_server [host [port]]\n");
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;

    /* Map service name to port number */
    sin.sin_port = htons((u_short) atoi(service));

    /* Allocate a socket */
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        fprintf(stderr, "can't creat socket\n");
        exit(1);
    }

    /* Bind the socket */
    if (bind(s, (struct sockaddr *) &sin, sizeof(sin)) < 0)
        fprintf(stderr, "can't bind to %s port\n", service);

    int byteTotal = 0;

    while (1) {
        alen = sizeof(fsin);
        if ((n = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &fsin, &alen)) < 0)
            fprintf(stderr, "recvfrom error\n");

        char filename[BUFLEN];
        strcpy(filename, buf);

        printf("%s \n", filename);
        printf("%d \n", strlen(filename));

        int i = 0;
        for (i = 0; i < n - 1; i++) {
            filename[i] = filename[i + 1];
        }
        filename[n - 2] = '\0';

        int fileDescriptor = open(filename, O_RDONLY); //change to filename later
        if (fileDescriptor < 0) {
            fprintf(stderr, "ERROR, file open failed");
            pts[0] = 'E';
            (void) sendto(s, pts, 1, 0, (struct sockaddr *) &fsin, sizeof(fsin));
        }

        while ((n = read(fileDescriptor, buf, 100)) > 0) {
            if (n == 100) {
                pts[0] = 'D';
                for (i = 0; i < n; i++) {
                    pts[i + 1] = buf[i];
                }

                printf("%s", pts);
                (void) sendto(s, pts, strlen(pts), 0, (struct sockaddr *) &fsin, sizeof(fsin));
            } else {

                pts[0] = 'F';
                for (i = 0; i < n; i++) {
                    pts[i + 1] = buf[i];
                }

                printf("%s", pts);
                (void) sendto(s, pts, n + 1, 0, (struct sockaddr *) &fsin, sizeof(fsin));
            }

            byteTotal += n;
        }

        close(fileDescriptor);
    }
}
