#pragma once


#include <Bnd_Box.hpp>
#include <IVtkOCC_Shape.hpp>
#include <Prs3d_Drawer.hpp>
#include <SelectMgr_SelectableObject.hpp>
#include <SelectMgr_Selection.hpp>

// -----------------------------------------------------------------------------
//! @class IVtkOCC_SelectableObject
//! @brief Class with selection primitives used by OCCT selection algorithm.
class IVtkOCC_SelectableObject : public SelectMgr_SelectableObject
{
public:
  typedef occ::handle<IVtkOCC_SelectableObject> Handle;

  //! Constructs a selectable object initialized by the given shape
  //! @param[in]  theShape Selectable shape
  IVtkOCC_SelectableObject(const IVtkOCC_Shape::Handle& theShape);

  //! Constructs uninitialized selectable object.
  //! setShape() should be called later.
  IVtkOCC_SelectableObject();

  ~IVtkOCC_SelectableObject() override;

  //! Sets the selectable shape
  //! @param[in]  theShape Selectable shape
  Standard_EXPORT void SetShape(const IVtkOCC_Shape::Handle& theShape);

  const IVtkOCC_Shape::Handle& GetShape() const { return myShape; };

  //! Returns bounding box of object
  Standard_EXPORT void BoundingBox(Bnd_Box& theBndBox) override;

  DEFINE_STANDARD_RTTIEXT(IVtkOCC_SelectableObject, SelectMgr_SelectableObject)

private:
  //! Internal method, computes selection data for viewer selector
  //! Inspired by AIS_Shape::ComputeSelection() from OCCT 6.5.1
  //! @param[in]  selection container for sensitive primitives
  //! @param[in]  mode Selection mode
  void ComputeSelection(const occ::handle<SelectMgr_Selection>& theSelection,
                        const int                               theMode) override;

  //! Dummy.
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

