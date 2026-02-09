#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeFix_Root.hpp>
#include <ShapeExtend_Status.hpp>
class ShapeFix_Shell;
class TopoDS_Solid;
class TopoDS_Shell;
class ShapeExtend_BasicMsgRegistrator;

#ifdef Status
  #undef Status
#endif

class ShapeFix_Solid : public ShapeFix_Root
{

public:
  Standard_EXPORT ShapeFix_Solid();

  Standard_EXPORT ShapeFix_Solid(const TopoDS_Solid& solid);

  Standard_EXPORT virtual void Init(const TopoDS_Solid& solid);

  Standard_EXPORT virtual bool Perform(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT TopoDS_Solid SolidFromShell(const TopoDS_Shell& shell);

  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  Standard_EXPORT TopoDS_Shape Solid() const;

  occ::handle<ShapeFix_Shell> FixShellTool() const { return myFixShell; }

  Standard_EXPORT void SetMsgRegistrator(
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg) override;

  Standard_EXPORT void SetPrecision(const double preci) override;

  Standard_EXPORT void SetMinTolerance(const double mintol) override;

  Standard_EXPORT void SetMaxTolerance(const double maxtol) override;

  int& FixShellMode() { return myFixShellMode; }

  int& FixShellOrientationMode() { return myFixShellOrientationMode; }

  bool& CreateOpenSolidMode() { return myCreateOpenSolidMode; }

  Standard_EXPORT TopoDS_Shape Shape();

  DEFINE_STANDARD_RTTIEXT(ShapeFix_Solid, ShapeFix_Root)

protected:
  TopoDS_Shape                mySolid;
  occ::handle<ShapeFix_Shell> myFixShell;
  int                         myStatus;
  int                         myFixShellMode;
  int                         myFixShellOrientationMode;
  bool                        myCreateOpenSolidMode;
};
