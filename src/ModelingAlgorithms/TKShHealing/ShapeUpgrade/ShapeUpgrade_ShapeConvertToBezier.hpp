#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <ShapeUpgrade_ShapeDivide.hpp>
class TopoDS_Shape;
class ShapeUpgrade_FaceDivide;
class Message_Msg;

class ShapeUpgrade_ShapeConvertToBezier : public ShapeUpgrade_ShapeDivide
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeUpgrade_ShapeConvertToBezier();

  Standard_EXPORT ShapeUpgrade_ShapeConvertToBezier(const TopoDS_Shape& S);

  void Set2dConversion(const bool mode);

  bool Get2dConversion() const;

  void Set3dConversion(const bool mode);

  bool Get3dConversion() const;

  void SetSurfaceConversion(const bool mode);

  bool GetSurfaceConversion() const;

  void Set3dLineConversion(const bool mode);

  bool Get3dLineConversion() const;

  void Set3dCircleConversion(const bool mode);

  bool Get3dCircleConversion() const;

  void Set3dConicConversion(const bool mode);

  bool Get3dConicConversion() const;

  void SetPlaneMode(const bool mode);

  bool GetPlaneMode() const;

  void SetRevolutionMode(const bool mode);

  bool GetRevolutionMode() const;

  void SetExtrusionMode(const bool mode);

  bool GetExtrusionMode() const;

  void SetBSplineMode(const bool mode);

  bool GetBSplineMode() const;

  Standard_EXPORT bool Perform(const bool newContext = true) override;

protected:
  Standard_EXPORT occ::handle<ShapeUpgrade_FaceDivide> GetSplitFaceTool() const override;

  Standard_EXPORT Message_Msg GetFaceMsg() const override;

  Standard_EXPORT Message_Msg GetWireMsg() const override;

  Standard_EXPORT Message_Msg GetEdgeMsg() const override;

private:
  bool my2dMode;
  bool my3dMode;
  bool mySurfaceMode;
  bool my3dLineMode;
  bool my3dCircleMode;
  bool my3dConicMode;
  bool myPlaneMode;
  bool myRevolutionMode;
  bool myExtrusionMode;
  bool myBSplineMode;
  int  myLevel;
};

inline void ShapeUpgrade_ShapeConvertToBezier::Set2dConversion(const bool mode)
{
  my2dMode = mode;
}

inline bool ShapeUpgrade_ShapeConvertToBezier::Get2dConversion() const
{
  return my2dMode;
}

inline void ShapeUpgrade_ShapeConvertToBezier::Set3dConversion(const bool mode)
{
  my3dMode = mode;
}

inline bool ShapeUpgrade_ShapeConvertToBezier::Get3dConversion() const
{
  return my3dMode;
}

inline void ShapeUpgrade_ShapeConvertToBezier::SetSurfaceConversion(const bool mode)
{
  mySurfaceMode = mode;
}

inline bool ShapeUpgrade_ShapeConvertToBezier::GetSurfaceConversion() const
{
  return mySurfaceMode;
}

inline void ShapeUpgrade_ShapeConvertToBezier::Set3dLineConversion(const bool mode)
{
  my3dLineMode = mode;
}

inline bool ShapeUpgrade_ShapeConvertToBezier::Get3dLineConversion() const
{
  return my3dLineMode;
}

inline void ShapeUpgrade_ShapeConvertToBezier::Set3dCircleConversion(const bool mode)
{
  my3dCircleMode = mode;
}

inline bool ShapeUpgrade_ShapeConvertToBezier::Get3dCircleConversion() const
{
  return my3dCircleMode;
}

inline void ShapeUpgrade_ShapeConvertToBezier::Set3dConicConversion(const bool mode)
{
  my3dConicMode = mode;
}

inline bool ShapeUpgrade_ShapeConvertToBezier::Get3dConicConversion() const
{
  return my3dConicMode;
}

inline void ShapeUpgrade_ShapeConvertToBezier::SetPlaneMode(const bool mode)
{
  myPlaneMode = mode;
}

inline bool ShapeUpgrade_ShapeConvertToBezier::GetPlaneMode() const
{
  return myPlaneMode;
}

inline void ShapeUpgrade_ShapeConvertToBezier::SetRevolutionMode(const bool mode)
{
  myRevolutionMode = mode;
}

inline bool ShapeUpgrade_ShapeConvertToBezier::GetRevolutionMode() const
{
  return myRevolutionMode;
}

inline void ShapeUpgrade_ShapeConvertToBezier::SetExtrusionMode(const bool mode)
{
  myExtrusionMode = mode;
}

inline bool ShapeUpgrade_ShapeConvertToBezier::GetExtrusionMode() const
{
  return myExtrusionMode;
}

inline void ShapeUpgrade_ShapeConvertToBezier::SetBSplineMode(const bool mode)
{
  myBSplineMode = mode;
}

inline bool ShapeUpgrade_ShapeConvertToBezier::GetBSplineMode() const
{
  return myBSplineMode;
}
