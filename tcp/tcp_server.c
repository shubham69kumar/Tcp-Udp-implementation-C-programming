#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>

#define Max 1024
#define Port 8080
#define SA struct sockaddr

void func(int sockfd)
{
	char buf[Max];
	int n;
	
	for(;;)
	{
		bzero(buf,Max);

		// read the message from the client

		read(sockfd,buf,sizeof(buf));
		printf("from client: %s\t To client :",buf);
		bzero(buf,Max);
		n = 0;

		//write server message in the buffer  

		while((buf[n++] = getchar()) != '\n')
			;
		write(sockfd,buf,sizeof(buf));

		if (strncmp("exit",buf,4) == 0)
		{
			printf("server exit..\n");
			break;
		}
	}


}


int main()
{
	int sockfd,connfd,len;
	struct sockaddr_in servaddr,cli;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd == -1)
	{
		printf("socket creation failed ..\n");
		exit(0);
	}
	else
		printf("socket created successfully\n");
	bzero(&servaddr,sizeof(servaddr));

	//assigning IP,port
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(Port);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// binding new socket to given ip and verification
	
	if ((bind(sockfd, (SA*)&servaddr,sizeof(servaddr))) != 0)
	{
		printf("socked bind failed..\n");
		exit(0);
	}
	else
		printf("socket binded successfully..\n");

	// listen and verification
	
	if ((listen(sockfd,5)) != 0)
	{
		printf("listen failed\n");
		exit(0);
	}
	else
		printf("server listening\n");
	len = sizeof(cli);


	// accept data packet from client and verify it
	
       	connfd = accept(sockfd,(SA*)&cli,&len);
	if(connfd < 0)
	{
		printf("server accept failed\n");
		exit(0);
	}
	else
		printf("server accept the client\n");

	// function call
	func(connfd);

	close(sockfd);
}
