#pragma once

#include <gp_Dir.hpp>
#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>
#include <Standard_Real.hpp>
#include <V3d_TypeOfOrientation.hpp>

class Graphic3d_Group;
class V3d_View;

class V3d
{
public:
  DEFINE_STANDARD_ALLOC

  static gp_Dir GetProjAxis(const V3d_TypeOfOrientation theOrientation)
  {
    switch (theOrientation)
    {
      case V3d_Xpos:
        return gp::DX();
      case V3d_Ypos:
        return gp::DY();
      case V3d_Zpos:
        return gp::DZ();
      case V3d_Xneg:
        return -gp::DX();
      case V3d_Yneg:
        return -gp::DY();
      case V3d_Zneg:
        return -gp::DZ();
      case V3d_XposYposZpos:
        return gp_Dir(1, 1, 1);
      case V3d_XposYposZneg:
        return gp_Dir(1, 1, -1);
      case V3d_XposYnegZpos:
        return gp_Dir(1, -1, 1);
      case V3d_XposYnegZneg:
        return gp_Dir(1, -1, -1);
      case V3d_XnegYposZpos:
        return gp_Dir(-1, 1, 1);
      case V3d_XnegYposZneg:
        return gp_Dir(-1, 1, -1);
      case V3d_XnegYnegZpos:
        return gp_Dir(-1, -1, 1);
      case V3d_XnegYnegZneg:
        return gp_Dir(-1, -1, -1);
      case V3d_XposYpos:
        return gp_Dir(1, 1, 0);
      case V3d_XposYneg:
        return gp_Dir(1, -1, 0);
      case V3d_XnegYpos:
        return gp_Dir(-1, 1, 0);
      case V3d_XnegYneg:
        return gp_Dir(-1, -1, 0);
      case V3d_XposZpos:
        return gp_Dir(1, 0, 1);
      case V3d_XposZneg:
        return gp_Dir(1, 0, -1);
      case V3d_XnegZpos:
        return gp_Dir(-1, 0, 1);
      case V3d_XnegZneg:
        return gp_Dir(-1, 0, -1);
      case V3d_YposZpos:
        return gp_Dir(0, 1, 1);
      case V3d_YposZneg:
        return gp_Dir(0, 1, -1);
      case V3d_YnegZpos:
        return gp_Dir(0, -1, 1);
      case V3d_YnegZneg:
        return gp_Dir(0, -1, -1);
    }
    return gp_Dir(0, 0, 0);
  }

  Standard_EXPORT static void ArrowOfRadius(const occ::handle<Graphic3d_Group>& garrow,
                                            const double                        X0,
                                            const double                        Y0,
                                            const double                        Z0,
                                            const double                        DX,
                                            const double                        DY,
                                            const double                        DZ,
                                            const double                        Alpha,
                                            const double                        Lng);

  Standard_EXPORT static void CircleInPlane(const occ::handle<Graphic3d_Group>& gcircle,
                                            const double                        X0,
                                            const double                        Y0,
                                            const double                        Z0,
                                            const double                        VX,
                                            const double                        VY,
                                            const double                        VZ,
                                            const double                        Radius);

  Standard_EXPORT static void SwitchViewsinWindow(const occ::handle<V3d_View>& aPreviousView,
                                                  const occ::handle<V3d_View>& aNextView);

  Standard_EXPORT static const char* TypeOfOrientationToString(V3d_TypeOfOrientation theType);

  static V3d_TypeOfOrientation TypeOfOrientationFromString(const char* theTypeString)
  {
    V3d_TypeOfOrientation aType = V3d_Xpos;
    TypeOfOrientationFromString(theTypeString, aType);
    return aType;
  }

  Standard_EXPORT static bool TypeOfOrientationFromString(const char*            theTypeString,
                                                          V3d_TypeOfOrientation& theType);
};
