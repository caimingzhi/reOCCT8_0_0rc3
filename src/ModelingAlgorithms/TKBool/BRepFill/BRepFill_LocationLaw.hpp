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

class BRepFill_LocationLaw : public Standard_Transient
{

public:
  Standard_EXPORT GeomFill_PipeError GetStatus() const;

  Standard_EXPORT virtual void TransformInG0Law();

  Standard_EXPORT virtual void TransformInCompatibleLaw(const double AngularTolerance);

  Standard_EXPORT void DeleteTransform();

  Standard_EXPORT int NbHoles(const double Tol = 1.0e-7);

  Standard_EXPORT void Holes(NCollection_Array1<int>& Interval) const;

  Standard_EXPORT int NbLaw() const;

  Standard_EXPORT const occ::handle<GeomFill_LocationLaw>& Law(const int Index) const;

  Standard_EXPORT const TopoDS_Wire& Wire() const;

  Standard_EXPORT const TopoDS_Edge& Edge(const int Index) const;

  Standard_EXPORT TopoDS_Vertex Vertex(const int Index) const;

  Standard_EXPORT void PerformVertex(const int            Index,
                                     const TopoDS_Vertex& InputVertex,
                                     const double         TolMin,
                                     TopoDS_Vertex&       OutputVertex,
                                     const int            Location = 0) const;

  Standard_EXPORT void CurvilinearBounds(const int Index, double& First, double& Last) const;

  Standard_EXPORT bool IsClosed() const;

  Standard_EXPORT int IsG1(const int    Index,
                           const double SpatialTolerance = 1.0e-7,
                           const double AngularTolerance = 1.0e-4) const;

  Standard_EXPORT void D0(const double Abscissa, TopoDS_Shape& Section);

  Standard_EXPORT void Parameter(const double Abscissa, int& Index, double& Param);

  Standard_EXPORT double Abscissa(const int Index, const double Param);

  DEFINE_STANDARD_RTTIEXT(BRepFill_LocationLaw, Standard_Transient)

protected:
  Standard_EXPORT void Init(const TopoDS_Wire& Path);

  Standard_EXPORT void TangentIsMain();

  Standard_EXPORT void NormalIsMain();

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
