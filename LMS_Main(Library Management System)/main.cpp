#include<iostream>
#include<windows.h>
#include<mysql.h>
#include<string>
#include<algorithm>
#include<vector>
#include<ctime>
#include<chrono>
#include<stdlib.h>


using namespace std;

class User
{
    string query,temp1,temp2,temp3,temp4;;
    int qstate;
    const char *q;
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *result;

    public:

    void display(int l);//Displays main menu
    int validate(int ch);// for input validation
    void establish_connection();// for establishing main database connection
    bool check_credentials(string name, string password);//for verification of credentials
    void new_registration(string name, string password);//for registration of new users
    void display_options();//for displaying sub menu after successful registration
    void books_database(int ch);// for displaying and connecting with different tables available within database
    void display_format(string choice);// for diaplaying the format of the data
    int query_display(int qs);// displaying the data from the different tables
    void get_time_date();//for displaying current date and time
    int display_main();// for displaying the main menu
    void book_issue(int qs);//for books issue on various subjects
    void reissue_return(string id);//for the reissue of books and return of books
    string check_department(string a);//for checking out the department of the issued book


};

void User::establish_connection()
{
    conn = mysql_init(0);
    //string query;

    if(conn)
        cout<<"\t connection object successfully established \n\n";
    else
        cout<<"\t connection not established \n\n";

    conn = mysql_real_connect(conn,"localhost","root","","library_system",0,NULL,0);


   if(conn)
    {
        cout<<"\t connected to mysql database!! \n\n";}

    else
    {
        cout<<"\t Some error occured while connection try again !! "<<mysql_error(conn);

    }


}

void User::new_registration(string name, string password)
{
    query = "insert into new_user(username,password) values ('"+name+"','"+password+"')";
    q= query.c_str();

    cout<<"Details you inserted is  "<<q<<"\n\n";
    qstate= mysql_query(conn,q);

    if(!qstate){
        cout<<"Registration successfully done...... \n\n";
        cout<<"Remember your credentials for future login......\n";
        cout<<"................................................\n\n";

        query = "insert into registered_user(username,password) values ('"+name+"','"+password+"')";
        q= query.c_str();
        //cout<<"Details you inserted is  "<<q<<"\n\n";
        qstate= mysql_query(conn,q);

        }
    else{
        cout<<"Sorry!! some error occured while registration.....Try again!!:  "<<mysql_error(conn)<<endl;
    }

    display(0);


}

int User::validate(int ch)
{
    /*
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    This line ignores the rest of the current line, up to '\n' or EOF - whichever comes first:
   '\n' sets the delimiter, i.e. the character after which cin stops ignoring
    numeric_limits<streamsize>::max() sets the maximum number of characters to ignore.
    Since this is the upper limit on the size of a stream, you are effectively telling cin that
    there is no limit to the number of characters to ignore
    */
   while(!(cin >> ch)){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.  Try again: ";
	}
	return ch;
}

void User::get_time_date()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    cout << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday; cout<<"    And your due date is \t";cout << (now->tm_year + 1900) << '-'
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday+14
         << endl;
}
void User::display(int ch)
{
    string name, password;

    int l=display_main();

	if(l==1)
    {
        cout<<"Enter your User Id and password for verification \n\n";

        cin>>name>>password;

        bool res= check_credentials(name,password);

        if(res)
        {
            cout<<"login successful \n";
            cout<<"-------------------- \n\n";
            display_options();

        }

        else
            cout<<"Wrong credentials try again \n\n";
    }

        else if(l==2)
        {

            cout<<"Hello New User!! Please enter your user id and password \n\n";

            cin>>name>>password;cout<<"\n\n";
            new_registration(name,password);
        }
        else{
            cout<<"Sorry wrong choice Try again!!! \n";
            cout<<"............................... \n\n";
            }


}

int User::display_main()
{
    int ch=0,l;
    cout<<"\t WELCOME TO LIBRARY MANAGEMENT SYSTEM(LMS) \n";
    cout<<"\t ......................................... \n\n";
    cout<<"\t Enter 1 for existing user and 2 for new user \n";
    cout<<"\t ............................................. \n\n";
    l=validate(ch);

	cout << "You enterd: " << l<< endl;

	return l;
}
void User::display_format(string choice)
{
        cout<<"The Books Available for   "<<choice<<"  are.....\n";
        cout<<"..................................................\n\n";
        cout<<"BOOK_ID    "<<"BOOK_NAME   "<<"AUTHOR   "<<"COPIES_AVAILABLE \n";
        cout<<".........  "<<"........... "<<".......  "<<"................. \n\n";
}

bool User::check_credentials(string name, string password)
{
 cout<<"You Entered......   "<<name<<"\t"<<password<<"\n\n";
 qstate= mysql_query(conn,"select *from registered_user");

 if(!qstate)
        {
            result = mysql_store_result(conn);
            while(row=mysql_fetch_row(result))
            {
                temp1= row[0];temp2=row[1];
                //cout<<temp1<<"   "<<temp2;
                if(name.compare(temp1)==0 && password.compare(temp2)==0)
                    return true;
            }
            }
 else{
    cout<<"Sorry!! Some error occured while verification "<<mysql_error(conn)<<"\n\n";
 }

 return false;
}

int User::query_display(int qs)
{

      int choice=0,l;cout<<"state is "<<qs<<"\n";

       if(!qs)
        {
            result = mysql_store_result(conn);
            while(row=mysql_fetch_row(result))
            {
                temp1= row[0];temp2=row[1];temp3=row[2];temp4=row[3];
                //cout<<temp1<<"   "<<temp2;
                cout<<temp1<<"  |  "<<temp2<<"  |  "<<temp3<<"  |  "<<temp4<<"  |\n";
                cout<<"................................................................\n";
            }
            return 0;
            }


       else{
    cout<<"Sorry!! Some error occured while verification "<<mysql_error(conn)<<"\n\n";return 1;}

}


string User::check_department(string a)
{
    string dept="dept";
    if(a[0]=='1')
       dept= "Computer Science";
    else if(a[0]=='2')
        dept= "Mathematics";
    return dept;

}
void User::book_issue(int qs)
{
    int l,choice=0,confirm;string temp_choice;cout<<"state is   "<<qs<<"\n";
    cout<<"Enter 1 if you want to issue a book from this department \n";
    cout<<".................................................................\n\n";
      l=validate(choice);cout << "You enterd: " << l<< endl;
      if(l==1)
      {

          cout<<"Enter the book id(three digit integer)/author's name/book name to be issued \n\n";
          cin>>temp_choice;cout<<"your choice is"<<temp_choice<<"\n";
          if(!qs)
          {
              //qstate= mysql_query(conn,"select *from computer_science");
             // if(!qstate)

            result = mysql_store_result(conn);
            while(row=mysql_fetch_row(result))
            {
                temp1= row[0];temp2=row[1];temp3=row[2];temp4=row[3];//cout<<temp3<<"\n";
                if(temp1.compare(temp_choice)==0 && temp4!="0")
                {
                    cout<<"you selected "<<temp2<<"   by  "<<temp3<<"\n\n";
                    cout<<"......................................................... \n";
                    cout<<"Enter 1 to confirm \n";confirm=validate(choice);
                    if(confirm==1)
                    {
                        cout<<"The book  "<<temp2<<"   by  "<<temp3<<"   is issued to you  on  \n";
                        cout<<".....................................................................\n";
                        get_time_date();string dept= check_department(temp1);
                        cout<<".........................................................\n";
                        query = "insert into issued_books(book_id,book_name,author,department) values ('"+temp1+"','"+temp2+"','"+temp3+"','"+dept+"')";
                        q= query.c_str();

                        //cout<<"Details you inserted is  "<<q<<"\n\n";
                        qstate= mysql_query(conn,q);

                        if(!qstate){
                            cout<<"Book Successfully issued!! Thank you \n";
                            cout<<"...................................... \n\n";


                            }

                    }

                    return;
                }
            }

          }

    }

    else
    {
        cout<<"Thank You \n";
        return;
    }

}

void User::reissue_return(string id)
{
   // cout<<"Hello this is reissue and return portal \n";
   int choice=0,l;
   cout<<"Enter 1 if you want to rei-issue a book, 2 if you want to return the book \n";
   cout<<"............................................................................. \n";
    l=validate(choice);

   if(l==2)
   {
       string dept= check_department(id);
       query = "insert into returned_books(book_id,department) values ('"+id+"','"+dept+"')";
       q= query.c_str();
       cout<<"Details you inserted is  "<<q<<"\n\n";
       qstate= mysql_query(conn,q);
       if(!qstate){
            cout<<"Book Successfully returned!! Thank you \n";
            cout<<"...................................... \n\n";
                            }
    }

    else if(l==1)
    {
        cout<<"The book with the book id "<<id<<" is successfully re-issued to your account on \n";
        cout<<"................................................................................. \n";
        get_time_date();
        cout<<"................................................................................. \n\n";
    }

    else{
        cout<<"Wrong choice try again \n";
        cout<<"......................... \n\n";}
}

void User::books_database(int ch)
{
    int s;

    if(ch==1)
    {
        display_format("COMPUTER_SCIENCE");
        qstate= mysql_query(conn,"select *from computer_science");
        s=query_display(qstate);
        qstate= mysql_query(conn,"select *from computer_science");
        book_issue(qstate);

    }
    else if(ch==2)
    {
        display_format("MATHEMATICS");
        qstate= mysql_query(conn,"select *from mathematics");
        s=query_display(qstate);
        qstate= mysql_query(conn,"select *from mathematics");
        book_issue(qstate);
    }
}
void User::display_options()
{
    int ch=0,l;
    //cout<<"Please Select Your Subject !!! \n";
    cout<<".................................. \n";
    cout<<"Press 1 For Book Issue and Queries \n";
    cout<<"...................................\n";
    cout<<"2 To Return/Re-issue a book \n";
    cout<<"...................................\n\n";
    l=validate(ch);
	cout << "You enterd: " << l<< endl;
	if(l==1)
	{
        cout<<"Please Enter your Subject \n";
        cout<<"......................... \n\n";
        cout<<"1 for Computer Science 2 for Mathematics \n";
        l=validate(ch);cout << "You enterd: " << l<< endl;
        books_database(l);}


    else if(l==2){
        cout<<"Enter your book id to be returned/re-issued(three digit integer) \n\n";
        //l=validate(id);cout << "You enterd: " << l<< endl;
        cin>>temp1;
        reissue_return(temp1);}

  else{
    cout<<"Wrong choice !! Try again \n";
    cout<<"..............................";
    }


}

int main()
{
    User u1;
    u1.establish_connection();
    u1.display(0);
}

