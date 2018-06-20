#include <iostream>
#include <string>
#include "occi.h"
using namespace oracle::occi;
using namespace std;

int main()
{
        string usr="root";
        string pwd="214365";
        string SID="orcl";
        string date;

        Environment *env=Environment::createEnvironment(Environment::OBJECT);
        Connection *conn= env->createConnection(usr,pwd,SID);//all strings
        if(conn)
                cout<<"success createConnection!"<<endl;
        else
                cout<<"failure createConnection!"<<endl;

        Statement *stmt = conn->createStatement();
        string sSQL = "select to_char(sysdate,'yyyy-mm-dd hh24:mi:ss') from dual";
        stmt->setSQL(sSQL);


        ResultSet *rs = stmt->executeQuery();
        if(rs->next())
        {
                date = rs->getString(1);
        }

        cout<<"now time :"<<date<<endl;

        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);

        return 0;
}
  
