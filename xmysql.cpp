#include "xmysql.h"

inline xmysql::xmysql() : host(xml::getConfig("database", "mysql", "host", "127.0.0.1").c_str()), user(xml::getConfig("database", "mysql", "user", "root").c_str()), passwd(xml::getConfig("database", "mysql", "password", "214365").c_str()), db(xml::getConfig("database", "mysql", "db", "test").c_str()), port((unsigned)(atoi(xml::getConfig("database", "mysql", "port", "3306").c_str())))
{
    this->initMysql();
}

 inline bool xmysql::initMysql()
 {
     this->isConnected = false;
     try {
        if ( NULL == mysql_init(&conn))
        {
            cout << "mysql_init errors!" << endl;
            return false;
        } else {
            cout << "mysql_init successfully!" << endl;
        }

        if (!mysql_real_connect(&conn, this->host.c_str(), this->user.c_str(), this->passwd.c_str(), this->db.c_str(), this->port, NULL, 0))
        {
            cout << "mysql_real_connect errors!" << endl;
            return false;
        } else {
            cout << "mysql_real_conn successfully!" << endl;
        }

        this->isConnected = true;
        return true;
     } catch (exception &ex) {
        cout << ex.what() << endl;

        this->isConnected = false;
        return false;
     }
     return false;
 }
xmysql::~xmysql()
{
    mysql_close(&conn);
}

