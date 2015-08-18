#include "Curler.h"

QString Curler::get(const string url) {
    QString content;
    CURL* curl;

    curl_global_init(CURL_GLOBAL_ALL); //pretty obvious
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_perform(curl);

    content = QString::fromStdString(data);

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return content;
}

size_t Curler::writeCallback(char* buf, size_t size, size_t nmemb, void* up)
{ //callback must have this declaration
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (int c = 0; c<size*nmemb; c++)
    {
        data.push_back(buf[c]);
        //++;
    }
    return size*nmemb; //tell curl how many bytes we handled
}
