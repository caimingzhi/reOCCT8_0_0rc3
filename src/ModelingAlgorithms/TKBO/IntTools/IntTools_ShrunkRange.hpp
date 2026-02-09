#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Edge.hpp>
#include <TopoDS_Vertex.hpp>
#include <Bnd_Box.hpp>
#include <Standard_Integer.hpp>
class IntTools_Context;

class IntTools_ShrunkRange
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_ShrunkRange();
  Standard_EXPORT virtual ~IntTools_ShrunkRange();

  Standard_EXPORT void SetData(const TopoDS_Edge&   aE,
                               const double         aT1,
                               const double         aT2,
                               const TopoDS_Vertex& aV1,
                               const TopoDS_Vertex& aV2);

  Standard_EXPORT void SetContext(const occ::handle<IntTools_Context>& aCtx);

  Standard_EXPORT const occ::handle<IntTools_Context>& Context() const;

  Standard_EXPORT void SetShrunkRange(const double aT1, const double aT2);

  Standard_EXPORT void ShrunkRange(double& aT1, double& aT2) const;

  Standard_EXPORT const Bnd_Box& BndBox() const;

  Standard_EXPORT const TopoDS_Edge& Edge() const;

  Standard_EXPORT void Perform();

  bool IsDone() const { return myIsDone; }

  bool IsSplittable() const { return myIsSplittable; }

  double Length() const { return myLength; }

protected:
  TopoDS_Edge                   myEdge;
  TopoDS_Vertex                 myV1;
  TopoDS_Vertex                 myV2;
  double                        myT1;
  double                        myT2;
  double                        myTS1;
  double                        myTS2;
  Bnd_Box                       myBndBox;
  occ::handle<IntTools_Context> myCtx;
  bool                          myIsDone;
  bool                          myIsSplittable;
  double                        myLength;
};
