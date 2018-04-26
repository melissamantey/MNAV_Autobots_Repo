#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

void error(const char * msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char * argv[]) {
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[2048];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	if(argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		error("ERROR opening socket");
	}
	int optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); 
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("ERROR on binding");
	}
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	struct timeval te;
	gettimeofday(&te, NULL);
	long long milliseconds1 = te.tv_sec*1000LL + te.tv_usec/100;
	
	if(newsockfd < 0) {
		error("ERROR on accept");
	}
	bzero(buffer, 2048);
	FILE *fp;
	fp = fopen("received.csv", "w+");
	n = 0;
	int i = 0;
	while(n < 1999) {
		n += recv(newsockfd, buffer + n, 2047 - n, 0);
	}
	for(i = 0; i < n; i++) {
		fprintf(fp, "%c", buffer[i]);
	}
	fclose(fp);

	close(newsockfd);
	close(sockfd);
		
	gettimeofday(&te, NULL);
	long long milliseconds2 = te.tv_sec*1000LL + te.tv_usec/100;
	FILE * fr;
	fr = fopen("time1.txt","a");
	fprintf(fp, "%s ", "Time to transmit: ");
	fprintf(fp, "%lld\n", milliseconds2-milliseconds1);
	fclose(fr);
	if(n < 0) {
		error("ERROR writing to socket");
	}

//	n = write(sockfd, buffer, 2047);

	return 0;
}
