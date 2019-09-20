/*
    Created on: 01.01.2019
    Author: Georgi Angelov
        http://www.wizio.eu/
        https://github.com/Wiz-IO    

    Need: EXPERIMENTAL MODE

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA   
 */

#include "ClientSecure.h"

#ifdef EX_MODE

#define DEBUG_SSL 
//Serial.printf

#define SSL_DEFAULT_TIMEOUT 20000L
//#define SSL_ERROR_STRING ERR_error_string(ERR_get_error(), NULL)

static int ssl_connect(secure_contex *client, const char *host, uint32_t port)
{
    if (NULL == client)
        return -1;
    if (client->sock >= 0)
        return -1;
    int rc;
    DEBUG_SSL("[SSL] Socket\n");
    client->sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client->sock < 0)
    {
        DEBUG_SSL("[ERROR] socket()\n");
        return -1;
    }

    DEBUG_SSL("[SSL] GetHostByName: %s\n", host);
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    struct hostent *hp = gethostbyname(host);
    if (hp == NULL)
    {
        DEBUG_SSL("[ERROR] gethostbyname()\n", host);
        return -1;
    }
    memcpy(&sa.sin_addr, hp->h_addr, sizeof(sa.sin_addr));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    
    DEBUG_SSL("[SSL] Host IP: %d.%d.%d.%d : %d\n",
              (int)((sa.sin_addr.s_addr) & 0xFF),
              (int)((sa.sin_addr.s_addr >> 8) & 0xFF),
              (int)((sa.sin_addr.s_addr >> 16) & 0xFF),
              (int)((sa.sin_addr.s_addr >> 24) & 0xFF),
              (int)(int)ntohs(sa.sin_port),
              sa.sin_addr.s_addr);

    if (client->timeout == 0)
        client->timeout = SSL_DEFAULT_TIMEOUT;

    int enable = 1;
    struct timeval interval = {client->timeout / 1000, 0};
    setsockopt(client->sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&interval, sizeof(struct timeval));
    setsockopt(client->sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&interval, sizeof(struct timeval));
    //setsockopt(client->sock, IPPROTO_TCP, TCP_NODELAY, (char *)&enable, sizeof(enable));
    setsockopt(client->sock, SOL_SOCKET, SO_KEEPALIVE, (char *)&enable, sizeof(enable));
    // CONNECT
    rc = ::connect(client->sock, (struct sockaddr *)&sa, sizeof(sa));
    if (rc < 0)
    {
        DEBUG_SSL("[ERROR] connect(): %d\n", rc);
        return -1;
    }
    DEBUG_SSL("[SSL] Socket connected\n");
    return client->sock;
}

void ClientSecure::printError()
{
    if (NULL == client.ssl)
        return;
    char err_buffer[80];
    int err = wolfSSL_get_error(client.ssl, 0);
    DEBUG_SSL("[ERROR] SSL: %s\n", wolfSSL_ERR_error_string(err, err_buffer));
}

int ClientSecure::ssl_try_load_files()
{
    //CA_LIST
    if (client.ca_cert)
    {
        if (0 == SSL_CTX_load_verify_locations(client.ctx, client.ca_cert, 0))
        {
            DEBUG_SSL("[ERROR] LOAD CA_FILE\n");
            return -1;
        }
        //TODO
        //SSL_CTX_set_client_CA_list(client.ctx, SSL_load_client_CA_file(client.ca_cert));
        DEBUG_SSL("[SSL] USE CA_FILE\n");
    }

    if (client.certificate)
    {
        //if (SSL_CTX_use_certificate_chain_file(client.ctx, client.certificate) <= 0)
        if (SSL_CTX_use_certificate_file(client.ctx, client.certificate, SSL_FILETYPE_PEM) <= 0)
        {
            DEBUG_SSL("[ERROR] CERTIFICATE\n");
            return -1;
        }
        DEBUG_SSL("[SSL] USE CERTIFICATE\n");
    }

    if (client.private_key)
    {
        if (SSL_CTX_use_PrivateKey_file(client.ctx, client.private_key, SSL_FILETYPE_PEM) <= 0)
        {
            DEBUG_SSL("[ERROR] USE PRIVATE KEY FILE\n");
            return -1;
        }
        if (!SSL_CTX_check_private_key(client.ctx))
        {
            DEBUG_SSL("[ERROR] VRF PRIVATE\n");
            return -1;
        }
        DEBUG_SSL("[SSL] USE PRIVATE KEY\n");
    }
    return 0;
}

int ClientSecure::ssl_try_load_array()
{
    //TODO
    return 0;
}

int ClientSecure::ssl_begin(const char *host, uint32_t port, int vrf)
{
    int rc;
    if (_connected) // allready
        return -1;
    if (ssl_connect(&client, host, port) < 0)
        return -1;

    client.method = wolfSSLv23_client_method(); //CyaSSLv23_client_method ()
    if (NULL == client.method)
    {
        DEBUG_SSL("[ERROR] SSL method\n");
        return -1;
    }

    client.ctx = SSL_CTX_new(client.method); // SSLv23_method()  23 can work with TLSv1_2_method
    if (NULL == client.ctx)
    {
        DEBUG_SSL("[ERROR] SSL create context\n");
        return -1;
    }

    if (ssl_try_load_files() || ssl_try_load_array())
        return -1;

    //CREATE SSL, must be here, after CTX initialization
    client.ssl = SSL_new(client.ctx);
    if (NULL == client.ssl)
    {
        DEBUG_SSL("[ERROR] SSL create ssl\n");
        return -1;
    }

    //CIPHERS
    if (client.ciphers)
        rc = wolfSSL_set_cipher_list(client.ssl, client.ciphers);
    else
        rc = wolfSSL_set_cipher_list(client.ssl, "ECDHE-RSA-AES128-SHA:ECDHE-RSA-AES256-SHA:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-SHA:ECDHE-RSA-AES256-SHA"); //SSL_SUCCESS
    DEBUG_SSL("[SSL] ciphers (%d)\n", rc);

    //for (int i = 0; i < 24; i++) DEBUG_SSL("%s\n", wolfSSL_get_cipher_list(i));

    //SNI todo
    if (client.sni_host_name)
    {
        wolfSSL_UseSNI(client.ssl, WOLFSSL_SNI_HOST_NAME, client.sni_host_name, strlen(client.sni_host_name)); //"www.wolfssl.com"
        //wolfSSL_CTX_UseSNI();
    }

    //if (vrf)
    SSL_set_verify(client.ssl, vrf, NULL); //SSL_VERIFY_NONE

    //ATTACH SOCKET
    if (SSL_set_fd(client.ssl, client.sock) <= 0)
    {
        DEBUG_SSL("[ERROR] SSL_set_fd()\n");
        return -1;
    }

    //HANDSHAKE
    rc = SSL_connect(client.ssl);
    if (rc <= 0)
    {
        DEBUG_SSL("[ERROR] SSL_connect()\n");
        printError();
        return -1;
    }

//TODO
#if 0
    if (vrf && SSL_get_verify_result(client.ssl) != 0) //X509_V_OK
    {
        //DEBUG_SSL("[ERROR] Certificate doesn't verify\n%s\n", SSL_ERROR_STRING);
        //ERR_print_errors_fp(stderr);
        return -1;
    }
#endif

    struct timeval interval = {0, 10 * 1000}; // 10ms timeout for reading and peek
    setsockopt(client.sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&interval, sizeof(struct timeval));
    return 0;
}

bool ClientSecure::verify(const char *domain_name)
{
//TODO
#if 0    
    char peer_CN[256];
    X509 *peer = SSL_get_peer_certificate(client.ssl);
    X509_NAME_get_text_by_NID(X509_get_subject_name(peer), NID_commonName, peer_CN, sizeof(peer_CN));
    if (strcmp(peer_CN, domain_name))
    {
        DEBUG_SSL("[ERROR] Common name doesn't match host name ( %s )\n", peer_CN);
        return -1;
    }
#endif
    return 0;
}

ClientSecure::ClientSecure()
{
    ssl_init();
    client.sock = -1;
    next = NULL;
    _connected = false;
}

ClientSecure::ClientSecure(int sock)
{
    ssl_init();
    _connected = false;
    if (sock >= 0)
        _connected = true;
    next = NULL;
}

ClientSecure::~ClientSecure()
{
    stop();
}

ClientSecure &ClientSecure::operator=(const ClientSecure &other)
{
    stop();
    client.sock = other.client.sock;
    _connected = other._connected;
    return *this;
}

void ClientSecure::stop()
{
    _connected = false;

    if (client.sock >= 0)
        ::close(client.sock);
    client.sock = -1;

    if (client.ssl)
        SSL_free(client.ssl);
    client.ssl = NULL;

    if (client.ctx)
        SSL_CTX_free(client.ctx);
    client.ctx = NULL;

    //if (client.method) client.method = NULL;

    DEBUG_SSL("[SSL] stop()\n");
}

int ClientSecure::connect(IPAddress ip, uint16_t port)
{
    if (client.pskIdent && client.psKey)
        return connect(ip, port, client.pskIdent, client.psKey);
    return connect(ip, port, client.ca_cert, client.certificate, client.private_key);
}

int ClientSecure::connect(IPAddress ip, uint16_t port, int32_t timeout)
{
    client.timeout = timeout;
    return connect(ip, port);
}

int ClientSecure::connect(const char *host, uint16_t port)
{
    if (client.pskIdent && client.psKey)
        return connect(host, port, client.pskIdent, client.psKey);
    return connect(host, port, client.ca_cert, client.certificate, client.private_key);
}

int ClientSecure::connect(const char *host, uint16_t port, int32_t timeout)
{
    client.timeout = timeout;
    return connect(host, port);
}

int ClientSecure::connect(IPAddress ip, uint16_t port, const char *_CA_cert, const char *_cert, const char *_private_key)
{
    return connect(ip.toString().c_str(), port, _CA_cert, _cert, _private_key);
}

int ClientSecure::connect(IPAddress ip, uint16_t port, const char *pskIdent, const char *psKey)
{
    return connect(ip.toString().c_str(), port, client.pskIdent, client.psKey);
}

int ClientSecure::connect(const char *host, uint16_t port, const char *_CA_cert, const char *_cert, const char *_private_key)
{
    client.psKey = NULL;
    client.pskIdent = NULL;
    if (ssl_begin(host, port, client.verify) < 0)
    {
        //DEBUG_SSL("[ERROR] ssl_begin 1\n");
        stop();
        return 0;
    }
    DEBUG_SSL("[SSL] CONNECTED\n");
    _connected = true;
    return 1;
}

int ClientSecure::connect(const char *host, uint16_t port, const char *pskIdent, const char *psKey)
{
    client.ca_cert = NULL;
    client.certificate = NULL;
    client.private_key = NULL;
    if (ssl_begin(host, port, client.verify) < 0)
    {
        //DEBUG_SSL("[ERROR] ssl_begin 2\n");
        stop();
        return 0;
    }
    DEBUG_SSL("[SSL] CONNECTED PSK\n");
    _connected = true;
    return 1;
}

uint8_t ClientSecure::connected()
{
    return _connected;
}

size_t ClientSecure::write(uint8_t data)
{
    return write(&data, 1);
}

size_t ClientSecure::write(const uint8_t *buf, size_t size)
{
    if (!_connected || NULL == buf || 0 == size)
        return 0;
    int rw = SSL_write(client.ssl, buf, size);
    if (rw < 1)
    {
        //DEBUG_SSL("[ERROR] SSL_write = %d\n", rw);
        stop();
        rw = 0;
    }
    return rw;
}

int ClientSecure::read()
{
    uint8_t data;
    return (read(&data, 1) == 1) ? data : -1;
}

int ClientSecure::read(uint8_t *buf, size_t size)
{
    if (!_connected || NULL == buf || 0 == size)
        return -1;
    int rd = SSL_read(client.ssl, buf, size);
    return (rd > 0) ? rd : -1;
}

int ClientSecure::available()
{
    if (!_connected)
        return 0;
    char buf[256];
    int rc = SSL_peek(client.ssl, buf, sizeof(buf));
    return (rc > 0) ? rc : 0;
}

int ClientSecure::peek()
{
    if (!_connected)
        return -1;
    char data;
    return SSL_peek(client.ssl, &data, 1) > 0 ? data : -1;
}

void ClientSecure::setCACert(const char *rootCA)
{
    client.ca_cert = rootCA;
}

void ClientSecure::setCertificate(const char *client_ca)
{
    client.certificate = client_ca;
}

void ClientSecure::setPrivateKey(const char *private_key)
{
    client.private_key = private_key;
}

void ClientSecure::setPreSharedKey(const char *pskIdent, const char *psKey)
{
    client.pskIdent = pskIdent;
    client.psKey = psKey;
}

char *ClientSecure::_streamLoad(Stream &stream, size_t size)
{
    static char *dest = nullptr;
    if (dest)
    {
        free(dest);
    }
    dest = (char *)malloc(size);
    if (!dest)
    {
        return nullptr;
    }
    if (size != stream.readBytes(dest, size))
    {
        free(dest);
        dest = nullptr;
    }
    return dest;
}

bool ClientSecure::loadCACert(Stream &stream, size_t size)
{
    char *dest = _streamLoad(stream, size);
    bool ret = false;
    if (dest)
    {
        setCACert(dest);
        ret = true;
    }
    return ret;
}

bool ClientSecure::loadCertificate(Stream &stream, size_t size)
{
    char *dest = _streamLoad(stream, size);
    bool ret = false;
    if (dest)
    {
        setCertificate(dest);
        ret = true;
    }
    return ret;
}

bool ClientSecure::loadPrivateKey(Stream &stream, size_t size)
{
    char *dest = _streamLoad(stream, size);
    bool ret = false;
    if (dest)
    {
        setPrivateKey(dest);
        ret = true;
    }
    return ret;
}

int ClientSecure::lastError(char *buf, const size_t size)
{
    if (!_lastError)
        return 0;
    //TODO SSL_ERROR_STRING
    return _lastError;
}

#else
#endif /* EX_MODE */