#include "xmail.h"

bool xmail::sendEmail()
{
    const std::string html("<html>"
    "<body>"
    "This is the html part of the message<br><br>"
    "<b>bold</b><br>"
    "<i>italic</i><br>"
    "<font size=\"7\">Large Text</font><br><br>"
    "Or a link: <a href=\"http://johnwiggins.net\">johnwiggins.net</a><br><br>"
    "</body>"
    "</html>");


    //const string touser = xml::getConfig("modules", "mail", "receiver", "000000");
    const string fromuser = xml::getConfig("modules", "mail", "sender", "000000");
    const string emailtitle = xml::getConfig("modules", "mail", "title", "000000");
    const string emailmesg = xml::getConfig("modules", "mail", "mesg", "000000");
    const string mailserver = xml::getConfig("modules", "mail", "mailserver", "000000");

    unsigned short port;
    if (xml::getConfig("modules", "mail", "port", "SMTP_PORT") == "SMTP_PORT")
    {
        port = mailer::SMTP_PORT;
    } else {
        cout << "port config errors!" << endl;
        return false;
    }

    bool MXLookup;
    if (xml::getConfig("modules", "mail", "MXLookup", "false") == "false")
    {
        MXLookup = false;
    } else if (xml::getConfig("modules", "mail", "MXLookup", "false") == "true")
    {
        MXLookup = true;
    } else {
        cout << "MXLookup config errors!" << endl;
        return false;
    }

    enum mailer::authtype authmode = mailer::PLAIN;
    if (xml::getConfig("modules", "mail", "authtype", "PLAIN") == "PLAIN")
    {
        authmode = mailer::PLAIN;
    } else if (xml::getConfig("modules", "mail", "authtype", "PLAIN") == "LOGIN")
    {
        authmode = mailer::LOGIN;
    } else {
        cout << "authtype config errors!" << endl;
        return false;
    }

    const string passwd = xml::getConfig("modules", "mail", "passwd", "000000");
    vector<string> touserlist = split(xml::getConfig("modules", "mail", "receiver", "000000"), ",");
    if (touserlist[0] == "000000")
    {
        return false;
    }

    cout << touserlist[1]  << endl;
    mailer m(touserlist[1].c_str(), fromuser.c_str(), emailtitle.c_str(), emailmesg.c_str(), mailserver.c_str(), port, MXLookup);

    for (auto iter = touserlist.begin()+1; iter != touserlist.end(); iter++)
    {
        cout << (*iter) << endl;
        m.addrecipient((*iter));
    }
    const string pattern =  xml::getConfig("modules", "mail", "pattern", "000000");
    if (pattern == "html")
    {
        m.setmessageHTML(html);
    } else if (pattern == "text") {

    } else {
        cout << "pattern config errors!" << endl;
    }
    if (xml::getConfig("modules", "mail", "attach", "000000") != "000000")
    {
        m.attach(xml::getConfig("modules", "mail", "attach", "000000"));
    }
    m.authtype(authmode);
    m.username(fromuser.c_str());
    m.password(passwd.c_str());
    m.send();
    if (m.response().substr(0, 3) == "250")
    {
        cout << m.response() << endl;
    } else {
        cout << "mail sand ok!" << endl;
    }
    return true;
}
