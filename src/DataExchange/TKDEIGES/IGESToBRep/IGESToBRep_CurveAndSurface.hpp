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

//! Provides methods to transfer CurveAndSurface from IGES to CASCADE.
class IGESToBRep_CurveAndSurface
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a tool CurveAndSurface ready to run, with
  //! epsilons set to 1.E-04, myModeTopo to True, the
  //! optimization of the continuity to False.
  Standard_EXPORT IGESToBRep_CurveAndSurface();

  //! Creates a tool CurveAndSurface ready to run.
  Standard_EXPORT IGESToBRep_CurveAndSurface(const double eps,
                                             const double epsGeom,
                                             const double epsCoeff,
                                             const bool   mode,
                                             const bool   modeapprox,
                                             const bool   optimized);

  //! Initializes the field of the tool CurveAndSurface with
  //! default creating values.
  Standard_EXPORT void Init();

  //! Changes the value of "myEps"
  void SetEpsilon(const double eps);

  //! Returns the value of "myEps"
  double GetEpsilon() const;

  //! Changes the value of "myEpsCoeff"
  void SetEpsCoeff(const double eps);

  //! Returns the value of "myEpsCoeff"
  double GetEpsCoeff() const;

  //! Changes the value of "myEpsGeom"
  Standard_EXPORT void SetEpsGeom(const double eps);

  //! Returns the value of "myEpsGeom"
  double GetEpsGeom() const;

  //! Changes the value of "myMinTol"
  void SetMinTol(const double mintol);

  //! Changes the value of "myMaxTol"
  void SetMaxTol(const double maxtol);

  //! Sets values of "myMinTol" and "myMaxTol" as follows
  //! myMaxTol = Max ("read.maxprecision.val", myEpsGeom * myUnitFactor)
  //! myMinTol = Precision::Confusion()
  //! Remark: This method is automatically invoked each time the values
  //! of "myEpsGeom" or "myUnitFactor" are changed
  Standard_EXPORT void UpdateMinMaxTol();

  //! Returns the value of "myMinTol"
  double GetMinTol() const;

  //! Returns the value of "myMaxTol"
  double GetMaxTol() const;

  //! Changes the value of "myModeApprox"
  void SetModeApprox(const bool mode);

  //! Returns the value of "myModeApprox"
  bool GetModeApprox() const;

  //! Changes the value of "myModeIsTopo"
  void SetModeTransfer(const bool mode);

  //! Returns the value of "myModeIsTopo"
  bool GetModeTransfer() const;

  //! Changes the value of "myContIsOpti"
  void SetOptimized(const bool optimized);

  //! Returns the value of "myContIsOpti"
  bool GetOptimized() const;

  //! Returns the value of " myUnitFactor"
  double GetUnitFactor() const;

  //! Changes the value of "mySurfaceCurve"
  void SetSurfaceCurve(const int ival);

  //! Returns the value of "mySurfaceCurve" 0 = value in
  //! file, 2 = keep 2d and compute 3d, 3 = keep 3d and
  //! compute 2d
  int GetSurfaceCurve() const;

  //! Set the value of "myModel"
  Standard_EXPORT void SetModel(const occ::handle<IGESData_IGESModel>& model);

  //! Returns the value of "myModel"
  occ::handle<IGESData_IGESModel> GetModel() const;

  //! Changes the value of "myContinuity"
  //! if continuity = 0 do nothing else
  //! if continuity = 1 try C1
  //! if continuity = 2 try C2
  void SetContinuity(const int continuity);

  //! Returns the value of "myContinuity"
  int GetContinuity() const;

  //! Set the value of "myMsgReg"
  void SetTransferProcess(const occ::handle<Transfer_TransientProcess>& TP);

  //! Returns the value of "myMsgReg"
  occ::handle<Transfer_TransientProcess> GetTransferProcess() const;

  //! Returns the result of the transfert of any IGES Curve
  //! or Surface Entity. If the transfer has failed, this
  //! member return a NullEntity.
  Standard_EXPORT TopoDS_Shape
    TransferCurveAndSurface(const occ::handle<IGESData_IGESEntity>& start,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Returns the result of the transfert the geometry of
  //! any IGESEntity. If the transfer has failed, this
  //! member return a NullEntity.
  Standard_EXPORT TopoDS_Shape
    TransferGeometry(const occ::handle<IGESData_IGESEntity>& start,
                     const Message_ProgressRange&            theProgress = Message_ProgressRange());

  //! Records a new Fail message
  void SendFail(const occ::handle<IGESData_IGESEntity>& start, const Message_Msg& amsg);

  //! Records a new Warning message
  void SendWarning(const occ::handle<IGESData_IGESEntity>& start, const Message_Msg& amsg);

  //! Records a new Information message from the definition
  //! of a Msg (Original+Value)
  void SendMsg(const occ::handle<IGESData_IGESEntity>& start, const Message_Msg& amsg);

  //! Returns True if start was already treated and has a result in "myMap"
  //! else returns False.
  Standard_EXPORT bool HasShapeResult(const occ::handle<IGESData_IGESEntity>& start) const;

  //! Returns the result of the transfer of the IGESEntity "start" contained
  //! in "myMap" . (if HasShapeResult is True).
  Standard_EXPORT TopoDS_Shape GetShapeResult(const occ::handle<IGESData_IGESEntity>& start) const;

  //! set in "myMap" the result of the transfer of the IGESEntity "start".
  Standard_EXPORT void SetShapeResult(const occ::handle<IGESData_IGESEntity>& start,
                                      const TopoDS_Shape&                     result);

  //! Returns the number of shapes results contained in "myMap" for the
  //! IGESEntity start (type VertexList or EdgeList).
  Standard_EXPORT int NbShapeResult(const occ::handle<IGESData_IGESEntity>& start) const;

  //! Returns the numth result of the IGESEntity start (type VertexList or
  //! EdgeList) in "myMap". (if NbShapeResult is not null).
  Standard_EXPORT TopoDS_Shape GetShapeResult(const occ::handle<IGESData_IGESEntity>& start,
                                              const int                               num) const;

  //! set in "myMap" the result of the transfer of the entity of the
  //! IGESEntity start (type VertexList or EdgeList).
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

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SetEpsilon(const double eps)
{
  myEps = eps;
}

//=================================================================================================

inline double IGESToBRep_CurveAndSurface::GetEpsilon() const
{
  return myEps;
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SetEpsCoeff(const double eps)
{
  myEpsCoeff = eps;
}

//=================================================================================================

inline double IGESToBRep_CurveAndSurface::GetEpsCoeff() const
{
  return myEpsCoeff;
}

//=================================================================================================

inline double IGESToBRep_CurveAndSurface::GetEpsGeom() const
{
  return myEpsGeom;
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SetMinTol(const double mintol)
{
  myMinTol = mintol;
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SetMaxTol(const double maxtol)
{
  myMaxTol = maxtol;
}

//=================================================================================================

inline double IGESToBRep_CurveAndSurface::GetMinTol() const
{
  return myMinTol;
}

//=================================================================================================

inline double IGESToBRep_CurveAndSurface::GetMaxTol() const
{
  return myMaxTol;
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SetModeApprox(const bool mode)
{
  myModeApprox = mode;
}

//=================================================================================================

inline bool IGESToBRep_CurveAndSurface::GetModeApprox() const
{
  return myModeApprox;
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SetModeTransfer(const bool mode)
{
  myModeIsTopo = mode;
}

//=================================================================================================

inline bool IGESToBRep_CurveAndSurface::GetModeTransfer() const
{
  return myModeIsTopo;
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SetOptimized(const bool optimized)
{
  myContIsOpti = optimized;
}

//=================================================================================================

inline bool IGESToBRep_CurveAndSurface::GetOptimized() const
{
  return myContIsOpti;
}

//=================================================================================================

inline double IGESToBRep_CurveAndSurface::GetUnitFactor() const
{
  return myUnitFactor;
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SetSurfaceCurve(const int ival)
{
  mySurfaceCurve = ival;
}

//=================================================================================================

inline int IGESToBRep_CurveAndSurface::GetSurfaceCurve() const
{
  return mySurfaceCurve;
}

//=================================================================================================

inline occ::handle<IGESData_IGESModel> IGESToBRep_CurveAndSurface::GetModel() const
{
  return myModel;
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SetContinuity(const int continuity)
{
  myContinuity = continuity;
}

//=================================================================================================

inline int IGESToBRep_CurveAndSurface::GetContinuity() const
{
  return myContinuity;
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SetTransferProcess(
  const occ::handle<Transfer_TransientProcess>& TP)
{
  myTP = TP;
}

//=================================================================================================

inline occ::handle<Transfer_TransientProcess> IGESToBRep_CurveAndSurface::GetTransferProcess() const
{
  return myTP;
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SendFail(const occ::handle<IGESData_IGESEntity>& start,
                                                 const Message_Msg&                      amsg)
{
  GetTransferProcess()->SendFail(start, amsg);
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SendWarning(const occ::handle<IGESData_IGESEntity>& start,
                                                    const Message_Msg&                      amsg)
{
  GetTransferProcess()->SendWarning(start, amsg);
}

//=================================================================================================

inline void IGESToBRep_CurveAndSurface::SendMsg(const occ::handle<IGESData_IGESEntity>& start,
                                                const Message_Msg&                      amsg)
{
  GetTransferProcess()->SendMsg(start, amsg);
}
