#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepLib_MakeShape.hpp>
#include <BRepLib_ShapeModification.hpp>
class TopoDS_CompSolid;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_Face;

//! Makes a solid from compsolid or shells.
class BRepLib_MakeSolid : public BRepLib_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Solid covers whole space.
  Standard_EXPORT BRepLib_MakeSolid();

  //! Make a solid from a CompSolid.
  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_CompSolid& S);

  //! Make a solid from a shell.
  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_Shell& S);

  //! Make a solid from two shells.
  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_Shell& S1, const TopoDS_Shell& S2);

  //! Make a solid from three shells.
  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_Shell& S1,
                                    const TopoDS_Shell& S2,
                                    const TopoDS_Shell& S3);

  //! Make a solid from a solid. Useful for adding later.
  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_Solid& So);

  //! Add a shell to a solid.
  Standard_EXPORT BRepLib_MakeSolid(const TopoDS_Solid& So, const TopoDS_Shell& S);

  //! Add the shell to the current solid.
  Standard_EXPORT void Add(const TopoDS_Shell& S);

  //! Returns the new Solid.
  Standard_EXPORT const TopoDS_Solid& Solid();
  Standard_EXPORT                     operator TopoDS_Solid();

  //! returns the status of the Face after
  //! the shape creation.
  Standard_EXPORT BRepLib_ShapeModification FaceStatus(const TopoDS_Face& F) const override;

protected:
  NCollection_List<TopoDS_Shape> myDeletedFaces;
};

