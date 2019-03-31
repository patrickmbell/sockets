#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int make_socket (uint16_t port)
{
	int sock;
	struct sockaddr_in name;

	sock = socket(PF_INET, SOCK_STREAM, 0);
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

	inet_ntop(AF_INET, &(name.sin_addr), buffer, len);
	printf("address: %s\n", buffer);
	

	return sock; 

}

int main()
{
	uint16_t port = 8080;
	int sock = make_socket(port);
	return 0; 
}
