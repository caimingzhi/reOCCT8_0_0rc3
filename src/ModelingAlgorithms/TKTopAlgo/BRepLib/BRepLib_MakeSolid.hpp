#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepLib_MakeShape.hpp>
#include <BRepLib_ShapeModification.hpp>
class TopoDS_CompSolid;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_Face;

class BRepLib_MakeSolid : public BRepLib_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepLib_MakeSolid();

  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_CompSolid& S);

  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_Shell& S);

  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_Shell& S1, const TopoDS_Shell& S2);

  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_Shell& S1,
                                    const TopoDS_Shell& S2,
                                    const TopoDS_Shell& S3);

  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_Solid& So);

  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_Solid& So, const TopoDS_Shell& S);

  Standard_EXPORT void Add(const TopoDS_Shell& S);

  Standard_EXPORT const TopoDS_Solid& Solid();
  Standard_EXPORT                     operator TopoDS_Solid();

  Standard_EXPORT BRepLib_ShapeModification FaceStatus(const TopoDS_Face& F) const override;

protected:
  NCollection_List<TopoDS_Shape> myDeletedFaces;
};
