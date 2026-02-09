#pragma once

#include <Bnd_Box.hpp>
#include <IVtkOCC_Shape.hpp>
#include <Prs3d_Drawer.hpp>
#include <SelectMgr_SelectableObject.hpp>
#include <SelectMgr_Selection.hpp>

class IVtkOCC_SelectableObject : public SelectMgr_SelectableObject
{
public:
  typedef occ::handle<IVtkOCC_SelectableObject> Handle;

  IVtkOCC_SelectableObject(const IVtkOCC_Shape::Handle& theShape);

  IVtkOCC_SelectableObject();

  ~IVtkOCC_SelectableObject() override;

  Standard_EXPORT void SetShape(const IVtkOCC_Shape::Handle& theShape);

  const IVtkOCC_Shape::Handle& GetShape() const { return myShape; };

  Standard_EXPORT void BoundingBox(Bnd_Box& theBndBox) override;

  DEFINE_STANDARD_RTTIEXT(IVtkOCC_SelectableObject, SelectMgr_SelectableObject)

private:
  void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                        const int                               theMode) override;

  void Compute(const occ::handle<PrsMgr_PresentationManager>&,
               const occ::handle<Prs3d_Presentation>&,
               const int) override
  {
  }

  const Bnd_Box& BoundingBox();

private:
  IVtkOCC_Shape::Handle myShape;
  Bnd_Box               myBndBox;
};
