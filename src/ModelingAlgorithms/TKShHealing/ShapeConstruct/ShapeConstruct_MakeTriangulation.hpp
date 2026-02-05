#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Wire.hpp>
#include <BRepBuilderAPI_MakeShape.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array1.hpp>

class ShapeConstruct_MakeTriangulation : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeConstruct_MakeTriangulation(const NCollection_Array1<gp_Pnt>& pnts,
                                                   const double                      prec = 0.0);

  Standard_EXPORT ShapeConstruct_MakeTriangulation(const TopoDS_Wire& wire,
                                                   const double       prec = 0.0);

  Standard_EXPORT void Build(
    const Message_ProgressRange& theRange = Message_ProgressRange()) override;

  Standard_EXPORT bool IsDone() const override;

private:
  Standard_EXPORT void Triangulate(const TopoDS_Wire& wire);

  Standard_EXPORT void AddFacet(const TopoDS_Wire& wire);

  double      myPrecision;
  TopoDS_Wire myWire;
};
