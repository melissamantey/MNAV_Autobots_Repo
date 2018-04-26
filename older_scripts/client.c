#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void error(const char *msg)
{
  perror(msg);
  exit(0);
}

int main(int argc, char *argv[])
{
  time_t rawtime;
  struct tm * timeinfo;

  time (&rawtime);
  timeinfo = localtime (&rawtime);
  printf("Current local time and date: %s", asctime (timeinfo) );
  FILE *fp;
  fp=fopen("time.txt","a");
  fprintf(fp,"%s", "Start time:" );
  fprintf(fp,"%s", asctime (timeinfo) );
  fclose(fp);

  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[2048];
  if (argc < 3) {
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(0);
  }

 portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0)
    error("ERROR opening socket");

  server = gethostbyname(argv[1]);
  if (server == NULL) {
    fprintf(stderr, "ERROR, no such host\n");
    exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
     error("ERROR connecting");

//   printf("Please enter the message: ");
   bzero(buffer, 2048);
  
//Read file
  char ch;
  int counter = 0;
  FILE *fptr;
  fptr = fopen("val.csv","r");

  if (fptr == NULL){
    printf("Cannot open file \n");
    exit(0);
  }
  //while(ch!=EOF){
  for(int i = 0; i < 1999; i++){
    printf("%c", ch);
    ch = fgetc(fptr);
    buffer[i] = ch;
    //counter++;
  }
  printf("Success! Closing file.");
  fclose(fptr);



//   fgets(buffer, 2047, stdin);
   n = write(sockfd, buffer, strlen(buffer));
   printf("%d\n", n); 
 if (n < 0)
    error("ERROR reading from socket");
  
  //listen(sockfd, 5);
  //n = read(sockfd, buffer, 2047);
  
  close(sockfd);

  time (&rawtime);
  timeinfo = localtime (&rawtime);
  printf("Current local time and date: %s", asctime (timeinfo) );
  fp=fopen("time.txt","a");
  fprintf(fp,"%s", "End time:" );
  fprintf(fp,"%s", asctime (timeinfo) );
  fclose(fp);

  return 0;
}
