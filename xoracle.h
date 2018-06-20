#ifndef ORACLE_H_INCLUDED
#define ORACLE_H_INCLUDED
#include "occi.h"
#include "xml.cpp"

using namespace oracle::occi;

class xoracle
{
public:
    xoracle();
    //xoracle(const string &_user, const string &_passwd, const string &_connstr);
    ~xoracle();

    bool querySQL(const string &sql);

private:
    const string user;
    const string passwd;
    const string connstr;

    Environment* env;
    Connection* conn;
    Statement *stmt ;

    bool initOracle();
    bool isConnected;
};

#endif // ORACLE_H_INCLUDED
