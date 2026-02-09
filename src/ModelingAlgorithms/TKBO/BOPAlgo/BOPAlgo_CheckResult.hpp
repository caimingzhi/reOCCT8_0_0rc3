#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>

enum BOPAlgo_CheckStatus
{
  BOPAlgo_CheckUnknown,
  BOPAlgo_BadType,
  BOPAlgo_SelfIntersect,
  BOPAlgo_TooSmallEdge,
  BOPAlgo_NonRecoverableFace,
  BOPAlgo_IncompatibilityOfVertex,
  BOPAlgo_IncompatibilityOfEdge,
  BOPAlgo_IncompatibilityOfFace,
  BOPAlgo_OperationAborted,
  BOPAlgo_GeomAbs_C0,
  BOPAlgo_InvalidCurveOnSurface,
  BOPAlgo_NotValid
};

#include <NCollection_List.hpp>

class BOPAlgo_CheckResult
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BOPAlgo_CheckResult();

  Standard_EXPORT void SetShape1(const TopoDS_Shape& TheShape);

  Standard_EXPORT void AddFaultyShape1(const TopoDS_Shape& TheShape);

  Standard_EXPORT void SetShape2(const TopoDS_Shape& TheShape);

  Standard_EXPORT void AddFaultyShape2(const TopoDS_Shape& TheShape);

  Standard_EXPORT const TopoDS_Shape& GetShape1() const;

  Standard_EXPORT const TopoDS_Shape& GetShape2() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& GetFaultyShapes1() const;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& GetFaultyShapes2() const;

  Standard_EXPORT void SetCheckStatus(const BOPAlgo_CheckStatus TheStatus);

  Standard_EXPORT BOPAlgo_CheckStatus GetCheckStatus() const;

  Standard_EXPORT void SetMaxDistance1(const double theDist);

  Standard_EXPORT void SetMaxDistance2(const double theDist);

  Standard_EXPORT void SetMaxParameter1(const double thePar);

  Standard_EXPORT void SetMaxParameter2(const double thePar);

  Standard_EXPORT double GetMaxDistance1() const;

  Standard_EXPORT double GetMaxDistance2() const;

  Standard_EXPORT double GetMaxParameter1() const;

  Standard_EXPORT double GetMaxParameter2() const;

private:
  TopoDS_Shape                   myShape1;
  TopoDS_Shape                   myShape2;
  BOPAlgo_CheckStatus            myStatus;
  NCollection_List<TopoDS_Shape> myFaulty1;
  NCollection_List<TopoDS_Shape> myFaulty2;
  double                         myMaxDist1;
  double                         myMaxDist2;
  double                         myMaxPar1;
  double                         myMaxPar2;
};
