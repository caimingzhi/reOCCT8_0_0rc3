#pragma once

#include <BRepTools_Modifier.hpp>
#include <ShapeBuild_ReShape.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Macro.hpp>
#include <Standard_Real.hpp>
#include <TCollection_AsciiString.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Shape.hpp>

enum BRepOffsetSimple_Status
{
  BRepOffsetSimple_OK,
  BRepOffsetSimple_NullInputShape,
  BRepOffsetSimple_ErrorOffsetComputation,
  BRepOffsetSimple_ErrorWallFaceComputation,
  BRepOffsetSimple_ErrorInvalidNbShells,
  BRepOffsetSimple_ErrorNonClosedShell
};

class BRepOffset_MakeSimpleOffset
{
public:
  Standard_EXPORT BRepOffset_MakeSimpleOffset();

  Standard_EXPORT BRepOffset_MakeSimpleOffset(const TopoDS_Shape& theInputShape,
                                              const double        theOffsetValue);

  Standard_EXPORT void Initialize(const TopoDS_Shape& theInputShape, const double theOffsetValue);

  Standard_EXPORT void Perform();

  Standard_EXPORT TCollection_AsciiString GetErrorMessage() const;

  BRepOffsetSimple_Status GetError() const { return myError; }

  bool GetBuildSolidFlag() const { return myIsBuildSolid; }

  void SetBuildSolidFlag(const bool theBuildFlag) { myIsBuildSolid = theBuildFlag; }

  double GetOffsetValue() const { return myOffsetValue; }

  void SetOffsetValue(const double theOffsetValue) { myOffsetValue = theOffsetValue; }

  double GetTolerance() const { return myTolerance; }

  void SetTolerance(const double theValue) { myTolerance = theValue; }

  bool IsDone() const { return myIsDone; }

  const TopoDS_Shape& GetResultShape() const { return myResShape; }

  double GetSafeOffset(const double theExpectedToler);

  Standard_EXPORT const TopoDS_Shape Generated(const TopoDS_Shape& theShape) const;

  Standard_EXPORT const TopoDS_Shape Modified(const TopoDS_Shape& theShape) const;

protected:
  void ComputeMaxAngle();

  void Clear();

private:
  TopoDS_Face BuildWallFace(const TopoDS_Edge& theOrigEdge);

  bool BuildMissingWalls();

  TopoDS_Shape myInputShape;

  double myOffsetValue;

  double myTolerance;

  bool myIsBuildSolid;

  double myMaxAngle;

  BRepOffsetSimple_Status myError;

  bool myIsDone;

  NCollection_DataMap<TopoDS_Vertex, TopoDS_Edge> myMapVE;

  BRepTools_Modifier myBuilder;

  occ::handle<ShapeBuild_ReShape> myReShape;

  TopoDS_Shape myResShape;
};
