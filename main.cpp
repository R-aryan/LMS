#include <iostream>
#include <windows.h>
#include <mysql.h>

using namespace std;

int main()
{
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn = mysql_init(0);

    int qstate;

    if(conn)
        cout<<"connection object successfully established \n\n";
    else

        cout<<"connection not established \n\n";
    conn = mysql_real_connect(conn,"localhost","root","","library_system",0,NULL,0);

   if(conn)
    {
        cout<<"connected to mysql database!! \n\n";
        qstate= mysql_query(conn,"select *from sample");

        if(!qstate)
        {
            res= mysql_store_result(conn);
            cout<<"records of the table are \n\n";
            while(row=mysql_fetch_row(res))
            {
                cout<<"book id: "<<row[0]<<"   book name:   "<<row[1]<<"\n\n";
            }
        }
    }

    else
    {

        cout<<"Some error occured whike connection try again !! "<<mysql_error(conn);
    }
    //cout << "Hello world!" << endl; */
    return 0;
}
