#ifndef XML_H_INCLUDED
#define XML_H_INCLUDED
#include "common.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class xml
{
public:
    xml(const string &_xmlname);
    xml();
    ~xml();
    bool creatXML();
    map<string, string> configInfo(string &configtree);
    static string getConfig(const string group , const string member, const string target, const string defauttarget);
private:
    const string xmlfile;
};

#endif // XML_H_INCLUDED
