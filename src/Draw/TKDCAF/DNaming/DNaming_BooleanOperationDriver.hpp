#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TFunction_Driver.hpp>
#include <Standard_Integer.hpp>
class TFunction_Logbook;
class TDF_Label;
class BRepAlgoAPI_BooleanOperation;
class TFunction_Function;

class DNaming_BooleanOperationDriver : public TFunction_Driver
{

public:
  Standard_EXPORT DNaming_BooleanOperationDriver();

  Standard_EXPORT void Validate(occ::handle<TFunction_Logbook>& theLog) const override;

  Standard_EXPORT bool MustExecute(const occ::handle<TFunction_Logbook>& theLog) const override;

  Standard_EXPORT int Execute(occ::handle<TFunction_Logbook>& theLog) const override;

  DEFINE_STANDARD_RTTIEXT(DNaming_BooleanOperationDriver, TFunction_Driver)

private:
  Standard_EXPORT void LoadNamingDS(const TDF_Label&              theResultLabel,
                                    BRepAlgoAPI_BooleanOperation& MS) const;

  Standard_EXPORT void LoadSectionNDS(const TDF_Label&              theResultLabel,
                                      BRepAlgoAPI_BooleanOperation& MS) const;

  Standard_EXPORT bool CheckAndLoad(BRepAlgoAPI_BooleanOperation&          theMkOpe,
                                    const occ::handle<TFunction_Function>& theFunction) const;
};
