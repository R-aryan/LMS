/*#include <iostream>
#include <windows.h>
#include <mysql.h>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn = mysql_init(0);
    string query;


    int qstate;

    if(conn)
        cout<<"connection object successfully established \n\n";
    else

        cout<<"connection not established \n\n";
    conn = mysql_real_connect(conn,"localhost","root","","library_system",0,NULL,0);

   if(conn)
    {
        cout<<"connected to mysql database!! \n\n";
       // query = "insert into sample(book_id,book_name) values (103,'Data Structures in C')";

        const char *q= query.c_str();
        cout<<"query is :"<<q<<"\n";
        qstate= mysql_query(conn,"select *from sample");

        if(!qstate)
        {
            res= mysql_store_result(conn);
            //cout<<"records inserted successfully in the table \n\n";
            while(row=mysql_fetch_row(res))
            {
                cout<<"book id: "<<row[0]<<"   book name:   "<<row[1]<<"\n\n";
            }
        }//
    }


    else
    {

        cout<<"Some error occured while connection try again !! "<<mysql_error(conn);
    }
    //cout << "Hello world!" << endl;
    return 0;
}
*/
