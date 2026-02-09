#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <BRepFill_SectionLaw.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
class Law_Function;
class TopoDS_Vertex;
class TopoDS_Wire;
class GeomFill_SectionLaw;
class TopoDS_Edge;

class BRepFill_ShapeLaw : public BRepFill_SectionLaw
{

public:
  Standard_EXPORT BRepFill_ShapeLaw(const TopoDS_Vertex& V, const bool Build = true);

  Standard_EXPORT BRepFill_ShapeLaw(const TopoDS_Wire& W, const bool Build = true);

  Standard_EXPORT BRepFill_ShapeLaw(const TopoDS_Wire&               W,
                                    const occ::handle<Law_Function>& L,
                                    const bool                       Build = true);

  Standard_EXPORT bool IsVertex() const override;

  Standard_EXPORT bool IsConstant() const override;

  Standard_EXPORT occ::handle<GeomFill_SectionLaw> ConcatenedLaw() const override;

  Standard_EXPORT GeomAbs_Shape Continuity(const int Index, const double TolAngular) const override;

  Standard_EXPORT double VertexTol(const int Index, const double Param) const override;

  Standard_EXPORT TopoDS_Vertex Vertex(const int Index, const double Param) const override;

  Standard_EXPORT void D0(const double Param, TopoDS_Shape& S) override;

  const TopoDS_Edge& Edge(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(BRepFill_ShapeLaw, BRepFill_SectionLaw)

protected:
  bool vertex;

private:
  Standard_EXPORT void Init(const bool B);

  TopoDS_Shape                                   myShape;
  occ::handle<NCollection_HArray1<TopoDS_Shape>> myEdges;
  occ::handle<Law_Function>                      TheLaw;
};

#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

inline const TopoDS_Edge& BRepFill_ShapeLaw::Edge(const int Index) const
{
  return TopoDS::Edge(myEdges->Value(Index));
}
