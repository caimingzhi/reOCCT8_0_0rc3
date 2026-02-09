#pragma once

#include <TDataStd_GenericEmpty.hpp>
class TDF_Label;
class gp_Lin;

class TDataXtd_Axis : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<TDataXtd_Axis> Set(const TDF_Label& label);

  Standard_EXPORT static occ::handle<TDataXtd_Axis> Set(const TDF_Label& label, const gp_Lin& L);

  Standard_EXPORT TDataXtd_Axis();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataXtd_Axis, TDataStd_GenericEmpty)
};
