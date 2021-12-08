#include <curl/curl.h>
#include <bits/stdc++.h>
#include <sstream>
using namespace std;

class CURLplusplus
{
private:
    CURL* curl;
    stringstream ss;
    long http_code;
    string response;
public:
    CURLplusplus()
            : curl(curl_easy_init())
    , http_code(0)
    {

    }
    ~CURLplusplus()
    {
        if (curl) curl_easy_cleanup(curl);
    }
    std::string Get(const std::string& url)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
        ss.str("");
        http_code = 0;
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            throw std::runtime_error(curl_easy_strerror(res));
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        return ss.str();
    }
    long GetHttpCode()
    {
        return http_code;
    }
    string get_response(){
        return response;
    }
private:
    static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
    {
        return static_cast<CURLplusplus*>(userp)->Write(buffer,size,nmemb);
    }
    size_t Write(void *buffer, size_t size, size_t nmemb)
    {
        ss.write((const char*)buffer,size*nmemb);
        return size*nmemb;
    }
};
int main(int argc, char const *argv[])
{
    string city = "leeds";
    string api = "e84f587b3544442fbe13ca10af139a5b";
    string link = "https://api.opencagedata.com/geocode/v1/json?q="+city+"&key="+api;
    CURLplusplus crl;
    crl.Get(link);
    cout << crl.GetHttpCode();
    return 0;
}
