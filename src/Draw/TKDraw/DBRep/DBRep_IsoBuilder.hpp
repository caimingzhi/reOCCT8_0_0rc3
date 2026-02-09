#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <NCollection_Array1.hpp>
#include <Standard_Integer.hpp>
#include <Geom2dHatch_Hatcher.hpp>
#include <NCollection_IndexedDataMap.hpp>
class TopoDS_Face;
class DBRep_Face;

class DBRep_IsoBuilder : public Geom2dHatch_Hatcher
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT DBRep_IsoBuilder(const TopoDS_Face& TopologicalFace,
                                   const double       Infinite,
                                   const int          NbIsos);

  int NbDomains() const { return myNbDom; }

  Standard_EXPORT void LoadIsos(const occ::handle<DBRep_Face>& Face) const;

protected:
  typedef NCollection_IndexedDataMap<TopoDS_Shape, occ::handle<Geom2d_Curve>> DataMapOfEdgePCurve;

  Standard_EXPORT void FillGaps(const TopoDS_Face& theFace, DataMapOfEdgePCurve& theEdgePCurveMap);

private:
  double                     myInfinite;
  double                     myUMin;
  double                     myUMax;
  double                     myVMin;
  double                     myVMax;
  NCollection_Array1<double> myUPrm;
  NCollection_Array1<int>    myUInd;
  NCollection_Array1<double> myVPrm;
  NCollection_Array1<int>    myVInd;
  int                        myNbDom;
};
