#pragma once

#include <IVtk_IShapePickerAlgo.hpp>
#include <IVtkOCC_ViewerSelector.hpp>

class IVtkOCC_ShapePickerAlgo : public IVtk_IShapePickerAlgo
{
public:
  typedef occ::handle<IVtkOCC_ShapePickerAlgo> Handle;

  Standard_EXPORT IVtkOCC_ShapePickerAlgo();

  Standard_EXPORT ~IVtkOCC_ShapePickerAlgo() override;

  Standard_EXPORT void SetView(const IVtk_IView::Handle& theView) override;

  Standard_EXPORT int NbPicked() override;

  Standard_EXPORT NCollection_List<IVtk_SelectionMode> GetSelectionModes(
    const IVtk_IShape::Handle& theShape) const override;

public:
  Standard_EXPORT void SetSelectionMode(const IVtk_IShape::Handle& theShape,
                                        const IVtk_SelectionMode   theMode,
                                        const bool                 theIsTurnOn = true) override;

  Standard_EXPORT void SetSelectionMode(const NCollection_List<IVtk_IShape::Handle>& theShapes,
                                        const IVtk_SelectionMode                     theMode,
                                        const bool theIsTurnOn = true) override;

public:
  Standard_EXPORT bool Pick(const double theX, const double theY) override;

  Standard_EXPORT bool Pick(const double theXMin,
                            const double theYMin,
                            const double theXMax,
                            const double theYMax) override;

  Standard_EXPORT bool Pick(double** thePolyLine, const int theNbPoints) override;

public:
  Standard_EXPORT const NCollection_List<IVtk_IdType>& ShapesPicked() const override;

  Standard_EXPORT void SubShapesPicked(const IVtk_IdType              theId,
                                       NCollection_List<IVtk_IdType>& theShapeList) const override;

  Standard_EXPORT virtual void RemoveSelectableObject(const IVtk_IShape::Handle& theShape);

  const gp_Pnt& TopPickedPoint() const { return myTopPickedPoint; }

public:
  DEFINE_STANDARD_RTTIEXT(IVtkOCC_ShapePickerAlgo, IVtk_IShapePickerAlgo)

private:
  void clearPicked();

  bool processPicked();

  IVtk_IView::Handle                                              myView;
  NCollection_List<IVtk_IdType>                                   myShapesPicked;
  NCollection_DataMap<IVtk_IdType, NCollection_List<IVtk_IdType>> mySubShapesPicked;
  gp_Pnt                                                          myTopPickedPoint;
  occ::handle<IVtkOCC_ViewerSelector>                             myViewerSelector;
};
