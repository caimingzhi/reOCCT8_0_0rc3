#pragma once

#include <Message_ProgressRange.hpp>
#include <OSD_Path.hpp>
#include <Poly_Triangulation.hpp>
#include <Standard_Macro.hpp>

class RWObj
{
public:
  Standard_EXPORT static occ::handle<Poly_Triangulation> ReadFile(
    const char*                  theFile,
    const Message_ProgressRange& aProgress = Message_ProgressRange());
};
