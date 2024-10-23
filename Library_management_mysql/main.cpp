#include<bits/stdc++.h>
#include<mysql.h> 
#include<mysqld_error.h>
#include<windows.h>
#include<sstream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "root";
const char* DB = "mydb";

class Student{

private:
	string Id;
	
public:
	Student(){
		Id = "";
	}
	void setId(string id){
		Id = id;
	}
	string getId(){
		return Id;
	}
};


class Library{

private:
	string Name;
	int Quantity;
	
public:
	Library(){
		Name = "";
		Quantity = 0;
	}
	
	void setName(string name){
		Name = name;
	}
	void setQuantity(int quantity){
		Quantity = quantity;
	}
	
	string getName(){
		return Name;
	}
	int getQuantity(){
		return Quantity;
	}
};


void display(MYSQL* conn){
	
	system("cls");
	string disp = "SELECT * FROM lib";
	cout << "Available Books" << endl;
	cout << "***************" << endl;
	
	if(mysql_query(conn,disp.c_str())){
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else{
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		if(res){
			int num = mysql_num_fields(res);
			MYSQL_ROW row;
			while(row = mysql_fetch_row(res)){
				for(int i = 0;i<num;i++){
					cout << " " << row[i];
				}
				cout << endl;
			}
			mysql_free_result(res);
		}
		
		
	}
}

int book(MYSQL* conn,string Bname){
	
	string exist = "SELECT Name,Quantity from lib WHERE Name='"+Bname+"'";
	
	if(mysql_query(conn,exist.c_str())){
		cout << "Error: " << mysql_error(conn) << endl;
	}
	
	else{
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		
		if(res){
			MYSQL_ROW row;
			while(row=mysql_fetch_row(res)){
				if(row[0] == Bname){
					int quantity = atoi(row[1]);
					mysql_free_result(res);	
					
					return quantity;
				}
				else{
					cout << "Book Not Found." << endl;
				}
				
			}
			mysql_free_result(res);	
		}
			
	}
	return 0;
	Sleep(3000);
}



void admin(MYSQL* conn,Library l,Student s){
	
	bool closed = false;
	while(!closed){
		int choice;
		cout << "1. Add Book." << endl;
		cout << "2. Add Student." << endl;
		cout << "3. Exit." << endl;
		cout << "Enter Choice: " << endl;
		cin >> choice;
		
		if(choice == 1){
			system("cls");
			string name;
			int quantity;
			
			cout << " Enter Book Name: ";
			cin >> name;
			
			cout << "Enter Quantity: ";
			cin >> quantity;
			
			l.setName(name);
			l.setQuantity(quantity);
			
			int qt = l.getQuantity();
			stringstream ss;
			ss<<qt;
			
			string st = ss.str();
			
			string book = "INSERT INTO lib (Name,Quantity) VALUES('"+l.getName()+"', '"+st+"') ";
			
			if(mysql_query(conn,book.c_str())){
				cout << "Error: " << mysql_error(conn) << endl;
			}
			else{
				cout << "Book Inserted Successfully" << endl;
			}
			
		}
		
		else if(choice == 2){
			system("cls");
			string id;
			cout << "Enter Student Id:";
			cin >> id;
			s.setId(id);
			
			string stu = "INSERT INTO student (Id) VALUES('"+s.getId()+"')";
			
			if(mysql_query(conn,stu.c_str())){
				cout << "Error: " << mysql_error(conn) << endl;
			}
			else{
				cout << "Student Registered successfully" << endl;
			}
			
		}
		else if(choice == 3){
			closed = true;
			cout << "Admin is closing" << endl;
			
		}
	
		
	}
	Sleep(3000);
	
}


void user(MYSQL* conn, Library l, Student s){
	
	system("cls");
	display(conn);
	Sleep(3000);
	
	string S_id;
	cout << "Enter Your Id:";
	cin >> S_id;
	
	string query = "SELECT * FROM student WHERE Id = '"+S_id+"'";
	if(mysql_query(conn,query.c_str())){
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else{
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		if(res){
			int num = mysql_num_rows(res);
			if(num == 1){
				cout << "Student ID Found" << endl;
				cout << "Enter Book Name to borrow: ";
				string Bname;
				cin >> Bname;
				if(book(conn,Bname) > 0){
					int curQuantity = book(conn,Bname)-1;
					stringstream ss;
					ss<<curQuantity;
					string qty = ss.str();
					
					string upd = "UPDATE lib SET Quantity = '"+qty+"' WHERE Name = '"+Bname+"'";
					
					if(mysql_query(conn,upd.c_str())){
						cout << "Error: " << mysql_error(conn) << endl;
					}
					else{
						cout << "Book is available. Borrowing Book";
					}
					
				}
				else{
					cout << "Book is not available" << endl;
				}
			}
			else if(num == 0){
				cout << "Student is not registered" << endl;
			}
			mysql_free_result(res);
		}

	}
	
}






int main() {
	
	Student s;
	Library l;
	
	MYSQL* conn;
	conn = mysql_init(NULL);
	
	if(!mysql_real_connect(conn,HOST,USER,PW,DB,3306,NULL,0)){
		
		cout << "Error " << mysql_error(conn) << endl;
	}
	else{
		cout << "Logged In!" << endl;
	}
	Sleep(3000);
	
	bool exit = false;
	while(!exit){
//		system("cls");
		int val;
		cout << "Library Management System" << endl;
		cout << "*************************" << endl;
		cout << "1. Administration" << endl;
		cout << "2. User" << endl;
		cout << "3. Exit" << endl;
		cout << "Enter Choice: ";
		cin >> val;
		
		if(val == 1){
			system("cls");
			admin(conn,l,s);
		}
		else if(val == 2){
			system("cls");
			user(conn,l,s);
			
		}
		else if(val == 3){
			exit = true;
			cout << "Thank You!" << endl;
			Sleep(3000);
		}
		else{
			cout << "Enter a valid choice" << endl;
		}
		
	}
	mysql_close(conn);
	
	return 0;
}
