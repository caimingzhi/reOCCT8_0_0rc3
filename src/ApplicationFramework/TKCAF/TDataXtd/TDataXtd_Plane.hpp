#pragma once

#include <TDataStd_GenericEmpty.hpp>
class TDF_Label;
class gp_Pln;

class TDataXtd_Plane : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataXtd_Plane> Set(const TDF_Label& label);

  Standard_EXPORT static occ::handle<TDataXtd_Plane> Set(const TDF_Label& label, const gp_Pln& P);

  Standard_EXPORT TDataXtd_Plane();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataXtd_Plane, TDataStd_GenericEmpty)
};
