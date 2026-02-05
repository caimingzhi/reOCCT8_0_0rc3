#pragma once

#include <AIS_InteractiveObject.hpp>

class QABugs_PresentableObject : public AIS_InteractiveObject
{
  DEFINE_STANDARD_RTTIEXT(QABugs_PresentableObject, AIS_InteractiveObject)
public:
  Standard_EXPORT QABugs_PresentableObject(
    const PrsMgr_TypeOfPresentation3d aTypeOfPresentation3d = PrsMgr_TOP_AllView);

protected:
  Standard_EXPORT void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSel,
                                        const int                               theMode) override;

  Standard_EXPORT void Compute(const occ::handle<PrsMgr_PresentationManager>& thePrsMgr,
                               const occ::handle<Prs3d_Presentation>&         thePrs,
                               const int                                      theMode) override;
};
