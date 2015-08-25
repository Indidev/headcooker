#include "Curler.h"

Curler::Curler() : data{0,0}
{
}

Curler::~Curler()
{
    if (data.buffer)
        free(data.buffer);
}

QByteArray Curler::getQByteArray(const QString url) {
    get(url);
    QByteArray content(data.buffer, data.size);
//    QByteArray content(data.c_str());

    return content;
}

QString Curler::getQString(const QString url) {
    get(url);

    return QString::fromLatin1(data.buffer, data.size);
}

const char *Curler::getCStr(const QString url, int &size)
{
    get(url);
    size = data.size;
    return data.buffer;
}

void Curler::get(const QString url) {
    CURL* handle;

    //clear data
    data.size = 0;

    //init curl
    curl_global_init(CURL_GLOBAL_ALL);
    handle = curl_easy_init();

    //set url
    curl_easy_setopt(handle, CURLOPT_URL, url.toStdString().c_str());
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    //set writeback function
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&data);

    //perform curl
    CURLcode res = curl_easy_perform(handle);

    if(res != CURLE_OK) {
        cerr << "Curler::get failes: " << curl_easy_strerror(res) << endl;
    }

    //cleanup
    curl_easy_cleanup(handle);
    curl_global_cleanup();
}

size_t Curler::writeCallback(char* buf, size_t size, size_t nmemb, void* up) {
    size_t tmpSize = size * nmemb;

    struct Memdata *data = (struct Memdata *) up;

    //resize buffer
    data->buffer = (char *)realloc(data->buffer, data->size + tmpSize + 1);

    if (data->buffer == NULL) {
        cerr << "Curler::writeCallback: Out of memory" << endl;
        tmpSize = 0; //tell curl we could not handle the data
    } else {
        //copy data into buffer
        memcpy(&(data->buffer[data->size]), buf, tmpSize);

        //set correct size in data struct
        data->size += tmpSize;
        data->buffer[data->size] = 0;
    }
    return tmpSize; //tell curl how many bytes we handled
}
