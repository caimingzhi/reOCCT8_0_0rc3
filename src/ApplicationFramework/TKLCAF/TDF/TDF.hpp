#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class Standard_GUID;
class TCollection_ExtendedString;

class TDF
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static const Standard_GUID& LowestID();

  Standard_EXPORT static const Standard_GUID& UppestID();

  Standard_EXPORT static void AddLinkGUIDToProgID(const Standard_GUID&              ID,
                                                  const TCollection_ExtendedString& ProgID);

  Standard_EXPORT static bool GUIDFromProgID(const TCollection_ExtendedString& ProgID,
                                             Standard_GUID&                    ID);

  Standard_EXPORT static bool ProgIDFromGUID(const Standard_GUID&        ID,
                                             TCollection_ExtendedString& ProgID);
};
