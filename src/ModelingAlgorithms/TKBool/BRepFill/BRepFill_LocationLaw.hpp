#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Wire.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <GeomFill_PipeError.hpp>
class GeomFill_LocationLaw;
class TopoDS_Edge;
class TopoDS_Vertex;
class TopoDS_Shape;

//! Location Law on a Wire.
class BRepFill_LocationLaw : public Standard_Transient
{

public:
  //! Return a error status, if the status is not PipeOk then
  //! it exist a parameter tlike the law is not valuable for t.
  Standard_EXPORT GeomFill_PipeError GetStatus() const;

  //! Apply a linear transformation on each law, to have
  //! continuity of the global law between the edges.
  Standard_EXPORT virtual void TransformInG0Law();

  //! Apply a linear transformation on each law, to reduce
  //! the dicontinuities of law at one rotation.
  Standard_EXPORT virtual void TransformInCompatibleLaw(const double AngularTolerance);

  Standard_EXPORT void DeleteTransform();

  Standard_EXPORT int NbHoles(const double Tol = 1.0e-7);

  Standard_EXPORT void Holes(NCollection_Array1<int>& Interval) const;

  //! Return the number of elementary Law
  Standard_EXPORT int NbLaw() const;

  //! Return the elementary Law of rank <Index>
  //! <Index> have to be in [1, NbLaw()]
  Standard_EXPORT const occ::handle<GeomFill_LocationLaw>& Law(const int Index) const;

  //! return the path
  Standard_EXPORT const TopoDS_Wire& Wire() const;

  //! Return the Edge of rank <Index> in the path
  //! <Index> have to be in [1, NbLaw()]
  Standard_EXPORT const TopoDS_Edge& Edge(const int Index) const;

  //! Return the vertex of rank <Index> in the path
  //! <Index> have to be in [0, NbLaw()]
  Standard_EXPORT TopoDS_Vertex Vertex(const int Index) const;

  //! Compute <OutputVertex> like a transformation of
  //! <InputVertex> the transformation is given by
  //! evaluation of the location law in the vertex of
  //! rank <Index>.
  //! <Location> is used to manage discontinuities:
  //! - -1 : The law before the vertex is used.
  //! -  1 : The law after the vertex is used.
  //! -  0 : Average of the both laws is used.
  Standard_EXPORT void PerformVertex(const int            Index,
                                     const TopoDS_Vertex& InputVertex,
                                     const double         TolMin,
                                     TopoDS_Vertex&       OutputVertex,
                                     const int            Location = 0) const;

  //! Return the Curvilinear Bounds of the <Index> Law
  Standard_EXPORT void CurvilinearBounds(const int Index, double& First, double& Last) const;

  Standard_EXPORT bool IsClosed() const;

  //! Compute the Law's continuity between 2 edges of the path
  //! The result can be :
  //! -1 : Case Not connex
  //! 0  : It is connex (G0)
  //! 1  : It is tangent (G1)
  Standard_EXPORT int IsG1(const int    Index,
                           const double SpatialTolerance = 1.0e-7,
                           const double AngularTolerance = 1.0e-4) const;

  //! Apply the Law to a shape, for a given Curvilinear abscissa
  Standard_EXPORT void D0(const double Abscissa, TopoDS_Shape& Section);

  //! Find the index Law and the parameter, for a given Curvilinear abscissa
  Standard_EXPORT void Parameter(const double Abscissa, int& Index, double& Param);

  //! Return the curvilinear abscissa corresponding to a point
  //! of the path, defined by <Index> of Edge and a parameter
  //! on the edge.
  Standard_EXPORT double Abscissa(const int Index, const double Param);

  DEFINE_STANDARD_RTTIEXT(BRepFill_LocationLaw, Standard_Transient)

protected:
  //! Initialize all the fields, this methode has to
  //! be called by the constructors of Inherited class.
  Standard_EXPORT void Init(const TopoDS_Wire& Path);

  //! To preserve if possible the Tangent in transformations
  //! It is the default mode.
  Standard_EXPORT void TangentIsMain();

  //! To preserve if possible the Normal in transformations
  Standard_EXPORT void NormalIsMain();

  //! To preserve if possible the BiNormal in transformations
  Standard_EXPORT void BiNormalIsMain();

  TopoDS_Wire                                                         myPath;
  double                                                              myTol;
  occ::handle<NCollection_HArray1<occ::handle<GeomFill_LocationLaw>>> myLaws;
  occ::handle<NCollection_HArray1<double>>                            myLength;
  occ::handle<NCollection_HArray1<TopoDS_Shape>>                      myEdges;
  occ::handle<NCollection_HArray1<int>>                               myDisc;

private:
  int myType;
};

