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

//! Computes Line 3D function
class DNaming_Line3DDriver : public TFunction_Driver
{

public:
  //! Constructor
  //! validation
  //! ==========
  Standard_EXPORT DNaming_Line3DDriver();

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

  DEFINE_STANDARD_RTTIEXT(DNaming_Line3DDriver, TFunction_Driver)

private:
  //! Loads a Line3D in a data framework
  Standard_EXPORT void LoadNamingDS(const TDF_Label&                        theResultLabel,
                                    const TopoDS_Wire&                      theWire,
                                    const NCollection_Array1<TopoDS_Shape>& theVertexes,
                                    const bool                              isClosed = false) const;
};

