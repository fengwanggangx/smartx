#include "xml.h"

inline xml::xml() : xmlfile("configuration.xml")
{

}

inline xml::xml(const string &_xmlname) : xmlfile(_xmlname)
{

}

inline xml::~xml()
{

}

map<string, string> xml::configInfo(string &configtree)
{
    map<string, string> configmap;
    configmap.clear();

    trimall(configtree);
    vector<string> element = split(configtree, ".");
    XMLDocument config;
    if (0 != config.LoadFile(xmlfile.c_str()))
    {
        cout << "load error" << endl;
    }
    XMLElement *root = config.RootElement();
    if (NULL == root)
    {
        cout << "config.RootElement error!" << endl;
    }
    const XMLElement *ele = root;

    for (auto iter = element.begin(); iter != element.end(); ++iter)
    {
        ele = ele->FirstChildElement((*iter).c_str());
        if (NULL == ele)
        {
            cout << "config-string errors!" << endl;
            break;
        }
    }
    if (NULL != ele)
    {
        const XMLAttribute *attr = ele->FirstAttribute();
        while (attr)
        {
            configmap.insert(make_pair(attr->Name(), attr->Value()));
            //cout << attr->Name() << ":" << attr->Value() << endl;
            //configmap.insert(std::pair<string, map<string, string>>("atrribute", map<string, string>((string)(attr->Name()), (string)(attr->Value()))));
            attr = attr->Next();
        }

        const char* val = ele->GetText();
        if (NULL != val)
        {
            configmap.insert(make_pair(ele->Name(), val));
          //  cout << ele->Name() << ":" <<  val << endl;
        }
        return configmap;
    }
    return configmap;
}

bool xml::creatXML()
{
    try {
        const char* declaration ="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
        XMLDocument doc;
        doc.Parse(declaration);


        XMLElement* root=doc.NewElement("root");
        doc.InsertEndChild(root);
        if (0 != doc.SaveFile(xmlfile.c_str()))
        {
            cout << "doc.SaveFile(xmlfile.c_str()) error!" << endl;
            return false;
        }

        if(0 != doc.LoadFile(xmlfile.c_str()))
        {
            cout<<"load xml file failed"<<endl;
            return 1;
        }
        root = doc.RootElement();
        XMLElement* database = doc.NewElement("database");
        root->InsertFirstChild(database);

        XMLElement* oracle = doc.NewElement("oracle");
        oracle->SetAttribute("host", "127.0.0.1");
        oracle->SetAttribute("user", "root");
        oracle->SetAttribute("password", "214365");
        oracle->SetAttribute("db", "orcl");
        oracle->SetAttribute("port", "1521");
        database->InsertEndChild(oracle);
        if (0 != doc.SaveFile(xmlfile.c_str()))
        {
            cout << "doc.SaveFile(xmlfile.c_str()) error!" << endl;
            return false;
        }

        XMLElement* mysql = doc.NewElement("mysql");
        mysql->SetAttribute("host", "127.0.0.1");
        mysql->SetAttribute("user", "root");
        mysql->SetAttribute("password", "214365");
        oracle->SetAttribute("db", "test");
        mysql->SetAttribute("port", "3306");
        database->InsertEndChild(mysql);
        if (0 != doc.SaveFile(xmlfile.c_str()))
        {
            cout << "doc.SaveFile(xmlfile.c_str()) error!" << endl;
            return false;
        }

        XMLElement* sqlserver = doc.NewElement("sqlserver");
        sqlserver->SetAttribute("host", "127.0.0.1");
        sqlserver->SetAttribute("user", "root");
        sqlserver->SetAttribute("password", "214365");
        sqlserver->SetAttribute("port", "1521");
        database->InsertEndChild(sqlserver);
        if (0 != doc.SaveFile(xmlfile.c_str()))
        {
            cout << "doc.SaveFile(xmlfile.c_str()) error!" << endl;
            return false;
        }

        XMLElement* access = doc.NewElement("access");
        access->SetAttribute("host", "127.0.0.1");
        access->SetAttribute("user", "root");
        access->SetAttribute("password", "214365");
        access->SetAttribute("port", "1521");
        database->InsertEndChild(access);
        if (0 != doc.SaveFile(xmlfile.c_str()))
        {
            cout << "doc.SaveFile(xmlfile.c_str()) error!" << endl;
            return false;
        }

        return true;
    } catch (exception &ex) {
        cout << ex.what() << endl;
        return false;
    }
}

string xml::getConfig(const string group , const string member, const string target, const string defauttarget)
{
    string node = group + "." + member;
    trimall(node);
    xml xml;
    map<string, string> conf = xml.configInfo(node);
    auto iter = conf.find(target);
    if (iter != conf.end())
    {
        return (iter->second);
    }

    return defauttarget;
}
