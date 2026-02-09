#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_OStream.hpp>
#include <Standard_CString.hpp>

class Vrml
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static Standard_OStream& VrmlHeaderWriter(Standard_OStream& anOStream);

  Standard_EXPORT static Standard_OStream& CommentWriter(const char*       aComment,
                                                         Standard_OStream& anOStream);
};
