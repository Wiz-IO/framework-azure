/// \file sysevent.h
/// \brief This header contains functions and types needed for system event notifications.
/// Applications can register for and unregister from update, power down, and shutdown
/// notifications. Apps can use these notifications to put themselves in a safe state before
/// application shutdown, or can attempt to defer these events.
#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include "applibs/eventloop.h"

/// <summary>
///     Flags for system event types
/// </summary>
typedef uint32_t SysEvent_Events;
enum {
    /// <summary>
    ///     No event given
    /// </summary>
    SysEvent_Events_None = 0x00,
    /// <summary>
    ///     An OS or application update
    /// </summary>
    SysEvent_Events_Update = 0x01,
    /// <summary>
    ///     A mask of all valid system events
    /// </summary>
    SysEvent_Events_Mask = SysEvent_Events_Update
};

/// <summary>
///     The status of the SysEvent_Events
/// </summary>
typedef uint32_t SysEvent_Status;
enum {
    /// <summary>
    ///     Indicates that the status was improperly initialized
    /// </summary>
    SysEvent_Status_Invalid = 0,
    /// <summary>
    ///     A 10 second warning that an event will occur, with the opportunity to defer that
    ///     event
    /// </summary>
    SysEvent_Status_Pending = 1,
    /// <summary>
    ///     A 10 second warning that an event will occur, without the opportunity for deferral
    /// </summary>
    SysEvent_Status_Final = 2,
    /// <summary>
    ///     The previously "Pending" event has been deferred, and will occur at a later time
    /// </summary>
    SysEvent_Status_Rejected = 3,
    /// <summary>
    ///     The system event is complete.
    /// </summary>
    /// <remarks>
    ///     For software update events, the complete status will only be sent for application
    ///     updates since OS updates require a device reboot to complete
    /// </remarks>
    SysEvent_Status_Complete = 4
};

/// <summary>
///     The type of update being applied
/// </summary>
typedef uint32_t SysEvent_UpdateType;
enum {
    /// <summary>
    ///     Indicates that this enum was improperly initialized
    /// </summary>
    SysEvent_UpdateType_Invalid = 0,
    /// <summary>
    ///     An application update that will restart the updated application but will not
    ///     reboot the device
    /// </summary>
    SysEvent_UpdateType_App = 1,
    /// <summary>
    ///     An OS software update that will require a device reboot
    /// </summary>
    SysEvent_UpdateType_System = 2
};

/// <summary>
///     A struct containing information about update events.  This struct is returned by
///     SysEvent_Info_GetUpdateData after passing in a SysEvent_Info returned by a
///     SysEvent_EventsCallback.  This struct is only valid when the event type is
///     SysEvent_Events_Update. Note: max_deferral_time_in_minutes is only defined for
///     SysEvent_Status_Pending
/// </summary>
typedef struct SysEvent_Info_UpdateData {
    unsigned int max_deferral_time_in_minutes;
    SysEvent_UpdateType update_type;
} SysEvent_Info_UpdateData;

/// <summary>
///     An opaque struct containing information about a system event. Data in this struct cannot be
///     accessed directly; rather, they must be accessed by calling a SysEvent_Info_Get function
///     specific to the event (such as SysEvent_Info_GetUpdateData for SysEvent_Events_Update
///     events).
/// </summary>
typedef struct SysEvent_Info SysEvent_Info;

/// <summary>
///     Used to retrieve update information such as the maximum deferral time in minutes and the
///     type of update. The SysEvent_Info * parameter must be from a SysEvents_Callback call.
/// </summary>
/// <param name="info">
///     A pointer containing information about the SysEvent_Events, retrieved from a
///     SysEvent_EventsCallback
/// </param>
/// <param name="update_info">
///     A pointer to a SysEvent_Info_UpdateData structure that will be populated with the software
///     update information if successful
/// </param>
/// <returns>
///      On success, returns 0
///      On error, returns -1 and sets errno
/// </returns>
int SysEvent_Info_GetUpdateData(const SysEvent_Info *info, SysEvent_Info_UpdateData *update_info);

/// <summary>
///     This function will be called whenever a registered event changes status.  Only one
///     SysEvent_Events flag will be marked, since there is exactly one callback call for each event
///     status change.
/// </summary>
/// <param name="event"> The event which has changed state </param>
/// <param name="state"> The state which the event has changed to </param>
/// <param name="info"> Additional info about the state change.  To retrieve the information,
///     info will need to be passed to an event-specific function (Such as
///     SysEvent_Info_GetUpdateData) </param>
/// <param name="context"> An optional context pointer which was passed in the registration </param>
typedef void SysEvent_EventsCallback(SysEvent_Events event, SysEvent_Status state,
                                     const SysEvent_Info *info, void *context);

/// <summary>
///     Registers the application to the set of events given by eventBitMask. The event registration
///     is returned on success, and will need to be retained until it is passed to
///     SysEvent_UnregisterForEventNotifications
///
///     Note: There must be only one active EventRegistration at a time for all system event
///     notifications.
/// </summary>
/// <param name="el"> The event loop to which the EventRegistration will be registered </param>
/// <param name="eventBitmask"> A bitmask with the events to listen for </param>
/// <param name="callbackFunction"> A function handler which will be called when the state of an
/// event in
///         eventBitmask changes </param>
/// <param name="context"> An optional user context pointer which will be passed to the events
/// callback when
///         an event occurs</param>
/// <returns>
///      On success returns a pointer to an EventRegistration
///      On error returns nullptr and sets errno
/// </returns>
EventRegistration *SysEvent_RegisterForEventNotifications(EventLoop *el,
                                                          SysEvent_Events eventBitmask,
                                                          SysEvent_EventsCallback callback_function,
                                                          void *context);

/// <summary>
///     Unregisters for the system notifications which were registered to by
///     SysEvent_RegisterForEventNotifications.
///     The EventRegistration must have been previously registered, and each EventRegistration
///     may only be unregistered once.
/// </summary>
/// <param name="reg"> The event registration to remove from the event loop </param>
/// <returns>
///      On success returns 0
///      On error returns -1 and sets errno
/// </returns>
int SysEvent_UnregisterForEventNotifications(EventRegistration *reg);

/// <summary>
///     Attempts to defer the given event for [requestedDeferTime] minutes
///     This should only be called when the event status is SysEvent_Status_Pending,
///     (in other words, it should only be called when there is an opportunity for deferral).
/// </summary>
/// <param name="event"> The type of event which is being deferred </param>
/// <param name="requestedDeferTime"> The amount of time in minutes for which the event will be
/// deferred
/// </param>
/// <returns>
///      On success returns 0
///      On error returns -1 and sets errno
/// </returns>
int SysEvent_DeferEvent(SysEvent_Events event, uint32_t requested_defer_time_in_minutes);

/// <summary>
///     If an event had been previously deferred, attempts to resume that event
/// </summary>
/// <param name="event"> The type of event which is being resumed </param>
/// <returns>
///      On success returns 0
///      On error returns -1 and sets errno
/// </returns>
int SysEvent_ResumeEvent(SysEvent_Events event);


#ifdef __cplusplus
}
#endif
