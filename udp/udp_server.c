#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define Port 8080
#define MAX 1024

int main()
{
	int sockfd;
	char buffer[MAX];
	char *hello = "hello from shobhit->billionaire in making";
	struct sockaddr_in servaddr,cliaddr;

	if((sockfd = socket(AF_INET, SOCK_DGRAM,0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	
	}

	memset(&servaddr,0,sizeof(servaddr));
	memset(&cliaddr,0,sizeof(cliaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port  = htons(Port);

	if(bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) <0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	int len,n;
	len = sizeof(cliaddr);

	n = recvfrom(sockfd, (char *)buffer,MAX,MSG_WAITALL, (struct sockaddr *)&cliaddr,&len);
	buffer[n] = '\0';
	printf("client : %s\n",buffer);
	sendto(sockfd,(const char *)hello,strlen(hello), MSG_CONFIRM, (const struct sockaddr *)&cliaddr,len);
	printf("dope message sent.\n");
	return 0;


}
