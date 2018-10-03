#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

struct sockaddr_in client_addr, remote;

int main(int argc, char* argv[]){


	if (argc < 4)
	{
		printf("USAGE:  <server_ip> <server_port> <message>\n");
		exit(1);
	}
	int portNum = atoi(argv[2]);
	char msg[strlen(argv[3])];
	strcpy(msg, argv[3]);
	char buff[1024];

	bzero(&remote,sizeof(remote));
	remote.sin_family = AF_INET;
	remote.sin_port = htons(portNum);
	remote.sin_addr.s_addr = inet_addr("127.0.1.1");

	bzero(&client_addr,sizeof(client_addr));

	socklen_t remoteLen = sizeof(remote);

	int sockfd;
	int valRead;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Unable to create socket\n");

	}

	if(connect(sockfd, (struct sockaddr *)&remote, sizeof(remote)) < 0){
		printf("Connect failed for port # %d\n", portNum);
		exit(-1);
	}

	send(sockfd, msg, strlen(msg), 0);
	printf("'%s' successfully sent\n", msg);

	valRead = read(sockfd, buff, 1024);
	printf("Buffer below:\n");
	printf("%s", buff);


	return 0;
}
