#pragma once

#include <stdint.h>
#include <curl/curl.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef enum DeviceAuthSslResult {
    /// <summary> Success. </summary>
    DeviceAuthSslResult_Success = 0,
    /// <summary> Accessing the current applications tenant id failed. </summary>
    DeviceAuthSslResult_GetTenantIdError = 1,
    /// <summary> Loading the device auth certificate for this tenant failed. </summary>
    DeviceAuthSslResult_GetTenantCertificateError = 2,
    /// <summary> Enabling the HW sign operation failed. </summary>
    DeviceAuthSslResult_EnableHwSignError = 3,

} DeviceAuthSslResult;

/// <summary>
/// Simple curl ssl function to be passed to curl via CURLOPT_SSL_CTX_FUNCTION.
/// Sets up the curl connection to do mutual auth with the endpoint, using the
/// current application's deviceauth credentials. Function signature matches
/// that of a curl callback, but only sslctx is directly modified. Returns
/// CURLE_CERTPROBLEM on error or CURLE_OK on success.
/// </summary>
CURLcode DeviceAuth_CurlSslFunc(CURL *curl, void *sslctx, void *userCtx);

/// <summary>
/// This is the minimal ssl function that can be invoked from within a curl ssl
/// function. This allows the user to potentially do other things to the curl
/// object in their user-defined ssl function, as well as handle errors on a
/// more fine grained basis.
/// </summary>
DeviceAuthSslResult DeviceAuth_SslCtxFunc(void *sslctx);


#ifdef __cplusplus
}
#endif
