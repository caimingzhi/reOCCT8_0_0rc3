#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TFunction_Driver.hpp>
#include <Standard_Integer.hpp>
class TFunction_Logbook;
class TDF_Label;
class BRepFilletAPI_MakeFillet;
class TopoDS_Shape;

class DNaming_FilletDriver : public TFunction_Driver
{

public:
  Standard_EXPORT DNaming_FilletDriver();

  Standard_EXPORT void Validate(occ::handle<TFunction_Logbook>& theLog) const override;

  Standard_EXPORT bool MustExecute(const occ::handle<TFunction_Logbook>& theLog) const override;

  Standard_EXPORT int Execute(occ::handle<TFunction_Logbook>& theLog) const override;

  DEFINE_STANDARD_RTTIEXT(DNaming_FilletDriver, TFunction_Driver)

private:
  Standard_EXPORT void LoadNamingDS(const TDF_Label&          theResultLabel,
                                    BRepFilletAPI_MakeFillet& mkFillet,
                                    const TopoDS_Shape&       theContext) const;
};
