#include <PrsDim_OffsetDimension.hpp>

#include <PrsDim.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepBuilderAPI_Transform.hpp>
#include <DsgPrs_OffsetPresentation.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <gce_MakeLin.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <gp_Ax1.hpp>
#include <gp_Ax2.hpp>
#include <gp_Ax3.hpp>
#include <gp_Lin.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Trsf.hpp>
#include <gp_Vec.hpp>
#include <Graphic3d_Structure.hpp>
#include <Precision.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Select3D_SensitiveBox.hpp>
#include <Select3D_SensitiveSegment.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Selection.hpp>
#include <StdPrs_WFShape.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_OffsetDimension, PrsDim_Relation)

//=================================================================================================

PrsDim_OffsetDimension::PrsDim_OffsetDimension(const TopoDS_Shape&               FistShape,
                                               const TopoDS_Shape&               SecondShape,
                                               const double                      aVal,
                                               const TCollection_ExtendedString& aText)
    : myFAttach(0., 0., 0.),
      mySAttach(0., 0., 0.)
{
  myFShape    = FistShape;
  mySShape    = SecondShape;
  mySymbolPrs = DsgPrs_AS_BOTHAR;
  myVal       = aVal;
  myText      = aText;
  // myArrowSize = fabs (myVal/5.);
  myArrowSize = fabs(myVal / 10.0);
  if (myArrowSize > 30.)
    myArrowSize = 30.;
  if (myArrowSize < 15.)
    myArrowSize = 15.;
  // std::cout<<"PrsDim_OffsetDimension::PrsDim_OffsetDimension " <<  myArrowSize << "
  // myArrowSize"<<std::endl;
}

//=================================================================================================

void PrsDim_OffsetDimension::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                     const occ::handle<Prs3d_Presentation>& aprs,
                                     const int)
{
  gp_Trsf aInvertTrsf = myRelativePos;
  // myArrowSize = fabs (myVal/5.);
  myArrowSize = fabs(myVal / 10.0);
  if (myArrowSize > 30.)
    myArrowSize = 30.;
  if (myArrowSize < 15.)
    myArrowSize = 15.;
  // std::cout<<"PrsDim_OffsetDimension::PrsDim_OffsetDimension " <<  myArrowSize << "
  // myArrowSize"<<std::endl;

  BRepAdaptor_Surface surf1(TopoDS::Face(myFShape));
  BRepAdaptor_Surface surf2(TopoDS::Face(mySShape));

  if (surf1.GetType() == GeomAbs_Cylinder || surf1.GetType() == GeomAbs_Cone
      || surf1.GetType() == GeomAbs_Torus)
  {
    if (surf2.GetType() == GeomAbs_Cylinder || surf2.GetType() == GeomAbs_Cone
        || surf2.GetType() == GeomAbs_Torus)
    {
      ComputeTwoAxesOffset(aprs, aInvertTrsf);
    }
    else
    {
      ComputeAxeFaceOffset(aprs, aInvertTrsf);
    }
  }
  else
  {
    // myDirAttach : oriente de myFShape vers mySShape
    gp_Pln aPln = surf1.Plane();
    gp_Pnt aPnt = aPln.Location();

    gp_Pln bPln = surf2.Plane();

    double uPnt, vPnt;
    ElSLib::Parameters(bPln, aPnt, uPnt, vPnt);
    gp_Pnt bPnt = ElSLib::Value(uPnt, vPnt, bPln);
    if (aPnt.IsEqual(bPnt, Precision::Confusion()))
    {
      gp_Ax1 aAx1 = aPln.Axis();
      myDirAttach = aAx1.Direction();
    }
    else
    {
      gp_Vec aVec(aPnt, bPnt);
      myDirAttach.SetCoord(aVec.X(), aVec.Y(), aVec.Z());
    }
    ComputeTwoFacesOffset(aprs, aInvertTrsf);
  }
}

//=================================================================================================

void PrsDim_OffsetDimension::ComputeSelection(const occ::handle<SelectMgr_Selection>& aSel,
                                              const int)
{
  // myArrowSize = fabs (myVal/5.);
  myArrowSize = fabs(myVal / 10.0);
  if (myArrowSize > 30.)
    myArrowSize = 30.;
  if (myArrowSize < 15.)
    myArrowSize = 15.;
  // std::cout<<"PrsDim_OffsetDimension::PrsDim_OffsetDimension " <<  myArrowSize << "
  // myArrowSize"<<std::endl;
  gp_Pnt myTFAttach    = myFAttach.Transformed(myRelativePos);
  gp_Pnt myTSAttach    = mySAttach.Transformed(myRelativePos);
  gp_Dir myTDirAttach  = myDirAttach.Transformed(myRelativePos);
  gp_Dir myTDirAttach2 = myDirAttach2.Transformed(myRelativePos);
  gp_Pnt Tcurpos       = myPosition.Transformed(myRelativePos);

  gp_Lin L1(myTFAttach, myTDirAttach);
  gp_Lin L2(myTSAttach, myTDirAttach2);
  gp_Pnt Proj1 = ElCLib::Value(ElCLib::Parameter(L1, Tcurpos), L1);
  gp_Pnt Proj2 = ElCLib::Value(ElCLib::Parameter(L2, Tcurpos), L2);
  gp_Lin L3;

  occ::handle<SelectMgr_EntityOwner> own = new SelectMgr_EntityOwner(this, 7);

  if (!Proj1.IsEqual(Proj2, Precision::Confusion()))
  {
    L3 = gce_MakeLin(Proj1, Proj2);
  }
  else
  { // case where the dimension is zero
    if (!Proj1.IsEqual(Tcurpos, Precision::Confusion()))
    {
      gp_Vec v3(Proj1, Tcurpos);
      gp_Dir d3(v3);
      L3 = gce_MakeLin(Proj1, d3);
    }
    else
    {
      L3 = gce_MakeLin(Proj1, myTDirAttach);
    }

    // Text
    double                             size(std::min(myVal / 100. + 1.e-6, myArrowSize + 1.e-6));
    occ::handle<Select3D_SensitiveBox> box = new Select3D_SensitiveBox(own,
                                                                       Tcurpos.X(),
                                                                       Tcurpos.Y(),
                                                                       Tcurpos.Z(),
                                                                       Tcurpos.X() + size,
                                                                       Tcurpos.Y() + size,
                                                                       Tcurpos.Z() + size);
    aSel->Add(box);
  }

  double parmin, parmax, parcur;
  parmin = ElCLib::Parameter(L3, Proj1);
  parmax = parmin;

  parcur = ElCLib::Parameter(L3, Proj2);
  parmin = std::min(parmin, parcur);
  parmax = std::max(parmax, parcur);

  parcur = ElCLib::Parameter(L3, Tcurpos);
  parmin = std::min(parmin, parcur);
  parmax = std::max(parmax, parcur);

  gp_Pnt PointMin = ElCLib::Value(parmin, L3);
  gp_Pnt PointMax = ElCLib::Value(parmax, L3);

  occ::handle<Select3D_SensitiveSegment> seg;
  if (!PointMin.IsEqual(PointMax, Precision::Confusion()))
  {
    seg = new Select3D_SensitiveSegment(own, PointMin, PointMax);
    aSel->Add(seg);
  }

  if (!myTFAttach.IsEqual(Proj1, Precision::Confusion()))
  {
    seg = new Select3D_SensitiveSegment(own, myTFAttach, Proj1);
    aSel->Add(seg);
  }
  if (!myTSAttach.IsEqual(Proj2, Precision::Confusion()))
  {
    seg = new Select3D_SensitiveSegment(own, myTSAttach, Proj2);
    aSel->Add(seg);
  }
}

//=================================================================================================

void PrsDim_OffsetDimension::ComputeTwoAxesOffset(const occ::handle<Prs3d_Presentation>& aprs,
                                                  const gp_Trsf&                         aTrsf)
{
  BRepAdaptor_Surface surf1(TopoDS::Face(myFShape));
  BRepAdaptor_Surface surf2(TopoDS::Face(mySShape));

  gp_Ax1 Ax1Surf1, Ax1Surf2;

  if (surf1.GetType() == GeomAbs_Cylinder)
  {
    gp_Cylinder aCyl = surf1.Cylinder();
    Ax1Surf1         = aCyl.Axis();
  }
  else if (surf1.GetType() == GeomAbs_Cone)
  {
    gp_Cone aCone = surf1.Cone();
    Ax1Surf1      = aCone.Axis();
  }
  else if (surf1.GetType() == GeomAbs_Torus)
  {
    gp_Torus aTore = surf1.Torus();
    Ax1Surf1       = aTore.Axis();
  }
  double FirstUParam = surf1.FirstUParameter();
  double FirstVParam = surf1.FirstVParameter();
  double LastVParam  = surf1.LastVParameter();
  gp_Pnt P1First     = surf1.Value(FirstUParam, FirstVParam);
  gp_Pnt P1Last      = surf1.Value(FirstUParam, LastVParam);

  if (surf2.GetType() == GeomAbs_Cylinder)
  {
    gp_Cylinder aCyl = surf2.Cylinder();
    Ax1Surf2         = aCyl.Axis();
  }
  else if (surf2.GetType() == GeomAbs_Cone)
  {
    gp_Cone aCone = surf2.Cone();
    Ax1Surf2      = aCone.Axis();
  }
  else if (surf2.GetType() == GeomAbs_Torus)
  {
    gp_Torus aTore = surf2.Torus();
    Ax1Surf2       = aTore.Axis();
  }
  FirstUParam    = surf2.FirstUParameter();
  FirstVParam    = surf2.FirstVParameter();
  LastVParam     = surf2.LastVParameter();
  gp_Pnt P2First = surf2.Value(FirstUParam, FirstVParam);
  gp_Pnt P2Last  = surf2.Value(FirstUParam, LastVParam);

  myFAttach    = Ax1Surf1.Location();
  mySAttach    = Ax1Surf2.Location();
  myDirAttach  = Ax1Surf1.Direction();
  myDirAttach2 = myDirAttach;
  gp_Pnt curpos;
  gp_Lin aProjLine = gce_MakeLin(myFAttach, myDirAttach);

  if (myAutomaticPosition)
  {
    curpos.SetX((myFAttach.X() + mySAttach.X()) / 2. + 0.01);
    curpos.SetY((myFAttach.Y() + mySAttach.Y()) / 2. + 0.01);
    curpos.SetZ((myFAttach.Z() + mySAttach.Z()) / 2. + 0.01);
    // + 0.01 pour eviter un raise de ComputeSelection...

    myPosition = curpos;
  }
  else
  {
    curpos = myPosition;
  }

  curpos = ElCLib::Value(ElCLib::Parameter(aProjLine, curpos), aProjLine);
  // on projette pour la presentation

  gp_Pnt P1FirstProj = ElCLib::Value(ElCLib::Parameter(aProjLine, P1First), aProjLine);
  gp_Pnt P1LastProj  = ElCLib::Value(ElCLib::Parameter(aProjLine, P1Last), aProjLine);
  if (P1FirstProj.Distance(curpos) > P1LastProj.Distance(curpos))
    myFAttach = P1FirstProj;
  else
    myFAttach = P1LastProj;

  gp_Pnt P2FirstProj = ElCLib::Value(ElCLib::Parameter(aProjLine, P2First), aProjLine);
  gp_Pnt P2LastProj  = ElCLib::Value(ElCLib::Parameter(aProjLine, P2Last), aProjLine);
  if (P2FirstProj.Distance(curpos) > P2LastProj.Distance(curpos))
    mySAttach = P2FirstProj;
  else
    mySAttach = P2LastProj;

  occ::handle<Prs3d_DimensionAspect> la  = myDrawer->DimensionAspect();
  occ::handle<Prs3d_ArrowAspect>     arr = la->ArrowAspect();
  // std::cout<<"PrsDim_OffsetDimension::PrsDim_OffsetDimension " <<  myArrowSize << "
  // myArrowSize"<<std::endl;
  arr->SetLength(myArrowSize);
  arr = la->ArrowAspect();
  arr->SetLength(myArrowSize);

  gp_Pnt myTFAttach    = myFAttach.Transformed(aTrsf);
  gp_Pnt myTSAttach    = mySAttach.Transformed(aTrsf);
  gp_Dir myTDirAttach  = myDirAttach.Transformed(aTrsf);
  gp_Dir myTDirAttach2 = myTDirAttach;
  gp_Pnt Tcurpos       = curpos.Transformed(aTrsf);

  if (myIsSetBndBox)
    Tcurpos = PrsDim::TranslatePointToBound(Tcurpos, myDirAttach, myBndBox);

  DsgPrs_OffsetPresentation::AddAxes(aprs,
                                     myDrawer,
                                     myText,
                                     myTFAttach,
                                     myTSAttach,
                                     myTDirAttach,
                                     myTDirAttach2,
                                     Tcurpos);

  BRepBuilderAPI_Transform transform1(myFShape, aTrsf, true);
  TopoDS_Shape             myTFShape = transform1.Shape();
  BRepBuilderAPI_Transform transform2(mySShape, aTrsf, true);
  TopoDS_Shape             myTSShape = transform2.Shape();

  StdPrs_WFShape::Add(aprs, myTFShape, myDrawer);
  StdPrs_WFShape::Add(aprs, myTSShape, myDrawer);
}

//=================================================================================================

void PrsDim_OffsetDimension::ComputeTwoFacesOffset(const occ::handle<Prs3d_Presentation>& aprs,
                                                   const gp_Trsf&                         aTrsf)
{
  gp_Dir norm1 = myDirAttach;
  gp_Pnt curpos;
  gp_Ax2 myax2;
  if (myAutomaticPosition && !myIsSetBndBox)
  {
    TopExp_Explorer explo(myFShape, TopAbs_VERTEX);
    if (explo.More())
    {
      TopoDS_Vertex vertref = TopoDS::Vertex(explo.Current());
      myFAttach             = BRep_Tool::Pnt(vertref);
      gp_Vec trans          = norm1.XYZ() * fabs(myVal / 2);
      gp_Ax2 ax2(myFAttach, norm1);
      myDirAttach = ax2.XDirection();
      curpos      = myFAttach.Translated(trans);
      if (myVal <= Precision::Confusion())
      {
        gp_Vec vecnorm1 = norm1.XYZ() * .001;
        curpos.Translate(vecnorm1);
      }
      myPosition = curpos;
      myax2      = ax2;
    }
  }
  else
  {
    if (myAutomaticPosition && myIsSetBndBox)
    {
      double aXmin, aYmin, aZmin, aXmax, aYmax, aZmax;
      myBndBox.Get(aXmin, aYmin, aZmin, aXmax, aYmax, aZmax);
      myPosition.SetCoord(aXmax, aYmax, aZmax);
    }

    curpos    = myPosition;
    myFAttach = PrsDim::Nearest(myFShape, curpos);
    if (myFAttach.Distance(curpos) <= Precision::Confusion())
    {
      gp_Ax2 ax2(myFAttach, norm1);
      myDirAttach = ax2.XDirection();
      myax2       = ax2;
    }
    else
    {
      gp_Dir orient(myFAttach.XYZ() - curpos.XYZ());
      gp_Ax2 ax2(myFAttach, norm1);
      if (orient.Angle(norm1) <= Precision::Angular())
      {
        myDirAttach = ax2.XDirection();
      }
      else
      {
        gp_Dir adir = norm1 ^ orient;
        myDirAttach = adir ^ norm1;
      }
      myax2 = ax2;
    }
  }
  // en attendant mieux
  mySAttach = PrsDim::Nearest(mySShape, curpos);
  gp_Ax3 anax3(myax2);
  gp_Pln apln(anax3);

  // gp_Pnt proj2;
  double u2, v2, uatt, vatt;
  ElSLib::Parameters(apln, mySAttach, uatt, vatt);
  ElSLib::Parameters(apln, curpos, u2, v2);

  if (uatt == u2 && vatt == v2)
  {
    myDirAttach2 = myDirAttach;
  }
  else
  {
    gp_Vec avec(ElSLib::Value(uatt, vatt, apln), ElSLib::Value(u2, v2, apln));
    myDirAttach2.SetCoord(avec.X(), avec.Y(), avec.Z());
  }

  occ::handle<Prs3d_DimensionAspect> la  = myDrawer->DimensionAspect();
  occ::handle<Prs3d_ArrowAspect>     arr = la->ArrowAspect();
  // std::cout<<"PrsDim_OffsetDimension::PrsDim_OffsetDimension " <<  myArrowSize << "
  // myArrowSize"<<std::endl;
  arr->SetLength(myArrowSize);
  arr = la->ArrowAspect();
  arr->SetLength(myArrowSize);

  gp_Pnt myTFAttach    = myFAttach.Transformed(aTrsf);
  gp_Pnt myTSAttach    = mySAttach.Transformed(aTrsf);
  gp_Dir myTDirAttach  = myDirAttach.Transformed(aTrsf);
  gp_Dir myTDirAttach2 = myDirAttach2.Transformed(aTrsf);
  gp_Pnt Tcurpos       = curpos.Transformed(aTrsf);

  /*
    if (myIsSetBndBox)
      {
        BRepAdaptor_Surface surf1(TopoDS::Face(myFShape));
        Tcurpos = PrsDim::TranslatePointToBound( Tcurpos, surf1.Plane().XAxis().Direction(),
    myBndBox );
      }
  */
  DsgPrs_OffsetPresentation::Add(aprs,
                                 myDrawer,
                                 myText,
                                 myTFAttach,
                                 myTSAttach,
                                 myTDirAttach,
                                 myTDirAttach2,
                                 Tcurpos);

  BRepBuilderAPI_Transform transform1(myFShape, aTrsf, true);
  TopoDS_Shape             myTFShape = transform1.Shape();
  BRepBuilderAPI_Transform transform2(mySShape, aTrsf, true);
  TopoDS_Shape             myTSShape = transform2.Shape();

  StdPrs_WFShape::Add(aprs, myTFShape, myDrawer);
  StdPrs_WFShape::Add(aprs, myTSShape, myDrawer);
}

//=================================================================================================

void PrsDim_OffsetDimension::ComputeAxeFaceOffset(const occ::handle<Prs3d_Presentation>& aprs,
                                                  const gp_Trsf&                         aTrsf)
{
  BRepBuilderAPI_Transform transform1(myFShape, aTrsf, true);
  TopoDS_Shape             myTFShape = transform1.Shape();
  BRepBuilderAPI_Transform transform2(mySShape, aTrsf, true);
  TopoDS_Shape             myTSShape = transform2.Shape();

  StdPrs_WFShape::Add(aprs, myTFShape, myDrawer);
  StdPrs_WFShape::Add(aprs, myTSShape, myDrawer);
}
