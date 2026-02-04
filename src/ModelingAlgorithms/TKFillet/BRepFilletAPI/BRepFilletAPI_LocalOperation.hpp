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

//! Construction of fillets on the edges of a Shell.
class BRepFilletAPI_LocalOperation : public BRepBuilderAPI_MakeShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Adds a contour in the builder (builds a
  //! contour of tangent edges).
  Standard_EXPORT virtual void Add(const TopoDS_Edge& E) = 0;

  //! Reset the contour of index IC, there is nomore
  //! information in the contour.
  Standard_EXPORT virtual void ResetContour(const int IC) = 0;

  //! Number of contours.
  Standard_EXPORT virtual int NbContours() const = 0;

  //! Returns the index of the contour containing the edge
  //! E, returns 0 if E doesn't belong to any contour.
  Standard_EXPORT virtual int Contour(const TopoDS_Edge& E) const = 0;

  //! Number of Edges in the contour I.
  Standard_EXPORT virtual int NbEdges(const int I) const = 0;

  //! Returns the Edge J in the contour I.
  Standard_EXPORT virtual const TopoDS_Edge& Edge(const int I, const int J) const = 0;

  //! remove the contour containing the Edge E.
  Standard_EXPORT virtual void Remove(const TopoDS_Edge& E) = 0;

  //! returns the length the contour of index IC.
  Standard_EXPORT virtual double Length(const int IC) const = 0;

  //! Returns the first Vertex of the contour of index IC.
  Standard_EXPORT virtual TopoDS_Vertex FirstVertex(const int IC) const = 0;

  //! Returns the last Vertex of the contour of index IC.
  Standard_EXPORT virtual TopoDS_Vertex LastVertex(const int IC) const = 0;

  //! returns the abscissa of the vertex V on
  //! the contour of index IC.
  Standard_EXPORT virtual double Abscissa(const int IC, const TopoDS_Vertex& V) const = 0;

  //! returns the relative abscissa([0.,1.]) of the
  //! vertex V on the contour of index IC.
  Standard_EXPORT virtual double RelativeAbscissa(const int IC, const TopoDS_Vertex& V) const = 0;

  //! returns true if the contour of index IC is closed
  //! an tangent.
  Standard_EXPORT virtual bool ClosedAndTangent(const int IC) const = 0;

  //! returns true if the contour of index IC is closed
  Standard_EXPORT virtual bool Closed(const int IC) const = 0;

  //! Reset all the fields updated by Build operation and
  //! leave the algorithm in the same state than before
  //! build call. It allows contours and radius
  //! modifications to build the result another time.
  Standard_EXPORT virtual void Reset() = 0;

  Standard_EXPORT virtual void Simulate(const int IC) = 0;

  Standard_EXPORT virtual int NbSurf(const int IC) const = 0;

  Standard_EXPORT virtual occ::handle<NCollection_HArray1<ChFiDS_CircSection>> Sect(
    const int IC,
    const int IS) const = 0;
};

