#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TFunction_Driver.hpp>
#include <Standard_Integer.hpp>
class TFunction_Logbook;
class TDF_Label;
class TNaming_NamedShape;
class gp_Trsf;

class DNaming_TransformationDriver : public TFunction_Driver
{

public:
  Standard_EXPORT DNaming_TransformationDriver();

  Standard_EXPORT void Validate(occ::handle<TFunction_Logbook>& theLog) const override;

  Standard_EXPORT bool MustExecute(const occ::handle<TFunction_Logbook>& theLog) const override;

  Standard_EXPORT int Execute(occ::handle<TFunction_Logbook>& theLog) const override;

  DEFINE_STANDARD_RTTIEXT(DNaming_TransformationDriver, TFunction_Driver)

private:
  Standard_EXPORT void LoadNamingDS(const TDF_Label&                       theResultLabel,
                                    const occ::handle<TNaming_NamedShape>& theSourceNS,
                                    const gp_Trsf&                         theTrsf) const;
};
