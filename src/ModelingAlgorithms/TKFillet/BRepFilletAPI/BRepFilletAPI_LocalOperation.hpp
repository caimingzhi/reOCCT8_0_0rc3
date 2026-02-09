#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepBuilderAPI_MakeShape.hpp>
#include <Standard_Integer.hpp>
#include <ChFiDS_CircSection.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
class TopoDS_Edge;
class TopoDS_Vertex;

class BRepFilletAPI_LocalOperation : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT virtual void Add(const TopoDS_Edge& E) = 0;

  Standard_EXPORT virtual void ResetContour(const int IC) = 0;

  Standard_EXPORT virtual int NbContours() const = 0;

  Standard_EXPORT virtual int Contour(const TopoDS_Edge& E) const = 0;

  Standard_EXPORT virtual int NbEdges(const int I) const = 0;

  Standard_EXPORT virtual const TopoDS_Edge& Edge(const int I, const int J) const = 0;

  Standard_EXPORT virtual void Remove(const TopoDS_Edge& E) = 0;

  Standard_EXPORT virtual double Length(const int IC) const = 0;

  Standard_EXPORT virtual TopoDS_Vertex FirstVertex(const int IC) const = 0;

  Standard_EXPORT virtual TopoDS_Vertex LastVertex(const int IC) const = 0;

  Standard_EXPORT virtual double Abscissa(const int IC, const TopoDS_Vertex& V) const = 0;

  Standard_EXPORT virtual double RelativeAbscissa(const int IC, const TopoDS_Vertex& V) const = 0;

  Standard_EXPORT virtual bool ClosedAndTangent(const int IC) const = 0;

  Standard_EXPORT virtual bool Closed(const int IC) const = 0;

  Standard_EXPORT virtual void Reset() = 0;

  Standard_EXPORT virtual void Simulate(const int IC) = 0;

  Standard_EXPORT virtual int NbSurf(const int IC) const = 0;

  Standard_EXPORT virtual occ::handle<NCollection_HArray1<ChFiDS_CircSection>> Sect(
    const int IC,
    const int IS) const = 0;
};
