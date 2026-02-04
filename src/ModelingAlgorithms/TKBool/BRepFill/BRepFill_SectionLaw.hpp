#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <GeomFill_SectionLaw.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <Standard_Transient.hpp>
#include <GeomAbs_Shape.hpp>
class GeomFill_SectionLaw;
class TopoDS_Vertex;
class TopoDS_Shape;
class TopoDS_Wire;
class TopoDS_Edge;

//! Build Section Law, with an Vertex, or an Wire
class BRepFill_SectionLaw : public Standard_Transient
{

public:
  Standard_EXPORT int NbLaw() const;

  Standard_EXPORT const occ::handle<GeomFill_SectionLaw>& Law(const int Index) const;

  Standard_EXPORT int IndexOfEdge(const TopoDS_Shape& anEdge) const;

  Standard_EXPORT virtual bool IsConstant() const = 0;

  Standard_EXPORT bool IsUClosed() const;

  Standard_EXPORT bool IsVClosed() const;

  Standard_EXPORT bool IsDone() const;

  //! Say if the input shape is a vertex.
  Standard_EXPORT virtual bool IsVertex() const = 0;

  Standard_EXPORT virtual occ::handle<GeomFill_SectionLaw> ConcatenedLaw() const = 0;

  Standard_EXPORT virtual GeomAbs_Shape Continuity(const int    Index,
                                                   const double TolAngular) const = 0;

  Standard_EXPORT virtual double VertexTol(const int Index, const double Param) const = 0;

  Standard_EXPORT virtual TopoDS_Vertex Vertex(const int Index, const double Param) const = 0;

  Standard_EXPORT virtual void D0(const double U, TopoDS_Shape& S) = 0;

  Standard_EXPORT void Init(const TopoDS_Wire& W);

  Standard_EXPORT TopoDS_Edge CurrentEdge();

  DEFINE_STANDARD_RTTIEXT(BRepFill_SectionLaw, Standard_Transient)

protected:
  occ::handle<NCollection_HArray1<occ::handle<GeomFill_SectionLaw>>> myLaws;
  bool                                                               uclosed;
  bool                                                               vclosed;
  bool                                                               myDone;
  NCollection_DataMap<TopoDS_Shape, int, TopTools_ShapeMapHasher>    myIndices;

private:
  BRepTools_WireExplorer myIterator;
};

