#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <ShapeExtend_Status.hpp>
class TopoDS_Face;
class gp_Pnt;
class TopoDS_Edge;
class TopoDS_Compound;

#ifdef Status
  #undef Status
#endif

class ShapeAnalysis_CheckSmallFace
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeAnalysis_CheckSmallFace();

  Standard_EXPORT int IsSpotFace(const TopoDS_Face& F,
                                 gp_Pnt&            spot,
                                 double&            spotol,
                                 const double       tol = -1.0) const;

  Standard_EXPORT bool CheckSpotFace(const TopoDS_Face& F, const double tol = -1.0);

  Standard_EXPORT bool IsStripSupport(const TopoDS_Face& F, const double tol = -1.0);

  Standard_EXPORT bool CheckStripEdges(const TopoDS_Edge& E1,
                                       const TopoDS_Edge& E2,
                                       const double       tol,
                                       double&            dmax) const;

  Standard_EXPORT bool FindStripEdges(const TopoDS_Face& F,
                                      TopoDS_Edge&       E1,
                                      TopoDS_Edge&       E2,
                                      const double       tol,
                                      double&            dmax);

  Standard_EXPORT bool CheckSingleStrip(const TopoDS_Face& F,
                                        TopoDS_Edge&       E1,
                                        TopoDS_Edge&       E2,
                                        const double       tol = -1.0);

  Standard_EXPORT bool CheckStripFace(const TopoDS_Face& F,
                                      TopoDS_Edge&       E1,
                                      TopoDS_Edge&       E2,
                                      const double       tol = -1.0);

  Standard_EXPORT int CheckSplittingVertices(
    const TopoDS_Face& F,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>&
                                                                                          MapEdges,
    NCollection_DataMap<TopoDS_Shape, NCollection_List<double>, TopTools_ShapeMapHasher>& MapParam,
    TopoDS_Compound& theAllVert);

  Standard_EXPORT bool CheckPin(const TopoDS_Face& F, int& whatrow, int& sence);

  Standard_EXPORT bool CheckTwisted(const TopoDS_Face& F, double& paramu, double& paramv);

  Standard_EXPORT bool CheckPinFace(
    const TopoDS_Face&                                                        F,
    NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& mapEdges,
    const double                                                              toler = -1.0);

  Standard_EXPORT bool CheckPinEdges(const TopoDS_Edge& theFirstEdge,
                                     const TopoDS_Edge& theSecondEdge,
                                     const double       coef1,
                                     const double       coef2,
                                     const double       toler) const;

  bool Status(const ShapeExtend_Status status) const;

  void SetTolerance(const double tol);

  double Tolerance() const;

  bool StatusSpot(const ShapeExtend_Status status) const;

  bool StatusStrip(const ShapeExtend_Status status) const;

  bool StatusPin(const ShapeExtend_Status status) const;

  bool StatusTwisted(const ShapeExtend_Status status) const;

  bool StatusSplitVert(const ShapeExtend_Status status) const;

  bool StatusPinFace(const ShapeExtend_Status status) const;

  bool StatusPinEdges(const ShapeExtend_Status status) const;

private:
  TopoDS_Shape myComp;
  int          myStatus;
  int          myStatusSpot;
  int          myStatusStrip;
  int          myStatusPin;
  int          myStatusTwisted;
  int          myStatusSplitVert;
  int          myStatusPinFace;
  int          myStatusPinEdges;
  double       myPrecision;
};

#include <ShapeExtend.hpp>

inline bool ShapeAnalysis_CheckSmallFace::Status(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatus, status);
}

inline void ShapeAnalysis_CheckSmallFace::SetTolerance(const double tol)
{
  myPrecision = tol;
}

inline double ShapeAnalysis_CheckSmallFace::Tolerance() const
{
  return myPrecision;
}

inline bool ShapeAnalysis_CheckSmallFace::StatusSpot(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusSpot, status);
}

inline bool ShapeAnalysis_CheckSmallFace::StatusStrip(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusStrip, status);
}

inline bool ShapeAnalysis_CheckSmallFace::StatusPin(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusPin, status);
}

inline bool ShapeAnalysis_CheckSmallFace::StatusTwisted(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusTwisted, status);
}

inline bool ShapeAnalysis_CheckSmallFace::StatusPinFace(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusPinFace, status);
}

inline bool ShapeAnalysis_CheckSmallFace::StatusPinEdges(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusPinEdges, status);
}

inline bool ShapeAnalysis_CheckSmallFace::StatusSplitVert(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus(myStatusSplitVert, status);
}
