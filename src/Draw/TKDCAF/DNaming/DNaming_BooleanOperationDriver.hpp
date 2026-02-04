#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TFunction_Driver.hpp>
#include <Standard_Integer.hpp>
class TFunction_Logbook;
class TDF_Label;
class BRepAlgoAPI_BooleanOperation;
class TFunction_Function;

//! Driver for Fuse, Cut, Common
class DNaming_BooleanOperationDriver : public TFunction_Driver
{

public:
  //! Constructor
  //! validation
  //! ==========
  Standard_EXPORT DNaming_BooleanOperationDriver();

  //! Validates labels of a function in <log>.
  //! In regeneration mode this method must be called (by the
  //! solver) even if the function is not executed, to build
  //! the valid label scope.
  //! execution of function
  //! ======================
  Standard_EXPORT void Validate(occ::handle<TFunction_Logbook>& theLog) const override;

  //! Analyse in <log> if the loaded function must be executed
  //! (i.e.arguments are modified) or not.
  //! If the Function label itself is modified, the function must
  //! be executed.
  Standard_EXPORT bool MustExecute(const occ::handle<TFunction_Logbook>& theLog) const override;

  //! Execute the function and push in <log> the impacted
  //! labels (see method SetImpacted).
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

