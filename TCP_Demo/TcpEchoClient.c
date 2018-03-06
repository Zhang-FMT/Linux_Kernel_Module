#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int iSocketFD;
	char buffer[1000];
	int iIncomingBytes;
	struct sockaddr_in sockaddr_inServerAddress;

	if(argc != 3)
	{
		printf("Socket error\n");
		exit(1);
	}

	if((iSocketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error\n");
		exit(1);
	}

	memset(&sockaddr_inServerAddress, 0, sizeof(sockaddr_inServerAddress));
	sockaddr_inServerAddress.sin_family = AF_INET;
	sockaddr_inServerAddress.sin_addr.s_addr = inet_addr(argv[1]);
	sockaddr_inServerAddress.sin_port = htons(atoi(argv[2]));

	if(connect(iSocketFD, (struct sockaddr *) &sockaddr_inServerAddress, sizeof(sockaddr_inServerAddress)) < 0)
	{
		printf("connect error\n");
		exit(1);
	}

	while(fgets(buffer, 1000,stdin) != NULL)
	{
		if(write(iSocketFD, buffer, strlen(buffer)) < 0)
		{
			perror("send error\n");
			exit(0);
		}
		if(iIncomingBytes = read(iSocketFD, buffer, sizeof(buffer)) > 0)
		{
			printf("%s", buffer);
		}
		memset(buffer, 0, 1000);
	}
	exit(0);
}




















