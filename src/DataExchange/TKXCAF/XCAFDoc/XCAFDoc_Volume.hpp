#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataStd_Real.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_Label;

class XCAFDoc_Volume : public TDataStd_Real
{

public:
  Standard_EXPORT XCAFDoc_Volume();

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Set(const double vol);

  Standard_EXPORT static occ::handle<XCAFDoc_Volume> Set(const TDF_Label& label, const double vol);

  Standard_EXPORT double Get() const;

  Standard_EXPORT static bool Get(const TDF_Label& label, double& vol);

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_Volume, TDataStd_Real)
};
