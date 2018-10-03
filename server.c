#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <memory.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <pthread.h>


#define MAXBUFSIZE 500





int main(int argc, char* argv[]){

	int bytesWritten = 0;
	int fd_server;
	struct sockaddr_in server_addr;
	unsigned int remoteLen;
	int nbytes;
	pid_t pid;
	int on = 1;

	char buffer[MAXBUFSIZE];

	char successMsg[] = "SERVER: I got your message!\n";

	if (argc != 2){
		printf("USAGE: %s  <port>\n", argv[1]);
		exit(1);
	}

	bzero(&server_addr, sizeof(server_addr));           //zero the struct

	setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

	server_addr.sin_family = AF_INET;                   //address family
	server_addr.sin_port = htons(8080);       			//htons() sets the port # to network byte order
	server_addr.sin_addr.s_addr = INADDR_ANY;           //supplies the IP address of the local machine
	

	if ((fd_server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("unable to create socket\n");
	}

	if (bind(fd_server, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("unable to bind socket\n");
	}

	if(listen(fd_server, 10) < 0 ){
		perror("unable to listen\n");
		close(fd_server);
		exit(0);
	}

	while(1){

		struct sockaddr_in client_addr;
		socklen_t sin_len = sizeof(client_addr);



		int fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &sin_len);

		if(fd_client < 0){
			perror("accept messed up");	
		}
		printf("Connection begun...\n");

		nbytes = read(fd_client, buffer, MAXBUFSIZE);
		printf("Message received:\n");
		printf("%s\n", buffer);

		send(fd_client, successMsg, sizeof(successMsg), 0);


	}

	return 0;
}