// Copyright (c) 2025 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef TKERNEL_PCH_H
#define TKERNEL_PCH_H

// Standard library headers
#include <atomic>
#include <iostream>
#include <limits>
#include <ostream>
#include <random>
#include <sstream>
#include <string>
#include <type_traits>

// Windows-specific headers (for MSVC)
#ifdef _WIN32
  #ifndef NOMINMAX
    #define NOMINMAX
  #endif
  #include <tchar.h>   // For Unicode/MBCS mappings
  #include <windows.h> // For Windows API functions like WideCharToMultiByte
  #ifdef GetObject
    #undef GetObject
  #endif
#endif

// TKernel headers
#include <Standard.hpp>
#include <Standard_DefineHandle.hpp>
#include <Standard_GUID.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Macro.hpp>
#include <iomanip>
#include <fstream>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

#include <Precision.hpp>

#include <Quantity_Color.hpp>
#include <Quantity_ColorRGBA.hpp>
#include <Quantity_TypeOfColor.hpp>

#include <TCollection_AsciiString.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TCollection_HExtendedString.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <NCollection_Buffer.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_HArray1.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_List.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Sequence.hpp>

#include <Message_ProgressIndicator.hpp>
#include <Message_ProgressRange.hpp>
#include <Message_ProgressScope.hpp>

#include <OSD_Parallel.hpp>
#include <OSD_Path.hpp>

#endif // TKERNEL_PCH_H
