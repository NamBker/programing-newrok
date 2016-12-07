#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include <errno.h>
#include <arpa/inet.h>
#include <termios.h>
#include <time.h>
#include "lib/error.h"
#include "start.h"
#include "lib/login_signup.h"


//-----------------------------
#define FAIL -1
#define BUFF_SIZE 256
//-----------------------------



//-----------------------------
int create_connection(int PORT,char IP[10])
{
		
	struct sockaddr_in serverAddr;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		printf("khong the tao duoc socket\n");
		return FAIL;
	}
	memset(&serverAddr,0,sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr(IP);
	if(connect(sockfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr))<0){
	printf("ket noi den server that bai\n");
	return FAIL;
	}
	printf("server duoc ket noi thanh cong ...\n");
	return SUCCESS;
}
int main()
{
	create_connection(5500,"127.0.0.1");
	int n,t;
	protocol p;
	while(1){
		// bien t de check trang thai cua signup
		t=-1;
		printf("1.LOGIN\n");
		printf("2.SIGNUP\n");		
		printf("3.QUIT\n");
		scanf("%d",&n);
		while(getchar()!='\n');
		if(n==3) break;
		switch(n){
			case 1: c_login(&p);
					break;
			case 2: t=c_signup(&p);
					break;
		}
		if(t==SIGNUP_FAIL) continue;
		send(sockfd,&p,sizeof(protocol),0);
		recv(sockfd,&p,sizeof(protocol),0);
		switch(p.flag){
			case SUCCESS: printf("\nLogin success!!\n"); start(p); break;
			case NO_ACCOUNT: printf("\n%s",LOGIN_ERROR);
							 break; 
			case LOGIN_FAIL: printf("\n%s",LOGIN_ERROR);
							 break; 
			case SIGNUP_FAIL: printf("\n%s",SIGNUP_ERROR2);
		}
	}
}
