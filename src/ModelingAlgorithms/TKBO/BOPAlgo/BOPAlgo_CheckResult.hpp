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

//! contains information about faulty shapes and faulty types
//! can't be processed by Boolean Operations
class BOPAlgo_CheckResult
{
public:
  DEFINE_STANDARD_ALLOC

  //! empty constructor
  Standard_EXPORT BOPAlgo_CheckResult();

  //! sets ancestor shape (object) for faulty sub-shapes
  Standard_EXPORT void SetShape1(const TopoDS_Shape& TheShape);

  //! adds faulty sub-shapes from object to a list
  Standard_EXPORT void AddFaultyShape1(const TopoDS_Shape& TheShape);

  //! sets ancestor shape (tool) for faulty sub-shapes
  Standard_EXPORT void SetShape2(const TopoDS_Shape& TheShape);

  //! adds faulty sub-shapes from tool to a list
  Standard_EXPORT void AddFaultyShape2(const TopoDS_Shape& TheShape);

  //! returns ancestor shape (object) for faulties
  Standard_EXPORT const TopoDS_Shape& GetShape1() const;

  //! returns ancestor shape (tool) for faulties
  Standard_EXPORT const TopoDS_Shape& GetShape2() const;

  //! returns list of faulty shapes for object
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& GetFaultyShapes1() const;

  //! returns list of faulty shapes for tool
  Standard_EXPORT const NCollection_List<TopoDS_Shape>& GetFaultyShapes2() const;

  //! set status of faulty
  Standard_EXPORT void SetCheckStatus(const BOPAlgo_CheckStatus TheStatus);

  //! gets status of faulty
  Standard_EXPORT BOPAlgo_CheckStatus GetCheckStatus() const;

  //! Sets max distance for the first shape
  Standard_EXPORT void SetMaxDistance1(const double theDist);

  //! Sets max distance for the second shape
  Standard_EXPORT void SetMaxDistance2(const double theDist);

  //! Sets the parameter for the first shape
  Standard_EXPORT void SetMaxParameter1(const double thePar);

  //! Sets the parameter for the second shape
  Standard_EXPORT void SetMaxParameter2(const double thePar);

  //! Returns the distance for the first shape
  Standard_EXPORT double GetMaxDistance1() const;

  //! Returns the distance for the second shape
  Standard_EXPORT double GetMaxDistance2() const;

  //! Returns the parameter for the fircst shape
  Standard_EXPORT double GetMaxParameter1() const;

  //! Returns the parameter for the second shape
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
