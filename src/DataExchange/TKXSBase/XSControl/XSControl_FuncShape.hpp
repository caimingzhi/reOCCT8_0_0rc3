#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_CString.hpp>
class XSControl_WorkSession;
class TCollection_AsciiString;

class XSControl_FuncShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static void Init();

  Standard_EXPORT static int MoreShapes(const occ::handle<XSControl_WorkSession>&         session,
                                        occ::handle<NCollection_HSequence<TopoDS_Shape>>& list,
                                        const char*                                       name);

  Standard_EXPORT static bool FileAndVar(const occ::handle<XSControl_WorkSession>& session,
                                         const char*                               file,
                                         const char*                               var,
                                         const char*                               def,
                                         TCollection_AsciiString&                  resfile,
                                         TCollection_AsciiString&                  resvar);
};
