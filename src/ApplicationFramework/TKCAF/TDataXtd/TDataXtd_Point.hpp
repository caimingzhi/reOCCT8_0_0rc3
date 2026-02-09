#pragma once

#include <TDataStd_GenericEmpty.hpp>
class TDF_Label;
class gp_Pnt;

class TDataXtd_Point : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataXtd_Point> Set(const TDF_Label& label);

  Standard_EXPORT static occ::handle<TDataXtd_Point> Set(const TDF_Label& label, const gp_Pnt& P);

  Standard_EXPORT TDataXtd_Point();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataXtd_Point, TDataStd_GenericEmpty)
};
