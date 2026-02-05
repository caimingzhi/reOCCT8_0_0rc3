#pragma once

#ifdef _WIN32
typedef void*  HANDLE;
typedef HANDLE Aspect_Handle;
#else
typedef unsigned long Aspect_Handle;
#endif /* _WIN32 */
