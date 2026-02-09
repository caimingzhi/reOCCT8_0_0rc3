#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TFunction_Driver.hpp>
#include <Standard_Integer.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Array1.hpp>
class TFunction_Logbook;
class TDF_Label;
class TopoDS_Wire;

class DNaming_Line3DDriver : public TFunction_Driver
{

public:
  Standard_EXPORT DNaming_Line3DDriver();

  Standard_EXPORT void Validate(occ::handle<TFunction_Logbook>& theLog) const override;

  Standard_EXPORT bool MustExecute(const occ::handle<TFunction_Logbook>& theLog) const override;

  Standard_EXPORT int Execute(occ::handle<TFunction_Logbook>& theLog) const override;

  DEFINE_STANDARD_RTTIEXT(DNaming_Line3DDriver, TFunction_Driver)

private:
  Standard_EXPORT void LoadNamingDS(const TDF_Label&                        theResultLabel,
                                    const TopoDS_Wire&                      theWire,
                                    const NCollection_Array1<TopoDS_Shape>& theVertexes,
                                    const bool                              isClosed = false) const;
};
