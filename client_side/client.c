#include "client.h"

int main(int argc, char * argv[]) {
#ifndef SOCK_IN_USE
	UNUSED(argv);
	UNUSED(argc);
#endif

#ifdef SOCK_IN_USE
	if(argc < 3) {
	printf("ERROR: too few arguments, expected <host>, <port>\n");
		exit(0);
	}

/****** SOCKET CREATION ***********************************************/

	int sockfd, portno;
	struct sockaddr_in serv_addr;
	struct hostent * server;

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) {
		perror("ERROR: could not open socket");
		exit(0);
	}
	
	server = gethostbyname(argv[1]); // Gets IPv4 address of input host
	if(server == NULL) {
		printf("ERROR: could not resolve host %s\n", argv[1]);
		exit(0);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);	
	serv_addr.sin_port = htons(portno); // htons converts from host short byte order to network byte order
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("ERROR: could not connect to %s at port %s\n", argv[1], argv[2]);
		exit(0);
	}
	
/****** END SOCKET CREATION *******************************************/
#endif
	
	char type;
	char value[BUF_SIZE];
	bzero(value, BUF_SIZE);
	
	//sock_write(1, "REQ");
	sock_read(sockfd, &type, value);
	switch(type) {
		case 0x53: // S
			printf("Got steering value\n");
			break;
		case 0x41: // A
			printf("Got latitude value\n");
			break;
		case 0x4F: // O
			printf("Got longitude value\n");
			break;
		default:
			printf("Got undefined data\n");
			break;
	}
	printf("%c,%s\n", type, value);

#ifdef SOCK_IN_USE
	close(sockfd);
#endif
	return 0;
}

void error(const char * msg) {
	perror(msg);
	exit(0);
}

int sock_write(int sockfd, char * string) {
#ifdef SOCK_IN_USE
	int n = write(sockfd, string, strlen(string));
	if(n < 0) {
		error("ERROR: write to socket failed");
	}
#else
	UNUSED(sockfd);
	printf("%s\n", string);
#endif
	return 0;
}

int sock_read(int sockfd, char * type, char * value) {
#ifdef SOCK_IN_USE
	char buffer[BUF_SIZE];
	int n = recv(sockfd, buffer, BUF_SIZE, 0);
	if(n <= 0) {
		error("ERROR: no read");
	}
	printf("%s\n", buffer);
	UNUSED(type);
	UNUSED(value);
	// Need to parse into type and value here somehow. IDK how right now.
#else
	UNUSED(sockfd);
	
	scanf("%[^,]%*c %s", type, value);
#endif
	return 0;
}
