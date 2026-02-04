#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <gp_XYZ.hpp>
class ShapeExtend_WireData;
class TopoDS_Wire;
class gp_XYZ;

// resolve name collisions with X11 headers
#ifdef Status
  #undef Status
#endif

//! Analyzes and records status of vertices in a Wire
//!
//! The Wire has formerly been loaded in a ShapeExtend_WireData
//! For each Vertex, a status and some data can be attached
//! (case found, position and parameters)
//! Then, these information can be used to fix problems
class ShapeAnalysis_WireVertex
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT ShapeAnalysis_WireVertex();

  Standard_EXPORT void Init(const TopoDS_Wire& wire, const double preci);

  Standard_EXPORT void Init(const occ::handle<ShapeExtend_WireData>& swbd, const double preci);

  Standard_EXPORT void Load(const TopoDS_Wire& wire);

  Standard_EXPORT void Load(const occ::handle<ShapeExtend_WireData>& sbwd);

  //! Sets the precision for work
  //! Analysing: for each Vertex, comparison between the end of the
  //! preceding edge and the start of the following edge
  //! Each Vertex rank corresponds to the End Vertex of the Edge of
  //! same rank, in the ShapeExtend_WireData. I.E. for Vertex <num>,
  //! Edge <num> is the preceding one, <num+1> is the following one
  Standard_EXPORT void SetPrecision(const double preci);

  Standard_EXPORT void Analyze();

  //! Records status "Same Vertex" (logically) on Vertex <num>
  Standard_EXPORT void SetSameVertex(const int num);

  //! Records status "Same Coords" (at the Vertices Tolerances)
  Standard_EXPORT void SetSameCoords(const int num);

  //! Records status "Close Coords" (at the Precision of <me>)
  Standard_EXPORT void SetClose(const int num);

  //! <num> is the End of preceding Edge, and its projection on the
  //! following one lies on it at the Precision of <me>
  //! <ufol> gives the parameter on the following edge
  Standard_EXPORT void SetEnd(const int num, const gp_XYZ& pos, const double ufol);

  //! <num> is the Start of following Edge, its projection on the
  //! preceding one lies on it at the Precision of <me>
  //! <upre> gives the parameter on the preceding edge
  Standard_EXPORT void SetStart(const int num, const gp_XYZ& pos, const double upre);

  //! <num> is the Intersection of both Edges
  //! <upre> is the parameter on preceding edge, <ufol> on
  //! following edge
  Standard_EXPORT void SetInters(const int     num,
                                 const gp_XYZ& pos,
                                 const double  upre,
                                 const double  ufol);

  //! <num> cannot be said as same vertex
  Standard_EXPORT void SetDisjoined(const int num);

  //! Returns True if analysis was performed, else returns False
  Standard_EXPORT bool IsDone() const;

  //! Returns precision value used in analysis
  Standard_EXPORT double Precision() const;

  //! Returns the number of edges in analyzed wire (i.e. the
  //! length of all arrays)
  Standard_EXPORT int NbEdges() const;

  //! Returns analyzed wire
  Standard_EXPORT const occ::handle<ShapeExtend_WireData>& WireData() const;

  //! Returns the recorded status for a vertex
  //! More detail by method Data
  Standard_EXPORT int Status(const int num) const;

  Standard_EXPORT gp_XYZ Position(const int num) const;

  Standard_EXPORT double UPrevious(const int num) const;

  Standard_EXPORT double UFollowing(const int num) const;

  //! Returns the recorded status for a vertex
  //! With its recorded position and parameters on both edges
  //! These values are relevant regarding the status:
  //! Status  Meaning    Position  Preceding   Following
  //! 0       Same       no        no          no
  //! 1       SameCoord  no        no          no
  //! 2       Close      no        no          no
  //! 3       End        yes       no          yes
  //! 4       Start      yes       yes         no
  //! 5       Inters     yes       yes         yes
  //! -1      Disjoined  no        no          no
  Standard_EXPORT int Data(const int num, gp_XYZ& pos, double& upre, double& ufol) const;

  //! For a given status, returns the rank of the vertex which
  //! follows <num> and has the same status. 0 if no more
  //! Acts as an iterator, starts on the first one
  Standard_EXPORT int NextStatus(const int stat, const int num = 0) const;

  //! For a given criter, returns the rank of the vertex which
  //! follows <num> and has the same status. 0 if no more
  //! Acts as an iterator, starts on the first one
  //! Criters are:
  //! 0: same vertex (status 0)
  //! 1: a solution exists (status >= 0)
  //! 2: same coords (i.e. same params) (status 0 1 2)
  //! 3: same coods but not same vertex (status 1 2)
  //! 4: redefined coords (status 3 4 5)
  //! -1: no solution (status -1)
  Standard_EXPORT int NextCriter(const int crit, const int num = 0) const;

private:
  occ::handle<ShapeExtend_WireData>        myWire;
  occ::handle<NCollection_HArray1<int>>    myStat;
  occ::handle<NCollection_HArray1<gp_XYZ>> myPos;
  occ::handle<NCollection_HArray1<double>> myUPre;
  occ::handle<NCollection_HArray1<double>> myUFol;
  double                                   myPreci;
  bool                                     myDone;
};

