#include "xoracle.cpp"
#include "xmysql.cpp"
#include "xmail.h"

int main()
{

   xmail::sendEmail();

       xmysql* myl = new xmysql();

        const string s = "select to_char(sysdate, 'yyyy-mm-dd hh24 : mi : ss') from dual";
        xoracle* myoracle = new xoracle();
        myoracle->querySQL(s);
        return 0;
}
