#pragma once

/// <summary>
/// Macro to tag a function or variable as obsolete and refer to its replacement.
/// </summary>
#ifndef _AZSPHERE_OBSOLETED_BY
#ifndef _AZSPHERE_USE_OBSOLETE_API
#define _AZSPHERE_OBSOLETED_BY(_Replacement) \
    __attribute__(                           \
        (error("This function or variable is obsolete. Please use '" #_Replacement "' instead.")))
#else
#define _AZSPHERE_OBSOLETED_BY(_Replacement)
#endif
#endif
