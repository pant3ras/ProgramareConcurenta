#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4567

int main(){

	int sockfd, ret;
	 struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}



                        while(1){
                                recv(newSocket, buffer, 1024, 0);

                                if(strcmp(buffer, ":exit") == 0){
                                        printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr)$
                                        break;
                        }

else if(strcmp(buffer, "1") == 0){
bzero(msg,100);
printf("am primit numarul: %s", buffer);
strcat(msg, ". Due to Coronavirus all TCP applications have to be converted to UDP to avoid Handshakes!");
strcat(buffer, msg);
send(newSocket, buffer, strlen(buffer),0);
printf("send joke :)) ");
bzero(buffer,100 );
}

else if(strcmp(buffer,"2") == 0){
bzero(msg,100);
printf("am primit numarul: %s", buffer);
strcat(msg, ". I do not know what to do herrreee!!!!");
strcat(buffer, msg);
send(newSocket,buffer, strlen(buffer), 0);
printf("send truth :(");
bzero(buffer, 100);
}
else if(strcmp(buffer,"3") == 0){
printf("am primit numarul: %s\n", buffer);
strcat(msg, ". Nothing.");
strcat(buffer, msg);
send(newSocket, buffer, strlen(buffer), 0);
printf("send nada\n");
bzero(buffer, 100);
}

else if(strcmp(buffer,"4") == 0) {
bzero(msg,100);
printf("am primit numarul: %s\n", buffer);
strcat(msg, ". Acesta e un test sa vedem daca merge");
strcat(buffer, msg);
send(newSocket, buffer, strlen(buffer),0);
bzero(buffer, 100);
}

else{
        printf("Client: %s\n", buffer);
        send(newSocket, buffer, strlen(buffer), 0);
        bzero(buffer, sizeof(buffer));
                                }
        }
}
        }

        close(newSocket);


        return 0;


}