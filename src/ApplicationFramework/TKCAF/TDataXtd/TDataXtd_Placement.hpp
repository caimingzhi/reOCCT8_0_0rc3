#pragma once

#include <TDataStd_GenericEmpty.hpp>
class TDF_Label;

class TDataXtd_Placement : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataXtd_Placement> Set(const TDF_Label& label);

  Standard_EXPORT TDataXtd_Placement();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataXtd_Placement, TDataStd_GenericEmpty)
};
