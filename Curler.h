#ifndef CURLER_H
#define CURLER_H

#include <QString>
#include <curl/curl.h>
#include <iostream>
using namespace std;

class Curler
{
public:
    Curler();
    ~Curler();
    QByteArray getQByteArray(const QString url);
    QString getQString(const QString url);
    const char *getCStr(const QString url, int &size);

private:
    static size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up);
    void get(const QString url);

    struct Memdata {
        char *buffer;
        size_t size;
    } data;
};

#endif // CURLER_H
