#define LOGIN 1
#define SIGNUP 2
#define SUCCESS 3
#define LOGIN_FAIL 4
#define SIGNUP_FAIL 5
#define SUB_QUES 6
#define QUES 7
#define ANSWER 8
#define ENTER_ROOM 9
#define WRONG_ANSWER 10
#define SUB_ANSWER 11
#define NO_ACCOUNT 12
#define FULL 13
#define WIN 14
#define MUON 15
#define CHANGE_QUES 16
#define VIEW_SCORE 17
#define DONE 18
typedef struct _score{
	char thoi_gian[32];
	int score;
}diem;
typedef struct user {
	char account[32];
	char password[32];
}user;
typedef struct cauhoi{
	char cauhoi[100];
	char dapan1[20];
	char dapan2[20];
	char dapan3[20];
	char dapan4[20];
	char dapan_dung;
}cauhoi;
typedef struct protocol{
	int flag; // 
	user u; // thong tin dang nhap
	cauhoi ch;
	char answer;
	diem sc;
	int count;

}protocol;
