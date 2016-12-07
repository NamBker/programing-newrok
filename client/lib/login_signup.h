static struct termios old, new;
void initTermios(int echo) {
	tcgetattr(0, &old);                       
	new = old;                                
	new.c_lflag &= ~ICANON;                   
	new.c_lflag &= echo ? ECHO : ~ECHO;       
	tcsetattr(0, TCSANOW, &new);              
}

void resetTermios(void) {
  tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo) {
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}

char getch(void) {
    return getch_(0);
}

int get_pass(char pass[]){
	int i=0;

	while(1){
		pass[i]=getch();
		if(pass[i]== '\n') break;
		printf("*");
		i++;
	}
	pass[i]='\0';
	return 1;
}


#define SIGNUP_SUCCESS 12
int check_user(user u)
{

	FILE *fp;
	user temp;
	fp=fopen("user.dat","rb");
	while(!feof(fp))
	{
		fread(&temp,1,sizeof(user),fp);
		if(!strcmp(u.account,temp.account))
		{
			if(!strcmp(u.password,temp.password)) {
				fclose(fp);
				return SUCCESS;
			}
			else {
				fclose(fp);
				return LOGIN_FAIL;
			}
		}
	}
	fclose(fp);
	return SIGNUP_SUCCESS;
}


void s_login(protocol *p)
{
	int temp;
	temp = check_user(p->u);
	if(temp!=SIGNUP_SUCCESS) p->flag=temp;
	else p->flag=NO_ACCOUNT;

}

void s_signup(protocol *p)
{
	FILE *fp,*fp1;
	int temp;
	char account[50]="user/";
	temp=check_user(p->u);
	if(temp==SIGNUP_SUCCESS) {
		p->flag=SUCCESS;
		fp=fopen("user.dat","ab");
		fwrite(&(p->u),1,sizeof(user),fp);
		fclose(fp);
		strcat(account,p->u.account);
		strcat(account,".dat");
		fp1=fopen(account,"wb");
		fclose(fp1);
	}
	else p->flag= SIGNUP_FAIL;
}



/// FOR CLIENT


void c_login(protocol *p)
{
	p->flag = LOGIN;
	printf("Account:\n");
	gets(p->u.account);
	printf("Password:\n");
	get_pass(p->u.password);
}

int c_signup(protocol *p)
{
	char t;
	char temp[32];
	p->flag = SIGNUP;
	do{
		printf("\nAccount:");
		gets(p->u.account);
		printf("\nPassword:");
		get_pass(p->u.password);
		printf("\nComfirmation:");
		get_pass(temp);
		if(!strcmp(p->u.password,temp)){
			return SUCCESS;
		}
		else {
			printf("ban co muon nhap lai khong(y/n)\n");
			t=getchar();
			while(getchar()!='\n');
		}
	}while(t=='y');
	return SIGNUP_FAIL;
}




