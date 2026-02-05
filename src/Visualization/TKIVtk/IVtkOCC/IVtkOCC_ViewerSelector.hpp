#pragma once

#include <IVtk_IView.hpp>
#include <SelectMgr_Selection.hpp>
#include <SelectMgr_ViewerSelector.hpp>

// -----------------------------------------------------------------------------
//! @class IVtkOCC_ViewerSelector
//! @brief Class that implements OCCT selection algorithm.
//!
//! Inspired by StdSelect_ViewerSelector3d class from OCCT 6.5.1
class IVtkOCC_ViewerSelector : public SelectMgr_ViewerSelector
{
public:
  IVtkOCC_ViewerSelector();

  ~IVtkOCC_ViewerSelector() override;

  //! Implements point picking
  //! @param[in]  theXPix, theYPix Display coordinates of the point
  //! @param[in]  theView  ICamera interface to update the projection parameters.
  void Pick(const int theXPix, const int theYPix, const IVtk_IView::Handle& theView);

  //! Picking by rectangle
  //! @param[in]  theXMin, theYMin, theXMax, theYMax Rectangle coords
  //! @param[in]  theView ICamera interface to calculate projections
  void Pick(const int                 theXMin,
            const int                 theYMin,
            const int                 theXMax,
            const int                 theYMax,
            const IVtk_IView::Handle& theView);

  //! Implements point picking
  void Pick(double** thePoly, const int theNbPoints, const IVtk_IView::Handle& theView);

  //! Activates the given selection
  void Activate(const occ::handle<SelectMgr_Selection>& theSelection);

  //! Deactivate the given selection
  void Deactivate(const occ::handle<SelectMgr_Selection>& theSelection);

  //! Converts VTK camera defined for input view to OCC camera
  static occ::handle<Graphic3d_Camera> ConvertVtkToOccCamera(const IVtk_IView::Handle& theView);

  DEFINE_STANDARD_RTTIEXT(IVtkOCC_ViewerSelector, SelectMgr_ViewerSelector)

private:
  int  myPixTol;
  bool myToUpdateTol;
};
