#ifndef XMAIL_H_INCLUDED
#define XMAIL_H_INCLUDED
#include "xml.h"
#include "jwsmtp/jwsmtp.h"

using namespace jwsmtp;

class xmail
{
public:
    static bool sendEmail();
};

#endif // XMAIL_H_INCLUDED
