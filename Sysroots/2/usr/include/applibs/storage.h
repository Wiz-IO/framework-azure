/// \file storage.h
/// \brief This header contains functionality for interacting with on-device storage.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


/// <summary>
///     <para>Returns a new descriptor to a file in nonvolatile storage where data will be
///     persisted over device reboot. This file will be retained over reboot as well
///     as over application update.</para>
///
///     <para>The file will be created if it does not exist. Otherwise, this function will return a
///     new file descriptor to an existing file.  The file can be deleted later with
///     <see cref="Storage_DeleteMutableFile"/></para>
///
///     <para> **Errors** </para>
///     <para>In case of errors, this function will return -1 and set errno to the error value.
///     </para>
///     <para>EACCES: The application does not have the application capability
///     (MutableStorage) required in order to use this API.</para>
///     <para>EIO: An error occurred while trying to create the file.</para>
///     <para>Any other errno may also be specified; such errors are not deterministic and
///     no guarantee is made that the same behavior will be retained through system updates.</para>
/// </summary>
/// <returns>
///     An opened file descriptor to persistent, mutable storage, or -1 on failure, in which case
///     errno is set to the error value.
/// </returns>
int Storage_OpenMutableFile(void);

/// <summary>
///     <para>Deletes any existing file previously obtained through <see
///     cref="Storage_OpenMutableFile"/>.  All descriptors on the file must have been closed,
///     otherwise the behavior of this function is undefined.</para>
///
///     <para>WARNING: this action is permanent!</para>
///
///     <para> **Errors** </para>
///     <para>In case of errors, this function will return -1 and set errno to the error value.
///     </para>
///     <para>EACCES: The application does not have the application capability (MutableStorage)
///     required in order to use this API.</para>
///     <para>EIO: An error occurred while trying to delete the file.</para>
///     <para>ENOENT:There was no existing mutable storage file to delete.</para>
///     <para>Any other errno may also be specified; such errors are not deterministic and
///     no guarantee is made that the same behavior will be retained through system updates.</para>
/// </summary>
/// <returns>0 on success, or -1 on failure, in which case errno is set to the error
/// value.</returns>
int Storage_DeleteMutableFile(void);

#ifdef __cplusplus
}
#endif
