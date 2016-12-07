#include <stdio.h>
#include <time.h>
#include <string.h>
#include "lib/protocol.h"
void save_score(char account[32],int score)
{
	FILE *fp;
	char file_name[50]="user/";
	diem sc;
	time_t rawtime;
    struct tm * timeinfo;

	time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strcpy(sc.thoi_gian,asctime(timeinfo));	
    printf("%s\n",sc.thoi_gian );
    sc.score=score;
    printf("%d\n",sc.score );
    strcat(file_name,account);
	strcat(file_name,".dat");
	fp=fopen(file_name,"ab");
	fwrite(&sc,sizeof(diem),1,fp);
	fclose(fp);
}
int get_score(char account[32],protocol *p,int i)
{
	FILE *fp;
	char file_name[50]="user/";
	strcat(file_name,account);
	strcat(file_name,".dat");
	fp=fopen(file_name,"rb");
	if(fseek(fp,i*sizeof(diem),SEEK_SET)!=0){
		printf("Fseek failed!!\n");
		return 0;
	}
	fread(&(p->sc),sizeof(diem),1,fp);
	if(feof(fp)){
		return 0;
	}
	else {
		fclose(fp);
		return 1;
	}
}
int main()
{
	protocol p;
	int i=0;
	while(1){
		if(get_score("duc5",&p,i)){
			i++;
			printf("thoi igna: %s\n",p.sc.thoi_gian);
			printf("diem_so:%d\n",p.sc.score);
		}else break;
	}
	

}