#ifndef AZURE_SAS_H
#define AZURE_SAS_H

#include <Arduino.h>
#include <Base64.h>

#define DBG_SAS
//Serial.printf

#include <sha256.h>

class AzureSAS
{
private:
    String SAS;

public:
    AzureSAS() { SAS = ""; }
    AzureSAS(const char *key, String url, uint32_t expire = 0)
    {
        SAS = create(key, url, expire);
    }

    static String urlEncode(const char *msg)
    {
        const char *hex = "0123456789abcdef";
        String encodedMsg = "";
        while (*msg != '\0')
        {
            if (('a' <= *msg && *msg <= 'z') || ('A' <= *msg && *msg <= 'Z') || ('0' <= *msg && *msg <= '9'))
            {
                encodedMsg += *msg;
            }
            else
            {
                encodedMsg += '%';
                encodedMsg += hex[*msg >> 4];
                encodedMsg += hex[*msg & 15];
            }
            msg++;
        }
        return encodedMsg;
    }

    String get()
    {
        return SAS;
    }

    String create(const char *key, String url, uint32_t expire)
    {
        if (expire == 0)
            expire = 1737504000; // Wed, 22 Jan 2025 00:00:00 GMT
        String URL = url;        // ?! make copy
        String stringToSign = url + "\n" + String(expire);
        DBG_SAS("stringToSign: %s \r\n", stringToSign.c_str());
        int keyLength = strlen(key);
        int decodedKeyLength = base64_dec_len((char *)key, keyLength);
        char decodedKey[decodedKeyLength];                 // allocate char array big enough for the base64 decoded key
        base64_decode(decodedKey, (char *)key, keyLength); // decode key
        Sha256.initHmac((const uint8_t *)decodedKey, decodedKeyLength);
        Sha256.print(stringToSign);
        char *sign = (char *)Sha256.resultHmac();
        // Get base64 of signature
        int encodedSignLen = base64_enc_len(32); // HASH_LENGTH
        char encodedSign[encodedSignLen];
        base64_encode(encodedSign, (char *)sign, 32); // HASH_LENGTH
        DBG_SAS("urlEncode: %s\n", urlEncode(encodedSign).c_str());
        // SharedAccessSignature
        SAS = "SharedAccessSignature sr=" + URL + "&sig=" + urlEncode(encodedSign) + "&se=" + String(expire);
        DBG_SAS("SAS: %s\n", SAS.c_str());
        return SAS;
    }

}; // AzureSAS

#endif /* AZURE_SAS_H */