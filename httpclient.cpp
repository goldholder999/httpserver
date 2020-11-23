
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>

#include <iostream>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams
using namespace std;

void GetHttp()
{
    http_client client(U("http://en.cppreference.com/w/"));
    auto resp = client.request(U("GET")).get();

    wcout << U("STATUS : ") << resp.status_code() << endl;
    wcout << "content-type : " << resp.headers().content_type() << endl;
    wcout << resp.extract_string(true).get() << endl;
}

void GetHttpAsync()
{
    http_client client(U("http://en.cppreference.com/w/"));

    client.request(U("GET")).then([](http_response resp) {
        wcout << U("STATUS : ") << resp.status_code() << endl;
        wcout << "content-type : " << resp.headers().content_type() << endl;

        resp.extract_string(true).then([](string_t sBoby) {
            wcout << sBoby << endl;
            }).wait();

        }).wait();

}


void GetJson()
{
    http_client client(U("http://date.jsontest.com/"));

    http_request req(methods::GET);

    client.request(req).then([=](http_response r) {
        wcout << U("STATUS : ") << r.status_code() << endl;
        wcout << "content-type : " << r.headers().content_type() << endl;

        //{
        //		"time": "11:25:23 AM",
        //		"milliseconds_since_epoch" : 1423999523092,
        //		"date" : "02-15-2015"
        //}

        r.extract_json(true).then([](json::value v) {
            wcout << v.at(U("date")).as_string() << endl;
            wcout << v.at(U("time")).as_string() << endl;
            }).wait();

        }).wait();

}

int main(int argc, char argv[])
{
    GetHttp();
    GetHttpAsync();
    GetJson();
    return 0;
}
