#ifndef CURLER_H
#define CURLER_H

#include <QString>
#include <curl/curl.h>
#include <iostream>
using namespace std;

static string data;

class Curler
{
public:
    static QString get(const QString url);

private:
    //static int peter = 1;
    static size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);
};

#endif // CURLER_H
