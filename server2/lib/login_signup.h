
#define SIGNUP_SUCCESS 12
int check_user(user u) {
	FILE *f;
	user temp;
	f = fopen("user.txt", "r+");
	if (f == NULL) return 0;
	while (!feof(f)) {
		if (fscanf(f, "%s %s\n", temp.account, temp.password) > 1) {
			if(!strcmp(u.account,temp.account))
			{
				if(!strcmp(u.password,temp.password)) {
					fclose(f);
					return SUCCESS;
				}
				else {
					fclose(f);
					return LOGIN_FAIL;
				}
			}
		}
	}
	fclose(f);
	return SIGNUP_SUCCESS;
}
void s_login(protocol *p)
{
	int temp;
	temp = check_user(p->u);
	if(temp!=SIGNUP_SUCCESS) p->flag=temp;
	else p->flag=NO_ACCOUNT;

}

void s_signup(protocol *p) {
	FILE *fp,*fp1;
	int temp;
	char account[50]="user/";

	temp = check_user(p->u);

	if(temp==SIGNUP_SUCCESS) {
		p->flag=SUCCESS;
		fp=fopen("user.txt","a");
	    fprintf(fp,"\n%s %s", p->u.account, p->u.password);
		fclose(fp);

		strcat(account,p->u.account);
		strcat(account,".txt");
		fp1=fopen(account,"a");
		fclose(fp1);
	}
	else p->flag= SIGNUP_FAIL;
}





