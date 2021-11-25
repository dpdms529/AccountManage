#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

class Account{	//계정 클래스 : 계정의 사이트, 아이디, 비밀번호를 가지고 있다. 
	public:
		Account(){}
		Account(string site, string id, string pw){
			this->site = site;
			this->id = id;
			this->pw = pw;
		}
		string getSite(){
			return site;
		}
		void setSite(string site){
			this->site = site;
		}
		string getID(){
			return id;
		}
		void setID(string id){
			this->id = id;
		}
		string getPW(){
			return pw;
		}
		void setPW(string pw){
			this->pw = pw;
		}
	private:
		string site;
		string id;
		string pw;
};

class User{	//사용자 클래스 : 사용자 이름, 사용자 비밀번호, 사용자의 계정 벡터를 가지고 있다. 
	public:
		User(){}
		User(string name, string pw){
			this->name =  name;
			this->pw = pw;
			num++;
			actNum = 0;
		}
		static int num;
		int actNum;
		string getName(){
			return name;
		}
		void setName(string name){
			this->name = name;
		}
		string getPW(){
			return pw;
		}
		void setPW(string pw){
			this->pw = pw;
		}
		void add();	//계정을 추가하는 함수 
		void del();	//계정을 삭제하는 함수 
		void change();	//계정의 아이디 또는 비밀번호를 변경하는 함수 
		void find();	//사이트 또는 아이디로 계정을 조회하는 함수 
		
	private:
		string name;
		string pw;
		vector<Account> account;
		
};
int User::num = 0;

vector<User> user(1);

void addUser();	//사용자를 추가하는 함수 
void deleteUser(User* u);	//사용자를 삭제하는 함수 
int isUser();	//사용자인지 확인하는 함수 
int changeUser();	//사용자를 변경하는 함수 
void makePW();	//비밀번호를 생성해주는 함수 
void menu(User* u);	//사용자별 메뉴를 보여주는 함수 
void start();	//프로그램을 시작하는 함수 

int main(){
	start();
	return 0;
}

void addUser(){
	bool more = true;
	string name, pw;
	char check;
	while(more){
		cout << endl << "< 사용자 추가 >" << endl;
		cout << "사용자명 : ";
		getline(cin, name);
		cout << "비밀번호 : ";
		getline(cin, pw); 
		User u(name,pw);
		user.push_back(u);
		cout << "사용자 추가가 완료되었습니다." << endl; 
		cout << "사용자 추가를 계속 할까요?(y/n) : ";
		cin >> check;
		cin.ignore();
		if(check == 'n'){
			more = false; 
			return;
		}
	}
	
}

void deleteUser(User* u){
	string name,pw,masterPW;
	char check;
	int index; 
	if(u->getName() == user[1].getName()){
		cout << "마스터 사용자이므로 삭제할 수 없습니다." << endl;
		return;	
	}
	cout << endl << "< 사용자 삭제 >" << endl;
	cout << "사용자명 : ";
	getline(cin,name);
	for(int i = 0;i<user.size();i++){
		if(u->getName() == user[i].getName()){
			index = i;
		}
	}
	if(name == u->getName()){
		cout << "사용자 비밀번호 : " ;
		getline(cin,pw);
		if(pw == u->getPW()){
			cout << "정말로 삭제하겠습니까?(y/n) : ";
			cin >> check;
			cin.ignore();
			if(check == 'y'){
				user.erase(user.begin() + index);
				User::num--;
				cout << "사용자 삭제가 완료되었습니다." << endl;
				do{
					cout << "마스터 사용자 비밀번호 : ";
					cin >> masterPW;
					cin.ignore();
					if(masterPW!=user[1].getPW()){
						cout << "비밀번호가 틀렸습니다." << endl;
					}
				}while(masterPW!=user[1].getPW());
				menu(&user[1]); 
			}
		}else{
			cout << "비밀번호가 틀렸습니다." << endl;
			return; 
		} 
	}else{
		cout << "사용자 본인이 아닙니다." << endl; 
	}
}

int isUser(){
	string name, pw;
	int i;
	cout << endl << "< 사용자 확인 >" << endl;
	cout << "사용자명 : ";
	getline(cin, name);
	for(i = 0;i<user.size();i++){
		if(name == user[i].getName()){
			cout << "사용자 비밀번호 : "; 
			getline(cin, pw);
			while(pw != user[i].getPW()){
				cout << "비밀번호가 틀렸습니다." << endl << "사용자 비밀번호 : ";
				getline(cin, pw);
			}
			return i; 
		}
	}
	if(i == user.size()){
		cout << "사용자가 아닙니다." << endl;
		return -1;
	}
	
}

int changeUser(){
	string name,pw;
	int i;
	cout << "변경할 사용자명 : ";
	getline(cin,name);
	for(i = 0;i<user.size();i++){
		if(name == user[i].getName()){
			cout << "사용자 비밀번호 : ";
			getline(cin,pw);
			while(pw != user[i].getPW()){
				cout << "비밀번호가 틀렸습니다." << endl << "사용자 비밀번호 : ";
				getline(cin,pw);
			}
			return i; 
		}
	}
	if(i == user.size()){
		cout << "사용자가 아닙니다." << endl;
		return -1;
	}
}

void makePW(){
	srand((unsigned int)time(NULL));
	int pwLen;
	char check;
	bool upper=false, sc=false;
	char ch[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
				,'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','~','!','@','#','$','%','^','&','*','?'};
	cout << "비밀번호 길이 : ";
	cin >> pwLen;
	char pw[pwLen+1];
	cout << "대문자를 사용하겠습니까?(y/n) : ";
	cin >> check;
	if(check == 'y'){
		upper = true;
	}
	cout << "특수문자를 사용하겠습니까?(y/n) : ";
	cin >> check;
	cin.ignore();
	if(check == 'y'){
		sc = true;
	}
	if(upper && sc){
		for(int i = 0;i<pwLen;i++){
			pw[i] = ch[rand()%72];
		}
	}else if(upper){
		for(int i = 0;i<pwLen;i++){
			pw[i] = ch[rand()%62];
		}
	}else if(sc){
		for(int i = 0;i<pwLen;i++){
			int r = rand()%5;
			if(r==0){
				pw[i] = ch[(rand()%10)+62];
			}else{
				pw[i] = ch[rand()%36];	
			}

		}
	}else{
		for(int i = 0;i<pwLen;i++){
			pw[i] = ch[rand()%36];
		}
	}
	pw[pwLen] = 0;
	string password(pw);
	cout << "생성된 비밀번호 : " << password << endl;
}

void menu(User* u){
	int n = 0, check;
	while(n != 9){
		cout << endl;
		cout << "사용자 : " << u->getName() << endl;
		cout << "---------- 메뉴 ---------- " << endl;
		cout << "1. 계정 추가" << endl << "2. 계정 삭제" << endl << "3. 계정 변경" << endl << "4. 계정 조회" << endl << "5. 비밀번호 생성" << endl 
			 << "6. 사용자 변경" << endl << "7. 사용자 추가" << endl << "8. 사용자 삭제" << endl << "9. 종료" << endl;
		cin >> n;
		cin.ignore();
		switch(n){
		case 1:
			cout << endl << "< 계정 추가 >" << endl;
			u->add();
			break;
		case 2:
			cout << endl << "< 계정 삭제 >" << endl; 
			u->del();
			break;
		case 3:
			cout << endl << "< 계정 변경 >" << endl;
			u->change();
			break;
		case 4:
			cout << endl << "< 계정 조회 >" << endl; 
			u->find();
			break;
		case 5:
			cout << endl << "< 비밀번호 생성 >" << endl;
			makePW();
			break;
		case 6:
			cout << endl << "< 사용자 변경 >" << endl; 
			check = changeUser();
			if(check != -1){
				menu(&user[check]);
			}
			break;
		case 7:
			addUser();
			break; 
		case 8:
			deleteUser(u);
			break; 
		case 9:
			cout << endl << "< 종료 >" << endl;
			cout << "이용해주셔서 감사합니다." << endl;
			Sleep(3000);
			exit(0);
		default:
			cout << "잘못 입력하셨습니다." << endl;
			break;
		}
	}
	
}

void start(){
	cout << "< 계정 관리 및 비밀번호 생성 프로그램 >" << endl;
	cout << "안녕하세요! 계정 관리 및 비밀번호 생성 프로그램입니다." << endl << "먼저 사용자를 추가해주세요." << endl;
	addUser();
	int check = -1;
	while(check == -1){
		check = isUser();
	}
	menu(&user[check]);
	return;
}

void User::add(){
	string site,id,pw;
	cout << "추가할 계정의 사이트명 : ";
	getline(cin, site);
	cout << "추가할 계정의 아이디 : ";
	getline(cin, id);
	cout << "추가할 계정의 비밀번호 : ";
	getline(cin, pw);
	Account a(site,id,pw);
	account.push_back(a);
	cout << "추가가 완료되었습니다." << endl;
 	actNum++;
}

void User::del(){
	string site;
	char check;
	vector<Account*> a;
	vector<int> index;
	int n;
	if(account.size() == 0){
		cout << "삭제할 계정이 존재하지 않습니다." << endl;
		return;	
	} 
	cout << "삭제할 계정의 사이트명 : ";
	getline(cin, site);
	for(int i = 0;i<account.size();i++){
		if(site == account[i].getSite()){
			a.push_back(&account[i]);
			index.push_back(i);
		}
	}
	if(a.size() == 0){
		cout << "원하시는 계정이 존재하지 않습니다." << endl;
		return;
	} 

	if(a.size() == 1){
		n = 1;
	}else{
		for(int i = 0;i<a.size();i++){
			cout << i+1 << ". "<< a[i]->getSite() << " : " << a[i]->getID() << endl;
		}		
		cout << "몇 번째 계정을 삭제하겠습니까? ";
		cin >> n; 		
	}

	for(int i = 0;i<a.size();i++){
		if(i == n-1){
			cout << "정말로 삭제하겠습니까?(y/n) : ";
			cin >> check;
			cin.ignore(); 
			if(check == 'y'){
				account.erase(account.begin()+index[n-1]);
				actNum--;
			}else{
				return;
			}	
			cout << "삭제가 완료되었습니다." << endl;
			return; 
		}
	}
	
}

void User::change(){
	string site,id,pw;
	char check;
	vector<Account*> a;
	int n;
	if(account.size() == 0){
		cout << "변경할 계정이 존재하지 않습니다." << endl;
		return;	
	} 
	cout << "변경할 계정의 사이트명 : ";
	getline(cin, site); 
	for(int i = 0;i<account.size();i++){
		if(site == account[i].getSite()){
			a.push_back(&account[i]);
		}
	}
	if(a.size() == 0){
		cout << "원하시는 계정이 존재하지 않습니다." << endl;
		return; 
	}
	if(a.size() == 1){
		n = 1;
	}else{
		for(int i = 0;i<a.size();i++){
			cout << i+1 << ". "<< a[i]->getSite() << " : " << a[i]->getID() << endl;
		}
		cout << "몇 번째 계정을 변경하겠습니까? ";
		cin >> n;		
	}
	
	for(int i = 0;i<a.size();i++){
		if(i==n-1){ 
			cout << site << "의 아이디를 변경하겠습니까?(y/n) : ";
			cin >> check;
			if(check == 'y'){
				cin.ignore();
				cout << "변경할 아이디 : ";
				getline(cin, id);
				a[i]->setID(id); 
			}
			cout << site << "의 비밀번호 변경하겠습니까?(y/n) : ";
			cin >> check;
			cin.ignore();
			if(check == 'y'){
				cout << "변경할 비밀번호 : "; 
				getline(cin, pw);
				a[i]->setPW(pw);
			}
			cout << "변경이 완료되었습니다." << endl;
			return;
		}
	}
	
}

void User::find(){
	bool check = false;
	int n;
	string site,id;
	
	if(account.size() == 0){
		cout << "조회할 계정이 존재하지 않습니다." << endl;
		return;	
	}else{
		cout << "1. 사이트명으로 조회" << "	2.아이디로 조회" << endl;
		cin >> n;
		cin.ignore();
		switch(n){
			case 1:
				cout << "조회할 계정의 사이트명 : ";
				getline(cin,site);
				for(int i = 0;i<account.size();i++){
					if(site == account[i].getSite()){
						cout << "아이디 : " << account[i].getID() << "	비밀번호 : " << account[i].getPW() << endl;
						check = true;
					}
				}
				break;

			case 2:
				cout << "조회할 계정의 아이디 : ";
				getline(cin,id);
				for(int i = 0;i<account.size();i++){
					if(id == account[i].getID()){
						cout << "사이트 : " << account[i].getSite() << "	비밀번호 : " << account[i].getPW() << endl;
						check = true;
					}
				} 
				break;
			default:
				cout << "잘못 입력하셨습니다." << endl;
				return;
		}
		if(!check){
			cout << "원하시는 계정이 존재하지 않습니다." << endl;
		}	
	}
	
}

