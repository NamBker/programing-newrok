
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
	gets(p->u.password);
}

int c_signup(protocol *p)
{
	char t;
	char temp[32];
	p->flag = SIGNUP;
	do{

		printf("Account:\n");
		gets(p->u.account);
		printf("Password:\n");
		gets(p->u.password);
		printf("Comfirmation:\n");
		gets(temp);
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





