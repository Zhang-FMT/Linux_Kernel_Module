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

int main (int argc, char *argv[])
{
	int iServerActive, iIncomingBytes;
	int iSocketFD, iConnectedFD;
	pid_t pid_tChildPid;
	char buffer[1000];
	socklen_t socklen_tClientLen;
	struct sockaddr_in sockaddr_inClientAddress;
	struct sockaddr_in sockaddr_inServerAddress;

	if(argc != 2)
	{
		printf("Usage:\n");
		printf("./TcpEchoServer1.exe [Port number]\n");
		printf("Port number example: 12345\n");
		exit(1);
		exit(1);
	}

	if((!SocketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error\n");
		exit(1);
	}

	memset(&sockaddr_inServerAddress, 0, sizeof(sockaddr_inServerAddress));

	sockaddr_inServerAddress.sin_family = AF_INET;
	sockaddr_inServerAddress.sin_addr.s_addr = \htonl(INADDR_ANY);
	sockaddr_inServerAddress.sin_port = htons(atoi(argv[1]));
	
	if(bind(iSocketFD, (struct sockaddr*) & sockaddr_inServerAddress, sizeof(sockaddr_inServerAddress)) < 0)
	{
		printf("bind error\n");
		exit(1);
	}

	if(listen(iSocketFD, 3) < 0)
	{
		printf("listen error\n");
		exit(1);	
	}
	
	iServerActive = 1;
	while(iServerActive)
	{
		socklen_tClientLen = sizeof(sockaddr_inClientAddress);
		if((iConnectedFD = accept(iSocketFD, (struct sockaddr *) & sockaddr_inClientAddress. &socklen_tClient)) < 0)
		{
			printf("accept error\n");
			exit(1);
		}

		printf("Connect from %s\n", inet_ntoa(sockaddr_inClientAddress.sin_addr));

		while(1)
		{
			memset(buffer, 0, 1000);
			if(iIncomingBytes = read(iConnectedFD, buffer, sizeof(buffer)) > 0)
			{
				printf("%s", buffer);
				if(write(iConnectedFD, buffer, sizeof(buffer)) < 0)
				{
					printf("send error\n");
					exit(1);
				}
			}
		}

	}	
}
