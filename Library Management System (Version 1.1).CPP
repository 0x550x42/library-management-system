/*
Objective: This program is intended to be used as a library management system
Programmer: Udit Bhatnagar
Lang: C++98
*/

/*
Bugs:-
>> user might enter invalid date
>> register_member(); can't write to the file when it checks the pre-existing
member with the same code that the user is trying to register otherwise, it's perfect
>> user may register two members with same mcode
>> user may register two books with same bcode
*/

/*
Library rules:-
>> fine: Rs. 5/- per day after 7 days
>> a member can only issue 1 book for a period of 7 days
>> no identity check is done to validate the user
*/

/*
Notes and ideas:-
>> display a welcome message
>> while writing any file, first insert the data and then a new line
>> add int number_of_copies_issued; to bdetails
>> remove fine when the member returns the book
>> add an option at each step of the program to return to the menu
>> when a member returns the book, ask the user whether the fine was paid
or not and accordingly reset the issue_date
*/

#include<fstream.h>	//for handling files and I/O operations
#include<conio.h>   //for getch() and clrscr()
#include<stdio.h>	  //for gets and puts
#include<process.h>	//for exit()
#include<string.h>	//for string functions

//all global variables...
int cur_date[3];

//all functions' prototypes...
void issue_book(void);
void return_book(void);

void register_member(void);
void add_book(void);

void show_member(void);
void show_book(void);

void modify_member(void);
void modify_book(void);

void remove_member(void);
void remove_book(void);

int calc_fine(int *, int *);


//definitions of all classes...
class book
{
	public:
		char title[25], bcode[25], author[25], publisher[25];
		int copies;

		void accept()
		{
			cout<<"Enter book code: ";
			gets(bcode);
			cout<<"Enter book's title: ";
			gets(title);
			cout<<"Enter publisher's name: ";
			gets(publisher);
			cout<<"Enter author's name: ";
			gets(author);
			cout<<"Enter number of copies in stock: ";
			cin>>copies;

			return;
		}

		void display()
		{
			cout<<"Book's code: ";
			puts(bcode);
			cout<<"Book's title: ";
			puts(title);
			cout<<"Publisher: ";
			puts(publisher);
			cout<<"Author: ";
			puts(author);
			cout<<"Currently there are "<<copies<<" copies in stock...";

			return;
		}
}bdetails;

class member
{
	public:
		char mname[25], mcode[25], addr[25], gender;
		unsigned long int contact;
		int date_issued[3];
		
		void accept();

		void display()
		{
			cout<<"Member's code: ";
			puts(mcode);
			cout<<"Member's name: ";
			puts(mname);
			cout<<"Gender: ";
			if(gender == 'm' || gender == 'M')
			{
				cout<<"Male";
			}
			else
			{
				cout<<"Female";
			}
			cout<<"\nResidencial address: ";
			puts(addr);
			cout<<"Contact number: "<<contact;
			cout<<"\nFine imposed: ";
			if(date_issued[0]==0 && date_issued[1]==0 && date_issued[2]==0)
			{
				cout<<"Rs. 0/-";
			}
			else
			{
				cout<<"Rs. "<<calc_fine(date_issued, cur_date)<<"/-";
			}

			return;
		}
}mdetails, input;

void member::accept()
{
	char temp;

	cout<<"Enter member's code: ";
	gets(mcode);
	cout<<"Enter name: ";
	gets(mname);
	cout<<"Enter gender as (m or f): ";
	temp = getch();
	cout<<temp;

check:

	if(temp == 'm' || temp == 'M' || temp == 'f' || temp == 'F')
	{
		gender = temp;
	}

	else
	{
		cout<<"\nPlease choose either of m and f: ";
		temp = getch();
		cout<<temp;
		goto check;
	}

	cout<<"\nEnter residencial address: ";
	gets(addr);
	cout<<"Enter contact number: ";
	cin>>contact;

	return;
}


/***************************************************************************/

void main()
{
	clrscr();
	cout<<"Following are the rules that this library management system follows:-";
	cout<<"\n\n>> A member has to give required details on the time of registration.";
	cout<<"\n\n>> Any member can issue only 1 book for a period of 7 days (including weekends) ";
	cout<<"after which a fine of Rs. 5/day will be imposed.";
	cout<<"\n\nPress a key to continue with the program...";
	getch();

	clrscr();
	char choice;

menu:

	clrscr();
	cout<<"Menu:-\n";
	cout<<"a. Issue book\n";
	cout<<"b. Return book\n\n";

	cout<<"c. Register member\n";
	cout<<"d. Add a book to the stock\n\n";

	cout<<"e. Show details of a member\n";
	cout<<"f. Show details of a book\n\n";

	cout<<"g. Modify details of a member\n";
	cout<<"h. Modify details of a book\n\n";

	cout<<"i. Remove a member from the registry\n";
	cout<<"j. Remove a book from the stock\n\n";

	cout<<"k. Exit\n";
	cout<<"\nChoose: ";
	choice = getch();
	cout<<choice;

check:

	switch(choice)
	{
		case 'a':
			issue_book();
			goto menu;

		case 'b':
			return_book();
			goto menu;

		case 'c':
			register_member();
			goto menu;

		case 'd':
			add_book();
			goto menu;

		case 'e':
			show_member();
			goto menu;

		case 'f':
			show_book();
			goto menu;

		case 'g':
			modify_member();
			goto menu;

		case 'h':
			modify_book();
			goto menu;

		case 'i':
			remove_member();
			goto menu;

		case 'j':
			remove_book();
			goto menu;

		case 'k':
			exit(0);

		default:
			cout<<"\nInvalid input! Choose a letter corresponding to your choice: ";
			choice = getch();
			cout<<choice;

			goto check;
	}
}

/***************************************************************************/

//all functions' definitions...

void show_member()
{
	clrscr();

	char code[25], choice, handler;
	int flag=1;

	clrscr();

	fstream f;
	f.open("Members.dat", ios::in | ios::binary);

	do
	{
		clrscr();

		cout<<"Enter member's code: ";
		gets(code);

		f.seekg(0);

		do
		{
			f.read((char*) &mdetails, sizeof(mdetails));
			f.get(handler);

			if(strcmp(mdetails.mcode, code)==0)
			{
				flag=0;   //member found...
				clrscr();
				mdetails.display();
				break;
			}

		}while(f.eof()==0);

		if(flag)  //member not found...
		{
			cout<<"\nNo member found having this code...";
			cout<<"\nPls. check member's identification code again...";
		}

		else
		{
			flag=1;
		}

		cout<<"\n\nWant to see details of more members? (Y/N): ";
		choice = getch();
		cout<<choice;

check:

		if(choice == 'y' || choice=='Y')
			goto end;

		else if(choice=='n' || choice=='N')
			break;

		else
		{
			cout<<"\nInvalid input...";
			cout<<"Enter either Y or N: ";
			choice=getch();
			cout<<choice;
			goto check;
		}

end:

	}while(choice == 'y' || choice == 'Y');

	f.close();
	clrscr();
	return;
}

/***************************************************************************/

void show_book()
{
	clrscr();

	char code[25], choice, handler;
	int flag=1;

	fstream f;
	f.open("Books.dat", ios::in | ios::binary);

	do
	{
		clrscr();

		cout<<"Enter book's code: ";
		gets(code);

		f.seekg(0);

		do
		{
			f.read((char*) &bdetails, sizeof(bdetails));
			f.get(handler);

			if(strcmp(bdetails.bcode, code)==0)
			{
				flag=0;  //book found...
				clrscr();
				bdetails.display();
				break;
			}

		}while(f.eof()==0);

		if(flag!=0) //book not found...
		{
			cout<<"\nThis book is not in the stock...";
			cout<<"\nPls. check book's code again...";
		}

		else
		{
			flag=1;
		}

		cout<<"\n\nWant to see details of any other book? (Y/N): ";
		choice = getch();
		cout<<choice;

check:

		if(choice == 'y' || choice=='Y')
			goto end;

		else if(choice=='n' || choice=='N')
			break;

		else
		{
			cout<<"\nInvalid input...";
			cout<<"Enter either Y or N: ";
			choice=getch();
			cout<<choice;
			goto check;
		}
end:

	}while(choice == 'y' || choice == 'Y');

	f.close();
	clrscr();
	return;
}

/***************************************************************************/
/*
Solution to the bug: Before validating the mcode entered by the user, Check for the size of file to be
greater than 0 Bytes
*/
void register_member()
{
	clrscr();

	char choice, handler;
	int flag=1;
	unsigned long int counter=0;

	fstream f;
	f.open("Members.dat", ios::in | ios::out | ios::binary);

	do
	{
		clrscr();

		input.accept();
		
		f.seekg(0);

		do
		{
			f.get(handler);
			counter+=f.tellg();
			
		}while(f.eof()==0);
		
		cout<<"Counter: "<<counter;
		
		if(counter>0)
		{

check1:
			f.seekg(0);	//validating mcode

			do
			{
				f.read((char*) &mdetails, sizeof(mdetails));
				f.get(handler);

				if(strcmp(mdetails.mcode, input.mcode)==0)
				{
					flag=0;	//member already exists...
					break;
				}
			}while(f.eof()==0);

			if(flag==0)
			{
				flag=1;
				cout<<"\nOops! Seems a member is already registered with this code...";
				cout<<"\nYou may try a new one: ";
				gets(input.mcode);
				goto check1;	
			}

			else
			{
				f.write((char*) &input, sizeof(input));
				f<<'\n';
			}
		}
		
		else
		{
			f.write((char*) &input, sizeof(input));
			f<<'\n';
		}

		cout<<"\nWant to register more members? (Y/N): ";
		choice = getch();
		cout<<choice;

check2:

		if(choice == 'y' || choice=='Y')
			goto end;

		else if(choice=='n' || choice=='N')
			break;

		else
		{
			cout<<"\nInvalid input! Enter either Y or N: ";
			choice = getch();
			cout<<choice;
			goto check2;
		}

end:

	}while(choice == 'y' || choice == 'Y');

	f.close();
	return;
}

/***************************************************************************/

void remove_member()
{
	char code[25], choice, handler;
	int flag=1, flag_exe=0;

	fstream f_old, f_new;
	f_old.open("Members.dat", ios::in | ios::out | ios::binary);
	f_new.open("New.dat", ios::out | ios::binary);

	do
	{
		clrscr();

		cout<<"Enter member's code: ";
		gets(code);
		f_old.seekg(0);

		for(;f_old.eof()==0;)
		{
			flag_exe=1; //file operations were performed and new.dat was created

			f_old.read((char*) &mdetails, sizeof(mdetails));
			f_old.get(handler);

			if(strcmp(mdetails.mcode, code)!=0)
			{
				f_new.write((char*) &mdetails, sizeof(mdetails));
				f_new<<'\n';
			}

			else
			{
				flag=0;
			}

		}

		if(flag_exe)
		{
			flag_exe=0;
			remove("Members.dat");
			rename("New.dat", "Members.dat");
		}

		clrscr();

		if(flag)  //member not found...
		{
			cout<<"Sorry, This person is not a member...";
			cout<<"\nYou might have entered a wrong member code...";
		}

		else
		{
			flag=1; //reset flag to member not found
			cout<<"Member successfully removed...";
		}

		cout<<"\nWant to remove more members? (Y/N): ";
		choice=getch();
		cout<<choice;

check:

		if(choice == 'y' || choice=='Y')
			goto end;

		else if(choice=='n' || choice=='N')
			break;

		else
		{
			cout<<"\nInvalid input...";
			cout<<"Enter either Y or N: ";
			choice=getch();
			cout<<choice;
			goto check;
		}
end:

	}while(choice == 'y' || choice=='Y');

	f_old.close();
	f_new.close();

	clrscr();
	return;
}

/***************************************************************************/

void add_book()
{
	clrscr();

	char choice;

	fstream f;
	f.open("Books.dat", ios::out | ios::app | ios::ate | ios::binary);

	do
	{
		clrscr();

		bdetails.accept();

		f.write((char*) &bdetails, sizeof(bdetails));
		f<<'\n';

		cout<<"\nWant to add more books? (Y/N): ";
		choice = getch();
		cout<<choice;

check:

		if(choice == 'y' || choice=='Y')
			goto end;

		else if(choice=='n' || choice=='N')
			break;

		else
		{
			cout<<"\nInvalid input...";
			cout<<"Enter either Y or N: ";
			choice=getch();
			cout<<choice;
			goto check;
		}

end:

	}while(choice == 'y' || choice == 'Y');

	f.close();
	clrscr();
	return;
}

/**************************************************************************/

void remove_book()
{
	clrscr();

	char choice, code[25], handler;
	int flag=1;

	fstream f_old, f_new;
	f_old.open("Books.dat", ios::in | ios::binary);
	f_new.open("New.dat", ios::out | ios::binary);

	do
	{
		clrscr();

		cout<<"Enter code of book to be removed: ";
		gets(code);

		for(;f_old.eof()==0;)   //entry controlled loop...
		{
			f_old.read((char*) &bdetails, sizeof(bdetails));
			f_old.get(handler);

			if(strcmp(bdetails.bcode, code) != 0)
			{
				f_new.write((char*) &bdetails, sizeof(bdetails));
				f_new<<'\n';
			}

			else
			{
				flag=0;
			}
		}

		remove("Books.dat");
		rename("New.dat", "Books.dat");

		if(flag)
		{
			cout<<"Book not found in stock...";
		}

		else
		{
			flag=1;
			cout<<"Book successfully removed from the stock...";
		}

		cout<<"\nWant to remove more books from the stock? (Y/N): ";
		choice = getch();
		cout<<choice;

check:

		if(choice == 'y' || choice=='Y')
			goto end;

		else if(choice=='n' || choice=='N')
			break;

		else
		{
			cout<<"\nInvalid input...";
			cout<<"Enter either Y or N: ";
			choice=getch();
			cout<<choice;
			goto check;
		}
end:

	}while(choice == 'y' || choice == 'Y');

	f_old.close();
	f_new.close();

	clrscr();
	return;
}

/***************************************************************************/

void issue_book()
{
	clrscr();

	char choice, bcode[25], mcode[25], handler;
	long loc;
	int flagb, flagm;

	flagb = flagm = 0;

	cout<<"Enter today's date in the form dd mm yyyy: ";
	cin>>cur_date[0]>>cur_date[1]>>cur_date[2];

	fstream fb, fm;
	fb.open("Books.dat", ios::in | ios::out | ios::binary);
	fm.open("Members.dat", ios::in | ios::out | ios::binary);

	do
	{
		cout<<"Enter code of book to be issued: ";
		gets(bcode);
		
		check1:

		do  //validating bcode...
		{
			fb.read((char*) &bdetails, sizeof(bdetails));

			if(strcmp(bdetails.bcode, bcode)==0) //book found
			{
				break;  //book's details can now be modified
			}

			else
			{
				flagb=1; //book not found in stock
			}

		}while(fb.eof()==0);

		if(flagb==1)
		{
			flagb=0;
			cout<<"\nBook not found in stock...";
			cout<<"\nEnter a valid code: ";
			gets(bcode);
			goto check1;
		}

		cout<<"Enter member's code: ";
		gets(mcode);

check2:

		do  //validating mcode...
		{
			fm.read((char*) &mdetails, sizeof(mdetails));

			if(strcmp(mdetails.mcode, mcode)==0) //member found
			{
				break;  //member's details can now be modified
			}

			else
			{
				flagm=1;	//member not found
			}
			
		}while(fm.eof()==0);

		if(flagm==1)
		{
			flagm=0;
			cout<<"\nMember not found in registry...";
			cout<<"\nEnter a valid code: ";
			gets(bcode);
			goto check2;
		}

		fb.seekg(0);	//updating book's record in books.dat
		do  
		{
			loc = fb.tellg();

			fb.read((char*) &bdetails, sizeof(bdetails));
			fb.get(handler);

			if(strcmp(bdetails.bcode, bcode) == 0) //book found in stock file
			{
				bdetails.copies-=1;
				fb.seekg(loc);
				fb.write((char*) &bdetails, sizeof(bdetails));
				break;
			}

		}while(fb.eof()==0);
		
		cout<<"\nBook's details have been modified successfully!";

		fm.seekg(0);	//updating member's record in members.dat
		do   
		{
			loc=fm.tellp();

			fm.read((char*) &mdetails, sizeof(mdetails));
			fm.get(handler);

			if(strcmp(mdetails.mcode, mcode) == 0)
			{
				mdetails.date_issued[0] = cur_date[0];
				mdetails.date_issued[1] = cur_date[1];
				mdetails.date_issued[2] = cur_date[2];

				fm.seekg(loc);
				fm.write((char*) &mdetails, sizeof(mdetails));

				break;
			}

		}while(fm.eof()==0);
		
		cout<<"\nMember's details have been modified successfully!";

		cout<<"\n\nWant to issue more books? (Y/N): ";
		choice = getch();
		cout<<choice;

check:

		if(choice == 'y' || choice=='Y')
			goto end;

		else if(choice=='n' || choice=='N')
			break;

		else
		{
			cout<<"\nInvalid input...";
			cout<<"Enter either Y or N: ";
			choice = getch();
			cout<<choice;
			goto check;
		}

end:

	}while(choice == 'y' || choice == 'Y');

	fb.close();
	fm.close();

cfunc:

	return;
}

/***************************************************************************/

void return_book()
{
	clrscr();

	char bcode[25], mcode[25], choice;
	long loc;
	int flagb=0, flagm=0;

	cout<<"Enter today's date as dd mm yyyy: ";
	cin>>cur_date[0]>>cur_date[1]>>cur_date[2];

	fstream fb, fm;
	fb.open("Books.dat", ios::in | ios::out | ios::binary);
	fm.open("Members.dat", ios::in | ios::out | ios::binary);

	do
	{
		cout<<"Enter code of book to be returned: ";
		gets(bcode);

check1:

		do  //validating bcode...
		{
			fb.read((char*) &bdetails, sizeof(bdetails));

			if(strcmp(bdetails.bcode, bcode)==0) //book found
			{
				break;  //book's details can now be modified
			}

			else
			{
				flagb=1; //book not found in stock
			}


		}while(fb.eof()==0);

		if(flagb==1)
		{
			flagb=0;
			cout<<"\nBook not found in stock...";
			cout<<"\nEnter a valid code: ";
			gets(bcode);
			goto check1;
		}

		cout<<"Enter member's code: ";
		gets(mcode);

check2:

		do  //validating mcode...
		{
			fm.read((char*) &mdetails, sizeof(mdetails));

			if(strcmp(mdetails.mcode, mcode)==0) //member found
			{
				break;  //member's details can now be modified
			}

			else
			{
				flagm=1;  //member not found
			}

		}while(fm.eof()==0);

		if(flagm==1)
		{
			flagm=0;
			cout<<"\nMember not found in registry...";
			cout<<"\nEnter a valid code: ";
			gets(mcode);
			goto check2;
		}

		fb.seekg(0);	//updating book's details
		do
		{
			loc = fb.tellg();
			fb.read((char*) &bdetails, sizeof(bdetails));

			if(strcmp(bdetails.bcode, bcode) == 0)
			{
				bdetails.copies+=1;
				fb.seekg(loc);
				fb.write((char*) &bdetails, sizeof(bdetails));
				break;
			}

		}while(fb.eof()==0);

		cout<<"Book's details have been modified successfully!";

		fm.seekg(0);	//updating member's details
		do
		{
			loc = fm.tellg();
			fm.read((char*) &mdetails, sizeof(mdetails));

			if(strcmp(mdetails.mcode, mcode) == 0)
			{
				cout<<"\nFine imposed: "<<calc_fine(mdetails.date_issued, cur_date);

				cout<<"\nHas the member paid the fine? (Y/N): ";
				choice = getch();
				cout<<choice;

check3:

				if(choice == 'y' || choice == 'Y')
				{
					fm.seekg(0);
					do
					{
						fm.seekg(loc);
						if(strcmp(mdetails.mcode, mcode)==0)
						{
							mdetails.date_issued[0]=0;
							mdetails.date_issued[1]=0;
							mdetails.date_issued[2]=0;

							fm.seekg(loc);
							fm.write((char*) &mdetails, sizeof(mdetails));
							break;
						}

					}while(fm.eof()==0);
					
					cout<<"\nFine updated!";
				}

				else if(choice == 'n' || choice == 'N')
				{
					cout<<"\nFine credited on user";
				}

				else
				{
					cout<<"\nInvalid input! Pls. choose either Y or N: ";
					choice = getch();
					cout<<choice;
					goto check3;
				}
			}

		}while(fm.eof()==0);

		cout<<"\nMember's details have been modified successfully!";

		cout<<"\n\nWant to return more books? (Y/N): ";
		choice = getch();
		cout<<choice;

check4:

		if(choice == 'y' || choice=='Y')
			goto end;

		else if(choice=='n' || choice=='N')
			break;

		else
		{
			cout<<"\nInvalid input...";
			cout<<"Enter either Y or N: ";
			choice=getch();
			cout<<choice;
			goto check4;
		}

end:

	}while(choice == 'y' || choice == 'Y');

	fb.close();
	fm.close();

cfunc:

	return;
}

/***************************************************************************/

int calc_fine(int idate[], int rdate[])
{
	int d1,d2,m1,m2,y1,y2,counter=0,fine;

	d1=idate[0]; m1=idate[1]; y1=idate[2];
	d2=rdate[0]; m2=rdate[1]; y2=rdate[2];

	while(!(d1==d2 && m1==m2 && y1==y2))
	{
		if(d1==31)
		{
			d1=1;
			counter+=1;
			m1+=1;
			if(m1==12)
			{
				m1=1;
				y1+=1;
			}
		}

		else
		{
			d1+=1;
			counter+=1;
		}
	}

	if(counter>7)
	{
		fine=(counter-7)*5;
		return fine;
	}

	else
	{
		fine=0;
		return fine;
	}
}

/***************************************************************************/

void modify_member()
{
	clrscr();
	
	char mcode[25], temp[25], gender, choice;
	unsigned long int contact;
	int flagm=0;
	long loc;
	
	cout<<"Enter the code of member whose details you wish to mofify: ";
	gets(mcode);

check1:

	fstream f;
	f.open("Members.dat", ios::in | ios::out | ios::binary);
	
	do  //validating mcode...
	{
		f.read((char*) &mdetails, sizeof(mdetails));

		if(strcmp(mdetails.mcode, mcode)==0) //member found
		{
			break;  //member's details can now be modified
		}

		else
		{
			flagm=1;
		}
	}while(f.eof()==0);

	if(flagm)
	{
		cout<<"\nMember not found in registry...";
		cout<<"\nEither enter a valid code or press '0' to return to menu...";
		gets(mcode);

		if(strcmp(mcode, 0)==0)
			goto cfunc;
		else
			goto check1;
	}

	cout<<"\nWhich details would you like to change?:-\n";
	cout<<"a. Name\n";
	cout<<"b. Address\n";
	cout<<"c. Contact number\n";
	cout<<"d. Gender\n";
	cout<<"e. Return to menu\n";
	cout<<"\nChoose: ";
	choice = getch();
	cout<<choice;
	
	f.seekg(0);
	
	switch(choice)
	{
check2:	
		case 'a':
			clrscr();
			cout<<"You have chosen to modify the name of member: ";
			puts(mcode);
			cout<<"Enter new name: ";
			gets(temp);
			
			do
			{
				loc = f.tellg();
				f.read((char*) &mdetails, sizeof(mdetails));
				if(strcmp(mdetails.mcode, mcode)==0)  //code matches
				{
					strcpy(mdetails.mname, temp);
					f.seekg(loc);
					f.write((char*) &mdetails, sizeof(mdetails));
					break;
				}
			}while(f.eof()==0);
			
			break;
			
		case 'b':
			clrscr();
			cout<<"You have chosen to modify the address of member: ";
			puts(mcode);
			cout<<"Enter new address: ";
			gets(temp);
			
			do
			{
				loc = f.tellg();
				f.read((char*) &mdetails, sizeof(mdetails));
				if(strcmp(mdetails.mcode, mcode)==0)  //code matches
				{
					strcpy(mdetails.addr, temp);
					f.seekg(loc);
					f.write((char*) &mdetails, sizeof(mdetails));
					break;
				}
			}while(f.eof()==0);

			break;
			
		case 'c':
			clrscr();
			cout<<"You have chosen to modify the contact number of member: ";
			puts(mcode);
			cout<<"Enter new contact number: ";
			cin>>contact;
			
			do
			{
				loc = f.tellg();
				f.read((char*) &mdetails, sizeof(mdetails));
				if(strcmp(mdetails.mcode, mcode)==0)  //code matches
				{
					mdetails.contact=contact;
					f.seekg(loc);
					f.write((char*) &mdetails, sizeof(mdetails));
					break;
				}
			}while(f.eof()==0);
			
			break;
			
		case 'd':
			clrscr();
			cout<<"You have chosen to modify the gender of member: ";
			puts(mcode);
			cout<<"Enter new gender: ";
			cin>>gender;
			
			do
			{
				loc = f.tellg();
				f.read((char*) &mdetails, sizeof(mdetails));
				if(strcmp(mdetails.mcode, mcode)==0)  //code matches
				{
					mdetails.gender = gender;
					f.seekg(loc);
					f.write((char*) &mdetails, sizeof(mdetails));
					break;
				}
			}while(f.eof()==0);

			break;
			
		case 'e':
			return;
			
		default:
			cout<<"\nInvalid choice! Pls. choose from the above options: ";
			choice=getch();
			cout<<choice;
			goto check2;
	}

	cout<<"\nMember's details have been modified successfully!";
	cout<<"\nPress a key to return to the menu...";
	getch();

cfunc:

	f.close();
	return;
}

/***************************************************************************/

void modify_book()
{
	clrscr();

	char bcode[25], temp[25], choice;
	int flagb=0, copies;
	long loc;

	cout<<"Enter the code of book you wish to modify the details of: ";
	gets(bcode);

	fstream f;
	f.open("Books.dat", ios::in | ios::out | ios::binary);

check1:

	do  //validating bcode...
		{
			f.read((char*) &bdetails, sizeof(bdetails));

			if(strcmp(bdetails.bcode, bcode)==0) //book found
			{
				break;  //book's details can now be modified
			}

			else
			{
				flagb=1; //book not found in stock
			}


		}while(f.eof()==0);

		if(flagb)
		{
			cout<<"\nBook not found in stock...";
			cout<<"\nEnter a valid code or press '0' to return to menu...";
			gets(bcode);

			if(bcode==0)
				goto cfunc;
			else
				goto check1;
		}

		cout<<"\nWhich details would you like to change?\n";
		cout<<"\na. Book's title";
		cout<<"\nb. Author's name";
		cout<<"\nc. Publisher's name";
		cout<<"\nd. Number of copies in the stock";
		cout<<"\ne. Return to the menu\n";
		cout<<"\nChoose: ";
		choice = getch();
		cout<<choice;

		f.seekg(0);

		switch(choice)
		{
check2:
			case 'a':
				clrscr();
				cout<<"You have chosen to modify the title of book: ";
				puts(bcode);
				cout<<"Enter new title: ";
				gets(temp);

				do
				{
					loc = f.tellg();
					f.read((char*) &bdetails, sizeof(bdetails));
					if(strcmp(bdetails.bcode, bcode)==0)  //code matches
					{
						strcpy(bdetails.title, temp);
						f.seekg(loc);
						f.write((char*) &bdetails, sizeof(bdetails));
						break;
					}
				}while(f.eof()==0);

				break;

			case 'b':
				clrscr();
				cout<<"You have chosen to modify the author of book: ";
				puts(bcode);
				cout<<"Enter new author: ";
				gets(temp);

				do
				{
					loc = f.tellg();
					f.read((char*) &bdetails, sizeof(bdetails));
					if(strcmp(bdetails.bcode, bcode)==0)  //code matches
					{
						strcpy(bdetails.author, temp);
						f.seekg(loc);
						f.write((char*) &bdetails, sizeof(bdetails));
						break;
					}
				}while(f.eof()==0);

				break;

			case 'c':
				clrscr();
				cout<<"You have chosen to modify the publisher of book: ";
				puts(bcode);
				cout<<"Enter new publisher: ";
				gets(temp);

				do
				{
					loc = f.tellg();
					f.read((char*) &bdetails, sizeof(bdetails));
					if(strcmp(bdetails.bcode, bcode)==0)  //code matches
					{
						strcpy(bdetails.publisher, temp);
						f.seekg(loc);
						f.write((char*) &bdetails, sizeof(bdetails));
						break;
					}
				}while(f.eof()==0);

				break;

			case 'd':
				clrscr();
				cout<<"You have chosen to modify the number of copies of book: ";
				puts(bcode);
				cout<<"Enter new number of copies: ";
				cin>>copies;

				do
				{
					loc = f.tellg();
					f.read((char*) &bdetails, sizeof(bdetails));
					if(strcmp(bdetails.bcode, bcode)==0)  //code matches
					{
						bdetails.copies = copies;
						f.seekg(loc);
						f.write((char*) &bdetails, sizeof(bdetails));
						break;
					}
				}while(f.eof()==0);

				break;
				
			case 'e':
				return;
				
			default:
				cout<<"Invalid choice! Pls. choose from the above options: ";
				choice=getch();
				cout<<choice;
				goto check2;
		}
		cout<<"\nBook's details have been modified successfully!";
		cout<<"\nPress a key to return to the menu...";
		getch();

cfunc:

	f.close();
	return;
}

/***************************************************************************/