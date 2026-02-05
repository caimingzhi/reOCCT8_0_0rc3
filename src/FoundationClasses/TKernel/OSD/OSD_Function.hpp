#pragma once

// This is in fact a pointer to a function.
// This is not an "enumeration" but a trick to solve an omission from CDL.

typedef int (*OSD_Function)(...);
