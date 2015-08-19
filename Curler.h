#ifndef CURLER_H
#define CURLER_H

#include <QString>
#include <curl/curl.h>
#include <iostream>
using namespace std;

static char *buffer = 0;
static int bufferSize;

class Curler
{
public:
    static QByteArray getQByteArray(const QString url);
    static QString getQString(const QString url);
    static const char *getCStr(const QString url, int &size);

private:
    static size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);
    static void get(const QString url);

    struct Memdata {
        char *tmpBuffer;
        size_t size;
    };
};

#endif // CURLER_H
