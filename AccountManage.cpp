#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

class Account{	//���� Ŭ���� : ������ ����Ʈ, ���̵�, ��й�ȣ�� ������ �ִ�. 
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

class User{	//����� Ŭ���� : ����� �̸�, ����� ��й�ȣ, ������� ���� ���͸� ������ �ִ�. 
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
		void add();	//������ �߰��ϴ� �Լ� 
		void del();	//������ �����ϴ� �Լ� 
		void change();	//������ ���̵� �Ǵ� ��й�ȣ�� �����ϴ� �Լ� 
		void find();	//����Ʈ �Ǵ� ���̵�� ������ ��ȸ�ϴ� �Լ� 
		
	private:
		string name;
		string pw;
		vector<Account> account;
		
};
int User::num = 0;

vector<User> user(1);

void addUser();	//����ڸ� �߰��ϴ� �Լ� 
void deleteUser(User* u);	//����ڸ� �����ϴ� �Լ� 
int isUser();	//��������� Ȯ���ϴ� �Լ� 
int changeUser();	//����ڸ� �����ϴ� �Լ� 
void makePW();	//��й�ȣ�� �������ִ� �Լ� 
void menu(User* u);	//����ں� �޴��� �����ִ� �Լ� 
void start();	//���α׷��� �����ϴ� �Լ� 

int main(){
	start();
	return 0;
}

void addUser(){
	bool more = true;
	string name, pw;
	char check;
	while(more){
		cout << endl << "< ����� �߰� >" << endl;
		cout << "����ڸ� : ";
		getline(cin, name);
		cout << "��й�ȣ : ";
		getline(cin, pw); 
		User u(name,pw);
		user.push_back(u);
		cout << "����� �߰��� �Ϸ�Ǿ����ϴ�." << endl; 
		cout << "����� �߰��� ��� �ұ��?(y/n) : ";
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
		cout << "������ ������̹Ƿ� ������ �� �����ϴ�." << endl;
		return;	
	}
	cout << endl << "< ����� ���� >" << endl;
	cout << "����ڸ� : ";
	getline(cin,name);
	for(int i = 0;i<user.size();i++){
		if(u->getName() == user[i].getName()){
			index = i;
		}
	}
	if(name == u->getName()){
		cout << "����� ��й�ȣ : " ;
		getline(cin,pw);
		if(pw == u->getPW()){
			cout << "������ �����ϰڽ��ϱ�?(y/n) : ";
			cin >> check;
			cin.ignore();
			if(check == 'y'){
				user.erase(user.begin() + index);
				User::num--;
				cout << "����� ������ �Ϸ�Ǿ����ϴ�." << endl;
				do{
					cout << "������ ����� ��й�ȣ : ";
					cin >> masterPW;
					cin.ignore();
					if(masterPW!=user[1].getPW()){
						cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
					}
				}while(masterPW!=user[1].getPW());
				menu(&user[1]); 
			}
		}else{
			cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
			return; 
		} 
	}else{
		cout << "����� ������ �ƴմϴ�." << endl; 
	}
}

int isUser(){
	string name, pw;
	int i;
	cout << endl << "< ����� Ȯ�� >" << endl;
	cout << "����ڸ� : ";
	getline(cin, name);
	for(i = 0;i<user.size();i++){
		if(name == user[i].getName()){
			cout << "����� ��й�ȣ : "; 
			getline(cin, pw);
			while(pw != user[i].getPW()){
				cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl << "����� ��й�ȣ : ";
				getline(cin, pw);
			}
			return i; 
		}
	}
	if(i == user.size()){
		cout << "����ڰ� �ƴմϴ�." << endl;
		return -1;
	}
	
}

int changeUser(){
	string name,pw;
	int i;
	cout << "������ ����ڸ� : ";
	getline(cin,name);
	for(i = 0;i<user.size();i++){
		if(name == user[i].getName()){
			cout << "����� ��й�ȣ : ";
			getline(cin,pw);
			while(pw != user[i].getPW()){
				cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl << "����� ��й�ȣ : ";
				getline(cin,pw);
			}
			return i; 
		}
	}
	if(i == user.size()){
		cout << "����ڰ� �ƴմϴ�." << endl;
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
	cout << "��й�ȣ ���� : ";
	cin >> pwLen;
	char pw[pwLen+1];
	cout << "�빮�ڸ� ����ϰڽ��ϱ�?(y/n) : ";
	cin >> check;
	if(check == 'y'){
		upper = true;
	}
	cout << "Ư�����ڸ� ����ϰڽ��ϱ�?(y/n) : ";
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
	cout << "������ ��й�ȣ : " << password << endl;
}

void menu(User* u){
	int n = 0, check;
	while(n != 9){
		cout << endl;
		cout << "����� : " << u->getName() << endl;
		cout << "---------- �޴� ---------- " << endl;
		cout << "1. ���� �߰�" << endl << "2. ���� ����" << endl << "3. ���� ����" << endl << "4. ���� ��ȸ" << endl << "5. ��й�ȣ ����" << endl 
			 << "6. ����� ����" << endl << "7. ����� �߰�" << endl << "8. ����� ����" << endl << "9. ����" << endl;
		cin >> n;
		cin.ignore();
		switch(n){
		case 1:
			cout << endl << "< ���� �߰� >" << endl;
			u->add();
			break;
		case 2:
			cout << endl << "< ���� ���� >" << endl; 
			u->del();
			break;
		case 3:
			cout << endl << "< ���� ���� >" << endl;
			u->change();
			break;
		case 4:
			cout << endl << "< ���� ��ȸ >" << endl; 
			u->find();
			break;
		case 5:
			cout << endl << "< ��й�ȣ ���� >" << endl;
			makePW();
			break;
		case 6:
			cout << endl << "< ����� ���� >" << endl; 
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
			cout << endl << "< ���� >" << endl;
			cout << "�̿����ּż� �����մϴ�." << endl;
			Sleep(3000);
			exit(0);
		default:
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
			break;
		}
	}
	
}

void start(){
	cout << "< ���� ���� �� ��й�ȣ ���� ���α׷� >" << endl;
	cout << "�ȳ��ϼ���! ���� ���� �� ��й�ȣ ���� ���α׷��Դϴ�." << endl << "���� ����ڸ� �߰����ּ���." << endl;
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
	cout << "�߰��� ������ ����Ʈ�� : ";
	getline(cin, site);
	cout << "�߰��� ������ ���̵� : ";
	getline(cin, id);
	cout << "�߰��� ������ ��й�ȣ : ";
	getline(cin, pw);
	Account a(site,id,pw);
	account.push_back(a);
	cout << "�߰��� �Ϸ�Ǿ����ϴ�." << endl;
 	actNum++;
}

void User::del(){
	string site;
	char check;
	vector<Account*> a;
	vector<int> index;
	int n;
	if(account.size() == 0){
		cout << "������ ������ �������� �ʽ��ϴ�." << endl;
		return;	
	} 
	cout << "������ ������ ����Ʈ�� : ";
	getline(cin, site);
	for(int i = 0;i<account.size();i++){
		if(site == account[i].getSite()){
			a.push_back(&account[i]);
			index.push_back(i);
		}
	}
	if(a.size() == 0){
		cout << "���Ͻô� ������ �������� �ʽ��ϴ�." << endl;
		return;
	} 

	if(a.size() == 1){
		n = 1;
	}else{
		for(int i = 0;i<a.size();i++){
			cout << i+1 << ". "<< a[i]->getSite() << " : " << a[i]->getID() << endl;
		}		
		cout << "�� ��° ������ �����ϰڽ��ϱ�? ";
		cin >> n; 		
	}

	for(int i = 0;i<a.size();i++){
		if(i == n-1){
			cout << "������ �����ϰڽ��ϱ�?(y/n) : ";
			cin >> check;
			cin.ignore(); 
			if(check == 'y'){
				account.erase(account.begin()+index[n-1]);
				actNum--;
			}else{
				return;
			}	
			cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
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
		cout << "������ ������ �������� �ʽ��ϴ�." << endl;
		return;	
	} 
	cout << "������ ������ ����Ʈ�� : ";
	getline(cin, site); 
	for(int i = 0;i<account.size();i++){
		if(site == account[i].getSite()){
			a.push_back(&account[i]);
		}
	}
	if(a.size() == 0){
		cout << "���Ͻô� ������ �������� �ʽ��ϴ�." << endl;
		return; 
	}
	if(a.size() == 1){
		n = 1;
	}else{
		for(int i = 0;i<a.size();i++){
			cout << i+1 << ". "<< a[i]->getSite() << " : " << a[i]->getID() << endl;
		}
		cout << "�� ��° ������ �����ϰڽ��ϱ�? ";
		cin >> n;		
	}
	
	for(int i = 0;i<a.size();i++){
		if(i==n-1){ 
			cout << site << "�� ���̵� �����ϰڽ��ϱ�?(y/n) : ";
			cin >> check;
			if(check == 'y'){
				cin.ignore();
				cout << "������ ���̵� : ";
				getline(cin, id);
				a[i]->setID(id); 
			}
			cout << site << "�� ��й�ȣ �����ϰڽ��ϱ�?(y/n) : ";
			cin >> check;
			cin.ignore();
			if(check == 'y'){
				cout << "������ ��й�ȣ : "; 
				getline(cin, pw);
				a[i]->setPW(pw);
			}
			cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
			return;
		}
	}
	
}

void User::find(){
	bool check = false;
	int n;
	string site,id;
	
	if(account.size() == 0){
		cout << "��ȸ�� ������ �������� �ʽ��ϴ�." << endl;
		return;	
	}else{
		cout << "1. ����Ʈ������ ��ȸ" << "	2.���̵�� ��ȸ" << endl;
		cin >> n;
		cin.ignore();
		switch(n){
			case 1:
				cout << "��ȸ�� ������ ����Ʈ�� : ";
				getline(cin,site);
				for(int i = 0;i<account.size();i++){
					if(site == account[i].getSite()){
						cout << "���̵� : " << account[i].getID() << "	��й�ȣ : " << account[i].getPW() << endl;
						check = true;
					}
				}
				break;

			case 2:
				cout << "��ȸ�� ������ ���̵� : ";
				getline(cin,id);
				for(int i = 0;i<account.size();i++){
					if(id == account[i].getID()){
						cout << "����Ʈ : " << account[i].getSite() << "	��й�ȣ : " << account[i].getPW() << endl;
						check = true;
					}
				} 
				break;
			default:
				cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
				return;
		}
		if(!check){
			cout << "���Ͻô� ������ �������� �ʽ��ϴ�." << endl;
		}	
	}
	
}

