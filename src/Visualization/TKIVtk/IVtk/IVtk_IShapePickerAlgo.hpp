#pragma once

#include <IVtk_IView.hpp>
#include <IVtk_IShape.hpp>

class IVtk_IShapePickerAlgo : public IVtk_Interface
{
public:
  typedef occ::handle<IVtk_IShapePickerAlgo> Handle;

  ~IVtk_IShapePickerAlgo() override = default;

  DEFINE_STANDARD_RTTIEXT(IVtk_IShapePickerAlgo, IVtk_Interface)

  virtual void SetView(const IVtk_IView::Handle& theView) = 0;
  virtual int  NbPicked()                                 = 0;

  virtual NCollection_List<IVtk_SelectionMode> GetSelectionModes(
    const IVtk_IShape::Handle& theShape) const = 0;

public:
  virtual void SetSelectionMode(const IVtk_IShape::Handle& theShape,
                                const IVtk_SelectionMode   theMode,
                                const bool                 theIsTurnOn = true) = 0;

  virtual void SetSelectionMode(const NCollection_List<IVtk_IShape::Handle>& theShapes,
                                const IVtk_SelectionMode                     theMode,
                                const bool theIsTurnOn = true) = 0;

public:
  virtual bool Pick(const double theX, const double theY) = 0;
  virtual bool Pick(const double theXMin,
                    const double theYMin,
                    const double theXMax,
                    const double theYMax)                 = 0;

  virtual bool Pick(double**, const int theNbPoints) = 0;

public:
  virtual const NCollection_List<IVtk_IdType>& ShapesPicked() const = 0;

  virtual void SubShapesPicked(const IVtk_IdType              theId,
                               NCollection_List<IVtk_IdType>& theShapeList) const = 0;
};
