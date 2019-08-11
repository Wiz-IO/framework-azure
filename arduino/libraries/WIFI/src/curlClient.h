/*
  Copyright (c) 2013-2014 Arduino LLC. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef curlClient_H_
#define curlClient_H_

#include <Arduino.h>
#include <curl/curl.h>
#include <applibs/networking.h>
#include <applibs/storage.h>
#include <applibs/log.h>

#define CURL_SETOPT(O, P) setopt(O, (void *)P)

typedef struct
{
  char *data;
  size_t size;
} MemoryBlock;

class curlClient
{
private:
  CURL *curlHandle;
  MemoryBlock block;
  char *certificatePath;

  static size_t StoreDownloadedDataCallback(void *chunks, size_t chunkSize, size_t chunksCount, void *memoryBlock)
  {
    MemoryBlock *block = (MemoryBlock *)memoryBlock;
    size_t additionalDataSize = chunkSize * chunksCount;
    block->data = (char *)realloc(block->data, block->size + additionalDataSize + 1);
    if (block->data == NULL)
    {
      //Log_Debug("Out of memory, realloc returned NULL: errno=%d (%s)'n", errno, strerror(errno));
      abort();
    }
    memcpy(block->data + block->size, chunks, additionalDataSize);
    block->size += additionalDataSize;
    block->data[block->size] = 0; // Ensure the block of memory is null terminated.
    return additionalDataSize;
  }

public:
  curlClient()
  {
    CURL *curlHandle = NULL;
    MemoryBlock block = {.data = NULL, .size = 0};
    char *certificatePath = NULL;
  }

  void end()
  {
    free(block.data);              // Clean up allocated memory.
    free(certificatePath);         //
    curl_easy_cleanup(curlHandle); // Clean up sample's cURL resources.
    curl_global_cleanup();         // Clean up cURL library's resources.
    curlHandle = NULL;
  }

  int setopt(CURLoption opt, void *param)
  {
    int res = -1;
    if (curlHandle)
      if ((res = curl_easy_setopt(curlHandle, opt, param)) != CURLE_OK) //0
      {
        //LogError();
        end();
      }
    return res;
  }

  int begin()
  {
    int res;
    if ((res = curl_global_init(CURL_GLOBAL_ALL)) == CURLE_OK) // Init the cURL library.
    {
      if ((curlHandle = curl_easy_init()) == NULL)
      {
        //Log_Debug("curl_easy_init() failed\n");
        end();
        res = -1;
      }
      CURL_SETOPT(CURLOPT_WRITEFUNCTION, StoreDownloadedDataCallback);
      CURL_SETOPT(CURLOPT_WRITEDATA, (void *)&block);
      CURL_SETOPT(CURLOPT_USERAGENT, "libcurl-agent/1.0");  
      CURL_SETOPT(CURLOPT_FOLLOWLOCATION, 1L);    
    }
    return res;
  }

  int run(MemoryBlock **data)
  {
    int res = -1;
    if (curlHandle)
      if ((res = curl_easy_perform(curlHandle)) != CURLE_OK)
      {
        //LogCurlError();
      }
      else
      {
        //Log_Debug("\n -===- Downloaded content (%zu bytes): -===-\n", block.size);
        //Log_Debug("%s\n", block.data);
        *data = &block;
      }
    return res;
  }

#ifdef SYSROOT_2_BETA1905
  void storage(const char *path)
  {
    // Get the full path to the certificate file used to authenticate the HTTPS server identity.
    // The DigiCertGlobalRootCA.pem file is the certificate that is used to verify the server identity.
    // certificatePath = Storage_GetAbsolutePathInImagePackage(path); // ?!?! "certs/DigiCertGlobalRootCA.pem" 2+Beta1905
    if (certificatePath == NULL)
    {
      Log_Debug("The certificate path could not be resolved: errno=%d (%s)\n", errno, strerror(errno));
      end();
    }
  }
#endif


};

#endif /* curlClient_H_ */
