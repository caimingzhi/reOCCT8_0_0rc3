#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Face.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <ShapeUpgrade_Tool.hpp>
class ShapeUpgrade_SplitCurve3d;
class ShapeUpgrade_SplitCurve2d;
class TopoDS_Edge;

class ShapeUpgrade_EdgeDivide : public ShapeUpgrade_Tool
{

public:
  //! Empty constructor
  Standard_EXPORT ShapeUpgrade_EdgeDivide();

  Standard_EXPORT void Clear();

  //! Sets supporting surface by face
  void SetFace(const TopoDS_Face& F);

  Standard_EXPORT virtual bool Compute(const TopoDS_Edge& E);

  bool HasCurve2d() const;

  bool HasCurve3d() const;

  occ::handle<NCollection_HSequence<double>> Knots2d() const;

  occ::handle<NCollection_HSequence<double>> Knots3d() const;

  //! Sets the tool for splitting pcurves.
  Standard_EXPORT void SetSplitCurve2dTool(
    const occ::handle<ShapeUpgrade_SplitCurve2d>& splitCurve2dTool);

  //! Sets the tool for splitting 3D curves.
  Standard_EXPORT void SetSplitCurve3dTool(
    const occ::handle<ShapeUpgrade_SplitCurve3d>& splitCurve3dTool);

  //! Returns the tool for splitting pcurves.
  Standard_EXPORT virtual occ::handle<ShapeUpgrade_SplitCurve2d> GetSplitCurve2dTool() const;

  //! Returns the tool for splitting 3D curves.
  Standard_EXPORT virtual occ::handle<ShapeUpgrade_SplitCurve3d> GetSplitCurve3dTool() const;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_EdgeDivide, ShapeUpgrade_Tool)

protected:
  TopoDS_Face                                myFace;
  bool                                       myHasCurve2d;
  bool                                       myHasCurve3d;
  occ::handle<NCollection_HSequence<double>> myKnots2d;
  occ::handle<NCollection_HSequence<double>> myKnots3d;

private:
  occ::handle<ShapeUpgrade_SplitCurve3d> mySplitCurve3dTool;
  occ::handle<ShapeUpgrade_SplitCurve2d> mySplitCurve2dTool;
};

inline void ShapeUpgrade_EdgeDivide::SetFace(const TopoDS_Face& F)
{
  myFace = F;
}

//=================================================================================================

inline bool ShapeUpgrade_EdgeDivide::HasCurve2d() const
{
  return myHasCurve2d;
}

//=================================================================================================

inline bool ShapeUpgrade_EdgeDivide::HasCurve3d() const
{
  return myHasCurve3d;
}

//=================================================================================================

inline occ::handle<NCollection_HSequence<double>> ShapeUpgrade_EdgeDivide::Knots2d() const
{
  return myKnots2d;
}

//=================================================================================================

inline occ::handle<NCollection_HSequence<double>> ShapeUpgrade_EdgeDivide::Knots3d() const
{
  return myKnots3d;
}
