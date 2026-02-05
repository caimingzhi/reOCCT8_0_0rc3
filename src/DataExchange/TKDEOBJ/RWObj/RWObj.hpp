#pragma once

#include <Message_ProgressRange.hpp>
#include <OSD_Path.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_Macro.hpp>

//! This class provides methods to read and write triangulation from / to the OBJ files.
class RWObj
{
public:
  //! Read specified OBJ file and returns its content as triangulation.
  //! In case of error, returns Null handle.
  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadFile(
    const char*                  theFile,
    const Message_ProgressRange& aProgress = Message_ProgressRange());
};
