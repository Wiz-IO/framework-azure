/// \file wificonfig.h
/// \brief This header contains functions that manage Wi-Fi network configurations on a device.
/// These functions are only permitted if the application has the WifiConfig capability
/// in its application manifest.
///
/// To use these functions, define WIFICONFIG_STRUCTS_VERSION in your source code with the structure
/// version you're using. Currently, the only valid version is 1.
///    \c \#define WIFICONFIG_STRUCTS_VERSION 1
/// Thereafter, you can use the friendly names of the WifiConfig_ structures, which start with
/// WifiConfig_.
///
/// These functions are not thread safe.
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/types.h>

#include <applibs/wificonfig_structs_v1.h>

#if WIFICONFIG_STRUCTS_VERSION == 1
/// <summary>
///     Alias to the z__WifiConfig_StoredNetwork_v1 structure. After you define
///     WIFICONFIG_STRUCTS_VERSION, you can refer to z__WifiConfig_StoredNetwork_v1
///     structures with this alias.
/// </summary>
typedef struct z__WifiConfig_StoredNetwork_v1 WifiConfig_StoredNetwork;
/// <summary>
///     Alias to the z__WifiConfig_ConnectedNetwork_v1 structure. After you define
///     WIFICONFIG_STRUCTS_VERSION, you can refer to z__WifiConfig_ConnectedNetwork_v1
///     structures with this alias.
/// </summary>
typedef struct z__WifiConfig_ConnectedNetwork_v1 WifiConfig_ConnectedNetwork;
/// <summary>
///     Alias to the z__WifiConfig_ScannedNetwork_v1 structure. After you define
///     WIFICONFIG_STRUCTS_VERSION, you can refer to z__WifiConfig_ScannedNetwork_v1
///     structures with this alias.
/// </summary>
typedef struct z__WifiConfig_ScannedNetwork_v1 WifiConfig_ScannedNetwork;
#else
#error To use applibs/wificonfig.h you must first #define WIFICONFIG_STRUCTS_VERSION
#endif

#include <applibs/wificonfig_internal.h>
#include <applibs/applibs_internal_api_traits.h>

/// <summary>
///     Stores an open Wi-Fi network without a key.
///     <para>This function will fail if an identical network is already stored on the device
///     without a key. See the error section (EEXIST). However, if a stored network includes a
///     key along with the same SSID, this function will succeed and store the network.</para>
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EEXIST: a stored Wi-Fi network that has the same SSID and no key already
///     exists.</para>
///     <para>EFAULT: the <paramref name="ssid"/> is NULL.</para>
///     <para>ERANGE: the <paramref name="ssidLength"/> is 0 or greater than <see
///     cref="WIFICONFIG_SSID_MAX_LENGTH"/>.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     <para>ENOSPC: there is no space left to store another Wi-Fi network.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <param name="ssid">
///     A pointer to an SSID byte array with unspecified character encoding that identifies the
///     Wi-Fi network.
/// </param>
/// <param name="ssidLength">
///     The number of bytes in the SSID of the Wi-Fi network.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
_AZSPHERE_DEPRECATED_BY(WifiConfig_AddNetwork)
int WifiConfig_StoreOpenNetwork(const uint8_t *ssid, size_t ssidLength);

/// <summary>
///     Stores a WPA2 Wi-Fi network that uses a pre-shared key.
///     <para>This function will fail if a network with the same SSID and pre-shared key is already
///     stored. See the error section(EEXIST).</para>
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EEXIST: a stored Wi-Fi network already exists that has the same SSID and uses
///     WPA2.</para>
///     <para>EFAULT: the <paramref name="ssid"> or <paramref name="psk"/> is NULL.</para>
///     <para>ERANGE: the <paramref name="ssidLength"/> or <paramref name="pskLength"/> is 0 or
///     greater than <see cref="WIFICONFIG_WPA2_KEY_MAX_BUFFER_SIZE"/> and <see
///     cref="WIFICONFIG_SSID_MAX_LENGTH"/>.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     <para>ENOSPC: there is no space left to store another Wi-Fi network.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <param name="ssid">
///     A pointer to an SSID byte array with unspecified character encoding that identifies the
///     Wi-Fi network.
/// </param>
/// <param name="ssidLength">
///     The number of bytes in the <paramref name="ssid"> of the Wi-Fi network.
/// </param>
/// <param name="psk">
///     A pointer to a buffer that contains the pre-shared key for the Wi-Fi network.
/// </param>
/// <param name="pskLength">
///     The length of the pre-shared key for the Wi-Fi network.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
_AZSPHERE_DEPRECATED_BY(WifiConfig_AddNetwork)
int WifiConfig_StoreWpa2Network(const uint8_t *ssid, size_t ssidLength, const char *psk,
                                size_t pskLength);

/// <summary>
///     Removes a Wi-Fi network from the device. Disconnects the device from the
///     network if it's currently connected.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EFAULT: the <paramref name="storedNetwork"/> is NULL.</para>
///     <para>ENOENT: the <paramref name="storedNetwork"/> does not match any of the stored
///     networks.</para>
///     <para>EINVAL: the <paramref name="storedNetwork"/> or its struct version is invalid.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
///     <para>ENOSPC: there are too many Wi-Fi networks to persist the config; remove one
///     and try again.</para>
/// </summary>
/// <param name="storedNetwork">
///     Pointer to a <see cref="WifiConfig_StoredNetwork"/> struct that describes the stored Wi-Fi
///     network to remove.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
_AZSPHERE_DEPRECATED_BY(WifiConfig_ForgetNetworkById)
static int WifiConfig_ForgetNetwork(const WifiConfig_StoredNetwork *storedNetwork);

/// <summary>
///     Removes a Wi-Fi network from the device. Disconnects the device from the
///     network if it's currently connected.
///     The change is effective immediately but will be lost across a reboot unless the <see
///     cref="WifiConfig_PersistConfig"/> function is called after this function.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EINVAL: the <paramref name="networkId"/> is invalid.</para>
///     <para>ENODEV: the <paramref name="networkId"/> does not match any of the stored
///     networks.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <param name="networkId">
///     The network ID for the network to be removed.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
int WifiConfig_ForgetNetworkById(int networkId);

/// <summary>
///     Removes all stored Wi-Fi networks from the device. Disconnects the device from
///     any connected network. The removal is persisted across a device reboot.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
int WifiConfig_ForgetAllNetworks(void);

/// <summary>
///     Gets the number of stored Wi-Fi networks on the device.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <returns>
///     The number of Wi-Fi networks stored on the device, or -1 for failure, in which case errno
///     is set to the error value.
/// </returns>
ssize_t WifiConfig_GetStoredNetworkCount(void);

/// <summary>
///     Retrieves all stored Wi-Fi networks on the device.
///     <para>If <paramref name="storedNetworkArray"/> is too small to hold all the stored Wi-Fi
///     networks, this function fills the array and returns the number of array elements.</para>
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EFAULT: the <paramref name="storedNetworkArray"/> is NULL.</para>
///     <para>ERANGE: the <paramref name="storedNetworkArrayCount"/> is 0.</para>
///     <para>EINVAL: the <paramref name="storedNetworkArray"/> struct version is invalid.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <param name="storedNetworkArray">
///     A pointer to an array that returns the stored Wi-Fi networks.
/// </param>
/// <param name="storedNetworkArrayCount">
///     The number of elements <paramref name="storedNetworkArray"/> can hold. The array should have
///     one element for each stored Wi-Fi network.
/// </param>
/// <returns>
///     The number of elements in the WifiConfig_StoredNetwork array, or -1 for failure,
///     in which case errno is set to the error value.
/// </returns>
static ssize_t WifiConfig_GetStoredNetworks(WifiConfig_StoredNetwork *storedNetworkArray,
                                            size_t storedNetworkArrayCount);

/// <summary>
///     Gets the Wi-Fi network that is connected to the device.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EFAULT: the <paramref name="connectedNetwork"/> is NULL.</para>
///     <para>ENOTCONN: the device is not currently connected to any network.</para>
///     <para>EINVAL: the <paramref name="connectedNetwork"/> or its struct version is
///     invalid.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <param name="connectedNetwork">
///     A pointer to a struct that returns the connected Wi-Fi network.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
static int WifiConfig_GetCurrentNetwork(WifiConfig_ConnectedNetwork *connectedNetwork);

/// <summary>
///     Starts a scan to find all available Wi-Fi networks.
///     <para>This is a blocking call.</para>
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
/// </summary>
/// <returns>
///     The number of networks found, or -1 for failure, in which case errno is set to the error
///     value.
/// </returns>
ssize_t WifiConfig_TriggerScanAndGetScannedNetworkCount(void);

/// <summary>
///     Gets the Wi-Fi networks found by the last scan operation.
///     <para>If scannedNetworkArray is too small to hold all the networks, this function fills all
///     the elements and returns the number of array elements.</para>
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EFAULT: the <paramref name="scannedNetworkArray"/> is NULL.</para>
///     <para>ERANGE: the <paramref name="scannedNetworkArrayCount"/> is 0.</para>
///     <para>EINVAL: the <paramref name="scannedNetworkArray"/> or its struct version is
///     invalid. </para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <param name="scannedNetworkArray">
///     A pointer to an array that returns the retrieved Wi-Fi networks.
/// </param>
/// <param name="scannedNetworkArrayCount">
///     The number of elements scannedNetworkArray can hold. The array should have one element for
///     each Wi-Fi network found by the last scan operation.
/// </param>
/// <returns>
///     The number of elements returned by scannedNetworkArray, or -1 for failure, in
///     which case errno is set to the error value.
/// </returns>
static ssize_t WifiConfig_GetScannedNetworks(WifiConfig_ScannedNetwork *scannedNetworkArray,
                                             size_t scannedNetworkArrayCount);

/// <summary>
///     Adds an unconfigured new network to be configured using the WifiConfig_Setxxx APIs such as
///     <see cref="WifiConfig_SetSSID"/>.
///     Any change in the network configuration is effective immediately but
///     will be lost across a reboot unless the <see cref="WifiConfig_PersistConfig"/> function is
///     called to save the configuration to nonvolatile storage.
///     <para> **Errors** </para> If an error is encountered, returns -1 and sets errno to the error
///     value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <returns>
///     The network ID of the new network (non-negative value), or -1 for failure, in which
///     case errno is set to the error value. The network ID is passed to
///     WifiConfig_Setxxx APIs as the identifier for the network to be configured.
/// </returns>
int WifiConfig_AddNetwork(void);

/// <summary>
///     Sets the SSID for the network.
///     The setting is effective immediately but will be lost across a reboot unless the <see
///     cref="WifiConfig_PersistConfig"/> function is called after this function.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EFAULT: the <paramref name="ssid"> is NULL.</para>
///     <para>ERANGE: the <paramref name="ssidLength"/> is 0 or greater than <see
///     cref="WIFICONFIG_SSID_MAX_LENGTH"/>.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     <para>EINVAL: the <paramref name="networkId"/> is invalid.</para>
///     <para>ENODEV: the <paramref name="networkId"/> does not match any of the stored
///     networks.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <param name="networkId">
///     The network ID for the network to be configured. The network ID is returned by
///     <see cref="WifiConfig_AddNetwork"/>.
/// </param>
/// <param name="ssid">
///     A pointer to an SSID byte array with unspecified character encoding that identifies
///     the Wi-Fi network.
/// </param>
/// <param name="ssidLength">
///     The number of bytes in the <paramref name="ssid"> of the Wi-Fi network.
///     Must be less than or equals to <see cref="WIFICONFIG_SSID_MAX_LENGTH"/>.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
static int WifiConfig_SetSSID(int networkId, const uint8_t *ssid, size_t ssidLength);

/// <summary>
///     Sets the security type for the network.
///     The setting is effective immediately but will be lost across a reboot unless the <see
///     cref="WifiConfig_PersistConfig"/> function is called after this function.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig
///     capability.</para>
///     <para>EINVAL: the <paramref name="securityType"/> is an invalid value. </para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     <para>EINVAL: the <paramref name="networkId"/> is invalid.</para>
///     <para>ENODEV: the <paramref name="networkId"/> does not match any of the stored
///     networks.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <param name="networkId">
///     The network ID for the network to be configured. The network ID is returned by
///     <see cref="WifiConfig_AddNetwork"/>.
/// </param>
/// <param name="securityType">
///     The security type for the specified network.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
static int WifiConfig_SetSecurityType(int networkId, WifiConfig_Security_Type securityType);

/// <summary>
///     Enables or disables the specified network configuration.
///     The setting is effective immediately but will be lost across a reboot unless the <see
///     cref="WifiConfig_PersistConfig"/> function is called after this function.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     <para>EINVAL: the <paramref name="networkId"/> is invalid.</para>
///     <para>ENODEV: the <paramref name="networkId"/> does not match any of the stored
///     networks.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <param name="networkId">
///     The network ID for the network to be configured. The network ID is returned by
///     <see cref="WifiConfig_AddNetwork"/>.
/// </param>
/// <param name="enabled">
///      A boolean value indicating whether the network should be enabled (true) or
///      disabled (false).
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
static int WifiConfig_SetNetworkEnabled(int networkId, bool enabled);

/// <summary>
///     Writes the current configuration for the network to nonvolatile storage so that
///     it will persist over a device reboot.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     <para>ENOSPC: there are too many Wi-Fi networks to persist the config; remove one
///     and try again.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
static int WifiConfig_PersistConfig(void);

/// <summary>
///     Sets the Pre-Shared Key (PSK) for the network. The PSK is used for
///     networks configured with the WifiConfig_Security_Wpa2_Psk security type.
///     The setting is effective immediately but will be lost across a reboot unless the <see
///     cref="WifiConfig_PersistConfig"/> function is called after this function.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EFAULT: the <paramref name="psk"> is NULL.</para>
///     <para>ERANGE: the <paramref name="pskLength"/> greater than
///     <see cref="WIFICONFIG_WPA2_KEY_MAX_BUFFER_SIZE"/>.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     <para>EINVAL: the <paramref name="networkId"/> is invalid.</para>
///     <para>ENODEV: the <paramref name="networkId"/> does not match any of the stored
///     networks.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <param name="networkId">
///     The network ID for the network to be configured. The network ID is returned by
///     <see cref="WifiConfig_AddNetwork"/>.
/// </param>
/// <param name="psk">
///     A pointer to a buffer that contains the pre-shared key for the Wi-Fi network.
/// </param>
/// <param name="pskLength">
///     The length of the pre-shared key for the Wi-Fi network. Must be less than or
///     equals to <see cref="WIFICONFIG_WPA2_KEY_MAX_BUFFER_SIZE"/>.
/// </param>
/// <returns>
///     0 for success, or -1 for failure, in which case errno is set to the error value.
/// </returns>
static int WifiConfig_SetPSK(int networkId, const char *psk, size_t pskLength);

/// <summary>
///     Enables or disables targeted scanning for the network. Targeted scanning
///     is used to connect to access points that are not broadcasting their
///     SSID or to connect to an access point in a noisy environment. Targeted
///     scanning is disabled by default.
///     N.B. that enabling targeted scanning will cause the device to transmit
///     probe requests with the SSID of the network. Use this only if other
///     devices possibly discovering the SSID of the access point you are trying
///     to connect to is a non-issue.
///     The setting is effective immediately but will be lost across a reboot unless the <see
///     cref="WifiConfig_PersistConfig"/> function is called after this function.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the WifiConfig capability.</para>
///     <para>EAGAIN: the Wi-Fi device isn't ready yet.</para>
///     <para>ENETDOWN: the Wi-Fi network interface is not available.</para>
///     <para>EINVAL: the <paramref name="networkId"/> is invalid.</para>
///     <para>ENODEV: the <paramref name="networkId"/> does not match any of the stored
///     networks.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behavior will be retained through system updates.
/// </summary>
/// <param name="networkId">
///     The network ID for the network to be configured. The network ID is returned by
///     <see cref="WifiConfig_AddNetwork"/>.
/// </param>
/// <param name="enabled">
///      A boolean value indicating whether targeted scanning for the network should be
///      enabled (true) or disabled (false).
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
static int WifiConfig_SetTargetedScanEnabled(int networkId, bool enabled);

#ifdef __cplusplus
}
#endif
