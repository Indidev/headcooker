#include "Curler.h"

QByteArray Curler::getQByteArray(const QString url) {
    get(url);
    QByteArray content(buffer, bufferSize);
//    QByteArray content(data.c_str());

    return content;
}

QString Curler::getQString(const QString url) {
    get(url);

    QString content(buffer);
 //   QString content(data.c_str());

    return content;
}

const char *Curler::getCStr(const QString url, int &size)
{
    get(url);
    size = bufferSize;
    return buffer;
}

size_t Curler::writeCallback(char* buf, size_t size, size_t nmemb, void* up) {
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    size_t tmpSize = size * nmemb;

    struct Memdata *data = (struct Memdata *) up;

    data->tmpBuffer = (char *)realloc(data->tmpBuffer, data->size + tmpSize + 1);

    if (data->tmpBuffer == NULL) {
        cerr << "Curler::writeCallback: Out of memory" << endl;
    }

    memcpy(&(data->tmpBuffer[data->size]), buf, tmpSize);

    data->size += tmpSize;
    data->tmpBuffer[data->size] = 0;

    return tmpSize; //tell curl how many bytes we handled
}

void Curler::get(const QString url) {
    free(buffer);
    CURL* handle;
    Memdata data{0, 0};

    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    handle = curl_easy_init();

    curl_easy_setopt(handle, CURLOPT_URL, url.toStdString().c_str());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    CURLcode res = curl_easy_perform(handle);

    if(res != CURLE_OK) {
        cerr << "Curler::get failes: " << curl_easy_strerror(res) << endl;
    }

    bufferSize = data.size;
    buffer = (char *) malloc(bufferSize);
    memcpy(buffer, data.tmpBuffer, bufferSize);

    free(data.tmpBuffer);
    curl_easy_cleanup(handle);
    curl_global_cleanup();
}
