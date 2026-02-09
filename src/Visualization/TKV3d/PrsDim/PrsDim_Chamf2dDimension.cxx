#include <PrsDim_Chamf2dDimension.hpp>

#include <PrsDim.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <DsgPrs_Chamf2dPresentation.hpp>
#include <ElCLib.hpp>
#include <Geom_Line.hpp>
#include <Geom_Plane.hpp>
#include <gp_Dir.hpp>
#include <gp_Pln.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <ProjLib.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_Drawer.hpp>
#include <Prs3d_Presentation.hpp>
#include <Select3D_SensitiveBox.hpp>
#include <Select3D_SensitiveSegment.hpp>
#include <SelectMgr_EntityOwner.hpp>
#include <SelectMgr_Selection.hpp>
#include <Standard_Type.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PrsDim_Chamf2dDimension, PrsDim_Relation)

PrsDim_Chamf2dDimension::PrsDim_Chamf2dDimension(const TopoDS_Shape&               aFShape,
                                                 const occ::handle<Geom_Plane>&    aPlane,
                                                 const double                      aVal,
                                                 const TCollection_ExtendedString& aText)

{
  myFShape            = aFShape;
  myPlane             = aPlane;
  myVal               = aVal;
  myText              = aText;
  mySymbolPrs         = DsgPrs_AS_LASTAR;
  myAutomaticPosition = true;

  myArrowSize = myVal / 100.;
}

PrsDim_Chamf2dDimension::PrsDim_Chamf2dDimension(const TopoDS_Shape&               aFShape,
                                                 const occ::handle<Geom_Plane>&    aPlane,
                                                 const double                      aVal,
                                                 const TCollection_ExtendedString& aText,
                                                 const gp_Pnt&                     aPosition,
                                                 const DsgPrs_ArrowSide            aSymbolPrs,
                                                 const double                      anArrowSize)

{
  myFShape    = aFShape;
  myPlane     = aPlane;
  myVal       = aVal;
  myText      = aText;
  myPosition  = aPosition;
  mySymbolPrs = aSymbolPrs;
  SetArrowSize(anArrowSize);
  myAutomaticPosition = false;
}

void PrsDim_Chamf2dDimension::Compute(const occ::handle<PrsMgr_PresentationManager>&,
                                      const occ::handle<Prs3d_Presentation>& aPresentation,
                                      const int)
{
  occ::handle<Geom_Curve> gcurv;
  gp_Pnt                  pfirst, plast;
  const TopoDS_Edge&      thechamfedge = TopoDS::Edge(myFShape);
  if (!PrsDim::ComputeGeometry(thechamfedge, gcurv, pfirst, plast))
    return;

  occ::handle<Geom_Line> glin = occ::down_cast<Geom_Line>(gcurv);
  gp_Dir                 dir1(glin->Position().Direction());
  gp_Dir                 norm1 = myPlane->Pln().Axis().Direction();
  myDir                        = norm1.Crossed(dir1);

  gp_Pnt curpos;
  if (myAutomaticPosition)
  {
    myPntAttach.SetXYZ((pfirst.XYZ() + plast.XYZ()) / 2);
    gp_Vec transVec(myDir);
    transVec *= myVal;
    curpos = myPntAttach.Translated(transVec);

    if (myIsSetBndBox)
      curpos = PrsDim::TranslatePointToBound(curpos, myDir, myBndBox);

    myPosition = curpos;
  }
  else
  {

    myPntAttach.SetXYZ((pfirst.XYZ() + plast.XYZ()) / 2);
    occ::handle<Geom_Line> dimLin    = new Geom_Line(myPntAttach, myDir);
    double                 parcurpos = ElCLib::Parameter(dimLin->Lin(), myPosition);
    curpos                           = ElCLib::Value(parcurpos, dimLin->Lin());

    if (curpos.Distance(myPntAttach) < 5.)
    {
      gp_Vec transVec(myDir);
      transVec *= 5.;
      curpos = myPntAttach.Translated(transVec);
    }
    myPosition = curpos;
  }

  occ::handle<Prs3d_DimensionAspect> la  = myDrawer->DimensionAspect();
  occ::handle<Prs3d_ArrowAspect>     arr = la->ArrowAspect();

  if (!myArrowSizeIsDefined)
  {
    double arrsize = myArrowSize;
    if ((myVal / 4) < arrsize)
      arrsize = myVal / 4;
    if (arrsize > 30.)
      arrsize = 30.;
    else if (arrsize < 8.)
      arrsize = 8.;
    myArrowSize = arrsize;
  }
  arr->SetLength(myArrowSize);

  DsgPrs_Chamf2dPresentation::Add(aPresentation,
                                  myDrawer,
                                  myPntAttach,
                                  curpos,
                                  myText,
                                  mySymbolPrs);
}

void PrsDim_Chamf2dDimension::ComputeSelection(const occ::handle<SelectMgr_Selection>& aSelection,
                                               const int)
{
  occ::handle<SelectMgr_EntityOwner>     own = new SelectMgr_EntityOwner(this, 7);
  occ::handle<Select3D_SensitiveSegment> seg =
    new Select3D_SensitiveSegment(own, myPntAttach, myPosition);
  aSelection->Add(seg);

  double                             size(std::min(myVal / 100. + 1.e-6, myArrowSize + 1.e-6));
  occ::handle<Select3D_SensitiveBox> box = new Select3D_SensitiveBox(own,
                                                                     myPosition.X(),
                                                                     myPosition.Y(),
                                                                     myPosition.Z(),
                                                                     myPosition.X() + size,
                                                                     myPosition.Y() + size,
                                                                     myPosition.Z() + size);
  aSelection->Add(box);
}
