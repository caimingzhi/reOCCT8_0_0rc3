#include <BRep_Tool.hpp>
#include <Draw_Display.hpp>
#include <DrawDim.hpp>
#include <DrawDim_Angle.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <gp_Ax1.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <IntAna_QuadQuadGeo.hpp>
#include <Precision.hpp>
#include <Standard_Type.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(DrawDim_Angle, DrawDim_Dimension)

//=================================================================================================

DrawDim_Angle::DrawDim_Angle(const TopoDS_Face& plane1, const TopoDS_Face& plane2)
{
  myPlane1 = plane1;
  myPlane2 = plane2;
}

//=================================================================================================

const TopoDS_Face& DrawDim_Angle::Plane1() const
{
  return myPlane1;
}

//=================================================================================================

void DrawDim_Angle::Plane1(const TopoDS_Face& plane)
{
  myPlane1 = plane;
}

//=================================================================================================

const TopoDS_Face& DrawDim_Angle::Plane2() const
{
  return myPlane2;
}

//=================================================================================================

void DrawDim_Angle::Plane2(const TopoDS_Face& plane)
{
  myPlane2 = plane;
}

//=================================================================================================

void DrawDim_Angle::DrawOn(Draw_Display&) const
{

  // input
  TopoDS_Shape myFShape = myPlane1;
  TopoDS_Shape mySShape = myPlane2;
  double       myVal    = GetValue();
  gp_Ax1       myAxis;

  // output
  gp_Pnt myFAttach;
  gp_Pnt mySAttach;
  gp_Pnt myPosition(0., 0., 0.);
  gp_Pnt myCenter;
  gp_Dir myFDir;
  gp_Dir mySDir;
  bool   myAutomaticPosition = true;

  // calculation of myAxis
  gp_Pln pln1, pln2;
  if (!DrawDim::Pln(myPlane1, pln1))
    return;
  if (!DrawDim::Pln(myPlane2, pln2))
    return;
  IntAna_QuadQuadGeo ip(pln1, pln2, Precision::Confusion(), Precision::Angular());
  if (!ip.IsDone())
    return;

  gp_Pnt curpos;
  gp_Ax1 AxePos     = myAxis;
  gp_Dir theAxisDir = AxePos.Direction();
  gp_Lin theaxis    = gp_Lin(myAxis);

  if (myAutomaticPosition)
  {
    TopExp_Explorer explo1(myFShape, TopAbs_VERTEX);
    double          curdist = 0;
    while (explo1.More())
    {
      TopoDS_Vertex vertref = TopoDS::Vertex(explo1.Current());
      gp_Pnt        curpt   = BRep_Tool::Pnt(vertref);
      if (theaxis.Distance(curpt) > curdist)
      {
        curdist   = theaxis.Distance(curpt);
        myFAttach = BRep_Tool::Pnt(vertref);
      }
      explo1.Next();
    }
    curpos          = myFAttach.Rotated(AxePos, myVal / 2.);
    myCenter        = ElCLib::Value(ElCLib::Parameter(theaxis, curpos), theaxis);
    double thedista = myCenter.Distance(myFAttach);
    if (thedista > Precision::Confusion())
    {
      curpos.Scale(myCenter, 1.05);
    }
    myPosition          = curpos;
    myAutomaticPosition = true;
  }
  else
  {
    curpos = myPosition;
    // myFAttach  = the point of myFShape closest to curpos (except for the case when this is a
    // point on the axis)
    double          dist = RealLast();
    TopExp_Explorer explo1(myFShape, TopAbs_VERTEX);
    gp_Pnt          AxePosition = AxePos.Location();
    gp_Vec          AxeVector(theAxisDir);
    gp_XYZ          AxeXYZ = AxeVector.XYZ();
    while (explo1.More())
    {
      gp_Pnt curpt = BRep_Tool::Pnt(TopoDS::Vertex(explo1.Current()));
      gp_Vec curvec(AxePosition, curpt);
      gp_XYZ curXYZ = curvec.XYZ();
      gp_XYZ Norm(curXYZ.Crossed(AxeXYZ));

      if (Norm.Modulus() > gp::Resolution())
      {
        double curdist = curpos.Distance(curpt);
        if (curdist < dist)
        {
          myFAttach = curpt;
          dist      = curdist;
        }
      }
      explo1.Next();
    }
    myCenter = ElCLib::Value(ElCLib::Parameter(theaxis, myFAttach), theaxis);
  }

  mySAttach = myFAttach.Rotated(AxePos, myVal);

  gp_Vec FVec(myCenter, myFAttach);
  myFDir.SetXYZ(FVec.XYZ());
  gp_Vec SVec(myCenter, mySAttach);
  mySDir.SetXYZ(SVec.XYZ());

  if (!myAutomaticPosition)
  {
    // Projection of the position on the plane defined by myFDir mySDir and normal theAxisDir
    gp_Pln aPln(myCenter, theAxisDir);
    double U, V;
    ElSLib::Parameters(aPln, curpos, U, V);
    curpos = ElSLib::Value(U, V, aPln);
  }

  // DISPLAY
  // Add (myVal, myText,myCenter,myFAttach,mySAttach,myFDir,mySDir,theAxisDir,curpos)
}
