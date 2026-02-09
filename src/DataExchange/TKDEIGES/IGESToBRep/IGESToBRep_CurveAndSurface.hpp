#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Message_ProgressRange.hpp>

class Geom_Surface;
class IGESData_IGESModel;
class Transfer_TransientProcess;
class TopoDS_Shape;
class IGESData_IGESEntity;
class Message_Msg;

class IGESToBRep_CurveAndSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESToBRep_CurveAndSurface();

  Standard_EXPORT IGESToBRep_CurveAndSurface(const double eps,
                                             const double epsGeom,
                                             const double epsCoeff,
                                             const bool   mode,
                                             const bool   modeapprox,
                                             const bool   optimized);

  Standard_EXPORT void Init();

  void SetEpsilon(const double eps);

  double GetEpsilon() const;

  void SetEpsCoeff(const double eps);

  double GetEpsCoeff() const;

  Standard_EXPORT void SetEpsGeom(const double eps);

  double GetEpsGeom() const;

  void SetMinTol(const double mintol);

  void SetMaxTol(const double maxtol);

  Standard_EXPORT void UpdateMinMaxTol();

  double GetMinTol() const;

  double GetMaxTol() const;

  void SetModeApprox(const bool mode);

  bool GetModeApprox() const;

  void SetModeTransfer(const bool mode);

  bool GetModeTransfer() const;

  void SetOptimized(const bool optimized);

  bool GetOptimized() const;

  double GetUnitFactor() const;

  void SetSurfaceCurve(const int ival);

  int GetSurfaceCurve() const;

  Standard_EXPORT void SetModel(const occ::handle<IGESData_IGESModel>& model);

  occ::handle<IGESData_IGESModel> GetModel() const;

  void SetContinuity(const int continuity);

  int GetContinuity() const;

  void SetTransferProcess(const occ::handle<Transfer_TransientProcess>& TP);

  occ::handle<Transfer_TransientProcess> GetTransferProcess() const;

  Standard_EXPORT TopoDS_Shape
    TransferCurveAndSurface(const occ::handle<IGESData_IGESEntity>& start,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT TopoDS_Shape
    TransferGeometry(const occ::handle<IGESData_IGESEntity>& start,
                     const Message_ProgressRange&            theProgress = Message_ProgressRange());

  void SendFail(const occ::handle<IGESData_IGESEntity>& start, const Message_Msg& amsg);

  void SendWarning(const occ::handle<IGESData_IGESEntity>& start, const Message_Msg& amsg);

  void SendMsg(const occ::handle<IGESData_IGESEntity>& start, const Message_Msg& amsg);

  Standard_EXPORT bool HasShapeResult(const occ::handle<IGESData_IGESEntity>& start) const;

  Standard_EXPORT TopoDS_Shape GetShapeResult(const occ::handle<IGESData_IGESEntity>& start) const;

  Standard_EXPORT void SetShapeResult(const occ::handle<IGESData_IGESEntity>& start,
                                      const TopoDS_Shape&                     result);

  Standard_EXPORT int NbShapeResult(const occ::handle<IGESData_IGESEntity>& start) const;

  Standard_EXPORT TopoDS_Shape GetShapeResult(const occ::handle<IGESData_IGESEntity>& start,
                                              const int                               num) const;

  Standard_EXPORT void AddShapeResult(const occ::handle<IGESData_IGESEntity>& start,
                                      const TopoDS_Shape&                     result);

  Standard_EXPORT void SetSurface(const occ::handle<Geom_Surface>& theSurface);

  Standard_EXPORT occ::handle<Geom_Surface> Surface() const;

  Standard_EXPORT double GetUVResolution();

private:
  double                                 myEps;
  double                                 myEpsCoeff;
  double                                 myEpsGeom;
  double                                 myMinTol;
  double                                 myMaxTol;
  bool                                   myModeIsTopo;
  bool                                   myModeApprox;
  bool                                   myContIsOpti;
  double                                 myUnitFactor;
  int                                    mySurfaceCurve;
  int                                    myContinuity;
  occ::handle<Geom_Surface>              mySurface;
  double                                 myUVResolution;
  bool                                   myIsResolCom;
  occ::handle<IGESData_IGESModel>        myModel;
  occ::handle<Transfer_TransientProcess> myTP;
};

#include <Transfer_TransientProcess.hpp>
#include <IGESData_IGESEntity.hpp>

inline void IGESToBRep_CurveAndSurface::SetEpsilon(const double eps)
{
  myEps = eps;
}

inline double IGESToBRep_CurveAndSurface::GetEpsilon() const
{
  return myEps;
}

inline void IGESToBRep_CurveAndSurface::SetEpsCoeff(const double eps)
{
  myEpsCoeff = eps;
}

inline double IGESToBRep_CurveAndSurface::GetEpsCoeff() const
{
  return myEpsCoeff;
}

inline double IGESToBRep_CurveAndSurface::GetEpsGeom() const
{
  return myEpsGeom;
}

inline void IGESToBRep_CurveAndSurface::SetMinTol(const double mintol)
{
  myMinTol = mintol;
}

inline void IGESToBRep_CurveAndSurface::SetMaxTol(const double maxtol)
{
  myMaxTol = maxtol;
}

inline double IGESToBRep_CurveAndSurface::GetMinTol() const
{
  return myMinTol;
}

inline double IGESToBRep_CurveAndSurface::GetMaxTol() const
{
  return myMaxTol;
}

inline void IGESToBRep_CurveAndSurface::SetModeApprox(const bool mode)
{
  myModeApprox = mode;
}

inline bool IGESToBRep_CurveAndSurface::GetModeApprox() const
{
  return myModeApprox;
}

inline void IGESToBRep_CurveAndSurface::SetModeTransfer(const bool mode)
{
  myModeIsTopo = mode;
}

inline bool IGESToBRep_CurveAndSurface::GetModeTransfer() const
{
  return myModeIsTopo;
}

inline void IGESToBRep_CurveAndSurface::SetOptimized(const bool optimized)
{
  myContIsOpti = optimized;
}

inline bool IGESToBRep_CurveAndSurface::GetOptimized() const
{
  return myContIsOpti;
}

inline double IGESToBRep_CurveAndSurface::GetUnitFactor() const
{
  return myUnitFactor;
}

inline void IGESToBRep_CurveAndSurface::SetSurfaceCurve(const int ival)
{
  mySurfaceCurve = ival;
}

inline int IGESToBRep_CurveAndSurface::GetSurfaceCurve() const
{
  return mySurfaceCurve;
}

inline occ::handle<IGESData_IGESModel> IGESToBRep_CurveAndSurface::GetModel() const
{
  return myModel;
}

inline void IGESToBRep_CurveAndSurface::SetContinuity(const int continuity)
{
  myContinuity = continuity;
}

inline int IGESToBRep_CurveAndSurface::GetContinuity() const
{
  return myContinuity;
}

inline void IGESToBRep_CurveAndSurface::SetTransferProcess(
  const occ::handle<Transfer_TransientProcess>& TP)
{
  myTP = TP;
}

inline occ::handle<Transfer_TransientProcess> IGESToBRep_CurveAndSurface::GetTransferProcess() const
{
  return myTP;
}

inline void IGESToBRep_CurveAndSurface::SendFail(const occ::handle<IGESData_IGESEntity>& start,
                                                 const Message_Msg&                      amsg)
{
  GetTransferProcess()->SendFail(start, amsg);
}

inline void IGESToBRep_CurveAndSurface::SendWarning(const occ::handle<IGESData_IGESEntity>& start,
                                                    const Message_Msg&                      amsg)
{
  GetTransferProcess()->SendWarning(start, amsg);
}

inline void IGESToBRep_CurveAndSurface::SendMsg(const occ::handle<IGESData_IGESEntity>& start,
                                                const Message_Msg&                      amsg)
{
  GetTransferProcess()->SendMsg(start, amsg);
}
