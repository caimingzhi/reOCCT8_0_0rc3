#pragma once

#include <Standard.hpp>

#include <TopoDS_Shell.hpp>
#include <TopoDS_Compound.hpp>
#include <ShapeFix_Root.hpp>
#include <ShapeExtend_Status.hpp>
#include <Message_ProgressRange.hpp>

class ShapeFix_Face;
class ShapeExtend_BasicMsgRegistrator;

#ifdef Status
  #undef Status
#endif

class ShapeFix_Shell : public ShapeFix_Root
{

public:
  Standard_EXPORT ShapeFix_Shell();

  Standard_EXPORT ShapeFix_Shell(const TopoDS_Shell& shape);

  Standard_EXPORT void Init(const TopoDS_Shell& shell);

  Standard_EXPORT bool Perform(const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT bool FixFaceOrientation(const TopoDS_Shell& shell,
                                          const bool          isAccountMultiConex = true,
                                          const bool          NonManifold         = false);

  Standard_EXPORT TopoDS_Shell Shell();

  Standard_EXPORT TopoDS_Shape Shape();

  Standard_EXPORT int NbShells() const;

  Standard_EXPORT TopoDS_Compound ErrorFaces() const;

  Standard_EXPORT bool Status(const ShapeExtend_Status status) const;

  occ::handle<ShapeFix_Face> FixFaceTool();

  Standard_EXPORT void SetMsgRegistrator(
    const occ::handle<ShapeExtend_BasicMsgRegistrator>& msgreg) override;

  Standard_EXPORT void SetPrecision(const double preci) override;

  Standard_EXPORT void SetMinTolerance(const double mintol) override;

  Standard_EXPORT void SetMaxTolerance(const double maxtol) override;

  int& FixFaceMode();

  int& FixOrientationMode();

  Standard_EXPORT virtual void SetNonManifoldFlag(const bool isNonManifold);

  DEFINE_STANDARD_RTTIEXT(ShapeFix_Shell, ShapeFix_Root)

protected:
  TopoDS_Shell               myShell;
  TopoDS_Compound            myErrFaces;
  int                        myStatus;
  occ::handle<ShapeFix_Face> myFixFace;
  int                        myFixFaceMode;
  int                        myFixOrientationMode;
  int                        myNbShells;
  bool                       myNonManifold;
};

inline occ::handle<ShapeFix_Face> ShapeFix_Shell::FixFaceTool()
{
  return myFixFace;
}

inline int& ShapeFix_Shell::FixFaceMode()
{
  return myFixFaceMode;
}

inline int& ShapeFix_Shell::FixOrientationMode()
{
  return myFixOrientationMode;
}
