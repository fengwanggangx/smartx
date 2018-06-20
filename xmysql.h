#ifndef MYSQL_H_INCLUDED
#define MYSQL_H_INCLUDED
#include "mysql/mysql.h"
#include "xml.h"

class xmysql
{
public:
    xmysql();
    xmysql(const string &_host, const string &_user, const string &_passwd, const string &_db, const unsigned int &_port);
    ~xmysql();

private:
    const string host;
    const string user;
    const string passwd;
    const string db;
    const  unsigned int port;

    MYSQL  conn;
    bool isConnected;

    bool initMysql();
};


#endif // MYSQL_H_INCLUDED
