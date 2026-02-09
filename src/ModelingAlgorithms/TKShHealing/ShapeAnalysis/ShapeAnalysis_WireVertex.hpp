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

#ifdef Status
  #undef Status
#endif

class ShapeAnalysis_WireVertex
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeAnalysis_WireVertex();

  Standard_EXPORT void Init(const TopoDS_Wire& wire, const double preci);

  Standard_EXPORT void Init(const occ::handle<ShapeExtend_WireData>& swbd, const double preci);

  Standard_EXPORT void Load(const TopoDS_Wire& wire);

  Standard_EXPORT void Load(const occ::handle<ShapeExtend_WireData>& sbwd);

  Standard_EXPORT void SetPrecision(const double preci);

  Standard_EXPORT void Analyze();

  Standard_EXPORT void SetSameVertex(const int num);

  Standard_EXPORT void SetSameCoords(const int num);

  Standard_EXPORT void SetClose(const int num);

  Standard_EXPORT void SetEnd(const int num, const gp_XYZ& pos, const double ufol);

  Standard_EXPORT void SetStart(const int num, const gp_XYZ& pos, const double upre);

  Standard_EXPORT void SetInters(const int     num,
                                 const gp_XYZ& pos,
                                 const double  upre,
                                 const double  ufol);

  Standard_EXPORT void SetDisjoined(const int num);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT double Precision() const;

  Standard_EXPORT int NbEdges() const;

  Standard_EXPORT const occ::handle<ShapeExtend_WireData>& WireData() const;

  Standard_EXPORT int Status(const int num) const;

  Standard_EXPORT gp_XYZ Position(const int num) const;

  Standard_EXPORT double UPrevious(const int num) const;

  Standard_EXPORT double UFollowing(const int num) const;

  Standard_EXPORT int Data(const int num, gp_XYZ& pos, double& upre, double& ufol) const;

  Standard_EXPORT int NextStatus(const int stat, const int num = 0) const;

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
