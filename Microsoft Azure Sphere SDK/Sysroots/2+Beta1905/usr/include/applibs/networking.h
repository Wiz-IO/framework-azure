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
#include <applibs/networking_structs_v1.h>

// Default the NETWORKING_STRUCTS_VERSION version to 1
#ifndef NETWORKING_STRUCTS_VERSION
#define NETWORKING_STRUCTS_VERSION 1
#endif

#if NETWORKING_STRUCTS_VERSION == 1
/// <summary>
///     Alias to the z__Networking_NetworkInterface_v1 structure. After you define
///     NETWORKING_STRUCTS_VERSION, you can refer to z__Networking_NetworkInterface_v1
///     structures with this alias.
/// </summary>
typedef struct z__Networking_NetworkInterface_v1 Networking_NetworkInterface;

/// <summary>
///     Alias to the z__Networking_StaticIpConfiguration_v1 structure. After you define
///     NETWORKING_STRUCTS_VERSION, you can refer to z__Networking_StaticIpConfiguration_v1
///     structures with this alias.
/// </summary>
typedef struct z__Networking_StaticIpConfiguration_v1 Networking_StaticIpConfiguration;

/// <summary>
///     Alias to the z__Networking_DhcpServerConfiguration_v1 structure. After you define
///     NETWORKING_STRUCTS_VERSION, you can refer to z__Networking_DhcpServerConfiguration_v1
///     structures with this alias.
/// </summary>
typedef struct z__Networking_DhcpServerConfiguration_v1 Networking_DhcpServerConfiguration;

#else // NETWORKING_STRUCTS_VERSION
#error NETWORKING_STRUCTS_VERSION is set to an unsupported value. Only version 1 is currently supported.
#endif // NETWORKING_STRUCTS_VERSION

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


/// <summary>
///     The network interface's connection status.
/// </summary>
typedef enum Networking_InterfaceConnectionStatus {
    /// <summary>Indicates that the interface is up </summary>
    Networking_InterfaceConnectionStatus_InterfaceUp = 1 << 0,
    /// <summary>Indicates that the interface is connected to a network</summary>
    Networking_InterfaceConnectionStatus_ConnectedToNetwork = 1 << 1,
    /// <summary>Indicates that the interface has an IP address assigned to it</summary>
    Networking_InterfaceConnectionStatus_IpAvailable = 1 << 2,
    /// <summary>Indicates that the interface is connected to internet</summary>
    Networking_InterfaceConnectionStatus_ConnectedToInternet = 1 << 3
} Networking_InterfaceConnectionStatus;

/// <summary>
///     Gets the number of registered network interfaces in the Azure Sphere device.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behaviour will be retained through system updates.
/// </summary>
/// <returns>
///     If the call is successful, the number of registered network interfaces is returned.
///     Otherwise it returns -1 for failure, in which case errno is set to the error value.
/// </returns>
ssize_t Networking_GetInterfaceCount(void);

/// <summary>
///     Gets the list of registered network interfaces in the Azure Sphere device. If <paramref
///     name="outNetworkInterfacesArray"/> is too small to hold all network interfaces in the
///     system, this function uses the available space and returns the total number of interfaces
///     it is able to provide. The total number of interfaces in the system will not change within a
///     boot cycle.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the <paramref name="outNetworkInterfacesArray"/> is NULL.</para>
///     <para>ERANGE: the <paramref name="networkInterfacesArrayCount"/> is 0.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="outNetworkInterfacesArray">
///      A pointer to the array, <see cref="Networking_NetworkInterface"/> to populate with
///      network interface properties. The caller needs to allocate memory for this after calling
///      <see cref="Networking_GetInterfacesCount" /> to find out the number of interfaces.
/// </param>
/// <param name="networkInterfacesArrayCount">
///      The number of elements <paramref name="outNetworkInterfacesArray"/> can hold. The array
///      should have one element for each network interface in the device.
/// </param>
/// <returns>
///     If the call is successful, the number of network interfaces populated in the <paramref
///     name="outNetworkInterfacesArray"/> is returned. On failure, -1 is returned, in which case
///     errno is set to the error value.
/// </returns>
static ssize_t Networking_GetInterfaces(Networking_NetworkInterface *outNetworkInterfacesArray,
                                        size_t networkInterfacesArrayCount);

/// <summary>
///     Sets the interface state to enabled or disabled.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the NetworkConfig capability.</para>
///     <para>ENOENT: no such interface if an invalid interface is passed in.</para>
///     <para>EPERM: this is not allowed on the interface mentioned.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The name of the network interface whose state needs to be toggled
/// </param>
/// <param name="isEnabled">
///      The boolean containing the value true for Enabling the interface, false for Disabling the
///      interface
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_SetInterfaceState(const char *networkInterfaceName, bool isEnabled);

/// <summary>
///     Initializes a <see cref="Networking_StaticIpConfiguration"/> struct with the default static
///     IP configuration.
/// </summary>
/// <param name="staticIpConfiguration">
///     A pointer to a <see cref="Networking_StaticIpConfiguration"/> struct that returns the
///     default static IP parameters.
/// </param>
/// <remarks>
///     This API is obsolete. Use <see cref="Networking_IpConfig_Init"/> instead.
/// </remarks>
_AZSPHERE_OBSOLETED_BY(Networking_IpConfig_Init)
static inline void Networking_InitStaticIpConfiguration(
    Networking_StaticIpConfiguration *staticIpConfiguration);

/// <summary>
///     Sets the static IP configuration for the interface specified. No checking is done that this
///     static IP address is compatible with dynamic IP addresses received through an interface
///     using DHCP client.  If overlapping IP address configurations are present on a device, the
///     behaviour is undefined.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the NetworkConfig capability.</para>
///     <para>ENOENT: the <see cref="networkInterfaceName/> interface does not exist.</para>
///     <para>EPERM:  this operation is not allowed on the network interface.</para>
///     <para>EFAULT: the <paramref name="staticIpConfiguration"/> is NULL.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The string specifying the network interface to configure
/// </param>
/// <param name="staticIpConfiguration">
///      The pointer to the <see cref="Networking_StaticIpConfiguration" /> that indicates the
///      static IP configuration
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
/// <remarks>
///     This API is obsolete. To configure the static IP, use <see
///     cref="Networking_IpConfig_EnableStaticIp"/> on a <see cref="Networking_IpConfig"/>
///     initialized struct, then apply it with <see cref="Networking_IpConfig_Apply"/>.
/// </remarks>
_AZSPHERE_OBSOLETED_BY(Networking_IpConfig_Apply)
int Networking_SetStaticIp(const char *networkInterfaceName,
                           const Networking_StaticIpConfiguration *staticIpConfiguration);

/// <summary>
///     Initializes a <see cref="Networking_IpConfig"/> struct with the default IP
///     configuration.
/// </summary>
/// <param name="ipConfig">
///     A pointer to a <see cref="Networking_IpConfig"/> struct that returns the default IP
///     configuration. Dynamic IP is enabled by default.
/// </param>
void Networking_IpConfig_Init(Networking_IpConfig *ipConfig);

/// <summary>
///     Modifies a <see cref="Networking_IpConfig"/> struct to have dynamic IP enabled and
///     static IP disabled.
/// </summary>
/// <param name="ipConfig">
///     A pointer to a <see cref="Networking_IpConfig"/> struct that enables dynamic IP and
///     disables static IP.
/// </param>
void Networking_IpConfig_EnableDynamicIp(Networking_IpConfig *ipConfig);

/// <summary>
///     Modifies an <see cref="Networking_IpConfig"/> to enable static IP and disable dynamic
///     IP.
/// </summary>
/// <param name="ipConfig">
///     A pointer to a <see cref="Networking_IpConfig"/> struct that enables and configures
/// static IP and disables dynamic IP.
/// </param>
/// <param name="ipAddress"> The desired static IP address. </param>
/// <param name="subnetMask"> The desired static subnet mask. </param>
/// <param name="gatewayAddress"> The desired static gateway address. </param>
void Networking_IpConfig_EnableStaticIp(Networking_IpConfig *ipConfig, struct in_addr ipAddress,
                                        struct in_addr subnetMask, struct in_addr gatewayAddress);

/// <summary>
///     Applies the IP configuration to the interface specified. No checking is done that the static
///     IP address (if any) is compatible with dynamic IP addresses received through an interface
///     using DHCP client.  No checking is done that a DHCP server is available on the network if a
///     dynamic IP address is configured. If overlapping IP address configurations are present on a
///     device, the behaviour is undefined.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the NetworkConfig capability.</para>
///     <para>ENOENT: the <see cref="networkInterfaceName/> interface does not exist.</para>
///     <para>EPERM:  this operation is not allowed on the network interface.</para>
///     <para>EFAULT: <paramref name="networkInterfaceName"/> or <paramref name="ipConfig"/>
///     is NULL.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behavior will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The string specifying the network interface to configure
/// </param>
/// <param name="ipConfig">
///      The pointer to the <see cref="Networking_IpConfig" /> that indicates the IP
///      configuration.
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_IpConfig_Apply(const char *networkInterfaceName,
                              const Networking_IpConfig *ipConfig);

/// <summary>
///     Destroys a <see cref="Networking_IpConfig"/> struct.
/// </summary>
/// <param name="ipConfig">
///     A pointer to a <see cref="Networking_IpConfig"/> struct to destroy.
/// </param>
void Networking_IpConfig_Destroy(Networking_IpConfig *ipConfig);

/// <summary>
///     Enables or disables the time-sync service. Changes take effect immediately without a
///     device reboot and are persisted. The time-sync service is then configured as requested at
///     boot time. This function allows applications to override the default behaviour which is to
///     enable time-sync at boot.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the calling application doesn't have the TimeSyncConfig capability.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="enabled">
///      A boolean value indicating whether the time-sync service should be enabled (true) or
///      disabled (false).
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_TimeSync_SetEnabled(bool enabled);

/// <summary>
///     Sets the enabled state of the NTP time-sync service to the value provided. Changes take
///     effect immediately without a device reboot and are persisted. The NTP service is then
///     configured as requested at boot time. This function allows applications to override the
///     default behaviour which is to enable NTP at boot.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the calling application doesn't have the NetworkConfig capability.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="isEnabled">
///      A boolean value indicating whether the NTP service should be enabled (true) or disabled
///      (false).
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
/// <remarks>
///     This API is obsolete. Use <see cref="Networking_TimeSync_SetEnabled"/> instead.
/// </remarks>
_AZSPHERE_OBSOLETED_BY(Networking_TimeSync_SetEnabled)
int Networking_SetNtpState(bool isEnabled);

/// <summary>
///     Gets the current enable state of the time-sync service.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the output parameter (outIsEnabled) provided is null.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="outIsEnabled">
///      A pointer to a boolean value that receives the current enable state.
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_TimeSync_GetEnabled(bool *outIsEnabled);

/// <summary>
///     Gets the current enable state of the NTP time-sync service.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the output parameter (outIsEnabled) provided is null.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="outIsEnabled">
///      A pointer to a boolean value that receives the current enable state.
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
/// <remarks>
///     This API is obsolete. Use <see cref="Networking_TimeSync_GetEnabled"/> instead.
/// </remarks>
_AZSPHERE_OBSOLETED_BY(Networking_TimeSync_GetEnabled)
int Networking_GetNtpState(bool *outIsEnabled);

/// <summary>
///     Registers and starts SNTP server for the interface specified. If the SNTP
///     server is already running and attached to the specified interface this function returns
///     success. If the <see cref="networkInterfaceName/> interface is down or disabled, then
///     the SNTP server service is registered for the interface but will not start it.
///     <para>**Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the NetworkConfig
///     capability.</para>
///     <para>EFAULT: the <see cref="networkInterfaceName/> is NULL.</para>
///     <para>ENOENT: the <see cref="networkInterfaceName/> interface does
///     not exist.</para>
///     <para>EPERM:  this operation is not allowed on the network
///     interface.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The string specifying the network interface in which SNTP server should run.
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
/// <remarks>
///     This API is obsolete. Use <see cref="Networking_SntpServer_Start"/> instead.
/// </remarks>
_AZSPHERE_OBSOLETED_BY(Networking_SntpServer_Start)
int Networking_StartSntpServer(const char *networkInterfaceName);

/// <summary>
///     Initializes a <see cref="Networking_DhcpServerConfiguration"/> struct with the DHCP server
///     parameters.
/// </summary>
/// <param name="dhcpServerConfiguration">
///     A pointer to a <see cref="Networking_DhcpServerConfiguration"/> struct that returns the
///     default DHCP server parameters.
/// </param>
/// <remarks>
///     This API is obsolete. Use <see cref="Networking_DhcpServerConfig_Init"/> instead.
/// </remarks>
_AZSPHERE_OBSOLETED_BY(Networking_DhcpServerConfig_Init)
static inline void Networking_InitDhcpServerConfiguration(
    Networking_DhcpServerConfiguration *dhcpServerConfiguration);

/// <summary>
///     Registers and starts the DHCP server for the interface specified. The configuration
///     parameters specified through this function call will overwrite any existing
///     configuration.
///     If the interface specified is up, the DHCP server service will be shut
///     down, configured and started. If the interface is down, the service will be started when
///     the interface is up.
///     The interface specified must be configured with a static IP address first before calling
///     this function. Otherwise, EPERM will be returned.
///     <para> **Errors** </para> If an error is encountered, returns -1 and sets errno to the error
///     value.
///     <para>EACCES: the application manifest does not include the NetworkConfig capability.</para>
///     <para>ENOENT: the <see cref="networkInterfaceName/> interface does not exist.</para>
///     <para>EPERM:  this operation is not allowed on the network interface.</para>
///     <para>EFAULT: the <paramref name="dhcpServerConfiguration"/> is NULL.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     <para>EINVAL: invalid parameters in configuration structure.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The string specifying the network interface to configure
/// </param>
/// <param name="dhcpServerConfiguration">
///      The pointer to the <see cref="Networking_DhcpServerConfiguration" /> that indicates the
///      DHCP server configuration
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
/// <remarks>
///     This API is obsolete. Use <see cref="Networking_DhcpServer_Start"/> instead.
/// </remarks>
_AZSPHERE_OBSOLETED_BY(Networking_DhcpServer_Start)
int Networking_StartDhcpServer(const char *networkInterfaceName,
                               const Networking_DhcpServerConfiguration *dhcpServerConfiguration);

/// <summary>
///     Gets the Network connection status for the interface specified
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the <paramref name="outStatus"/> is NULL.</para>
///     <para>ENOENT: the <see cref="networkInterfaceName/> interface does not exist.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The string specifying the network interface for which the connectivity status has to be
///      returned.
/// </param>
/// <param name="outStatus">
///      A pointer to the enum containing the bitmask, <see
///      cref="Networking_InterfaceConnectionStatus"/> to populate with network connectivity status.
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_GetInterfaceConnectionStatus(const char *networkInterfaceName,
                                            Networking_InterfaceConnectionStatus *outStatus);

/// <summary>
///     Initializes a <see cref="Networking_SntpServerConfig"/> struct with the default SNTP
///     Server configuration.
/// </summary>
/// <param name="sntpServerConfig">
///     A pointer to a <see cref="Networking_SntpServerConfig"/> struct that returns the
///     default SNTP server configuration.
/// </param>
void Networking_SntpServerConfig_Init(Networking_SntpServerConfig *sntpServerConfig);

/// <summary>
///     Destroys a <see cref="Networking_SntpServerConfig"/> struct.
/// </summary>
/// <param name="sntpServerConfig">
///     A pointer to a <see cref="Networking_SntpServerConfig"/> struct to destroy.
/// </param>
void Networking_SntpServerConfig_Destroy(Networking_SntpServerConfig *sntpServerConfig);

/// <summary>
///     Registers and starts SNTP server for the interface specified. If the SNTP
///     server is already running and attached to the specified interface this function returns
///     success. If the <see cref="networkInterfaceName/> interface is down or disabled, then
///     the SNTP server service is registered for the interface but will not start it.
///     <para>**Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EACCES: the application manifest does not include the SntpService capability.</para>
///     <para>EFAULT: the <see cref="networkInterfaceName/> is NULL.</para>
///     <para>EFAULT: the <see cref="sntpServerConfig/> is NULL.</para>
///     <para>ENOENT: the <see cref="networkInterfaceName/> interface does not exist.</para>
///     <para>EPERM:  this operation is not allowed on the network interface.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The string specifying the network interface in which SNTP server should run.
/// </param>
/// <param name="sntpServerConfig">
///      The pointer to the <see cref="Networking_SntpServerConfig" /> that indicates the
///      SNTP server configuration.
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_SntpServer_Start(const char *networkInterfaceName,
                                const Networking_SntpServerConfig *sntpServerConfig);

/// <summary>
///     Initializes a <see cref="Networking_DhcpServerConfig"/> struct with the default DHCP
///     Server configuration.
/// </summary>
/// <param name="dhcpServerConfig">
///     A pointer to a <see cref="Networking_DhcpServerConfig"/> struct that returns the
///     default DHCP server configuration.
/// </param>
void Networking_DhcpServerConfig_Init(Networking_DhcpServerConfig *dhcpServerConfig);

/// <summary>
///     Destroys a <see cref="Networking_DhcpServerConfig"/> struct.
/// </summary>
/// <param name="dhcpServerConfig">
///     A pointer to a <see cref="Networking_DhcpServerConfig"/> struct to destroy.
/// </param>
void Networking_DhcpServerConfig_Destroy(Networking_DhcpServerConfig *dhcpServerConfig);

/// <summary>
///     Modifies a <see cref="Networking_DhcpServerConfig"/> with the provided lease info.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the <paramref name="dhcpServerConfig"/> is NULL.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="dhcpServerConfig">
///     A pointer to a <see cref="Networking_DhcpServerConfig"/> struct to be modified.
/// </param>
/// <param name="startIpAddress">Starting IP address in the address range to lease.</param>
/// <param name="ipAddressCount">The number of IP addresses the server can lease.</param>
/// <param name="subnetMask">The subnet mask the server should use.</param>
/// <param name="gatewayAddress">The gateway address the server should use.</param>
/// <param name="leaseTimeInHours">Duration in hours a lease will last.</param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_DhcpServerConfig_SetLease(Networking_DhcpServerConfig *dhcpServerConfig,
                                         struct in_addr startIpAddress, uint8_t ipAddressCount,
                                         struct in_addr subnetMask, struct in_addr gatewayAddress,
                                         uint32_t leaseTimeInHours);

/// <summary>
///     Modifies a <see cref="Networking_DhcpServerConfig"/> with the provided NTP server addresses.
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the <paramref name="dhcpServerConfig"/> is NULL.</para>
///     <para>EFAULT: the <paramref name="ntpServerAddresses"/> is NULL.</para>
///     <para>EINVAL: More than three NTP address were provided.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="dhcpServerConfig">
///     A pointer to a <see cref="Networking_DhcpServerConfig"/> struct to be modified.
/// </param>
/// <param name="ntpServerAddresses">Pointer to an array of NTP IP addresses.</param>
/// <param name="serverCount">The number of NTP server addresses in the array.</param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_DhcpServerConfig_SetNtpServerAddresses(Networking_DhcpServerConfig *dhcpServerConfig,
                                                      const struct in_addr *ntpServerAddresses,
                                                      size_t serverCount);

/// <summary>
///     Registers and starts the DHCP server for the interface specified. The configuration
///     parameters specified through this function call will overwrite any existing
///     configuration.
///     If the interface specified is up, the DHCP server service will be shut
///     down, configured and started. If the interface is down, the service will be started when
///     the interface is up.
///     The interface specified must be configured with a static IP address first before calling
///     this function. Otherwise, EPERM will be returned.
///     <para> **Errors** </para> If an error is encountered, returns -1 and sets errno to the error
///     value.
///     <para>EACCES: the application manifest does not include the DhcpService capability.</para>
///     <para>ENOENT: the <see cref="networkInterfaceName/> interface does not exist.</para>
///     <para>EPERM:  this operation is not allowed on the network interface.</para>
///     <para>EFAULT: the <paramref name="networkInterfaceName"/> is NULL.</para>
///     <para>EFAULT: the <paramref name="dhcpServerConfig"/> is NULL.</para>
///     <para>EAGAIN: the networking stack isn't ready yet.</para>
///     <para>EINVAL: invalid parameters in configuration structure.</para>
///     Any other errno may be specified; such errors aren't deterministic and there's no guarantee
///     that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="networkInterfaceName">
///      The string specifying the network interface to configure
/// </param>
/// <param name="dhcpServerConfig">
///      The pointer to the <see cref="Networking_DhcpServerConfig" /> that indicates the
///      DHCP server configuration
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int Networking_DhcpServer_Start(const char *networkInterfaceName,
                                const Networking_DhcpServerConfig *dhcpServerConfig);


#ifdef __cplusplus
}
#endif
