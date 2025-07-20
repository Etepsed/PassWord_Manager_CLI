#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <cstdlib>
#include "include/nlohmann/json.hpp"
#include <random>
#include <unistd.h>

int PASSWORD_LEGTH = 30;

using namespace std;
using json = nlohmann::json;
namespace fs = filesystem;


// def functions
void page_one(string UserName,const json& User_Data);
void page_two(vector<string> sites,int choice, const json& User_Data, string UserName);
void page_home(string UserName,const json& User_Data);
void page_tree(vector<string> accouts,vector<string> sites,int choice, const json& User_Data, string UserName, const json& All_data, int Selected_site);
void page_add_site(string UserName, const json& User_Data);
void new_site(string UserName, const json& User_Data);
void add_account(string UserName, const json& User_Data,string site);
void page_del(string UserName, const json& User_Data);
void account_del(string UserName, const json& User_Data);
void rm_account(string UserName, const json& User_Data, string site);
string gen_password();
//main function
int main(int argc, char *argv[]){

	string UserName, Password, FileName;

	if(argc != 3){
		cout << "use: " << argv[0] << "<UserName> <Password>";
			return 0;
	}

	UserName = argv[1];
	Password = argv[2];
	FileName = UserName + ".json";
	// if the user file don't exist , will create one.
	if(!fs::exists(FileName)){
		ofstream User_File(FileName);
		json New_Data;
		User_File << New_Data.dump(4);
		User_File.close();
	}	
        
	// load data user of file;
	json User_Data;
	ifstream File_User(FileName);
	File_User >> User_Data;
	File_User.close();

	// page 1 
	page_home(UserName,User_Data);	
	
	return 0;
}

void page_home(string UserName,const json& User_Data){
	system("clear");
	int choice;
	cout << "hello, " << UserName << endl;
	cout << "password manager:" << endl;
	cout << " [" << 1 << "] " << "show passwords" << endl; 
	cout << " [" << 2 << "] " << "add password" << endl;
	cout << " [" << 3 << "] " << "del account" << endl;
	cout << " [" << 4 << "] " << "del site" << endl;
	cout << endl << "[" << 0 << "] " << "exit" << endl;
	cout << "/>: ";
	cin >> choice;
	switch(choice){
		case 1:
			page_one(UserName,User_Data);
			break;
		case 2: 
			page_add_site(UserName,User_Data);
			break;
		case 3:
			account_del(UserName,User_Data);
			break;
		case 4:
			page_del(UserName,User_Data);
			break;
		case 0:
			return;
		default:
			page_home(UserName,User_Data);
			break;
	}
	return;
}

void account_del(string UserName, const json& User_Data){
	system("clear");
	int choice;
	int i = 1;
	vector<string> sites;

	cout << "delete account"<< endl;
	cout << "choose a site: "<< endl;
	for(const auto& [site,_] : User_Data.items()){
		cout << " [" << i << "] " << site << endl;
		sites.push_back(site);
		i++;
	}

	cout << endl << "[0] back" << endl;
		cout << "/>: ";
	cin >> choice;

	if (choice == 0){
		page_home(UserName,User_Data);	
		return;	
	}

	if(choice < 0 || choice > i -1){
		page_del(UserName,User_Data);
	}
	
	string site = sites[choice-1];

	rm_account(UserName,User_Data,site);

}

void rm_account(string UserName, const json& User_Data, string site){
	system("clear");
	int choice;
	int i = 1;
	string choc;
	vector<string> accounts;
	cout << "delete account"<< endl;
	cout << "site: " << site << endl;
	cout << "choose a account: "<< endl;
	for(const auto& [account,_] : User_Data[site].items()){
		cout << " [" << i << "] " << account << endl;
		accounts.push_back(account);
		i++;
	}

	cout << endl << "[0] back" << endl;
		cout << "/>: ";
	cin >> choice;

	if (choice == 0){
		page_home(UserName,User_Data);	
		return;	
	}

	if(choice < 0 || choice > i -1){
		rm_account(UserName,User_Data,site);
		return;
	}


	while (choc != "1" && choc != "2") {
		system("clear");
		cout << "[ " <<  accounts[choice - 1] << " ]"<< endl;
		cout << "you want to delete this account?"<< endl;
		cout << " [1] yes \n [2] not "<< endl;	
		cout << "/>: ";
		cin >> choc;

	}
	
	if(choc == "1"){
		string FileName = UserName + ".json";
		json user_data = User_Data;

		user_data[site].erase(accounts[choice -1]);

		ofstream User_File(FileName);
		User_File << user_data.dump(4);
		User_File.close();
		rm_account(UserName,user_data,site);
	}else{
		rm_account(UserName,User_Data,site);
		return;
	}


}

void page_del(string UserName, const json& User_Data){
	string choc,site;
	int choice;
	system("clear");
	
	int i = 1;
	vector<string> sites;
	cout << "delete mode"<< endl;
	cout << "choose a site: "<< endl;
	for(const auto& [site,_] : User_Data.items()){
		cout << " [" << i << "] " << site << endl;
		sites.push_back(site);
		i++;
	}

	cout << endl << "[0] back" << endl;
		cout << "/>: ";
	cin >> choice;

	if (choice == 0){
		page_home(UserName,User_Data);	
		return;	
	}

	if(choice < 0 || choice > i -1){
		page_del(UserName,User_Data);
	}
	
	site = sites[choice-1];
	
	while (choc != "1" && choc != "2") {
		system("clear");
		cout << "site: [ "<< site <<" ]"<< endl;
		cout << "delete this site with all password storege?"<< endl;
		cout << " [1] yes \n [2] not "<< endl;	
		cout << "/>: ";
		cin >> choc;

	}
	
	if(choc == "1"){
		string FileName = UserName + ".json";
		json user_data = User_Data;

		user_data.erase(site);

		ofstream User_File(FileName);
		User_File << user_data.dump(4);
		User_File.close();
		page_del(UserName,user_data);
	}else{
		page_del(UserName,User_Data);
		return;
	}

}

void page_add_site(string UserName, const json& User_Data){
	
	system("clear");
	
	int i = 2;
	vector<string> sites;
	cout << "add password"<< endl;
	cout << "choose a site: "<< endl;
	cout << " [1] new site" << endl;
	for(const auto& [site,_] : User_Data.items()){
		cout << " [" << i << "] " << site << endl;
		sites.push_back(site);
		i++;
	}

	cout << endl << "[0] back" << endl;
	int choice;
	cout << "/>: ";
	cin >> choice;

	if (choice == 0){
		page_home(UserName,User_Data);	
		return;	
	}
	
	system("clear");
	
	if(choice == 1){
		new_site(UserName,User_Data);	
		return;
	}

	if(choice < 1 || choice > i - 1 ){
		page_one(UserName,User_Data);
		return;
	}
	// page for add password	
	add_account(UserName,User_Data,sites[choice -2]);
	return;
}

void new_site(string UserName, const json& User_Data){
	system("clear");
	string FileName = UserName + ".json";
	string site,choice;
	json user_data = User_Data;
	cout << "enter your [site] or [0] to back:"<< endl;
	cout << "/>: ";
	cin >> site;

	if(site == "0"){
		page_add_site(UserName,User_Data);
		return;
	}

	if(user_data.contains(site)){
		add_account(UserName,user_data,site);
		return;
	}

	system("clear");
	cout << "site: "<< site << endl;
	cout << "you want to add this site? " << endl;
	cout << " [1] yes " << " [2] not " << endl;
	cout << "/>: ";
	cin >> choice;
	
	if(choice == "1"){
		user_data[site] = {};
		ofstream User_File(FileName);
		User_File << user_data.dump(4);
		User_File.close();
		add_account(UserName,user_data,site);
		return;

	}else{
		new_site(UserName,User_Data);
	}


}

void add_account(string UserName, const json& User_Data,string site){
	system("clear");
	string FileName = UserName + ".json";
	string login,password, choice;
	json user_data = User_Data;
	cout << "site: "<< site << endl;
	cout << "enter your login: " << endl;
	cout << "login: ";
	cin >> login;
	while (choice != "1" && choice != "2") {
		system("clear");
		cout << "site: "<< site << endl;
		cout << " login: "<< login << endl;
		cout << "use automatic password generation?"<< endl;
		cout << " [1] yes ( recommended ) \n [2] not ( not recommended )"<< endl;	
		cout << "/>: ";
		cin >> choice;

	}
	bool auto_gen = false;
	if(choice =="2"){
		system("clear");
		cout << "site: "<< site  << endl;
		cout << " login: "<< login << endl;
		cout << "entrer your password:" << endl;
		cout << "password: ";
		cin >> password;

	}else if(choice == "1"){
		// gen a new password;
		password = gen_password();
		auto_gen = true;
	}
	choice = "";
	while( choice != "1" && choice != "2"){
		system("clear");
		cout << "site: "<< site  << endl;
		cout << " login: "<< login << endl;
		cout << " password: " << password << endl;
		cout << endl <<"is you data correct?"<< endl;
		cout << " [1] yes \n [2] not "<< endl;
		cout << " [3] edit login" << endl;
		cout << " [4] edit password" << endl;
		cout << " [5] back to home" << endl;
		if(auto_gen){
			cout << " [6] gen password" << endl;
		}
		cout << "/>: ";
		cin >> choice;

		if(choice == "3"){
			cout << "enter your login: " << endl;
			cout << "login: ";
			cin >> login;
		}

		if(choice == "4"){
			cout << "entrer your password:" << endl;
			cout << "password: ";
			cin >> password;

		}
		if (choice == "5") {
			page_home(UserName,User_Data);	
			return;
		}

		if(choice == "6" && auto_gen == true){
			password = gen_password();
		}
	}

	if(choice == "1"){
		user_data[site][login]["login"] = login;
		user_data[site][login]["password"] = password;
		ofstream User_File(FileName);
		User_File << user_data.dump(4);
		User_File.close();
		page_home(UserName,user_data);
		return;

	}else if ( choice == "2"){
		add_account(UserName,User_Data, site);
	}

}

void page_one(string UserName,const json& User_Data){

	system("clear");
	
	int i = 1;
	vector<string> sites;
	cout << "show password" << endl;
	cout << "chose a site: " << endl;
	for(const auto& [site,_] : User_Data.items()){
		cout << " [" << i << "] " << site << endl;
		sites.push_back(site);
		i++;
	}

	cout << endl << "[0] back" << endl;
	int choice;
	cout << "/>: ";
	cin >> choice;

	if (choice == 0){
		page_home(UserName,User_Data);	
		return;	
	}
	
	system("clear");

	if(choice < 0 || choice > i - 1 ){
		page_one(UserName,User_Data);
		return;
	}
	
	page_two(sites,choice,User_Data,UserName);
	return;
}

void page_two(vector<string> sites,int choice, const json& User_Data, string UserName){
	system("clear");
	vector<string> accouts;
	int i,Selected_site;

	Selected_site = choice -1;
	cout << "site: (" << sites[choice -1] << ")" << endl;
	cout << "accouts: "<< endl;
	i = 1;
	for(const auto&[accout,_] : User_Data[sites[choice - 1]].items()){
		cout << " [" << i << "] " << accout << endl;
		accouts.push_back(accout);
		i++;
	}
	cout << endl << "[" << 0 << "] " "back" << endl;

	cout << "/>: ";
	cin >> choice;

	if(choice == 0){
		page_one(UserName,User_Data);
		return;
	}

	if(choice < 0 || choice > i -1){	
		page_two(sites,Selected_site + 1,User_Data,UserName);
		return;
	}

	page_tree(accouts,sites,choice,User_Data[sites[Selected_site]],UserName,User_Data, Selected_site);
	return;
}

void page_tree(vector<string> accouts,vector<string> sites,int choice, const json& User_Data, string UserName, const json& All_data , int Selected_site){

	system("clear");
	vector<string> data;
	int i,j;
	j = choice;
	
	cout << "site: (" << sites[Selected_site] << ") "<<endl;
	cout << "accout: (" << accouts[choice -1] << ") "<<endl;
	cout << "login:" << endl;
	cout << " [ user/email ]: "<< User_Data[ accouts[choice -1] ]["login"].get<string>()<< endl;
	cout << " [  password  ]: "<< User_Data[ accouts[choice -1] ]["password"].get<string>()<< endl;
	
	cout << endl << "[" << 0 << "] " "back" << endl;

	cout << "/>: ";
	cin >> choice;

	if(choice == 0){
		page_two(sites,Selected_site + 1,All_data,UserName);
		return;
	}

	if(choice < 0 || choice > 0){	
		page_tree(accouts,sites,j,User_Data,UserName,All_data,Selected_site);
		return;
	}


	return;
}

string gen_password(){
	string password;
	string characters =
	"abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()-_=+[]{}|;:,.<>?";

	random_device rd;
	mt19937 gerador(rd());
	uniform_int_distribution <> dist(0, characters.size() - 1);
	
	for(int i = 0; i < PASSWORD_LEGTH; ++i){
		password += characters[dist(gerador)];
	}

	return password;
}
