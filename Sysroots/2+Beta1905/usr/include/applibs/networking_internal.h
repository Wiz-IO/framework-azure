/// \file networking_internal.h
/// \brief This header contains internal functions of the Networking API and should not be included
/// directly; include applibs/networking.h instead.
#pragma once

#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
///    Version support info for the Networking_NetworkInterface structs. Refer to
///    Networking_NetworkInterface and the appropriate networking_structs_v[n].h header for actual
///    struct fields.
/// </summary>
struct z__Networking_NetworkInterface_Base {
    /// <summary>Internal version field.</summary>
    uint32_t z__magicAndVersion;
};

/// <summary>
///    A magic value that provides version support for the Networking_NetworkInterface struct.
/// </summary>
#define z__NETWORKING_NETWORK_INTERFACE_STRUCT_MAGIC 0xfa9a0000

/// <summary>
///    Version support info for the Networking_StaticIpConfiguration structs. Refer to
///    Networking_StaticIpConfiguration and the appropriate networking_structs_v[n].h header for
///    actual struct fields.
/// </summary>
struct z__Networking_StaticIpConfiguration_Base {
    /// <summary>Internal version field.</summary>
    uint32_t z__magicAndVersion;
};

/// <summary>
///    A magic value that provides version support for the Networking_StaticIpConfiguration struct.
/// </summary>
#define z__NETWORKING_STATICIPCONFIGURATION_STRUCT_MAGIC 0xaa140000

/// <summary>
///    Version support info for the Networking_DhcpServerConfiguration structs. Refer to
///    Networking_DhcpServerConfiguration and the appropriate networking_structs_v[n].h header for
///    actual struct fields.
/// </summary>
struct z__Networking_DhcpServerConfiguration_Base {
    /// <summary>Internal version field.</summary>
    uint32_t z__magicAndVersion;
};

/// <summary>
///    A magic value that provides version support for the Networking_DhcpServerConfiguration
///    struct.
/// </summary>
#define z__NETWORKING_DHCPSERVERCONFIGURATION_STRUCT_MAGIC 0x598e0000

/// <summary>
///    Adds struct version support to Networking_GetInterfaces. Do not use this directly; use
///    Networking_GetInterfaces instead.
/// </summary>
/// <param name="outNetworkInterfacesArray">
///     A pointer to a Networking_NetworkInterface structure that is type cast to
///     z__Networking_NetworkInterface_Base.
/// </param>
/// <param name="networkInterfacesArrayCount">
///     The number of elements in the outNetworkInterfacesArray.
/// </param>
/// <param name="networkInterfaceStructVersion">
///     The version of the network interface structure.
/// </param>
/// <returns>
///     If the call is successful, the number of network interfaces populated in the <paramref
///     name="outNetworkInterfacesArray"/> is returned. On failure, -1 is returned, in which case
///     errno is set to the error value.
/// </returns>
ssize_t z__Networking_GetInterfaces(
    struct z__Networking_NetworkInterface_Base *outNetworkInterfacesArray,
    size_t networkInterfacesArrayCount, uint32_t networkInterfaceStructVersion);

/// <summary>
///     Gets the list of registered network interfaces in the Azure Sphere device. If <paramref
///     name="outNetworkInterfacesArray"/> is too small to hold all network interfaces in the
///     system, this function uses the available space and returns the total number of interfaces
///     it is able to provide. The number of interfaces in the system will not change within a boot
///     cycle.
///      <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EFAULT: the <paramref name="outNetworkInterfacesArray"/> is NULL.</para>
///     <para>ERANGE: the <paramref name="networkInterfacesArrayCount"/> is 0.</para>
///     Any other errno may be specified; such errors aren't deterministic and
///     there's no guarantee that the same behaviour will be retained through system updates.
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
static inline ssize_t Networking_GetInterfaces(
    Networking_NetworkInterface *outNetworkInterfacesArray, size_t networkInterfacesArrayCount)
{
    return z__Networking_GetInterfaces(
        (struct z__Networking_NetworkInterface_Base *)outNetworkInterfacesArray,
        networkInterfacesArrayCount, NETWORKING_STRUCTS_VERSION);
}

/// <summary>
///    Adds struct version support to Networking_InitStaticIpConfiguration. Do not use this
///    directly; use Networking_InitStaticIpConfiguration instead.
/// </summary>
/// <param name="staticIpConfiguration">
///     A pointer to a <see cref="Networking_StaticIpConfiguration"/> struct that returns the
///     default static IP configuration.
/// </param>
/// <param name="staticIpStructVersion">
///     The static IP configuration struct version.
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int z__Networking_InitStaticIpConfiguration(
    struct z__Networking_StaticIpConfiguration_Base *staticIpConfiguration,
    uint32_t staticIpStructVersion);

/// <summary>
///     Initializes a <see cref="Networking_StaticIpConfiguration"/> struct with the default static
///     IP parameters.
/// </summary>
/// <param name="staticIpConfiguration">
///     A pointer to a <see cref="Networking_StaticIpConfiguration"/> struct that returns the
///     default static IP parameters.
/// </param>
static inline void Networking_InitStaticIpConfiguration(
    Networking_StaticIpConfiguration *staticIpConfiguration)
{
    z__Networking_InitStaticIpConfiguration(
        (struct z__Networking_StaticIpConfiguration_Base *)staticIpConfiguration,
        NETWORKING_STRUCTS_VERSION);
}

/// <summary>
///    Adds struct version support to Networking_SetStaticIp. Do not use this
///    directly; use Networking_SetStaticIp instead.
/// </summary>
/// <param name="networkInterfaceName">
///      The pointer to a char that specifies the interface name
/// </param>
/// <param name="staticIpConfiguration">
///      The pointer to the <see cref="Networking_StaticIpConfiguration" /> that indicates the
///      static IP address, net mask and gateway address
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int z__Networking_SetStaticIp(
    const char *networkInterfaceName,
    const struct z__Networking_StaticIpConfiguration_Base *staticIpConfiguration);

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
static inline int Networking_SetStaticIp(
    const char *networkInterfaceName, const Networking_StaticIpConfiguration *staticIpConfiguration)
{
    return z__Networking_SetStaticIp(
        networkInterfaceName,
        (struct z__Networking_StaticIpConfiguration_Base *)staticIpConfiguration);
}

/// <summary>
///    Adds struct version support to Networking_InitDhcpServerConfiguration. Do not use this
///    directly; use Networking_InitDhcpServerConfiguration instead.
/// </summary>
/// <param name="dhcpServerConfiguration">
///     A pointer to a <see cref="Networking_DhcpServerConfiguration"/> struct that returns the
///     default DHCP server configuration.
/// </param>
/// <param name="dhcpServerStructVersion">
///     The DHCP server configuration struct version.
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int z__Networking_InitDhcpServerConfiguration(
    struct z__Networking_DhcpServerConfiguration_Base *dhcpServerConfiguration,
    uint32_t dhcpServerStructVersion);

/// <summary>
///     Initializes a <see cref="Networking_DhcpServerConfiguration"/> struct with the default DHCP
///     server parameters.
/// </summary>
/// <param name="dhcpServerConfiguration">
///     A pointer to a <see cref="Networking_DhcpServerConfiguration"/> struct that returns the
///     default DHCP server parameters.
/// </param>
static inline void Networking_InitDhcpServerConfiguration(
    Networking_DhcpServerConfiguration *dhcpServerConfiguration)
{
    z__Networking_InitDhcpServerConfiguration(
        (struct z__Networking_DhcpServerConfiguration_Base *)dhcpServerConfiguration,
        NETWORKING_STRUCTS_VERSION);
}

/// <summary>
///    Adds struct version support to Networking_StartDhcpServer. Do not use this
///    directly; use Networking_StartDhcpServer instead.
/// </summary>
/// <param name="networkInterfaceName">
///      The pointer to a char that specifies the interface name
/// </param>
/// <param name="dhcpServerConfiguration">
///      The pointer to the <see cref="Networking_StartDhcpServer" /> that indicates the
///      DHCP server configuration parameters
/// </param>
/// <returns>
///     0 for success, -1 for failure, in which case errno is set to the error value.
/// </returns>
int z__Networking_StartDhcpServer(
    const char *networkInterfaceName,
    const struct z__Networking_DhcpServerConfiguration_Base *dhcpServerConfiguration);

/// <summary>
///     Registers and starts the DHCP server for the interface specified. The configuration
///     parameters specified through this function call will overwrite the existing configuration.
///     The DHCP server service will be restarted using the supplied configuration.
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
static inline int Networking_StartDhcpServer(
    const char *networkInterfaceName,
    const Networking_DhcpServerConfiguration *dhcpServerConfiguration)
{
    return z__Networking_StartDhcpServer(
        networkInterfaceName,
        (struct z__Networking_DhcpServerConfiguration_Base *)dhcpServerConfiguration);
}

#ifdef __cplusplus
}
#endif
