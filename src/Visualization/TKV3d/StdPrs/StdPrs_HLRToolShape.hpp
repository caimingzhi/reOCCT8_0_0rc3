#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <HLRAlgo_EdgeIterator.hpp>
#include <Standard_Integer.hpp>
class HLRBRep_Data;
class TopoDS_Shape;
class HLRAlgo_Projector;
class BRepAdaptor_Curve;

class StdPrs_HLRToolShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StdPrs_HLRToolShape(const TopoDS_Shape&      TheShape,
                                      const HLRAlgo_Projector& TheProjector);

  Standard_EXPORT int NbEdges() const;

  Standard_EXPORT void InitVisible(const int EdgeNumber);

  Standard_EXPORT bool MoreVisible() const;

  Standard_EXPORT void NextVisible();

  Standard_EXPORT void Visible(BRepAdaptor_Curve& TheEdge, double& U1, double& U2);

  Standard_EXPORT void InitHidden(const int EdgeNumber);

  Standard_EXPORT bool MoreHidden() const;

  Standard_EXPORT void NextHidden();

  Standard_EXPORT void Hidden(BRepAdaptor_Curve& TheEdge, double& U1, double& U2);

private:
  occ::handle<HLRBRep_Data> MyData;
  HLRAlgo_EdgeIterator      myEdgeIterator;
  int                       MyCurrentEdgeNumber;
};

