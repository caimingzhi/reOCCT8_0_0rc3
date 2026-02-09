#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Real.hpp>
#include <TDataStd_Real.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_Label;

class XCAFDoc_Area : public TDataStd_Real
{

public:
  Standard_EXPORT XCAFDoc_Area();

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Set(const double vol);

  Standard_EXPORT static occ::handle<XCAFDoc_Area> Set(const TDF_Label& label, const double area);

  Standard_EXPORT double Get() const;

  Standard_EXPORT static bool Get(const TDF_Label& label, double& area);

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_Area, TDataStd_Real)
};
