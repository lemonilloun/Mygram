#ifndef SERV_HPP
#define SERV_HPP

#include <fstream>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <vector>
#include<string>

class server 
{
private:
    int m_socket {-1};
    int m_port {443};

    string m_certificate_path;
    string m_key_path;
    string m_ca_path;
    string m_html_data; // буквально html страница (ну хз вдруг надо будет)

    string m_start_data_time;
    string m_get_requseted_count {0}; // кол-во гет-реквестов

    SSL_METHOD *mp_ssl_method {nullptr};
    SSL_CTX  *mp_ssl_context {nullptr};

    vector<char> m_fav_icon_buffer; // icon буффер для браузера

public:
    server(int aPort = 443);
    ~server();
    bool start();

    void setCertPath(std::string);
    void setKeyPath(std::string);
    void setPathForCA(std::string);

private:
    bool _ssl_init();
    bool _soket_init();
    bool _client_processing(int, std::string);
    
};

#endif 