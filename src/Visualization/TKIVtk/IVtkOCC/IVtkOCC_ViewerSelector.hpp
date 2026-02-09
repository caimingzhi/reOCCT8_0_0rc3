#pragma once

#include <IVtk_IView.hpp>
#include <SelectMgr_Selection.hpp>
#include <SelectMgr_ViewerSelector.hpp>

class IVtkOCC_ViewerSelector : public SelectMgr_ViewerSelector
{
public:
  IVtkOCC_ViewerSelector();

  ~IVtkOCC_ViewerSelector() override;

  void Pick(const int theXPix, const int theYPix, const IVtk_IView::Handle& theView);

  void Pick(const int                 theXMin,
            const int                 theYMin,
            const int                 theXMax,
            const int                 theYMax,
            const IVtk_IView::Handle& theView);

  void Pick(double** thePoly, const int theNbPoints, const IVtk_IView::Handle& theView);

  void Activate(const occ::handle<SelectMgr_Selection>& theSelection);

  void Deactivate(const occ::handle<SelectMgr_Selection>& theSelection);

  static occ::handle<Graphic3d_Camera> ConvertVtkToOccCamera(const IVtk_IView::Handle& theView);

  DEFINE_STANDARD_RTTIEXT(IVtkOCC_ViewerSelector, SelectMgr_ViewerSelector)

private:
  int  myPixTol;
  bool myToUpdateTol;
};
