#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <StepShape_OpenShell.hpp>
#include <StepShape_Face.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class StepShape_Face;

class StepShape_OrientedOpenShell : public StepShape_OpenShell
{

public:
  //! Returns a OrientedOpenShell
  Standard_EXPORT StepShape_OrientedOpenShell();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_OpenShell>&      aOpenShellElement,
                            const bool                                   aOrientation);

  Standard_EXPORT void SetOpenShellElement(
    const occ::handle<StepShape_OpenShell>& aOpenShellElement);

  Standard_EXPORT occ::handle<StepShape_OpenShell> OpenShellElement() const;

  Standard_EXPORT void SetOrientation(const bool aOrientation);

  Standard_EXPORT bool Orientation() const;

  Standard_EXPORT void SetCfsFaces(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>>& aCfsFaces) override;

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepShape_Face>>> CfsFaces()
    const override;

  Standard_EXPORT occ::handle<StepShape_Face> CfsFacesValue(const int num) const override;

  Standard_EXPORT int NbCfsFaces() const override;

  DEFINE_STANDARD_RTTIEXT(StepShape_OrientedOpenShell, StepShape_OpenShell)

private:
  occ::handle<StepShape_OpenShell> openShellElement;
  bool                             orientation;
};
