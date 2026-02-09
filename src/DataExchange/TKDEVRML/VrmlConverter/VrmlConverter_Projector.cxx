

#include <Bnd_Box.hpp>
#include <BRepBndLib.hpp>
#include <gp_Ax3.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array1.hpp>
#include <Vrml_Instancing.hpp>
#include <Vrml_TransformSeparator.hpp>
#include <VrmlConverter_Projector.hpp>

IMPLEMENT_STANDARD_RTTIEXT(VrmlConverter_Projector, Standard_Transient)

VrmlConverter_Projector::VrmlConverter_Projector(const NCollection_Array1<TopoDS_Shape>& Shapes,
                                                 const double                            Focus,
                                                 const double                            DX,
                                                 const double                            DY,
                                                 const double                            DZ,
                                                 const double                            XUp,
                                                 const double                            YUp,
                                                 const double                            ZUp,
                                                 const VrmlConverter_TypeOfCamera        Camera,
                                                 const VrmlConverter_TypeOfLight         Light)

{

  myTypeOfCamera = Camera;
  myTypeOfLight  = Light;

  int     i;
  Bnd_Box box;
  double  Xmin, Xmax, Ymin, Ymax, Zmin, Zmax, diagonal;
  double  Xtarget, Ytarget, Ztarget, Angle, MaxAngle, Height, MaxHeight;

  for (i = Shapes.Lower(); i <= Shapes.Upper(); i++)
  {
    BRepBndLib::AddClose(Shapes.Value(i), box);
  }

  double DistMax = 500000;
  double TolMin  = 0.000001;

  box.Enlarge(TolMin);
  box.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);

  if (box.IsOpenXmin())
    Xmin = -DistMax;
  if (box.IsOpenXmax())
    Xmax = DistMax;
  if (box.IsOpenYmin())
    Ymin = -DistMax;
  if (box.IsOpenYmax())
    Ymax = DistMax;
  if (box.IsOpenZmin())
    Zmin = -DistMax;
  if (box.IsOpenZmax())
    Zmax = DistMax;

  double xx = (Xmax - Xmin);
  double yy = (Ymax - Ymin);
  double zz = (Zmax - Zmin);

  Xtarget = (Xmin + Xmax) / 2;
  Ytarget = (Ymin + Ymax) / 2;
  Ztarget = (Zmin + Zmax) / 2;

  gp_Dir Zpers(DX, DY, DZ);
  gp_Vec V(Zpers);

  diagonal = std::sqrt(xx * xx + yy * yy + zz * zz);

  gp_Vec aVec = V.Multiplied(0.5 * diagonal + TolMin + Focus);

  gp_Pnt Source;
  Source.SetX(Xtarget + aVec.X());
  Source.SetY(Ytarget + aVec.Y());
  Source.SetZ(Ztarget + aVec.Z());

  gp_Vec VSource(Source.X(), Source.Y(), Source.Z());

  gp_Dir Ypers(XUp, YUp, ZUp);

  if (Ypers.IsParallel(Zpers, Precision::Angular()))
  {
    throw Standard_Failure("Projection Vector is Parallel to High Point Direction");
  }
  gp_Dir Xpers = Ypers.Crossed(Zpers);

  gp_Ax3 Axe(Source, Zpers, Xpers);

  gp_Trsf T;

  T.SetTransformation(Axe);

  bool Pers = false;
  if (Camera == VrmlConverter_PerspectiveCamera)
    Pers = true;

  myProjector = HLRAlgo_Projector(T, Pers, Focus);

  gp_Trsf T3;
  T3 = T.Inverted();

  myMatrixTransform.SetMatrix(T3);

  if (Light == VrmlConverter_DirectionLight)
  {
    myDirectionalLight.SetDirection(Zpers.Reversed());
  }

  if (Light == VrmlConverter_PointLight)
  {
    myPointLight.SetLocation(VSource);
  }

  if (Light == VrmlConverter_SpotLight || Camera != VrmlConverter_NoCamera)
  {

    gp_Pnt                     CurP;
    NCollection_Array1<gp_Pnt> ArrP(1, 8);

    CurP.SetCoord(Xmin, Ymin, Zmin);
    ArrP.SetValue(1, CurP);
    CurP.SetCoord(Xmin + xx, Ymin, Zmin);
    ArrP.SetValue(2, CurP);
    CurP.SetCoord(Xmin + xx, Ymin + yy, Zmin);
    ArrP.SetValue(3, CurP);
    CurP.SetCoord(Xmin, Ymin + yy, Zmin);
    ArrP.SetValue(4, CurP);

    CurP.SetCoord(Xmin, Ymin, Zmax);
    ArrP.SetValue(5, CurP);
    CurP.SetCoord(Xmin + xx, Ymin, Zmax);
    ArrP.SetValue(6, CurP);
    CurP.SetCoord(Xmin + xx, Ymin + yy, Zmax);
    ArrP.SetValue(7, CurP);
    CurP.SetCoord(Xmin, Ymin + yy, Zmax);
    ArrP.SetValue(8, CurP);

    gp_Vec V1, V2;
    gp_Pnt P1, P2;

    MaxHeight = TolMin;
    MaxAngle  = TolMin;

    for (i = ArrP.Lower(); i <= ArrP.Upper(); i++)
    {
      P1 = ArrP.Value(i);
      P2 = P1.Transformed(T);

      V1.SetX(P2.X());
      V1.SetY(P2.Y());
      V1.SetZ(P2.Z());

      V2.SetX(P2.X());
      V2.SetY(0);
      V2.SetZ(P2.Z());

      if (std::abs(V1.Angle(V2)) > std::abs(MaxAngle))
        MaxAngle = std::abs(V1.Angle(V2));

      V2.SetX(0);
      V2.SetY(P2.Y());
      V2.SetZ(P2.Z());

      if (std::abs(V1.Angle(V2)) > std::abs(MaxAngle))
        MaxAngle = std::abs(V1.Angle(V2));

      if (std::abs(P2.Y()) > std::abs(MaxHeight))
      {

        MaxHeight = std::abs(P2.Y());
      }

      if (std::abs(P2.X()) > std::abs(MaxHeight))
      {

        MaxHeight = std::abs(P2.X());
      }
    }
    Height = MaxHeight;

    Angle = MaxAngle;

    if (Light == VrmlConverter_SpotLight)
    {
      mySpotLight.SetLocation(VSource);
      mySpotLight.SetDirection(Zpers.Reversed());
      mySpotLight.SetCutOffAngle(2 * Angle);
    }

    if (Camera == VrmlConverter_PerspectiveCamera)
    {

      myPerspectiveCamera.SetFocalDistance(Focus);
      myPerspectiveCamera.SetAngle(2 * Angle);
    }

    if (Camera == VrmlConverter_OrthographicCamera)
    {

      myOrthographicCamera.SetFocalDistance(Focus);
      myOrthographicCamera.SetHeight(2 * Height);
    }
  }
}

void VrmlConverter_Projector::Add(Standard_OStream& anOStream) const
{
  switch (myTypeOfCamera)
  {
    case VrmlConverter_NoCamera:
      break;
    case VrmlConverter_PerspectiveCamera:
    {
      Vrml_TransformSeparator TS;
      TS.Print(anOStream);
      myMatrixTransform.Print(anOStream);
      Vrml_Instancing I1("Perspective Camera");
      I1.DEF(anOStream);
      myPerspectiveCamera.Print(anOStream);
      TS.Print(anOStream);
    }
    break;
    case VrmlConverter_OrthographicCamera:
    {
      Vrml_TransformSeparator TS;
      TS.Print(anOStream);
      myMatrixTransform.Print(anOStream);
      Vrml_Instancing I2("Orthographic Camera");
      I2.DEF(anOStream);
      myOrthographicCamera.Print(anOStream);
      TS.Print(anOStream);
    }
    break;
  }

  switch (myTypeOfLight)
  {
    case VrmlConverter_NoLight:
      break;
    case VrmlConverter_DirectionLight:
    {
      myDirectionalLight.Print(anOStream);
    }
    break;
    case VrmlConverter_PointLight:
    {
      myPointLight.Print(anOStream);
    }
    break;
    case VrmlConverter_SpotLight:
    {
      mySpotLight.Print(anOStream);
    }
    break;
  }
}

void VrmlConverter_Projector::SetCamera(const VrmlConverter_TypeOfCamera aCamera)
{
  myTypeOfCamera = aCamera;
}

VrmlConverter_TypeOfCamera VrmlConverter_Projector::Camera() const
{
  return myTypeOfCamera;
}

void VrmlConverter_Projector::SetLight(const VrmlConverter_TypeOfLight aLight)
{
  myTypeOfLight = aLight;
}

VrmlConverter_TypeOfLight VrmlConverter_Projector::Light() const
{
  return myTypeOfLight;
}

HLRAlgo_Projector VrmlConverter_Projector::Projector() const
{
  return myProjector;
}
