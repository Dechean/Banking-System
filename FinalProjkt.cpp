//1.

#include<fstream>
#include<iostream>
#include<string.h>
#include<iomanip> // manipulate the output of C++ program (setw,flags,setfill,setprecision)
using namespace std;
class BankAccount{ // generic class
	protected:
	char name[50]; int accNo, noDeposit,noWithdraw;  
	float balance,annualInterest,monthlysrvChrg; bool status;
	public:
		BankAccount(); //default constructor
	
		void virtual makeDeposit(float d);  // virtual functions
		void virtual makeWithdrawal(float w);
		void virtual calcInt(); 	// calculate interest 
		void virtual monthlyProc();  // monthlyProcess
		void showMthlyStatus();   // shows monthly statistics (mutator function)
};

BankAccount::BankAccount(){ // constructor
	balance =0.0; annualInterest=0.3; monthlysrvChrg=0.0;
	noDeposit=0; noWithdraw=0; status=false;
}


void BankAccount::makeDeposit(float d){
	balance = balance + d; //OR,  	balance += d;
	noDeposit++; // balance deposited so increase (noDeposit) variable
}

void BankAccount::makeWithdrawal(float w){
	balance = balance - w; // OR,	balance -= w;
	noWithdraw++; // withdrawal made so increase the (noWithdraw) variable
}

void BankAccount::calcInt(){
	float monthlyInterestRate=annualInterest/12;
	float monthlyInterest=balance * monthlyInterestRate;
	balance = balance + monthlyInterest;
	
	// check if the balance is above $25, then a/c is active
	if(balance>25.00){
		status=true; // a/c is active
	}
	else{
		cout <<"\nYour account is inactive...\n"; // status = false, a/c below $25
		return;
	}
}

void BankAccount::monthlyProc(){
	balance= balance - monthlysrvChrg; // subtracts monthly service charges from balance
	calcInt(); 	// calling calcInt() to get the new balance after adding monthly interest
	
}


void BankAccount::showMthlyStatus(){

	cout <<"\n";
	cout.setf(ios::left,ios::adjustfield);
	cout.width(15);
	cout <<name;
	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(16);
	cout <<accNo;
	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(14);
	cout <<noDeposit;
	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(15);
	cout <<noWithdraw;
	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(18);
	cout <<monthlysrvChrg;				

	cout.setf(ios::left,ios::adjustfield);
	cout.width(18);
	cout <<balance;
	
	cout <<"\n\n";
}





class Savings:public BankAccount{ // child class
	protected:
	bool status; // flag variable
	public:
		Savings():BankAccount(){} // dummy constructor
		void makeWithdrawal(float w); // function overriding
		void makeDeposit(float d); // deposit amt 
		void monthlyProc();  // monthlyProcess
		void setAccountInfo(); // set Account Information
		int returnId(); // returns the Client's Account Id
		int returnNoWithdraw(); // returns no. of withdrawal
		void getStatus(); // show status
		void showAllAcc(); // show all accounts in the file
		
};

void Savings::makeWithdrawal(float w){
	cout <<"\nStatus: "<<status;
	if(status==false){ //  a/c below $25
		cout <<"\nYour account is inactive....\n";
		return;
	}
	else if(w>balance){ //withdrawn amt greater than the a/c balance
		cout <<"\nPlease enter the amount less than the balance..\n";
	}
	else if(balance-w >0 && balance-w <25.00){
		cout <<"\nBalance is now below $25, your account will be deactivated.....\n";
		BankAccount::makeWithdrawal(w);
		status=false; //  a/c below $25
	}
	else{
		BankAccount::makeWithdrawal(w); // function overriding
	}
}


void Savings::makeDeposit(float d){
	if(balance <25 && balance + d >25){
		status=true;
		BankAccount::makeDeposit(d);
	}
	else if (balance >25){
		BankAccount::makeDeposit(d);
	}

} 

void Savings::getStatus(){ // to print the status of the account
	if(status==1){
		cout << "Active"<<"\n\n";
	}
	else{
		cout << "Inactive"<<"\n\n";
	}
}


int Savings::returnNoWithdraw(){
	return noWithdraw;
}


void Savings::monthlyProc(){ 
	
	if(noWithdraw>4){ // if no. of withdraw is greater than 4
		 
		// srv.charge $1 for each withdrawal above 4 
		monthlysrvChrg = monthlysrvChrg + 1.00 * (noWithdraw-4);
	
	// need to check the a/c balance after the srv.charge is taken 	 (active or inactive)
		if(balance-monthlysrvChrg <25.00){ // subtract service charges from account
		cout <<"\nBalance is now below $25, your account will be deactivated...\n";
		status=false; //  a/c below $25
		}	
	}
	
	BankAccount::monthlyProc();		// shows monthly Process
	BankAccount::showMthlyStatus();   // shows monthly statistics 
	noDeposit=0; noWithdraw=0; monthlysrvChrg=0.0;
}


void Savings::setAccountInfo(){
	cout <<"\nEnter the name of account holder: ";cin>>name;
	cout <<"\nEnter the Account ID: ";cin>>accNo;
	cout <<"\nEnter the balance: ";cin>>balance;
	if(balance>25.00){
		status=true; // a/c is active
	}
	else{
		cout <<"\nYour account is inactive...\n"; // status = false, a/c below $25
		return;
	}
	
}

void Savings::showAllAcc(){
		cout <<"\n\n";
	cout.setf(ios::left,ios::adjustfield);
	cout.width(15);
	cout <<name;
	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(16);
	cout <<accNo;
	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(15);
	cout <<balance<<"\n\n";
		
}

int Savings::returnId(){	// returns account ID
	return accNo;
}





class Checking:public BankAccount{		// child class 2
	public:
		Checking():BankAccount(){}
		void makeWithdrawal(float w); // 
		void makeDeposit(float d); 	void getStatus();
		void monthlyProc(); 	int getId();
		void setCheckingInfo(); void displayAccount();
};

void Checking::makeWithdrawal(float w){
	if(status==false){
		cout <<"\nYour account is inactive...";
		return;
	}
	else if(balance-w<0){ // balance below $0
		cout <<"\nPlease enter the amount less than the main balance...";
		monthlysrvChrg = monthlysrvChrg + 15.00; // service charge of $15 is added to account
		// withdrawal is not made
	}
	else if(balance-w>0 && balance-w<25){ // remaining balance after withdrawing is > 0, < 25
		cout <<"\nYour account is below $25, so it will be deactivated.....";
		BankAccount::makeWithdrawal(w);
		status=false; // balance below $25
	}
	else{
		BankAccount::makeWithdrawal(w);
	}	
}

void Checking::makeDeposit(float d){ // deposit amount
	if(balance + d > 25){
		status = true;
	}
	if(status==false){
		cout <<"\nYour account is inactive...";
		return;
	}
	BankAccount::makeDeposit(d);
}

void Checking::monthlyProc(){
	// adding monthly fee of $5 plus $0.10 per withdrawal to base class's monthlyservicecharge
	monthlysrvChrg = monthlysrvChrg + ( 5.00 + (noWithdraw * .10));
	BankAccount::monthlyProc(); 	// calling base class monthlyProc()
	BankAccount::showMthlyStatus();  // calling base class showMonthlyStatus()
	noWithdraw=0; noDeposit=0; monthlysrvChrg=0.0;
}

void Checking::setCheckingInfo(){
	cout <<"\nEnter the name of account holder: ";cin>>name;
	cout <<"\nEnter the Account ID: ";cin>>accNo;
	cout <<"\nEnter the balance: ";cin>>balance;
	if(balance>25.00){
		status=true; // a/c is active
	}
	else{
		cout <<"\nYour account is inactive...\n"; // status = false, a/c below $25
		return;
	}
}

int Checking::getId(){ // returns account ID
	return accNo;
}

void Checking::getStatus(){ // get status 
	if(status==1){
		cout << "Active"<<"\n\n";
	}
	else{
		cout << "Inactive"<<"\n\n";
	}
}


void Checking::displayAccount(){
	cout <<"\n\n";
	cout.setf(ios::left,ios::adjustfield);
	cout.width(15);
	cout <<name;
	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(16);
	cout <<accNo;
	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(15);
	cout <<balance<<"\n\n";
}





class AccountsManager{ 
	Savings sv;  Checking ck;		// composition
	public:
		// For savings
		void createAccount(); 	void deleteRecords();
		void noteDeposit(); 	void searchAccount();
		void noteWithdrawal();	void setAcInfo();
		void showAccDetails();	void showMnthStat();
			
			// For Checkings
		void openAccount();	 	void makeWithdraw();
		void makeDeposit();		void setCheckingInfo();
		void showAccount();		void searchRecords();
		void getMnthlyStat();	void deleteAccount(); 		
};

void AccountsManager::createAccount(){ // create a new file
	fstream file; string psw1,psw2;
	file.open("e:/pjt/pswd.dat",ios::in|ios::out|ios::binary);
	cout <<"\nEnter password: ";cin>>psw1;
	file>>psw2;
	if(psw1==psw2){
		cout <<"\nPassword matched!..You can create a file..";
		fstream file;
		file.open("e:/pjt/acc.txt",ios::out|ios::binary);
		file.close();
	}
	else{
		cout <<"\nSorry!! Nice Try...";
		exit(0);
	}
	file.close();
	system("pause");
}


void AccountsManager::setAcInfo(){ // to set the info of account holder
	fstream file; 
	file.open("e:/pjt/acc.txt",ios::ate|ios::in|ios::out|ios::binary);
	if(file.is_open()){
				sv.setAccountInfo(); 
				if(file.write((char*)&sv,sizeof(sv))){
					cout <<"\nSuccessfully wrote to file......\n";
				}
				else{
					cout <<"\nCouldn't write successfully to file....\n";
				}
			}
	else{
		cout <<"\nError in opening the file...";
	}
	file.close();
system("pause");
	
}


void AccountsManager::noteDeposit(){ // to make deposit into account

	fstream file; int Id;  float y; // y = amount to deposit
		char ch; 
		file.open("e:/pjt/acc.txt",ios::in|ios::out|ios::binary);
		file.seekg(0);   //rewind the file pointer
		cout <<"\nEnter the Account ID to Deposit: ";cin>>Id;
		cout <<"\nAre you sure that you wanna continue (y/n)? ";cin>>ch;
		if(ch=='y'||ch=='Y'){
			while(file.read((char*)&sv,sizeof(sv))){ // reading from file
			
				if(Id==sv.returnId()){
					sv.showAllAcc();	 // shows the found account
					cout <<"Enter the amount to deposit: ";cin>>y;
					
					if(file.is_open()){ // error handling
						//  tellg() = moves put pointer to the current position 
						int pos = file.tellg();
						int position = ( pos - sizeof(sv) );  
						file.seekp(position);
						
						
						sv.makeDeposit(y); // deposit function called
						if(file.write((char*)&sv,sizeof(sv))){
							cout <<"\nSuccessfully wrote to file......\n";
						}
						else{
								cout <<"\nCouldn't write successfully to file....\n";
						}
					}
					else{
						cout <<"\nError in opening the file...";
					}
				}
			}
		}
		else if(ch=='n'||ch=='N'){
			return;
		}
	file.close();
	system("pause");
}



void AccountsManager::noteWithdrawal(){ // to make withdrawal from account
	fstream file; 	int Id; float y;   // y = amount to withdraw
	char ch; 
		file.open("e:/pjt/acc.txt",ios::in|ios::out|ios::binary);
		file.seekg(0);   //rewind the file pointer
		cout <<"\nEnter the Account ID from which you wanna withdraw: ";cin>>Id;
		cout <<"\nAre you sure that you wanna continue (y/n)? ";cin>>ch;
		if(ch=='y'||ch=='Y'){
			while(file.read((char*)&sv,sizeof(sv))){
		
				if(Id==sv.returnId() ){ //check whether the account is in the file or not
					sv.showAllAcc();	 // shows the found account
					cout <<"Enter the amount to withdraw: ";cin>>y;
					
					if(file.is_open()){ // error handling
						//  tellg(0) = moves put pointer to the current position 
						int pos = file.tellg();
						int position = ( pos - sizeof(sv) );  
						file.seekp(position);
						
						sv.makeWithdrawal(y); // deposit function called
					
						if(file.write((char*)&sv,sizeof(sv))){
							cout <<"\nSuccessfully wrote to file......\n";
						}
						else{
								cout <<"\nCouldn't write successfully to file....\n";
						}
					}
					else{
						cout <<"\nError in opening the file...\n";
					}					
				}		
			}
		}
		else if(ch=='n'||ch=='N'){
			return;
		}
		
	file.close();	
	system("pause");
}

void AccountsManager::searchAccount(){ // search the records of account
	fstream file;
	file.open("e:/pjt/acc.txt",ios::ate|ios::in|ios::binary);
	file.seekg(0); int aId;
	cout <<"\nEnter the account Id to search: ";cin>>aId;
	while(file.read((char*)&sv,sizeof(sv))){
		if(sv.returnId()==aId){
			cout <<"\n------------Account Found-----------\n";
			cout.setf(ios::left,ios::adjustfield);
			cout.width(15);cout <<"Name";cout.setf(ios::left,ios::adjustfield);cout.width(15);
			cout <<"Account No.";cout.setf(ios::left,ios::adjustfield);cout.width(15);
			cout <<"Balance";
			
			sv.showAllAcc();
			cout <<"\nStatus: ";sv.getStatus();
		}
	
	}
	file.close();	
	system("pause");
}

void AccountsManager::deleteRecords(){ // delete a particular record 
	fstream file,dfile; 		// dfile - temporary file
	file.open("e:/pjt/acc.txt",ios::in|ios::binary); //reading the file
	dfile.open("e:/pjt/temp.txt",ios::out|ios::binary); //creating a temp file where we're gonna write
		if (file.fail()){ // error handling
			cout <<"\nError in opening the file";
		}
		else{
			int aId;char ch;
			cout <<"\nEnter the account Id to delete: ";cin>>aId;
			cout <<"\nAre you sure that you wanna continue (y/n)? ";cin>>ch;
			if(ch=='y'||ch=='Y'){
				while(file.read((char*)&sv,sizeof(sv))){
					if(sv.returnId()!=aId){ // if I wanna delete acc of Dan then write all those acc 
						dfile.write((char*)&sv,sizeof(sv));	// whose acc holder name is not Dan
					}
				}
			}
			else if(ch=='n'||ch=='N'){
				return;
			}
			
		}
	file.close();
	dfile.close();
	
	remove("e:/pjt/acc.txt");
	rename("e:/pjt/temp.txt","e:/pjt/acc.txt");
	
system("pause");
}


void AccountsManager::showAccDetails(){ // shows all the accounts in the file
	fstream file;  
			cout <<"\n\n----------------SAVINGS ACCOUNT-------------------\n\n";
			cout.setf(ios::left,ios::adjustfield);
			cout.width(15);
			cout <<"Name";
			
			cout.setf(ios::left,ios::adjustfield);
			cout.width(15);
			cout <<"Account No.";
			
			cout.setf(ios::left,ios::adjustfield);
			cout.width(15);
			cout <<"Balance";
			cout <<"\n---------------------------------------------------";
		
	file.open("e:/pjt/acc.txt",ios::in|ios::binary);
	if(file.is_open()){
	
		file.seekg(0); // rewind the file pointer
		while(file.read((char*)&sv,sizeof(sv))){
			sv.showAllAcc();
		}
	}
	file.close();
system("pause");

}



void AccountsManager::showMnthStat(){
	fstream file;
	cout <<"\n\n************************** SAVINGS ACCOUNT MONTHLY STATISTICS ******************************";
	cout <<"\n----------------------------------------------------------------------------------------------\n";
		
		//put this while reading the file
	cout.setf(ios::left,ios::adjustfield);
	cout.width(15);
	cout <<"Name";	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(15);
	cout <<"Account No.";	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(13);
	cout <<"Deposits";	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(15);
	cout <<"Withdrawals";	
	cout.setf(ios::left,ios::adjustfield);
	cout.width(18);
	cout <<"Service Charges";				
	cout.setf(ios::left,ios::adjustfield);
	cout.width(18);
	cout <<"Ending Balance";
	cout <<"\n----------------------------------------------------------------------------------------------";
	
	file.open("e:/pjt/acc.txt",ios::in|ios::out|ios::binary);
	if(file.is_open()){
		file.seekg(0); // rewind the file pointer
		while(file.read((char*)&sv,sizeof(sv))){
				int pos = file.tellg(); // tells the current position
				int position = pos - sizeof(sv); // it's been read so move back one pointer
				file.seekp(position); // move put pointer to current position
				sv.monthlyProc();  // calling monthlyProc to write the updated balance to file
				file.write((char*)&sv,sizeof(sv));		
		}
	}

	file.close();
	system("pause");
}



// For Checkings
void AccountsManager::openAccount(){ // creating a new file
	fstream file; string psw1,psw2;
	file.open("e:/pjt/chkPswd.dat",ios::in|ios::out|ios::binary);

	if(file.fail()){ // error handling
		cout <<"\nCouldn't create a file..";
	}
	else{
		cout <<"\nEnter a password: ";cin>>psw1;
		file>>psw2; // reading the data from file
		if(psw1==psw2){
			cout <<"\nPassword matched..You can now create a file..";
			fstream file;
			file.open("e:/pjt/chk.txt",ios::out|ios::binary); // creating a file chk.txt
			file.close();
		}
		else{
			cout <<"\nSorry! Nice Try...";
			exit(0);
		}
	}
	file.close();
system("pause");
}

void AccountsManager::setCheckingInfo(){ // set the checking account info
	fstream file; 
	file.open("e:/pjt/chk.txt",ios::ate|ios::in|ios::out|ios::binary);
	if(file.is_open()){
		ck.setCheckingInfo(); 
			if(file.write((char*)&ck,sizeof(ck))){
					cout <<"\nSuccessfully wrote to file......\n";
			}
			else{
				cout <<"\nCouldn't write successfully to file....\n";
			}
	}
	else{
		cout <<"\nError in opening the file...";
	}
	file.close();
system("pause");
}

void AccountsManager::makeWithdraw(){
	fstream file; 	int Id; float y;   // y = amount to withdraw
	char ch;
	file.open("e:/pjt/chk.txt",ios::in|ios::out|ios::binary);
	file.seekg(0);   //rewind the file pointer
	cout <<"\nEnter the Account ID from which you wanna withdraw: ";cin>>Id;
	cout <<"\nAre you sure that you wanna continue (y/n)? ";cin>>ch;
	if(ch=='y'||ch=='Y'){	
		while(file.read((char*)&ck,sizeof(ck))){
	
			if(Id==ck.getId()){ //check whether the account is in the file or not
				ck.displayAccount();	 // shows the found account
				cout <<"Enter the amount to withdraw: ";cin>>y;
				
				if(file.is_open()){ // error handling
					//  tellg() = moves put pointer to the current position 
					int pos = file.tellg();
					int position = ( pos - sizeof(ck) );  
					file.seekp(position);
					
					ck.makeWithdrawal(y); // deposit function called
				
					if(file.write((char*)&ck,sizeof(ck))){
						cout <<"\nSuccessfully wrote to file......\n";
					}
					else{
						cout <<"\nCouldn't write successfully to file....\n";
					}
				}
				else{
					cout <<"\nError in opening the file...\n";
				}
				
			}		
		}
	}
	else if(ch=='n'||ch=='N'){
		return;
	}
	file.close();	
	system("pause");
}

void AccountsManager::makeDeposit(){
	fstream file; int Id;  float y; // y = amount to deposit
	char ch;
	file.open("e:/pjt/chk.txt",ios::in|ios::out|ios::binary);
	file.seekg(0);   //rewind the file pointer
	cout <<"\nEnter the Account ID to Deposit: ";cin>>Id;
	cout <<"\nAre you sure that you wanna continue (y/n)? ";cin>>ch;
	if(ch=='y'||ch=='Y'){
		while(file.read((char*)&ck,sizeof(ck))){ // reading from file
		
			if(Id==ck.getId()){
				ck.displayAccount();	 // shows the found account
				cout <<"Enter the amount to deposit: ";cin>>y;
				
				if(file.is_open()){ // error handling
					//  tellg() = moves put pointer to the current position 
					int pos = file.tellg();
					int position = ( pos - sizeof(ck) );  
					file.seekp(position);
					
					ck.makeDeposit(y); // deposit function called
					if(file.write((char*)&ck,sizeof(ck))){
						cout <<"\nSuccessfully wrote to file......\n";
					}
					else{
							cout <<"\nCouldn't write successfully to file....\n";
					}
				}
				else{
					cout <<"\nError in opening the file...";
				}
			}
		}
	}
	else if(ch=='n'||ch=='N'){
		return;
	}
	file.close();
	system("pause");
}	

void AccountsManager::searchRecords(){ // search the account  
	fstream file;
	file.open("e:/pjt/chk.txt",ios::ate|ios::in|ios::binary);
	file.seekg(0); int aId;
	cout <<"\nEnter the account Id to search: ";cin>>aId;
		while(file.read((char*)&ck,sizeof(ck))){
			if(ck.getId()==aId){
				cout <<"\n------------Account Found-----------\n";
				cout.setf(ios::left,ios::adjustfield);
				cout.width(15);cout <<"Name";cout.setf(ios::left,ios::adjustfield);cout.width(15);
				cout <<"Account No.";cout.setf(ios::left,ios::adjustfield);cout.width(15);
				cout <<"Balance";
				
				ck.displayAccount();
				cout <<"\nStatus: ";ck.getStatus();
			}
		
		}
	file.close();	
system("pause");
}

void AccountsManager::deleteAccount(){ // delete a particular record
	fstream file,dfile; 
	file.open("e:/pjt/chk.txt",ios::in|ios::binary); //reading the file
	dfile.open("e:/pjt/temp.txt",ios::out|ios::binary); //creating a temp file where we're gonna write
		if (file.fail()){ // error handling
			cout <<"\nError in opening the file";
		}
		else{
			int aId;char ch;
			cout <<"\nEnter the account Id to delete: ";cin>>aId;
			cout <<"\nAre you sure that you wanna continue (y/n)? ";cin>>ch;
			if(ch=='y'||ch=='Y'){
				while(file.read((char*)&ck,sizeof(ck))){
					if(ck.getId()!=aId){ // if I wanna delete acc of Dan then write all those acc 
						dfile.write((char*)&ck,sizeof(ck));	// whose acc holder name is not Dan
					}
				}
			}
			else if(ch=='n'||ch=='N'){
				return;
			}
		}
	file.close();
	dfile.close();
	
	remove("e:/pjt/chk.txt");
	rename("e:/pjt/temp.txt","e:/pjt/chk.txt");
	
	system("pause");
} 



void AccountsManager::showAccount(){
	fstream file;  
			cout <<"\n\n----------------CHECKINGS ACCOUNT-------------------\n\n";
			cout.setf(ios::left,ios::adjustfield);
			cout.width(15);
			cout <<"Name";
			
			cout.setf(ios::left,ios::adjustfield);
			cout.width(15);
			cout <<"Account No.";
			
			cout.setf(ios::left,ios::adjustfield);
			cout.width(15);
			cout <<"Balance";
			cout <<"\n---------------------------------------------------";
		
	file.open("e:/pjt/chk.txt",ios::in|ios::binary);
	if(file.is_open()){
	
		file.seekg(0); // rewind the file pointer
		while(file.read((char*)&ck,sizeof(ck))){
			ck.displayAccount();
		}
	}
	file.close();
system("pause");
}	
	
void AccountsManager::getMnthlyStat(){
	fstream file;
		cout <<"\n\n************************** CHECKINGS ACCOUNT MONTHLY STATISTICS ******************************";
		cout <<"\n----------------------------------------------------------------------------------------------\n";
			
			//put this while reading the file
		cout.setf(ios::left,ios::adjustfield);
		cout.width(15);
		cout <<"Name";
		
		cout.setf(ios::left,ios::adjustfield);
		cout.width(15);
		cout <<"Account No.";
		
		cout.setf(ios::left,ios::adjustfield);
		cout.width(13);
		cout <<"Deposits";
		
		cout.setf(ios::left,ios::adjustfield);
		cout.width(15);
		cout <<"Withdrawals";
		
		cout.setf(ios::left,ios::adjustfield);
		cout.width(18);
		cout <<"Service Charges";				
	
		cout.setf(ios::left,ios::adjustfield);
		cout.width(18);
		cout <<"Ending Balance";
		cout <<"\n----------------------------------------------------------------------------------------------";
	
	file.open("e:/pjt/chk.txt",ios::in|ios::out|ios::binary);
		if(file.is_open()){
		
			file.seekg(0); // rewind the file pointer
			while(file.read((char*)&ck,sizeof(ck))){
					int pos = file.tellg();
					int position = pos - sizeof(sv);
					file.seekp(position);
					ck.monthlyProc();  // calling monthlyProc to write the updated balance to file
					file.write((char*)&ck,sizeof(ck));			
			}
		}

	file.close();
	system("pause");
}	


int main()
{
	AccountsManager am; int ch;
	while(1){
		system("cls");
		cout <<"\n1. Savings";
		cout <<"\n2. Checkings";
		cout <<"\n3. Exit";
		cout <<"\nEnter your choice: ";cin>>ch;
		switch(ch){
			case 1:
				while(1){
					system("cls");
						cout <<"\nSAVINGS ACCOUNT..\n";
						cout <<"\n1. Open Account";
						cout <<"\n2. Add Account Info";
						cout <<"\n3. Make Deposits";
						cout <<"\n4. Withdraw Amount";
						cout <<"\n5. Show Account Details";
						cout <<"\n6. Delete Records";
						cout <<"\n7. Search Account";
						cout <<"\n8. Show Monthly Statistics";
						cout <<"\n9. Exit";
						cout <<"\nEnter your choice: ";cin>>ch;
							if(ch==1){
								am.createAccount();
							}
							else if(ch==2){
								am.setAcInfo();
							}
							else if(ch==3){
								am.noteDeposit();
							}
							else if(ch==4){
								am.noteWithdrawal();
							}
							else if(ch==5){
								am.showAccDetails();
							}
							else if(ch==6){
								am.deleteRecords();
							}
							else if(ch==7){
								am.searchAccount();
							}
							else if(ch==8){
								am.showMnthStat();
							}			
							else if(ch==9){
								break;
							}								
				}
			system("pause");
			break;
			
			case 2:
				while(1){
					system("cls");
						cout <<"\nCHECKINGS ACCOUNT..\n";
						cout <<"\n1. Open Account";
						cout <<"\n2. Add Account Info";
						cout <<"\n3. Make Deposits";
						cout <<"\n4. Withdraw Amount";
						cout <<"\n5. Show Account Details";
						cout <<"\n6. Delete Records";
						cout <<"\n7. Search Account";
						cout <<"\n8. Show Monthly Statistics";
						cout <<"\n9. Exit";						
						cout <<"\n\nEnter your choice: ";cin>>ch;
							if(ch==1){
								am.openAccount();		 	 			 
							}
							else if(ch==2){
								am.setCheckingInfo();
							}
							else if(ch==3){
								am.makeDeposit();
							}
							else if(ch==4){
								am.makeWithdraw();
							}
							else if(ch==5){
								am.showAccount();
							}
							else if(ch==6){
								am.deleteAccount(); 
							}
							else if(ch==7){
								am.searchRecords();
							}
							else if(ch==8){
								am.getMnthlyStat();
							}
							
							else if(ch==9){
								break;
							}
					
				}
			system("pause");
			break;
			
			case 3:
				exit(0);
			break;
		
		}
			
	}

}



