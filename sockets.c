#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#define PORT 8080
#define MAXMSG 512


int make_socket (uint16_t port)
{
	int sock;
	struct sockaddr_in name;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock<0)
	{	
		perror("socket");
		exit(EXIT_FAILURE);
	}

	name.sin_family = AF_INET;
      	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
 	if(bind(sock, (struct sockaddr*)&name, sizeof(name))<0)
	{
		perror ("bind");
		exit (EXIT_FAILURE);
	}
	
	printf( "connected\n");
	
	int len=20;
	char buffer[len];

	//inet_ntop(AF_INET, &(name.sin_addr), buffer, len);
	//printf("address: %s\n", buffer);
	

	return sock; 

}

void init_sockaddr(struct sockaddr_in *name, const char* hostname, uint16_t port){
	struct hostent *hostinfo;

	name->sin_family = AF_INET;
	name->sin_port = htons(port);
	hostinfo = gethostbyname(hostname);
	
	if(hostinfo == NULL){
		printf("Uknown host %s\n", hostname);
		exit(EXIT_FAILURE);
	}

	name->sin_addr = *(struct in_addr *) hostinfo->h_addr_list[0];  
}

void write_to_server(int filedes){
	int nbytes;
	const char* message = "Hello! A server!";
	nbytes = write(filedes, message, strlen(message) + 1);
	if(nbytes<0){
		perror("write");
		exit (EXIT_FAILURE);
	}
}

int main()
{
	int port = 8080;
	int sock; 
	//int sock = make_socket(port);
	struct sockaddr_in server;


	sock = socket(PF_INET, SOCK_STREAM, 0); 
	init_sockaddr(&server, "Patrick-PC", port);

	



	// if(0 < connect(sock, (struct sockaddr *)&server, sizeof(server)))
	// {
	// 	perror("connect (client)");
	// 	exit (EXIT_FAILURE);
	// }
	// write_to_server(sock);

	// close(sock);
	// exit(EXIT_SUCCESS);


	return 0; 
}
