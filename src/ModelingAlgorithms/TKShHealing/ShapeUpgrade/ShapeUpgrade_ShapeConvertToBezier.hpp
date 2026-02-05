#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <ShapeUpgrade_ShapeDivide.hpp>
class TopoDS_Shape;
class ShapeUpgrade_FaceDivide;
class Message_Msg;

//! API class for performing conversion of 3D, 2D curves to bezier curves
//! and surfaces to bezier based surfaces (
//! bezier surface,
//! surface of revolution based on bezier curve,
//! offset surface based on any previous type).
class ShapeUpgrade_ShapeConvertToBezier : public ShapeUpgrade_ShapeDivide
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor.
  Standard_EXPORT ShapeUpgrade_ShapeConvertToBezier();

  //! Initialize by a Shape.
  Standard_EXPORT ShapeUpgrade_ShapeConvertToBezier(const TopoDS_Shape& S);

  //! Sets mode for conversion 2D curves to bezier.
  void Set2dConversion(const bool mode);

  //! Returns the 2D conversion mode.
  bool Get2dConversion() const;

  //! Sets mode for conversion 3d curves to bezier.
  void Set3dConversion(const bool mode);

  //! Returns the 3D conversion mode.
  bool Get3dConversion() const;

  //! Sets mode for conversion surfaces curves to
  //! bezier basis.
  void SetSurfaceConversion(const bool mode);

  //! Returns the surface conversion mode.
  bool GetSurfaceConversion() const;

  //! Sets mode for conversion Geom_Line to bezier.
  void Set3dLineConversion(const bool mode);

  //! Returns the Geom_Line conversion mode.
  bool Get3dLineConversion() const;

  //! Sets mode for conversion Geom_Circle to bezier.
  void Set3dCircleConversion(const bool mode);

  //! Returns the Geom_Circle conversion mode.
  bool Get3dCircleConversion() const;

  //! Sets mode for conversion Geom_Conic to bezier.
  void Set3dConicConversion(const bool mode);

  //! Returns the Geom_Conic conversion mode.
  bool Get3dConicConversion() const;

  //! Sets mode for conversion Geom_Plane to Bezier
  void SetPlaneMode(const bool mode);

  //! Returns the Geom_Pline conversion mode.
  bool GetPlaneMode() const;

  //! Sets mode for conversion Geom_SurfaceOfRevolution to Bezier
  void SetRevolutionMode(const bool mode);

  //! Returns the Geom_SurfaceOfRevolution conversion mode.
  bool GetRevolutionMode() const;

  //! Sets mode for conversion Geom_SurfaceOfLinearExtrusion to Bezier
  void SetExtrusionMode(const bool mode);

  //! Returns the Geom_SurfaceOfLinearExtrusion conversion mode.
  bool GetExtrusionMode() const;

  //! Sets mode for conversion Geom_BSplineSurface to Bezier
  void SetBSplineMode(const bool mode);

  //! Returns the Geom_BSplineSurface conversion mode.
  bool GetBSplineMode() const;

  //! Performs converting and computes the resulting shape
  Standard_EXPORT bool Perform(const bool newContext = true) override;

protected:
  //! Returns the tool for dividing faces.
  Standard_EXPORT occ::handle<ShapeUpgrade_FaceDivide> GetSplitFaceTool() const override;

  Standard_EXPORT Message_Msg GetFaceMsg() const override;

  Standard_EXPORT Message_Msg GetWireMsg() const override;

  //! Returns a message describing modification of a shape.
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

//=================================================================================================

inline bool ShapeUpgrade_ShapeConvertToBezier::Get2dConversion() const
{
  return my2dMode;
}

//=================================================================================================

inline void ShapeUpgrade_ShapeConvertToBezier::Set3dConversion(const bool mode)
{
  my3dMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ShapeConvertToBezier::Get3dConversion() const
{
  return my3dMode;
}

//=================================================================================================

inline void ShapeUpgrade_ShapeConvertToBezier::SetSurfaceConversion(const bool mode)
{
  mySurfaceMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ShapeConvertToBezier::GetSurfaceConversion() const
{
  return mySurfaceMode;
}

//=================================================================================================

inline void ShapeUpgrade_ShapeConvertToBezier::Set3dLineConversion(const bool mode)
{
  my3dLineMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ShapeConvertToBezier::Get3dLineConversion() const
{
  return my3dLineMode;
}

//=================================================================================================

inline void ShapeUpgrade_ShapeConvertToBezier::Set3dCircleConversion(const bool mode)
{
  my3dCircleMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ShapeConvertToBezier::Get3dCircleConversion() const
{
  return my3dCircleMode;
}

//=================================================================================================

inline void ShapeUpgrade_ShapeConvertToBezier::Set3dConicConversion(const bool mode)
{
  my3dConicMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ShapeConvertToBezier::Get3dConicConversion() const
{
  return my3dConicMode;
}

//=================================================================================================

inline void ShapeUpgrade_ShapeConvertToBezier::SetPlaneMode(const bool mode)
{
  myPlaneMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ShapeConvertToBezier::GetPlaneMode() const
{
  return myPlaneMode;
}

//=================================================================================================

inline void ShapeUpgrade_ShapeConvertToBezier::SetRevolutionMode(const bool mode)
{
  myRevolutionMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ShapeConvertToBezier::GetRevolutionMode() const
{
  return myRevolutionMode;
}

//=================================================================================================

inline void ShapeUpgrade_ShapeConvertToBezier::SetExtrusionMode(const bool mode)
{
  myExtrusionMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ShapeConvertToBezier::GetExtrusionMode() const
{
  return myExtrusionMode;
}

//=================================================================================================

inline void ShapeUpgrade_ShapeConvertToBezier::SetBSplineMode(const bool mode)
{
  myBSplineMode = mode;
}

//=================================================================================================

inline bool ShapeUpgrade_ShapeConvertToBezier::GetBSplineMode() const
{
  return myBSplineMode;
}
