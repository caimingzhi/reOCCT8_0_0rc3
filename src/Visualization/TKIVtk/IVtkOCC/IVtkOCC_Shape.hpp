#pragma once

#include <IVtk_IShape.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <SelectMgr_SelectableObject.hpp>

class IVtkOCC_Shape : public IVtk_IShape
{
public:
  typedef occ::handle<IVtkOCC_Shape> Handle;

  Standard_EXPORT IVtkOCC_Shape(
    const TopoDS_Shape&              theShape,
    const occ::handle<Prs3d_Drawer>& theDrawerLink = occ::handle<Prs3d_Drawer>());

  Standard_EXPORT ~IVtkOCC_Shape() override;

  Standard_EXPORT IVtk_IdType GetSubShapeId(const IVtk_IShape::Handle&) const;

  DEFINE_STANDARD_RTTIEXT(IVtkOCC_Shape, IVtk_IShape)

  const TopoDS_Shape& GetShape() const { return myTopoDSShape; }

  Standard_EXPORT IVtk_IdType GetSubShapeId(const TopoDS_Shape& theSubShape) const;

  Standard_EXPORT NCollection_List<IVtk_IdType> GetSubIds(const IVtk_IdType) const override;

  Standard_EXPORT const TopoDS_Shape& GetSubShape(const IVtk_IdType theId) const;

  void SetSelectableObject(const occ::handle<SelectMgr_SelectableObject>& theSelObj)
  {
    mySelectable = theSelObj;
  }

  const occ::handle<SelectMgr_SelectableObject>& GetSelectableObject() const
  {
    return mySelectable;
  }

  const occ::handle<Prs3d_Drawer>& Attributes() const { return myOCCTDrawer; }

  void SetAttributes(const occ::handle<Prs3d_Drawer>& theDrawer) { myOCCTDrawer = theDrawer; }

private:
  void buildSubShapeIdMap();

private:
  NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> mySubShapeIds;
  TopoDS_Shape                                                  myTopoDSShape;
  occ::handle<Prs3d_Drawer>                                     myOCCTDrawer;
  occ::handle<SelectMgr_SelectableObject>                       mySelectable;
};
