#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepShape_ManifoldSolidBrep.hpp>
#include <StepShape_OrientedClosedShell.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Integer.hpp>
class StepShape_FacetedBrep;
class StepShape_BrepWithVoids;
class TCollection_HAsciiString;
class StepShape_ClosedShell;
class StepShape_OrientedClosedShell;

class StepShape_FacetedBrepAndBrepWithVoids : public StepShape_ManifoldSolidBrep
{

public:
  //! Returns a FacetedBrepAndBrepWithVoids
  Standard_EXPORT StepShape_FacetedBrepAndBrepWithVoids();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<StepShape_ClosedShell>&    aOuter,
                            const occ::handle<StepShape_FacetedBrep>&    aFacetedBrep,
                            const occ::handle<StepShape_BrepWithVoids>&  aBrepWithVoids);

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                                        aName,
    const occ::handle<StepShape_ClosedShell>&                                           aOuter,
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>>& aVoids);

  Standard_EXPORT void SetFacetedBrep(const occ::handle<StepShape_FacetedBrep>& aFacetedBrep);

  Standard_EXPORT occ::handle<StepShape_FacetedBrep> FacetedBrep() const;

  Standard_EXPORT void SetBrepWithVoids(const occ::handle<StepShape_BrepWithVoids>& aBrepWithVoids);

  Standard_EXPORT occ::handle<StepShape_BrepWithVoids> BrepWithVoids() const;

  Standard_EXPORT void SetVoids(
    const occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>>& aVoids);

  Standard_EXPORT occ::handle<NCollection_HArray1<occ::handle<StepShape_OrientedClosedShell>>>
                  Voids() const;

  Standard_EXPORT occ::handle<StepShape_OrientedClosedShell> VoidsValue(const int num) const;

  Standard_EXPORT int NbVoids() const;

  DEFINE_STANDARD_RTTIEXT(StepShape_FacetedBrepAndBrepWithVoids, StepShape_ManifoldSolidBrep)

private:
  occ::handle<StepShape_FacetedBrep>   facetedBrep;
  occ::handle<StepShape_BrepWithVoids> brepWithVoids;
};
