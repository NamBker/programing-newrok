#include "lib/cauhoi.h"
#include "lib/test.h"
#define VIEWER 20
#define OUT 21
int sockfd;
int ngaunhien(int i)
{
    int j;
    while(1){
            srand(time(NULL));
            j=1+rand()%4;
            if(j!=i) break;
    }
    return j;
}
void in_dapan(cauhoi ch,int i){
	switch(i){
		case 1: printf("	A.%s\n",ch.dapan1); break;
		case 2: printf("	B.%s\n",ch.dapan2); break;
		case 3: printf("	C.%s\n",ch.dapan3); break;
		case 4: printf("	D.%s\n",ch.dapan4); break;
	}
}
void in_50_50(cauhoi ch,int i,int j)
{
	printf("  %s\n",ch.cauhoi);
	if(i<j){
		in_dapan(ch,i);
		in_dapan(ch,j);
	}
	else{
		in_dapan(ch,j);
		in_dapan(ch,i);
	}
}
int _50_50(cauhoi ch)
{
	char temp;
	int j;
	temp=ch.dapan_dung;
	switch(temp){
		case 'a': j=ngaunhien(1);
				  in_50_50(ch,1,j);
				  break;
		case 'b': j=ngaunhien(2);
				  in_50_50(ch,2,j);
				  break;
		case 'c': j=ngaunhien(3);
				  in_50_50(ch,3,j);
				  break;
		case 'd': j=ngaunhien(4);
				  in_50_50(ch,4,j);
				  break;
	}

}
void tro_giup(int t)
{
	switch(t){
		case 0: printf("		Het quyen tro giup\n");
				printf("\n		tro giup: 50-50:x   change-ques:x\n\n");break;
		case 1: printf("		50-50 press key h\n");
				printf("\n		tro giup: 50-50:o   change-ques:x\n\n");break;
		case 2: printf("		change-ques press key g\n");
				printf("\n		tro giup: 50-50:x   change-ques:o\n\n");break;
		case 3: printf("		50-50 press key h\n");
				printf("		change-ques press key g\n");
				printf("\n		tro giup: 50-50:o   change-ques:o\n\n");break;
	}
}

void delay()
{
	printf(" The game will start in: \n");
	get_answer(2000);
	printf("3...\n");
	get_answer(2000);
	printf("2...\n");
	get_answer(2000);
	printf("1....\n");
	get_answer(1000);
}
int score(int count)
{
	switch(count){
		case 1: return 10;
		case 2: return 20;
		case 3: return 40;
		case 4: return 80;
		case 5: return 100;
		case 6: return 200;
		case 7: return 500;
		case 8: return 800;
		case 9: return 1000;
		case 10: return 2000;
		case 11: return 4000;
		case 12: return 6000;
		case 13: return 8000;
		case 14: return 10000;
		case 15: return 15000;
		default: return 0;
	}
}

int start(protocol p)
{
	int temp;
	while(1){
		printf("\t+++++++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("\t+     Hello,%s\n",p.u.account);
		printf("\t+ 1.Enter room and Watting for other user to play\n");
		printf("\t+ 2.Xem lich su\n");
		printf("\t+ 3.khan gia\n");
		printf("\t+ 4.Quit\n");
		printf("\t++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("You Chose:");
		scanf("%d",&temp);
		while(getchar()!='\n');
		if(temp==4) break;
		if(temp == 1) {
		printf("Watting for other user....\n");
		start_game();
		}
		if(temp==2) in_lichsu();
		if(temp==3) viewer();
	}

}
void in_lichsu()
{
	protocol p;
	p.flag=VIEW_SCORE;
	printf("lich su nguoi choi\n");
	while(1){
		send(sockfd,&p,sizeof(protocol),0);
		recv(sockfd,&p,sizeof(protocol),0);
		if(p.flag==DONE) break;
		printf("thoi gian: %s\n",p.sc.thoi_gian);
        printf("diem_so:%d\n",p.sc.score);
		 
	}
}
void viewer()
{
	protocol p;
	p.flag=VIEWER;
	send(sockfd,&p,sizeof(protocol),0);
	while(1){
		recv(sockfd,&p,sizeof(protocol),0);
		if(p.flag==QUES){
			printf("Player answer : %c \n",p.answer );
			get_answer(1000);
			in_cauhoi(p.ch);
		}
		if(p.flag==WRONG_ANSWER){
			printf("Wrong answer\n");
			break;
		}
		if(p.flag==WIN){
			printf("Player win!!!\n");
			break;
		}
	}
}
int start_game()
{
	int check_50_50=1,check_ch_q=1;
	int t=3;
	char temp;

	int count=0;
	protocol p;
	p.flag=ENTER_ROOM;
	int check=1;
	while(1){
		send(sockfd,&p,sizeof(protocol),0);
		recv(sockfd,&p,sizeof(protocol),0);
		switch(p.flag){
			case SUB_QUES: 	printf("Da du so luong nguoi choi\n");
							delay();
							printf("phan choi cau hoi phu bat dau\n");
							p.flag = SUB_ANSWER;
							in_cauhoi(p.ch);
							p.answer=get_answer(TIME_OUT);
							break;
			case QUES: 	if((temp=='g')) printf("Thay doi cau hoi\n"); 
						else printf("		Correct!!\n");
						get_answer(1000);
						if(check==1){
							printf("Chuc mung ban da la nguoi choi chinh\n");
							get_answer(1000);
							delay();
							check=0;
						}
						printf("-Ques %d\n",p.count);
						tro_giup(t);
						in_cauhoi(p.ch);
						temp=get_answer(TIME_OUT);
						if((temp=='h')&&(check_50_50==1)) {
							t=t-1;
							tro_giup(t);
							check_50_50=_50_50(p.ch);
							p.flag=ANSWER;
							temp=get_answer(TIME_OUT);
							count=p.count;
						}
						if((temp=='g')&&(check_ch_q==1)){
							p.flag=CHANGE_QUES;
							check_ch_q=0;
							t=t-2;
						}
						else {
							p.flag=ANSWER;
							p.answer=temp;
						}
						count=p.count;
						break;
			case WRONG_ANSWER:  if(p.answer=='F'){
									printf("%s\n",TIME_OUT_ERROR);
								}else printf("Wrong answer !!\n");
								break;
			case MUON: printf("you had answered too late\n");

		}
		if(p.flag==WIN){
			printf("CONGRATULATION,YOU ARE THE MILLIONAIRE\n");
			congra();
			break;
		}
		if(p.flag==FULL){
			printf("%s\n\n",FULL_ROOM);
			break;
		}
		if((p.flag == WRONG_ANSWER)||(p.flag==MUON)){
			printf("End Game :( :( :(\n\n");
			break;
			}
	}
	printf("\n\nYour score: %d\n\n\n",score(count));
}