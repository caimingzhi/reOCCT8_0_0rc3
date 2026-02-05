#pragma once

#ifdef _WIN32
typedef void* Aspect_Drawable; /* HDC under WNT */
#else
typedef unsigned long Aspect_Drawable; /* Window or Pixmap under UNIX */
#endif /* _WIN32 */
