#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Geom2dHatch_Element.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Boolean.hpp>
#include <TopAbs_Orientation.hpp>
class Geom2dHatch_Element;
class gp_Pnt2d;
class gp_Lin2d;
class Geom2dAdaptor_Curve;

class Geom2dHatch_Elements
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dHatch_Elements();

  Standard_EXPORT Geom2dHatch_Elements(const Geom2dHatch_Elements& Other);

  Standard_EXPORT void Clear();

  ~Geom2dHatch_Elements() { Clear(); }

  Standard_EXPORT bool Bind(const int K, const Geom2dHatch_Element& I);

  Standard_EXPORT bool IsBound(const int K) const;

  Standard_EXPORT bool UnBind(const int K);

  Standard_EXPORT const Geom2dHatch_Element& Find(const int K) const;

  const Geom2dHatch_Element& operator()(const int K) const { return Find(K); }

  Standard_EXPORT Geom2dHatch_Element& ChangeFind(const int K);

  Geom2dHatch_Element& operator()(const int K) { return ChangeFind(K); }

  Standard_EXPORT bool CheckPoint(gp_Pnt2d& P);

  Standard_EXPORT bool Reject(const gp_Pnt2d& P) const;

  Standard_EXPORT bool Segment(const gp_Pnt2d& P, gp_Lin2d& L, double& Par);

  Standard_EXPORT bool OtherSegment(const gp_Pnt2d& P, gp_Lin2d& L, double& Par);

  Standard_EXPORT void InitWires();

  Standard_EXPORT bool MoreWires() const;

  Standard_EXPORT void NextWire();

  Standard_EXPORT bool RejectWire(const gp_Lin2d& L, const double Par) const;

  Standard_EXPORT void InitEdges();

  Standard_EXPORT bool MoreEdges() const;

  Standard_EXPORT void NextEdge();

  Standard_EXPORT bool RejectEdge(const gp_Lin2d& L, const double Par) const;

  Standard_EXPORT void CurrentEdge(Geom2dAdaptor_Curve& E, TopAbs_Orientation& Or) const;

private:
  NCollection_DataMap<int, Geom2dHatch_Element>           myMap;
  NCollection_DataMap<int, Geom2dHatch_Element>::Iterator Iter;
  int                                                     NumWire;
  int                                                     NumEdge;
  int                                                     myCurEdge;
  double                                                  myCurEdgePar;
};
