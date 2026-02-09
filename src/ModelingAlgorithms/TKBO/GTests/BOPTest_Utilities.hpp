#pragma once

#include <gtest/gtest.h>

#include <BOPAlgo_BOP.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Operation.hpp>
#include <BRepPrimAPI_MakeBox.hpp>
#include <BRepPrimAPI_MakeSphere.hpp>
#include <BRepPrimAPI_MakeCylinder.hpp>
#include <BRepPrimAPI_MakeCone.hpp>
#include <BRepBuilderAPI_MakePolygon.hpp>
#include <BRepPrimAPI_MakePrism.hpp>
#include <BRepPrimAPI_MakeRevol.hpp>
#include <TopExp.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS_Face.hpp>
#include <BRepBuilderAPI_MakeFace.hpp>
#include <BRepBuilderAPI_NurbsConvert.hpp>
#include <BRepBuilderAPI_Transform.hpp>
#include <BRepBuilderAPI_MakeVertex.hpp>
#include <BRepBuilderAPI_MakeEdge.hpp>
#include <BRepBuilderAPI_MakeWire.hpp>
#include <BRepFilletAPI_MakeFillet.hpp>
#include <gp_Trsf.hpp>
#include <gp_Ax1.hpp>
#include <gp_Vec.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS_Vertex.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS.hpp>
#include <ElSLib.hpp>
#include <gp_Vec2d.hpp>
#include <gp_Pnt2d.hpp>
#include <gp_Circ.hpp>
#include <gp_Ax2.hpp>
#include <Precision.hpp>
#include <BRepAlgoAPI_Cut.hpp>
#include <BRepAlgoAPI_Fuse.hpp>
#include <BRepAlgoAPI_Common.hpp>
#include <BRepTools.hpp>
#include <GProp_GProps.hpp>
#include <BRepGProp.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <Standard_Real.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <gp_Dir.hpp>

#include <cmath>
#include <memory>

#ifndef M_PI
  #define M_PI 3.14159265358979323846
#endif

class BOPTest_Utilities
{
public:
  enum class ProfileCmd
  {
    O,
    P,
    F,
    X,
    Y,
    L,
    XX,
    YY,
    T,
    TT,
    R,
    RR,
    D,
    C,
    W,
    WW
  };

  struct ProfileOperation
  {
    ProfileCmd          cmd;
    std::vector<double> params;

    ProfileOperation(ProfileCmd c)
        : cmd(c)
    {
    }

    ProfileOperation(ProfileCmd c, double p1)
        : cmd(c),
          params({p1})
    {
    }

    ProfileOperation(ProfileCmd c, double p1, double p2)
        : cmd(c),
          params({p1, p2})
    {
    }

    ProfileOperation(ProfileCmd c, double p1, double p2, double p3)
        : cmd(c),
          params({p1, p2, p3})
    {
    }

    ProfileOperation(ProfileCmd c, double p1, double p2, double p3, double p4, double p5, double p6)
        : cmd(c),
          params({p1, p2, p3, p4, p5, p6})
    {
    }

    ProfileOperation(ProfileCmd c, const std::vector<double>& p)
        : cmd(c),
          params(p)
    {
    }
  };

  static constexpr double DefaultTolerance() { return 1.0e-6; }

  static constexpr double DefaultFuzzyValue() { return 1.0e-8; }

  static double GetSurfaceArea(const TopoDS_Shape& theShape)
  {
    if (theShape.IsNull())
    {
      return 0.0;
    }
    GProp_GProps aProps;
    BRepGProp::SurfaceProperties(theShape, aProps);
    return aProps.Mass();
  }

  static double GetVolume(const TopoDS_Shape& theShape)
  {
    if (theShape.IsNull())
    {
      return 0.0;
    }
    GProp_GProps aProps;
    BRepGProp::VolumeProperties(theShape, aProps);
    return aProps.Mass();
  }

  static bool IsEmpty(const TopoDS_Shape& theShape, const double theTolerance = DefaultTolerance())
  {
    return GetSurfaceArea(theShape) <= theTolerance;
  }

  static TopoDS_Shape CreateUnitBox()
  {
    BRepPrimAPI_MakeBox aBoxMaker(1.0, 1.0, 1.0);
    return aBoxMaker.Shape();
  }

  static TopoDS_Shape CreateBox(const gp_Pnt& theCorner, double theX, double theY, double theZ)
  {
    BRepPrimAPI_MakeBox aBoxMaker(theCorner, theX, theY, theZ);
    return aBoxMaker.Shape();
  }

  static TopoDS_Shape CreateUnitSphere()
  {
    BRepPrimAPI_MakeSphere aSphereMaker(1.0);
    return aSphereMaker.Shape();
  }

  static TopoDS_Shape CreateSphere(const gp_Pnt& theCenter, double theRadius)
  {
    BRepPrimAPI_MakeSphere aSphereMaker(theCenter, theRadius);
    return aSphereMaker.Shape();
  }

  static TopoDS_Shape CreateCylinder(double theRadius, double theHeight)
  {
    BRepPrimAPI_MakeCylinder aCylinderMaker(theRadius, theHeight);
    return aCylinderMaker.Shape();
  }

  static TopoDS_Shape CreateCone(double theR1, double theR2, double theHeight)
  {
    BRepPrimAPI_MakeCone aConeMaker(theR1, theR2, theHeight);
    return aConeMaker.Shape();
  }

  static TopoDS_Shape ConvertToNurbs(const TopoDS_Shape& theShape)
  {
    BRepBuilderAPI_NurbsConvert aNurbsConverter(theShape);
    if (!aNurbsConverter.IsDone())
    {
      return TopoDS_Shape();
    }
    return aNurbsConverter.Shape();
  }

  static TopoDS_Shape CreatePolygonFace(const gp_Pnt& theP1,
                                        const gp_Pnt& theP2,
                                        const gp_Pnt& theP3,
                                        const gp_Pnt& theP4)
  {
    BRepBuilderAPI_MakePolygon aPolygonMaker;
    aPolygonMaker.Add(theP1);
    aPolygonMaker.Add(theP2);
    aPolygonMaker.Add(theP3);
    aPolygonMaker.Add(theP4);
    aPolygonMaker.Close();

    if (!aPolygonMaker.IsDone())
    {
      return TopoDS_Shape();
    }

    BRepBuilderAPI_MakeFace aFaceMaker(aPolygonMaker.Wire());
    return aFaceMaker.Shape();
  }

  static TopoDS_Shape RotateShape(const TopoDS_Shape& theShape,
                                  const gp_Ax1&       theAxis,
                                  double              theAngle)
  {
    gp_Trsf aTrsf;
    aTrsf.SetRotation(theAxis, theAngle);
    BRepBuilderAPI_Transform aTransformer(theShape, aTrsf);
    return aTransformer.Shape();
  }

  static TopoDS_Shape TranslateShape(const TopoDS_Shape& theShape, const gp_Vec& theVector)
  {
    gp_Trsf aTrsf;
    aTrsf.SetTranslation(theVector);
    BRepBuilderAPI_Transform aTransformer(theShape, aTrsf);
    return aTransformer.Shape();
  }

  static TopoDS_Vertex CreateVertex(const gp_Pnt& thePoint)
  {
    BRepBuilderAPI_MakeVertex aVertexMaker(thePoint);
    return aVertexMaker.Vertex();
  }

  static TopoDS_Edge CreateEdge(const gp_Pnt& theP1, const gp_Pnt& theP2)
  {
    BRepBuilderAPI_MakeEdge anEdgeMaker(theP1, theP2);
    return anEdgeMaker.Edge();
  }

  static TopoDS_Wire CreatePolygonWire(const std::vector<gp_Pnt>& thePoints, bool theClose = true)
  {
    BRepBuilderAPI_MakePolygon aPolygonMaker;
    for (const gp_Pnt& aPt : thePoints)
    {
      aPolygonMaker.Add(aPt);
    }
    if (theClose)
    {
      aPolygonMaker.Close();
    }
    return aPolygonMaker.Wire();
  }

  static TopoDS_Wire CreateProfileWire(const gp_Pln&                   thePlane,
                                       const gp_Pnt2d&                 theStartPt,
                                       const std::vector<std::string>& theCommands)
  {

    std::vector<gp_Pnt2d> aPoints;
    aPoints.push_back(theStartPt);

    gp_Pnt2d aCurrentPt = theStartPt;
    gp_Vec2d aCurrentDir(1.0, 0.0);

    for (size_t i = 0; i < theCommands.size(); ++i)
    {
      const std::string& aCmd = theCommands[i];
      if (aCmd == "Y" && i + 1 < theCommands.size())
      {

        double aDY = std::stod(theCommands[i + 1]);
        aCurrentPt.SetY(aCurrentPt.Y() + aDY);
        aPoints.push_back(aCurrentPt);
        i++;
      }
      else if (aCmd == "C" && i + 2 < theCommands.size())
      {

        double aRadius = std::stod(theCommands[i + 1]);

        gp_Vec2d aMoveVec = aCurrentDir * aRadius;
        aCurrentPt.Translate(aMoveVec);
        aPoints.push_back(aCurrentPt);
        i += 2;
      }
    }

    std::vector<gp_Pnt> a3DPoints;
    for (const gp_Pnt2d& aPt2d : aPoints)
    {
      gp_Pnt aPt3d = ElSLib::Value(aPt2d.X(), aPt2d.Y(), thePlane);
      a3DPoints.push_back(aPt3d);
    }

    return CreatePolygonWire(a3DPoints, true);
  }

  static TopoDS_Shape CreateProfile(const gp_Pln&                        thePlane,
                                    const std::vector<ProfileOperation>& theOperations)
  {
    BRepBuilderAPI_MakeWire aMakeWire;

    gp_Pnt2d aCurrentPt(0, 0);
    gp_Vec2d aCurrentDir(1, 0);
    bool     aFirstSet = false;
    gp_Pnt2d aFirstPt(0, 0);
    gp_Pln   aWorkingPlane = thePlane;

    for (const auto& op : theOperations)
    {
      switch (op.cmd)
      {
        case ProfileCmd::O:
          if (op.params.size() >= 3)
          {

            gp_Pnt aNewOrigin(op.params[0], op.params[1], op.params[2]);
            gp_Ax3 aNewAx3(aNewOrigin,
                           aWorkingPlane.Axis().Direction(),
                           aWorkingPlane.XAxis().Direction());
            aWorkingPlane = gp_Pln(aNewAx3);

            if (!aFirstSet)
            {
              aCurrentPt.SetCoord(0.0, 0.0);
              aFirstPt  = aCurrentPt;
              aFirstSet = true;
            }
          }
          break;

        case ProfileCmd::P:
          if (op.params.size() >= 6)
          {

            gp_Vec aNormal(op.params[0], op.params[1], op.params[2]);
            gp_Vec aXDir(op.params[3], op.params[4], op.params[5]);

            gp_Dir aNormalDir(aNormal);
            gp_Dir aXDirection(aXDir);

            gp_Ax3 aNewAx3(aWorkingPlane.Location(), aNormalDir, aXDirection);
            aWorkingPlane = gp_Pln(aNewAx3);
          }
          break;

        case ProfileCmd::F:
          if (op.params.size() >= 2)
          {
            aCurrentPt.SetCoord(op.params[0], op.params[1]);
            aFirstPt  = aCurrentPt;
            aFirstSet = true;
          }
          break;

        case ProfileCmd::X:
          if (op.params.size() >= 1)
          {

            if (!aFirstSet)
            {
              aCurrentPt.SetCoord(0.0, 0.0);
              aFirstPt  = aCurrentPt;
              aFirstSet = true;
            }

            gp_Pnt2d aNewPt(aCurrentPt.X() + op.params[0], aCurrentPt.Y());

            gp_Pnt aPt1 = ElSLib::Value(aCurrentPt.X(), aCurrentPt.Y(), aWorkingPlane);
            gp_Pnt aPt2 = ElSLib::Value(aNewPt.X(), aNewPt.Y(), aWorkingPlane);
            aMakeWire.Add(BRepBuilderAPI_MakeEdge(aPt1, aPt2));
            aCurrentPt  = aNewPt;
            aCurrentDir = gp_Vec2d(op.params[0] > 0 ? 1 : -1, 0);
          }
          break;

        case ProfileCmd::Y:
          if (op.params.size() >= 1)
          {

            if (!aFirstSet)
            {
              aCurrentPt.SetCoord(0.0, 0.0);
              aFirstPt  = aCurrentPt;
              aFirstSet = true;
            }

            gp_Pnt2d aNewPt(aCurrentPt.X(), aCurrentPt.Y() + op.params[0]);

            gp_Pnt aPt1 = ElSLib::Value(aCurrentPt.X(), aCurrentPt.Y(), aWorkingPlane);
            gp_Pnt aPt2 = ElSLib::Value(aNewPt.X(), aNewPt.Y(), aWorkingPlane);
            aMakeWire.Add(BRepBuilderAPI_MakeEdge(aPt1, aPt2));
            aCurrentPt  = aNewPt;
            aCurrentDir = gp_Vec2d(0, op.params[0] > 0 ? 1 : -1);
          }
          break;

        case ProfileCmd::C:
          if (op.params.size() >= 2)
          {
            double aRadius   = std::abs(op.params[0]);
            double aAngleDeg = op.params[1];
            double aAngleRad = aAngleDeg * M_PI / 180.0;

            if (std::abs(aAngleDeg) >= 360.0)
            {

              gp_Pnt2d aCenter2D = aFirstSet ? aCurrentPt : gp_Pnt2d(0, 0);
              gp_Pnt   aCenter3D = ElSLib::Value(aCenter2D.X(), aCenter2D.Y(), aWorkingPlane);

              gp_Circ aCirc(gp_Ax2(aCenter3D, aWorkingPlane.Axis().Direction()), aRadius);
              aMakeWire.Add(BRepBuilderAPI_MakeEdge(aCirc));

              aCurrentPt  = gp_Pnt2d(aCenter2D.X() + aRadius, aCenter2D.Y());
              aCurrentDir = gp_Vec2d(0, 1);
              aFirstSet   = true;
            }
            else
            {

              if (!aFirstSet)
              {
                aCurrentPt.SetCoord(0.0, 0.0);
                aCurrentDir = gp_Vec2d(1, 0);
                aFirstPt    = aCurrentPt;
                aFirstSet   = true;
              }

              gp_Vec2d aNormal(-aCurrentDir.Y(), aCurrentDir.X());
              gp_Pnt2d aCenter = aCurrentPt.Translated(aNormal * aRadius);

              double aStartAngle =
                atan2(aCurrentPt.Y() - aCenter.Y(), aCurrentPt.X() - aCenter.X());
              double   aEndAngle = aStartAngle + aAngleRad;
              gp_Pnt2d aEndPt(aCenter.X() + aRadius * cos(aEndAngle),
                              aCenter.Y() + aRadius * sin(aEndAngle));

              gp_Pnt aPt1      = ElSLib::Value(aCurrentPt.X(), aCurrentPt.Y(), aWorkingPlane);
              gp_Pnt aPt2      = ElSLib::Value(aEndPt.X(), aEndPt.Y(), aWorkingPlane);
              gp_Pnt aCenter3D = ElSLib::Value(aCenter.X(), aCenter.Y(), aWorkingPlane);

              gp_Circ aCirc(gp_Ax2(aCenter3D, aWorkingPlane.Axis().Direction()), aRadius);
              aMakeWire.Add(BRepBuilderAPI_MakeEdge(aCirc, aPt1, aPt2));

              aCurrentPt  = aEndPt;
              aCurrentDir = gp_Vec2d(cos(aEndAngle + M_PI / 2), sin(aEndAngle + M_PI / 2));
            }
          }
          break;

        case ProfileCmd::D:
          if (op.params.size() >= 2)
          {
            aCurrentDir = gp_Vec2d(op.params[0], op.params[1]);
            aCurrentDir.Normalize();
          }
          break;

        case ProfileCmd::W:

          break;

        default:

          break;
      }
    }

    if (aFirstSet && !aCurrentPt.IsEqual(aFirstPt, Precision::Confusion()))
    {

      gp_Pnt aPt1 = ElSLib::Value(aCurrentPt.X(), aCurrentPt.Y(), aWorkingPlane);
      gp_Pnt aPt2 = ElSLib::Value(aFirstPt.X(), aFirstPt.Y(), aWorkingPlane);
      aMakeWire.Add(BRepBuilderAPI_MakeEdge(aPt1, aPt2));
    }

    EXPECT_TRUE(aMakeWire.IsDone()) << "Profile wire creation failed";
    TopoDS_Wire aWire = aMakeWire.Wire();

    BRepBuilderAPI_MakeFace aFaceMaker(aWire);
    EXPECT_TRUE(aFaceMaker.IsDone()) << "Profile face creation failed";
    return aFaceMaker.Face();
  }

  static TopoDS_Shape CreateProfileFromOperations(
    const std::vector<ProfileOperation>& theOperations)
  {

    const gp_Pln aPlane(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z));
    return CreateProfile(aPlane, theOperations);
  }

  static TopoDS_Wire CreateRectangularProfile(const gp_Pnt& theCorner, double theX, double theY)
  {
    std::vector<gp_Pnt> aPoints;
    aPoints.push_back(theCorner);
    aPoints.push_back(gp_Pnt(theCorner.X() + theX, theCorner.Y(), theCorner.Z()));
    aPoints.push_back(gp_Pnt(theCorner.X() + theX, theCorner.Y() + theY, theCorner.Z()));
    aPoints.push_back(gp_Pnt(theCorner.X(), theCorner.Y() + theY, theCorner.Z()));
    return CreatePolygonWire(aPoints, true);
  }

  static TopoDS_Shape CreateFaceFromWire(const TopoDS_Wire& theWire)
  {
    BRepBuilderAPI_MakeFace aFaceMaker(theWire);
    if (!aFaceMaker.IsDone())
    {
      return TopoDS_Shape();
    }
    return aFaceMaker.Shape();
  }

  static TopoDS_Shape CreatePrism(const TopoDS_Shape& theProfile, const gp_Vec& theDirection)
  {
    BRepPrimAPI_MakePrism aPrismMaker(theProfile, theDirection);
    if (!aPrismMaker.IsDone())
    {
      return TopoDS_Shape();
    }
    return aPrismMaker.Shape();
  }

  static TopoDS_Shape CreateRectangularPrism(const gp_Pnt& theCorner,
                                             double        theX,
                                             double        theY,
                                             double        theZ)
  {
    TopoDS_Wire  aWire = CreateRectangularProfile(theCorner, theX, theY);
    TopoDS_Shape aFace = CreateFaceFromWire(aWire);
    return CreatePrism(aFace, gp_Vec(0, 0, theZ));
  }

  static TopoDS_Shape CreateRevolution(const TopoDS_Shape& theProfile,
                                       const gp_Ax1&       theAxis,
                                       double              theAngle)
  {
    BRepPrimAPI_MakeRevol aRevolMaker(theProfile, theAxis, theAngle);
    EXPECT_TRUE(aRevolMaker.IsDone()) << "Revolution operation failed";
    return aRevolMaker.Shape();
  }

  static TopoDS_Face GetFaceByIndex(const TopoDS_Shape& theShape, int theIndex)
  {
    TopExp_Explorer anExp(theShape, TopAbs_FACE);
    int             aCurrentIndex = 1;

    while (anExp.More())
    {
      if (aCurrentIndex == theIndex)
      {
        return TopoDS::Face(anExp.Current());
      }
      aCurrentIndex++;
      anExp.Next();
    }
    return TopoDS_Face();
  }

  static TopoDS_Shape RotateZ(const TopoDS_Shape& theShape, double theAngleDeg)
  {
    gp_Trsf aRotation;
    aRotation.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Z)),
                          theAngleDeg * M_PI / 180.0);
    BRepBuilderAPI_Transform aTransform(theShape, aRotation);
    return aTransform.Shape();
  }

  static TopoDS_Shape RotateY(const TopoDS_Shape& theShape, double theAngleDeg)
  {
    gp_Trsf aRotation;
    aRotation.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::Y)),
                          theAngleDeg * M_PI / 180.0);
    BRepBuilderAPI_Transform aTransform(theShape, aRotation);
    return aTransform.Shape();
  }

  static TopoDS_Shape RotateX(const TopoDS_Shape& theShape, double theAngleDeg)
  {
    gp_Trsf aRotation;
    aRotation.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(gp_Dir::D::X)),
                          theAngleDeg * M_PI / 180.0);
    BRepBuilderAPI_Transform aTransform(theShape, aRotation);
    return aTransform.Shape();
  }

  static TopoDS_Shape RotateStandard(const TopoDS_Shape& theShape)
  {
    TopoDS_Shape aResult = RotateZ(theShape, -90.0);
    return RotateY(aResult, -45.0);
  }

  static TopoDS_Shape Translate(const TopoDS_Shape& theShape,
                                double              theDx,
                                double              theDy,
                                double              theDz)
  {
    gp_Trsf aTranslation;
    aTranslation.SetTranslation(gp_Vec(theDx, theDy, theDz));
    BRepBuilderAPI_Transform aTransform(theShape, aTranslation);
    return aTransform.Shape();
  }

  static TopoDS_Shape RotateY90(const TopoDS_Shape& theShape)
  {
    gp_Trsf aRotation;
    aRotation.SetRotation(gp_Ax1(gp_Pnt(0, 0, 1), gp_Dir(gp_Dir::D::Y)), 90.0 * M_PI / 180.0);
    BRepBuilderAPI_Transform aTransform(theShape, aRotation);
    return aTransform.Shape();
  }

  static void CreateSphereAndBox(TopoDS_Shape& theSphere, TopoDS_Shape& theBox)
  {
    theSphere = CreateUnitSphere();
    theBox    = CreateUnitBox();
  }

  static void CreateIdenticalBoxes(TopoDS_Shape& theBox1, TopoDS_Shape& theBox2)
  {
    theBox1 = CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
    theBox2 = CreateBox(gp_Pnt(0, 0, 0), 1.0, 1.0, 1.0);
  }

  static void CreateNurbsAndRegularBox(TopoDS_Shape& theNurbsBox,
                                       TopoDS_Shape& theRegularBox,
                                       const gp_Pnt& theNurbsCorner   = gp_Pnt(0, 0, 0),
                                       const gp_Pnt& theRegularCorner = gp_Pnt(0, 1, 0),
                                       double        theNurbsX        = 1.0,
                                       double        theNurbsY        = 1.0,
                                       double        theNurbsZ        = 1.0,
                                       double        theRegularX      = 1.0,
                                       double        theRegularY      = 0.5,
                                       double        theRegularZ      = 1.0)
  {
    theNurbsBox = CreateBox(theNurbsCorner, theNurbsX, theNurbsY, theNurbsZ);
    theNurbsBox = ConvertToNurbs(theNurbsBox);

    theRegularBox = CreateBox(theRegularCorner, theRegularX, theRegularY, theRegularZ);
  }

  static TopoDS_Shape CreateBlend(const TopoDS_Shape& theShape, int theEdgeIndex, double theRadius)
  {

    TopExp_Explorer anExp(theShape, TopAbs_EDGE);
    int             aCurrentIndex = 1;
    TopoDS_Edge     aTargetEdge;

    while (anExp.More())
    {
      if (aCurrentIndex == theEdgeIndex)
      {
        aTargetEdge = TopoDS::Edge(anExp.Current());
        break;
      }
      aCurrentIndex++;
      anExp.Next();
    }

    if (aTargetEdge.IsNull())
    {
      return theShape;
    }

    BRepFilletAPI_MakeFillet aFilletMaker(theShape, ChFi3d_Rational);

    aFilletMaker.SetParams(1e-2, 1.0e-4, 1.e-5, 1.e-4, 1.e-5, 1.e-3);

    aFilletMaker.SetContinuity(GeomAbs_C1, 1.e-2);

    aFilletMaker.Add(theRadius, aTargetEdge);
    aFilletMaker.Build();

    if (!aFilletMaker.IsDone())
    {
      return TopoDS_Shape();
    }

    return aFilletMaker.Shape();
  }

  static TopoDS_Shape CreateCylinderOnPlane(const gp_Pln& thePlane,
                                            double        theRadius,
                                            double        theHeight)
  {

    const gp_Ax2 anAx2 = thePlane.Position().Ax2();

    BRepPrimAPI_MakeCylinder aCylinderMaker(anAx2, theRadius, theHeight);
    aCylinderMaker.Build();

    if (!aCylinderMaker.IsDone())
    {
      return TopoDS_Shape();
    }

    return aCylinderMaker.Shape();
  }
};

class BRepAlgoAPI_TestBase : public ::testing::Test
{
protected:
  void SetUp() override { myTolerance = BOPTest_Utilities::DefaultTolerance(); }

  TopoDS_Shape PerformCut(const TopoDS_Shape& theObject, const TopoDS_Shape& theTool)
  {
    BRepAlgoAPI_Cut aCutter(theObject, theTool);
    EXPECT_TRUE(aCutter.IsDone()) << "BRepAlgoAPI_Cut operation failed";
    return aCutter.Shape();
  }

  TopoDS_Shape PerformFuse(const TopoDS_Shape& theShape1, const TopoDS_Shape& theShape2)
  {
    BRepAlgoAPI_Fuse aFuser(theShape1, theShape2);
    EXPECT_TRUE(aFuser.IsDone()) << "BRepAlgoAPI_Fuse operation failed";
    return aFuser.Shape();
  }

  TopoDS_Shape PerformCommon(const TopoDS_Shape& theShape1, const TopoDS_Shape& theShape2)
  {
    BRepAlgoAPI_Common aCommoner(theShape1, theShape2);
    EXPECT_TRUE(aCommoner.IsDone()) << "BRepAlgoAPI_Common operation failed";
    return aCommoner.Shape();
  }

  void ValidateResult(const TopoDS_Shape& theResult,
                      double              theExpectedSurfaceArea = -1.0,
                      double              theExpectedVolume      = -1.0,
                      bool                theExpectedEmpty       = false)
  {
    if (theExpectedEmpty)
    {
      EXPECT_TRUE(BOPTest_Utilities::IsEmpty(theResult, myTolerance)) << "Result should be empty";
      return;
    }

    EXPECT_FALSE(theResult.IsNull()) << "Result shape should not be null";

    if (theExpectedSurfaceArea >= 0.0)
    {
      const double aSurfaceArea = BOPTest_Utilities::GetSurfaceArea(theResult);
      EXPECT_NEAR(aSurfaceArea, theExpectedSurfaceArea, 5000.0) << "Surface area mismatch";
    }

    if (theExpectedVolume >= 0.0)
    {
      const double aVolume = BOPTest_Utilities::GetVolume(theResult);
      EXPECT_NEAR(aVolume, theExpectedVolume, myTolerance) << "Volume mismatch";
    }
  }

protected:
  double myTolerance;
};

class BOPAlgo_TestBase : public ::testing::Test
{
protected:
  void SetUp() override
  {
    myTolerance  = BOPTest_Utilities::DefaultTolerance();
    myFuzzyValue = BOPTest_Utilities::DefaultFuzzyValue();
    myPaveFiller.reset();
  }

  void TearDown() override { myPaveFiller.reset(); }

  TopoDS_Shape PerformDirectBOP(const TopoDS_Shape& theShape1,
                                const TopoDS_Shape& theShape2,
                                BOPAlgo_Operation   theOp)
  {
    occ::handle<NCollection_BaseAllocator> aAL = NCollection_BaseAllocator::CommonBaseAllocator();
    BOPAlgo_BOP                            aBOP(aAL);

    aBOP.AddArgument(theShape1);
    aBOP.AddTool(theShape2);
    aBOP.SetOperation(theOp);
    aBOP.SetFuzzyValue(myFuzzyValue);
    aBOP.SetRunParallel(false);
    aBOP.SetNonDestructive(false);

    aBOP.Perform();

    EXPECT_FALSE(aBOP.HasErrors()) << "Direct BOP operation failed";
    return aBOP.Shape();
  }

  TopoDS_Shape PerformTwoStepBOP(const TopoDS_Shape& theShape1,
                                 const TopoDS_Shape& theShape2,
                                 BOPAlgo_Operation   theOp)
  {

    PreparePaveFiller(theShape1, theShape2);

    return PerformBOPWithPaveFiller(theOp);
  }

  void PreparePaveFiller(const TopoDS_Shape& theShape1, const TopoDS_Shape& theShape2)
  {
    NCollection_List<TopoDS_Shape> aLC;
    aLC.Append(theShape1);
    aLC.Append(theShape2);

    occ::handle<NCollection_BaseAllocator> aAL = NCollection_BaseAllocator::CommonBaseAllocator();
    myPaveFiller                               = std::make_unique<BOPAlgo_PaveFiller>(aAL);

    myPaveFiller->SetArguments(aLC);
    myPaveFiller->SetFuzzyValue(myFuzzyValue);
    myPaveFiller->SetRunParallel(false);
    myPaveFiller->SetNonDestructive(false);

    myPaveFiller->Perform();
    EXPECT_FALSE(myPaveFiller->HasErrors()) << "PaveFiller preparation failed";
  }

  TopoDS_Shape PerformBOPWithPaveFiller(BOPAlgo_Operation theOp)
  {
    EXPECT_TRUE(myPaveFiller != nullptr) << "PaveFiller must be prepared first";

    BOPAlgo_BOP                           aBOP;
    const NCollection_List<TopoDS_Shape>& aArguments = myPaveFiller->Arguments();
    EXPECT_EQ(aArguments.Extent(), 2) << "Wrong number of arguments";

    const TopoDS_Shape& aS1 = aArguments.First();
    const TopoDS_Shape& aS2 = aArguments.Last();

    aBOP.AddArgument(aS1);
    aBOP.AddTool(aS2);
    aBOP.SetOperation(theOp);
    aBOP.SetRunParallel(false);

    aBOP.PerformWithFiller(*myPaveFiller);

    EXPECT_FALSE(aBOP.HasErrors()) << "BOP operation with PaveFiller failed";
    return aBOP.Shape();
  }

  void ValidateResult(const TopoDS_Shape& theResult,
                      double              theExpectedSurfaceArea = -1.0,
                      double              theExpectedVolume      = -1.0,
                      bool                theExpectedEmpty       = false)
  {
    if (theExpectedEmpty)
    {
      EXPECT_TRUE(BOPTest_Utilities::IsEmpty(theResult, myTolerance)) << "Result should be empty";
      return;
    }

    EXPECT_FALSE(theResult.IsNull()) << "Result shape should not be null";

    if (theExpectedSurfaceArea >= 0.0)
    {
      const double aSurfaceArea = BOPTest_Utilities::GetSurfaceArea(theResult);
      EXPECT_NEAR(aSurfaceArea, theExpectedSurfaceArea, 5000.0) << "Surface area mismatch";
    }

    if (theExpectedVolume >= 0.0)
    {
      const double aVolume = BOPTest_Utilities::GetVolume(theResult);
      EXPECT_NEAR(aVolume, theExpectedVolume, myTolerance) << "Volume mismatch";
    }
  }

protected:
  double                              myTolerance;
  double                              myFuzzyValue;
  std::unique_ptr<BOPAlgo_PaveFiller> myPaveFiller;
};
