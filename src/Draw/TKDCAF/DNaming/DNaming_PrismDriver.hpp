#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TFunction_Driver.hpp>
#include <Standard_Integer.hpp>
class TFunction_Logbook;
class TDF_Label;
class BRepPrimAPI_MakePrism;
class TopoDS_Shape;

class DNaming_PrismDriver : public TFunction_Driver
{

public:
  Standard_EXPORT DNaming_PrismDriver();

  Standard_EXPORT void Validate(occ::handle<TFunction_Logbook>& theLog) const override;

  Standard_EXPORT bool MustExecute(const occ::handle<TFunction_Logbook>& theLog) const override;

  Standard_EXPORT int Execute(occ::handle<TFunction_Logbook>& theLog) const override;

  DEFINE_STANDARD_RTTIEXT(DNaming_PrismDriver, TFunction_Driver)

private:
  Standard_EXPORT void LoadNamingDS(const TDF_Label&       theResultLabel,
                                    BRepPrimAPI_MakePrism& mkPrism,
                                    const TopoDS_Shape&    Basis,
                                    const TopoDS_Shape&    Context) const;
};
