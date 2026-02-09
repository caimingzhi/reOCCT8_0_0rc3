#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_Map.hpp>
#include <Standard_Integer.hpp>
#include <ShapeFix_Root.hpp>
#include <ShapeExtend_Status.hpp>
#include <Message_ProgressRange.hpp>

class ShapeFix_Solid;
class ShapeFix_Shell;
class ShapeFix_Face;
class ShapeFix_Wire;
class ShapeFix_Edge;
class ShapeExtend_BasicMsgRegistrator;

#ifdef Status
  #undef Status
#endif

class ShapeFix_Shape : public ShapeFix_Root
{

public:
  Standard_EXPORT ShapeFix_Shape();

  Standard_EXPORT ShapeFix_Shape(const TopoDS_Shape& shape);

  Standard_EXPORT void Init(const TopoDS_Shape& shape);

  Standard_EXPORT bool Perform(const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT TopoDS_Shape Shape() const;

  occ::handle<ShapeFix_Solid> FixSolidTool() const;

  occ::handle<ShapeFix_Shell> FixShellTool() const;

  occ::handle<ShapeFix_Face> FixFaceTool() const;

  occ::handle<ShapeFix_Wire> FixWireTool() const;

  occ::handle<ShapeFix_Edge> FixEdgeTool() const;

  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  Standard_EXPORT void SetMsgRegistrator(
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg) override;

  Standard_EXPORT void SetPrecision(const double preci) override;

  Standard_EXPORT void SetMinTolerance(const double mintol) override;

  Standard_EXPORT void SetMaxTolerance(const double maxtol) override;

  int& FixSolidMode();

  int& FixFreeShellMode();

  int& FixFreeFaceMode();

  int& FixFreeWireMode();

  int& FixSameParameterMode();

  int& FixVertexPositionMode();

  int& FixVertexTolMode();

  DEFINE_STANDARD_RTTIEXT(ShapeFix_Shape, ShapeFix_Root)

protected:
  Standard_EXPORT void SameParameter(
    const TopoDS_Shape&          shape,
    const bool                   enforce,
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  TopoDS_Shape                                           myResult;
  occ::handle<ShapeFix_Solid>                            myFixSolid;
  NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher> myMapFixingShape;
  int                                                    myFixSolidMode;
  int                                                    myFixShellMode;
  int                                                    myFixFaceMode;
  int                                                    myFixWireMode;
  int                                                    myFixSameParameterMode;
  int                                                    myFixVertexPositionMode;
  int                                                    myFixVertexTolMode;
  int                                                    myStatus;
};

#include <ShapeFix_Solid.hpp>
#include <ShapeFix_Shell.hpp>
#include <ShapeFix_Face.hpp>
#include <ShapeFix_Wire.hpp>

inline occ::handle<ShapeFix_Solid> ShapeFix_Shape::FixSolidTool() const
{
  return myFixSolid;
}

inline occ::handle<ShapeFix_Shell> ShapeFix_Shape::FixShellTool() const
{
  return myFixSolid->FixShellTool();
}

inline occ::handle<ShapeFix_Face> ShapeFix_Shape::FixFaceTool() const
{
  return myFixSolid->FixShellTool()->FixFaceTool();
}

inline occ::handle<ShapeFix_Wire> ShapeFix_Shape::FixWireTool() const
{
  return myFixSolid->FixShellTool()->FixFaceTool()->FixWireTool();
}

inline occ::handle<ShapeFix_Edge> ShapeFix_Shape::FixEdgeTool() const
{
  return myFixSolid->FixShellTool()->FixFaceTool()->FixWireTool()->FixEdgeTool();
}

inline int& ShapeFix_Shape::FixSolidMode()
{
  return myFixSolidMode;
}

inline int& ShapeFix_Shape::FixFreeShellMode()
{
  return myFixShellMode;
}

inline int& ShapeFix_Shape::FixFreeFaceMode()
{
  return myFixFaceMode;
}

inline int& ShapeFix_Shape::FixFreeWireMode()
{
  return myFixWireMode;
}

inline int& ShapeFix_Shape::FixSameParameterMode()
{
  return myFixSameParameterMode;
}

inline int& ShapeFix_Shape::FixVertexPositionMode()
{
  return myFixVertexPositionMode;
}

inline int& ShapeFix_Shape::FixVertexTolMode()
{
  return myFixVertexTolMode;
}
