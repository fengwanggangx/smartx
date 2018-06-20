#include "xoracle.h"


inline xoracle::xoracle()  :  user(xml::getConfig("database", "oracle", "user", "root").c_str()), passwd(xml::getConfig("database", "oracle", "password", "214365").c_str()), connstr(xml::getConfig("database", "oracle", "db", "orcl").c_str())
{

    isConnected = false;
    this->initOracle();
}
//"localhost:1521/orcl


inline xoracle::~xoracle()
{
    conn->terminateStatement(stmt);
    env->terminateConnection(conn);
    Environment::terminateEnvironment(env);
    if (NULL != stmt)
    {
        delete stmt;
        stmt = NULL;
    }
    if (NULL != conn)
    {
        delete conn;
        conn = NULL;
    }
    if (NULL != env)
    {
        delete env;
        env = NULL;
    }

    isConnected = false;
}

bool xoracle::initOracle()
{
    try
    {
        env = Environment::createEnvironment(Environment::OBJECT);
        if (NULL == env)
        {
            cout << "env:createEvironment error" << endl;
            return false;
        }
        conn = env->createConnection(this->user, this->passwd, this->connstr);
        if (NULL == conn)
        {
            cout << "conn: createConnection error" << endl;
            return false;
        }
        stmt = conn->createStatement();
        if (NULL == stmt)
        {
            cout << "stmt:createStatement error" << endl;
            return false;
        }

        isConnected = true;
        return true;
    } catch (SQLException &e) {
        cout << e.getErrorCode() << ":" << e.getMessage() << endl;

        isConnected = false;
        return false;
    }

    isConnected = false;
    return false;
}

bool xoracle::querySQL(const string &sql)
{

    if (this->isConnected)
    {
        cout << "oracle is ready!" << endl;
        this->stmt->setSQL(sql);
        ResultSet* rs = this->stmt->executeQuery();
        while (rs->next())
        {
            cout << rs->getString(1) << endl;
        }
        return true;
    } else {
        cout << "oracle is disconnected!" << endl;
        return false;
    }
}
//0:select 1:insert && update 2:comand;

