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

//! Creation of isoparametric curves.
class DBRep_IsoBuilder : public Geom2dHatch_Hatcher
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates the builder.
  Standard_EXPORT DBRep_IsoBuilder(const TopoDS_Face& TopologicalFace,
                                   const double       Infinite,
                                   const int          NbIsos);

  //! Returns the total number of domains.
  int NbDomains() const { return myNbDom; }

  //! Loading of the isoparametric curves in the
  //! Data Structure of a drawable face.
  Standard_EXPORT void LoadIsos(const occ::handle<DBRep_Face>& Face) const;

protected:
  typedef NCollection_IndexedDataMap<TopoDS_Shape, occ::handle<Geom2d_Curve>> DataMapOfEdgePCurve;

  //! Adds to the hatcher the 2D segments connecting the p-curves
  //! of the neighboring edges to close the 2D gaps which are
  //! closed in 3D by the tolerance of vertices shared between edges.
  //! It will allow trimming correctly the iso-lines passing through
  //! such gaps.
  //! The method also trims the intersecting 2D curves of the face,
  //! forbidding the iso-lines beyond the face boundaries.
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

