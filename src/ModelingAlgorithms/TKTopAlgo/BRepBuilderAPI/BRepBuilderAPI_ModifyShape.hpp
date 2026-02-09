#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepTools_Modifier.hpp>
#include <TopoDS_Shape.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <NCollection_List.hpp>
class BRepTools_Modification;

class BRepBuilderAPI_ModifyShape : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& Modified(const TopoDS_Shape& S) override;

  Standard_EXPORT virtual TopoDS_Shape ModifiedShape(const TopoDS_Shape& S) const;

protected:
  Standard_EXPORT BRepBuilderAPI_ModifyShape();

  Standard_EXPORT BRepBuilderAPI_ModifyShape(const TopoDS_Shape& S);

  Standard_EXPORT BRepBuilderAPI_ModifyShape(const occ::handle<BRepTools_Modification>& M);

  Standard_EXPORT BRepBuilderAPI_ModifyShape(const TopoDS_Shape&                        S,
                                             const occ::handle<BRepTools_Modification>& M);

  Standard_EXPORT void DoModif(const TopoDS_Shape& S);

  Standard_EXPORT void DoModif(const occ::handle<BRepTools_Modification>& M);

  Standard_EXPORT void DoModif(const TopoDS_Shape& S, const occ::handle<BRepTools_Modification>& M);

  BRepTools_Modifier                  myModifier;
  TopoDS_Shape                        myInitialShape;
  occ::handle<BRepTools_Modification> myModification;

private:
  Standard_EXPORT void DoModif();
};
