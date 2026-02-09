#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

class IFSelect_SelectAnyType : public IFSelect_SelectExtract
{

public:
  Standard_EXPORT virtual occ::handle<Standard_Type> TypeForMatch() const = 0;

  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectAnyType, IFSelect_SelectExtract)
};
