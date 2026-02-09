#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectAnyList.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_EntityIterator;

class IFSelect_SelectInList : public IFSelect_SelectAnyList
{

public:
  Standard_EXPORT virtual occ::handle<Standard_Transient> ListedEntity(
    const int                              num,
    const occ::handle<Standard_Transient>& ent) const = 0;

  Standard_EXPORT void FillResult(const int                              n1,
                                  const int                              n2,
                                  const occ::handle<Standard_Transient>& ent,
                                  Interface_EntityIterator&              result) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectInList, IFSelect_SelectAnyList)
};
