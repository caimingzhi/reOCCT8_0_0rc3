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

// resolve name collisions with X11 headers
#ifdef Status
  #undef Status
#endif

//! Provides method to build a solid from a shells and
//! orients them in order to have a valid solid with finite volume
class ShapeFix_Solid : public ShapeFix_Root
{

public:
  //! Empty constructor;
  Standard_EXPORT ShapeFix_Solid();

  //! Initializes by solid.
  Standard_EXPORT ShapeFix_Solid(const TopoDS_Solid& solid);

  //! Initializes by solid .
  Standard_EXPORT virtual void Init(const TopoDS_Solid& solid);

  //! Iterates on shells and performs fixes
  //! (calls ShapeFix_Shell for each subshell). The passed
  //! progress indicator allows user to consult the current
  //! progress stage and abort algorithm if needed.
  Standard_EXPORT virtual bool Perform(
    const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Calls MakeSolid and orients the solid to be "not infinite"
  Standard_EXPORT TopoDS_Solid SolidFromShell(const TopoDS_Shell& shell);

  //! Returns the status of the last Fix.
  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  //! Returns resulting solid.
  Standard_EXPORT TopoDS_Shape Solid() const;

  //! Returns tool for fixing shells.
  occ::handle<ShapeFix_Shell> FixShellTool() const { return myFixShell; }

  //! Sets message registrator
  Standard_EXPORT void SetMsgRegistrator(
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg) override;

  //! Sets basic precision value (also to FixShellTool)
  Standard_EXPORT void SetPrecision(const double preci) override;

  //! Sets minimal allowed tolerance (also to FixShellTool)
  Standard_EXPORT void SetMinTolerance(const double mintol) override;

  //! Sets maximal allowed tolerance (also to FixShellTool)
  Standard_EXPORT void SetMaxTolerance(const double maxtol) override;

  //! Returns (modifiable) the mode for applying fixes of
  //! ShapeFix_Shell, by default True.
  int& FixShellMode() { return myFixShellMode; }

  //! Returns (modifiable) the mode for applying analysis and fixes of
  //! orientation of shells in the solid; by default True.
  int& FixShellOrientationMode() { return myFixShellOrientationMode; }

  //! Returns (modifiable) the mode for creation of solids.
  //! If mode myCreateOpenSolidMode is equal to true
  //! solids are created from open shells
  //! else solids are created from closed shells only.
  //! ShapeFix_Shell, by default False.
  bool& CreateOpenSolidMode() { return myCreateOpenSolidMode; }

  //! In case of multiconnexity returns compound of fixed solids
  //! else returns one solid.
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

