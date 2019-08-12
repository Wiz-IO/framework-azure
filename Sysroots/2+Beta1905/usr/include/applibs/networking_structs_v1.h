/// \file networking_structs_v1.h
/// \brief This header contains data structures and enumerations for the Networking library.
///
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <netinet/ip.h>
#include <net/if.h>

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
///     The IP configuration options for a network interface.
/// </summary>
typedef enum {
    /// <summary>Indicates that the interface does not have any DHCP client attached to it.
    /// This means that a static IP for the interface has to be set using <see
    /// cref="Networking_IpConfig_Apply" /></summary>
    Networking_IpType_DhcpNone = 0,
    /// <summary> Indicates that the interface has a dynamic IP with a DHCP Client attached to it.
    /// </summary>
    Networking_IpType_DhcpClient = 1
} Networking_IpType;

typedef uint8_t Networking_IpType_Type;

/// <summary>
///     The medium type of the network interface.
/// </summary>
typedef enum {
    /// <summary>Indicates that the interface is unspecified</summary>
    Networking_InterfaceMedium_Unspecified = 0,
    /// <summary>Indicates that the interface is Wi-Fi</summary>
    Networking_InterfaceMedium_Wifi = 1,
    /// <summary>Indicates that the interface is Ethernet</summary>
    Networking_InterfaceMedium_Ethernet = 2
} Networking_InterfaceMedium;

typedef uint8_t Networking_InterfaceMedium_Type;

/// <summary>
///     The properties of a network interface
/// </summary>
struct z__Networking_NetworkInterface_v1 {
    /// <summary>A magic number that uniquely identifies the struct version.</summary>
    uint32_t z__magicAndVersion;
    /// <summary>Whether or not the network interface is enabled.</summary>
    bool isEnabled;
    /// <summary>The network interface name.</summary>
    char interfaceName[IF_NAMESIZE];
    /// <summary>The network interface name length.</summary>
    uint32_t interfaceNameLength;
    /// <summary>Enum <see cref="Networking_IpType" /> containing IP types for the
    /// interface.</summary>
    Networking_IpType_Type ipConfigurationType;
    /// <summary>Enum <see cref="Networking_InterfaceMedium" /> containing the Mac type of the
    /// interface options for the interface.</summary>
    Networking_InterfaceMedium_Type interfaceMediumType;
};

/// <summary>
///     The configuration parameters for setting static IP for an interface
/// </summary>
struct z__Networking_StaticIpConfiguration_v1 {
    /// <summary>A magic number that uniquely identifies the struct version.</summary>
    uint32_t z__magicAndVersion;
    /// <summary>The Static IP address for the interface.</summary>
    struct in_addr ipAddress;
    /// <summary>The netmask for the Static IP address.</summary>
    struct in_addr netMask;
    /// <summary>The gateway address for the interface. This should be set to 0.0.0.0</summary>
    struct in_addr gatewayAddress;
};

/// <summary>
///     An opaque buffer representing the IP configuration for an interface.
/// </summary>
typedef struct Networking_IpConfig {
    uint64_t reserved[5];
} Networking_IpConfig;

/// <summary>
///     The configuration parameters for setting DHCP server configuration for an interface. All
///     in_addr parameters are in network byte order.
/// </summary>
struct z__Networking_DhcpServerConfiguration_v1 {
    /// <summary>A magic number that uniquely identifies the struct version.</summary>
    uint32_t z__magicAndVersion;
    /// <summary>Starting IP address.</summary> 
    struct in_addr startIpAddress;
    /// <summary>Number of incrementing IP addresses supported including startIpAddress. Only
    /// supported value is 1. </summary> 
    uint8_t ipAddressCount;
    /// <summary>(DHCP Option 1): The netmask for the IP addresses.</summary> 
    struct in_addr netMask;
    /// <summary>(DHCP Option 3): The gateway address for the interface. Note that Azure Sphere does
    /// not support IP routing. This address could indicate an alternate gateway on the private
    /// network. All zeros indicate an unspecified value and the DHCP server will not return this
    /// option to the client.
    /// The gateway address must be in the same subnet as the IP address range
    /// specified by startIpAddress and ipAddressCount and must not overlap with that range.
    /// </summary> 
    struct in_addr gatewayAddress;
    /// <summary>(DHCP Option 42): NTP server addresses by order of preference. Maximum 3    
    /// supported. All zeros indicate an unspecified value and the DHCP server will not return this
    /// option to the client.
    /// </summary> 
    struct in_addr ntpServers[3];
    /// <summary>(DHCP Option 51): IP Address Lease Time in hours. Minimum is 1 hour and maximum
    /// of 24 hours.
    /// </summary> 
    uint32_t leaseTimeHours;
};

/// <summary>
///     An opaque buffer representing the SNTP server configuration for an interface.
/// </summary>
typedef struct Networking_SntpServerConfig {
    uint64_t reserved[3];
} Networking_SntpServerConfig;

/// <summary>
///     An opaque buffer representing the DHCP server configuration for an interface.
/// </summary>
typedef struct Networking_DhcpServerConfig {
    uint64_t reserved[8];
} Networking_DhcpServerConfig;


#ifdef __cplusplus
}
#endif
