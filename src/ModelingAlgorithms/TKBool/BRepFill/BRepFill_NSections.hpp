#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_HArray2.hpp>
#include <BRepFill_SectionLaw.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_Integer.hpp>
class Geom_BSplineSurface;
class GeomFill_SectionLaw;
class TopoDS_Vertex;
class TopoDS_Shape;

//! Build Section Law, with N Sections
class BRepFill_NSections : public BRepFill_SectionLaw
{

public:
  //! Construct
  Standard_EXPORT BRepFill_NSections(const NCollection_Sequence<TopoDS_Shape>& S,
                                     const bool                                Build = true);

  //! Construct
  Standard_EXPORT BRepFill_NSections(const NCollection_Sequence<TopoDS_Shape>& S,
                                     const NCollection_Sequence<gp_Trsf>&      Trsfs,
                                     const NCollection_Sequence<double>&       P,
                                     const double                              VF,
                                     const double                              VL,
                                     const bool                                Build = true);

  //! Say if the input shape is a vertex.
  Standard_EXPORT bool IsVertex() const override;

  //! Say if the Law is Constant.
  Standard_EXPORT bool IsConstant() const override;

  //! Give the law build on a concatenated section
  Standard_EXPORT occ::handle<GeomFill_SectionLaw> ConcatenedLaw() const override;

  Standard_EXPORT GeomAbs_Shape Continuity(const int Index, const double TolAngular) const override;

  Standard_EXPORT double VertexTol(const int Index, const double Param) const override;

  Standard_EXPORT TopoDS_Vertex Vertex(const int Index, const double Param) const override;

  Standard_EXPORT void D0(const double Param, TopoDS_Shape& S) override;

  DEFINE_STANDARD_RTTIEXT(BRepFill_NSections, BRepFill_SectionLaw)

private:
  Standard_EXPORT void Init(const NCollection_Sequence<double>& P, const bool B);

  double                                         VFirst;
  double                                         VLast;
  NCollection_Sequence<TopoDS_Shape>             myShapes;
  NCollection_Sequence<gp_Trsf>                  myTrsfs;
  NCollection_Sequence<double>                   myParams;
  occ::handle<NCollection_HArray2<TopoDS_Shape>> myEdges;
  occ::handle<Geom_BSplineSurface>               mySurface;
};

