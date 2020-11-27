// Brayden Lappies & Jo Eun Kim
// Project 4 - web server
// This program will create a web server that will take a request from
// the web browser and send the requested file (or return 404 file not found)

#include <unistd.h>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <libgen.h>

#define PORT 8000
char cmd[45] = "HTTP/1.0 200 OK\nContent-Length:";
char *servPath;

//thread
void *t_action(void *sock); // will search for file

//helper function for substring from m to nth
char* mySubstr(const char *src, int m, int n) {
	// get length of the destination string
	int len = n - m;
	// allocate (len + 1) chars for destination (+1 for extra null character)
	char *dest = (char*)malloc(sizeof(char) * (len + 1));
	// extracts characters between m'th and n'th index from source string
	// and copy them into the destination string
	for (int i = m; i < n && (*(src + i) != '\0'); i++) {
		*dest = *(src + i);
		dest++;
	}
	// null-terminate the destination string
	*dest = '\0';
	// return the destination string
	return dest - len;
}

int main(int argc, char *argv[]) {
	int server_fd, new_socket; //server on server_fd, new_socket to accept client
	struct sockaddr_in address, client;
	int addrlen = sizeof(address);
	pthread_t request;
	
	if (argc != 2 ) {
		printf("supply a path,starting with the /!\n");
	 	exit(1);
	}
	servPath = argv[1]; // gets path from command line
	
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {//set up server socket
        perror("In socket");
        exit(EXIT_FAILURE);
    }
	
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT ); // short int port to server info
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) { //binds socket
        perror("In bind");
        exit(EXIT_FAILURE);
    }
	 if (listen(server_fd, 10) < 0) { //sets up socket listening
        perror("In listen");
        exit(EXIT_FAILURE);
    }

	while ((new_socket = accept(server_fd, (struct sockaddr *)&client, (socklen_t*)&addrlen)) ) {
		if (pthread_create(&request, NULL, t_action, (void *)(intptr_t)new_socket) == 0);
			pthread_join( request, NULL); // so program doesn't terminate 
	}
	return 0;
}

void *t_action(void *sock) {
	int new_socket2, startPos=0, cnt=0;
	char *rqstType;
	char *rqstPath;
	char request[2048];
	char nRes[2048] = "HTTP/1.0 404 Not Found"; // negative response
	new_socket2 = (intptr_t)sock;
	struct stat st;
	
	char fullPath[] = "."; //initialize to current directory
	strcat(fullPath, servPath);  // sets path to what is specified in command line argument under curr dir
	
  	int fd, contentLen; // will hold file and the length of content in it respectively
	
	/* Take request and create response */
    bzero(request, 2048);
    recv(new_socket2, request, sizeof(request)-1, 0);

   	printf("\nClient:\n%s", request);

   	//substring the first line of request to get the Type and Path of the request individually
	for(int i=0; i<strlen(request); i++) {
	   	if (request[i] == '\n') // ignore except 1st line
	   		break;
	   	if( request[i] == ' ') {
	   		if(cnt == 0) { //first occurance of ' ' => substr from 0 to i(current)
	   			rqstType = mySubstr(request, 0, i); // 0=start pos, i=len
	   			startPos = i+1; // update startPos for the next substr
	   			cnt ++;
	   		}
	   		if (cnt == 1) { //second occurance of ' ' => substr from updated startPos to i(current)
	   			rqstPath = mySubstr(request, startPos, i);
	   		}
	   	}
	}
	//get the whole path starting from current directory to file name to be searched
	printf("requested path: %s\n", rqstPath);
	strcat(fullPath, rqstPath); // "./[argv][path]"
	fd = open(fullPath, O_RDONLY); //open file as read only
	
	char pRes[2048], buf[2048], temp[10]; //pRes will be the whole response, buf will hold the content, temp will be used for concatenation
	if (fd < 0) { //can't open/find the file => 404 error.
	 	write(new_socket2, nRes, strlen(nRes)); 
		printf("404 Error Sent.\n");
	} 
	else { //prepare for the response 
		read(fd, buf, 2048); // read content inside and store it into buf
		stat(fullPath, &st); // get file properties
		contentLen = st.st_size;
		sprintf(temp, "%d", contentLen); // convert int to string and store it to temp to be concatenated
		strcpy(pRes, cmd); // copy cmd to pRes => pRes = "HTTP/1.0 200 OK\nContect-Length:"
		strcat(pRes, temp); // "HTTP/1.0 200 OK\nContect-Length:[contentLen]"
		strcat(pRes, "\n\n"); // "HTTP/1.0 200 OK\nContect-Length:[contentLen]\n\n"
		strcat(pRes, buf); // "HTTP/1.0 200 OK\nContect-Length:[contentLen]\n\n[buf]"

		printf("Response:\n%s\n\n", pRes);
		strcpy(request, pRes);
		//send pRes to browser
		write(new_socket2, request, strlen(pRes));

		close(fd);
		//clear the message buffer: request
		memset(request, 0, 2048);
	}
    close(new_socket2);
}