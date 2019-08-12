/// \file application.h
/// \brief This header contains the functions and types needed to communicate with
/// and control an application running on an I/O core.
///
#pragma once

#ifdef __cplusplus
extern "C" {
#endif


/// <summary>
///     Creates a socket that can communicate with a
///     real-time capable application. The socket is created in a connected
///     state, and may be used with the send() and recv() functions to transfer
///     messages to and from the real-time capable application. The message format is
///     similar to a datagram.
///
///     The application manifest of the current application must list the component ID
///     of the real-time capable application in the AllowedApplicationConnections capability.
///     In addition, the application manifest of the real-time capable application must list the
///     component ID of the current application in the AllowedApplicationConnections
///     capability.
///
///     <para> **Errors** </para>
///     If an error is encountered, returns -1 and sets errno to the error value.
///     <para>EINVAL: An invalid <paramref name="componentId"/> was specified.</para>
///     <para>EACCES: The component ID of the real-time capable application was not listed in the
///     "AllowedApplicationConnections" capability in the application manifest of
///     <paramref name="componentId"/>.</para>
///     Any other errno may also be specified; such errors aren't deterministic and there's no
///     guarantee that the same behaviour will be retained through system updates.
/// </summary>
/// <param name="componentId">
///     A pointer to a string that represents the component ID of the real-time capable
///     application.
/// </param>
/// <returns>
///     The file descriptor of the socket, or -1 for failure, in which case errno is set to
///     the error value.
/// </returns>
int Application_Socket(const char *componentId);


#ifdef __cplusplus
}
#endif
