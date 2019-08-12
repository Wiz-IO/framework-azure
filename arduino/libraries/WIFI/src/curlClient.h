/*
    Created on: 01.01.2019
    Author: Georgi Angelov
        http://www.wizio.eu/
        https://github.com/Wiz-IO    
		
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

#ifndef curlClient_H_
#define curlClient_H_

#include <Arduino.h>
#include <curl/curl.h>
#include <applibs/networking.h>
#include <applibs/storage.h>

#include <variant.h>
#define DEBUG_CURL 
//Serial.printf

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
    //DEBUG_CURL("[CURL] callback\n");
    MemoryBlock *block = (MemoryBlock *)memoryBlock;
    size_t additionalDataSize = chunkSize * chunksCount;
    block->data = (char *)realloc(block->data, block->size + additionalDataSize + 1);
    if (block->data == NULL)
    {
      DEBUG_CURL("[ERROR] CURL callback\n");
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
    if (block.data)
    {
      free(block.data); // Clean up allocated memory.
      block.data = NULL;
      block.size = 0;
    }
    if (certificatePath)
    {
      free(certificatePath);
      certificatePath = NULL;
    }
    if (curlHandle)
    {
      curl_easy_cleanup(curlHandle); // Clean up sample's cURL resources.
      curl_global_cleanup();         // Clean up cURL library's resources.
      curlHandle = NULL;
    }
    //DEBUG_CURL("[CURL] end()\n");
  }

  int setopt(CURLoption opt, void *param)
  {
    int res = -1;
    if (curlHandle)
    {
      if ((res = curl_easy_setopt(curlHandle, opt, param)) != CURLE_OK) // 0
      {
        DEBUG_CURL("[ERROR] curl_easy_setopt\n");
      }
      else
      {
        //DEBUG_CURL("[CURL] SETOPT: %d = 0x%08X\n", (int)opt, param);
      }
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
        DEBUG_CURL("[ERROR] curl_easy_init\n");
        end();
        res = -1;
      }
      CURL_SETOPT(CURLOPT_WRITEFUNCTION, StoreDownloadedDataCallback);
      CURL_SETOPT(CURLOPT_WRITEDATA, &block);
      CURL_SETOPT(CURLOPT_USERAGENT, "AzureSphere");
      CURL_SETOPT(CURLOPT_FOLLOWLOCATION, 1L);
    }
    else
    {
      DEBUG_CURL("[ERROR] curl_global_init\n");
    }
    return res;
  }

  int begin(const char *url)
  {
    int rc = -1;
    if (url && CURLE_OK == (rc = begin()))
    {
      //DEBUG_CURL("[CURL] SETOPT URL: %s\n", url);
      CURL_SETOPT(CURLOPT_URL, url);
    }
    return rc;
  }

  int run(MemoryBlock **data)
  {
    int rc = -1;
    if (curlHandle)
    {
      //DEBUG_CURL("[CURL] run()\n");
      if ((rc = curl_easy_perform(curlHandle)) != CURLE_OK)
      {
        DEBUG_CURL("[ERROR] curl_easy_perform: %d\n", rc);
        end();
        *data = NULL;
      }
      else
      {
        //DEBUG_CURL("\n -===- Downloaded content (%zu bytes): -===-\n", block.size);
        *data = &block;
      }
    }
    return rc;
  }

#ifdef SYSROOT_2_BETA1905
  void storage(const char *path)
  {
    certificatePath = Storage_GetAbsolutePathInImagePackage(path); // 2+Beta1905 "certs/DigiCertGlobalRootCA.pem"
    if (certificatePath == NULL)
    {
      DEBUG_CURL("[ERROR] The certificate path could not be resolved\n");
    }
    else
    {
      CURL_SETOPT(CURLOPT_CAINFO, path);
    }
  }
#endif
};

#endif /* curlClient_H_ */
