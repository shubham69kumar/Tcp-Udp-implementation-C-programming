#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define Port 8080
#define Max 1024

int main()
{
	int sockfd;
	char buffer[Max];
	char *hello = "hello from billionaire";
	struct sockaddr_in servaddr;

	if((sockfd = socket(AF_INET, SOCK_DGRAM,0))<0)
	{
		perror("socket creating failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr,0,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(Port);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n,len;
	len = sizeof(servaddr);

	sendto(sockfd,(const char *)hello, strlen(hello),MSG_CONFIRM,(const struct sockaddr *)&servaddr,sizeof(servaddr));
	printf("hello message sent\n");

	n = recvfrom(sockfd, (char *)buffer, Max, MSG_WAITALL, (struct sockaddr *)&servaddr,&len);
	buffer[n] = '\0';
	printf("server : %s\n",buffer);

	close(sockfd);
	return 0;


}
