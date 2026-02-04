#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <StepShape_ClosedShell.hpp>
#include <StepShape_Face.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepShape_Face;

class StepShape_OrientedClosedShell : public StepShape_ClosedShell
{

public:
  //! Returns a OrientedClosedShell
  Standard_EXPORT StepShape_OrientedClosedShell();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_ClosedShell>&    aClosedShellElement,
                            const bool                                   aOrientation);

  Standard_EXPORT void SetClosedShellElement(
    const occ::handle<StepShape_ClosedShell>& aClosedShellElement);

  Standard_EXPORT occ::handle<StepShape_ClosedShell> ClosedShellElement() const;

  Standard_EXPORT void SetOrientation(const bool aOrientation);

  Standard_EXPORT bool Orientation() const;

  Standard_EXPORT void SetCfsFaces(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>>& aCfsFaces) override;

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> CfsFaces()
    const override;

  Standard_EXPORT occ::handle<StepShape_Face> CfsFacesValue(const int num) const override;

  Standard_EXPORT int NbCfsFaces() const override;

  DEFINE_STANDARD_RTTIEXT(StepShape_OrientedClosedShell, StepShape_ClosedShell)

private:
  occ::handle<StepShape_ClosedShell> closedShellElement;
  bool                               orientation;
};

