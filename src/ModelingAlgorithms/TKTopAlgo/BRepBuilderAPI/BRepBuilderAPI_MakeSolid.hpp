#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepLib_MakeSolid.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
class TopoDS_CompSolid;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_Shape;

class BRepBuilderAPI_MakeSolid : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepBuilderAPI_MakeSolid();

  Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_CompSolid& S);

  Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_Shell& S);

  Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_Shell& S1, const TopoDS_Shell& S2);

  Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_Shell& S1,
                                           const TopoDS_Shell& S2,
                                           const TopoDS_Shell& S3);

  Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_Solid& So);

  Standard_EXPORT BRepBuilderAPI_MakeSolid(const TopoDS_Solid& So, const TopoDS_Shell& S);

  Standard_EXPORT void Add(const TopoDS_Shell& S);

  Standard_EXPORT bool IsDone() const override;

  Standard_EXPORT const TopoDS_Solid& Solid();
  Standard_EXPORT                     operator TopoDS_Solid();

  Standard_EXPORT bool IsDeleted(const TopoDS_Shape& S) override;

private:
  BRepLib_MakeSolid myMakeSolid;
};
