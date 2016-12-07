#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include "protocol.h"

//duong dan den bo cau hoi

//thoi gian cho viec tra loi 1 cau hoi
void get_thoigian(char *thoi_gian)
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  strcpy(thoi_gian,asctime (timeinfo));
}
#define TIME_OUT 15000
char get_answer(int time_out)
{
    struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
    char answer;

    if( poll(&mypoll, 1, time_out) )
    {
        scanf("%c", &answer);
        while(getchar()!='\n');
        return answer;
    }
    else return 'F';
}
struct cauhoi nhap_cauhoi(i)
{
	struct cauhoi ch;
	printf("nhap cau hoi %d: \n",i);
	gets(ch.cauhoi);
	printf("nhap dap an 1:\n");
	gets(ch.dapan1);
	printf("nhap dap an 2:\n");
	gets(ch.dapan2);
	printf("nhap dap an 3:\n");
	gets(ch.dapan3);
	printf("nhap dap an 4:\n");
	gets(ch.dapan4);
	printf("nhap dan an dung:\n");
	ch.dapan_dung=getchar();
	while(getchar()!='\n');
	return ch;
}

void them_cauhoi(){
	int i=1;
	struct cauhoi ch;
	char temp[5];
	FILE *fp;
	char bo_cauhoi[15];
	printf("bo cau hoi ban muon them:\n");
	gets(bo_cauhoi);
	strcat(bo_cauhoi,".dat");
	fp=fopen(bo_cauhoi,"wb");
	do{
		ch=nhap_cauhoi(i);
		fwrite(&ch,sizeof(struct cauhoi),1,fp);
		printf("tiep tuc khong (y/n)\n");
		gets(temp);
		i++;
	}while(!strcmp(temp,"y"));
	fclose(fp);
}
struct cauhoi *lay_cauhoi(int set,int vi_tri)
{
	char bo_cauhoi[32]="bo_cauhoi/bo_cauhoi";
	char b[15];
    sprintf(b, "%d",set );
    strcat(bo_cauhoi,b);
	struct cauhoi *ch;
	FILE *fp;
	strcat(bo_cauhoi,".dat");
	ch=(struct cauhoi*)malloc(sizeof(struct cauhoi));
	fp= fopen(bo_cauhoi,"r+b");
	if(fp==NULL){
		printf("khong ton tai bo cau hoi tren.\n");
		return NULL;
	}
	if(fseek(fp,vi_tri*sizeof(struct cauhoi),SEEK_SET)!=0){
		printf("Fseek failed!!\n");
		return NULL;
	}
	fread(ch,sizeof(struct cauhoi),1,fp);
	fclose(fp);
	return ch;
}
void in_cauhoi(cauhoi ch)
{
	printf("  %s\n\n",ch.cauhoi );
	printf("---------------------------------------\n");
	printf("\tA.%s\n",ch.dapan1);
	printf("\tB.%s\n",ch.dapan2);
	printf("\tC.%s\n",ch.dapan3);
	printf("\tD.%s\n",ch.dapan4);
}

