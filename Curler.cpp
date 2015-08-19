#include "Curler.h"

QByteArray Curler::getQByteArray(const QString url) {
    get(url);
    QByteArray content(rawBuffer, bufferSize);
//    QByteArray content(data.c_str());

    return content;
}

QString Curler::getQString(const QString url) {
    get(url);

    QString content(rawBuffer);
 //   QString content(data.c_str());

    return content;
}

const char *Curler::getCStr(const QString url, int &size)
{
    get(url);
    size = bufferSize;
    return rawBuffer;
}

size_t Curler::writeCallback(char* buf, size_t size, size_t nmemb, void* up) {
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    bufferSize = size * nmemb;

    if (rawBuffer) {
        free(rawBuffer);
    }

    rawBuffer = (char*) malloc(bufferSize);
    memcpy(rawBuffer, buf, bufferSize);

    return bufferSize; //tell curl how many bytes we handled
}

void Curler::get(const QString url) {
    CURL* curl;

    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    curl_global_cleanup();
}
