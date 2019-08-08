/// \file networking.h
/// \brief This header contains functionality for interacting with the networking
/// subsystem. It defines methods for querying network state and for getting &
/// setting network service configuration. The functions described in this header that
/// change state are only permitted if the application has the capability noted in the function
/// summary in its application manifest.
///
/// The default version of the networking structs(NETWORKING_STRUCTS_VERSION) is 1. Currently this
/// is the only valid version. These functions are not thread safe.
#pragma once

#include <stdbool.h>

#include <applibs/networking_internal.h>
#include <applibs/applibs_internal_versioning.h>

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
///     Verifies whether internet connectivity is available.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the provided <paramref name="outIsNetworkingReady"/> is NULL.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="outIsNetworkingReady">
///      A pointer to a boolean that returns the result. This value is set to true if
///      networking is ready, otherwise false.
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_IsNetworkingReady(bool *outIsNetworkingReady);


#ifdef __cplusplus
}
#endif
