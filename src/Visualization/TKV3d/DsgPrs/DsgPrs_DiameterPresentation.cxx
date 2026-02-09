#include <DsgPrs_DiameterPresentation.hpp>

#include <DsgPrs.hpp>
#include <ElCLib.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_Arrow.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Text.hpp>
#include <TCollection_ExtendedString.hpp>

void DsgPrs_DiameterPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                      const occ::handle<Prs3d_Drawer>&       aDrawer,
                                      const TCollection_ExtendedString&      aText,
                                      const gp_Pnt&                          AttachmentPoint,
                                      const gp_Circ&                         aCircle,
                                      const DsgPrs_ArrowSide                 ArrowPrs,
                                      const bool                             IsDiamSymbol)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  double parat    = ElCLib::Parameter(aCircle, AttachmentPoint);
  gp_Pnt ptoncirc = ElCLib::Value(parat, aCircle);

  gp_Pnt center = aCircle.Location();
  gp_Vec vecrap(ptoncirc, center);

  double dist    = center.Distance(AttachmentPoint);
  double aRadius = aCircle.Radius();
  bool   inside  = (dist < aRadius);

  gp_Pnt pt1 = AttachmentPoint;
  if (inside)
  {
    pt1  = ptoncirc;
    dist = aRadius;
  }
  vecrap.Normalize();
  vecrap *= (dist + aRadius);
  gp_Pnt OppositePoint = pt1.Translated(vecrap);

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(pt1);
  aPrims->AddVertex(OppositePoint);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  TCollection_ExtendedString Text = aText;
  if (IsDiamSymbol)
    Text = TCollection_ExtendedString("\330  ") + aText;
  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), Text, AttachmentPoint);

  gp_Dir arrdir(vecrap);
  if (inside)
    arrdir.Reverse();

  gp_Vec vecrap2   = vecrap;
  gp_Pnt ptoncirc2 = ptoncirc;
  gp_Dir arrdir2   = arrdir;
  vecrap2.Normalize();
  vecrap2 *= (aCircle.Radius() * 2.);
  ptoncirc2.Translate(vecrap2);
  arrdir2.Reverse();

  DsgPrs::ComputeSymbol(aPresentation, LA, ptoncirc, ptoncirc2, arrdir, arrdir2, ArrowPrs);
}

static bool DsgPrs_InDomain(const double fpar, const double lpar, const double para)
{
  if (fpar >= 0.)
  {
    if (lpar > fpar)
      return ((para >= fpar) && (para <= lpar));
    else
    {
      double delta = 2. * M_PI - fpar;
      double lp, par, fp;
      lp  = lpar + delta;
      par = para + delta;
      while (lp > 2 * M_PI)
        lp -= 2 * M_PI;
      while (par > 2 * M_PI)
        par -= 2 * M_PI;
      fp = 0.;
      return ((par >= fp) && (par <= lp));
    }
  }
  if (para >= (fpar + 2 * M_PI))
    return true;
  if (para <= lpar)
    return true;
  return false;
}

void DsgPrs_DiameterPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                      const occ::handle<Prs3d_Drawer>&       aDrawer,
                                      const TCollection_ExtendedString&      aText,
                                      const gp_Pnt&                          AttachmentPoint,
                                      const gp_Circ&                         aCircle,
                                      const double                           uFirst,
                                      const double                           uLast,
                                      const DsgPrs_ArrowSide                 ArrowPrs,
                                      const bool                             IsDiamSymbol)
{
  double fpara = uFirst;
  double lpara = uLast;
  while (lpara > 2. * M_PI)
  {
    fpara -= 2. * M_PI;
    lpara -= 2. * M_PI;
  }

  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());
  double parEndOfArrow = ElCLib::Parameter(aCircle, AttachmentPoint);
  gp_Pnt EndOfArrow;
  gp_Pnt DrawPosition = AttachmentPoint;

  gp_Pnt Center      = aCircle.Location();
  gp_Pnt FirstPoint  = ElCLib::Value(uFirst, aCircle);
  gp_Pnt SecondPoint = ElCLib::Value(uLast, aCircle);

  if (!DsgPrs_InDomain(fpara, lpara, parEndOfArrow))
  {
    double otherpar = parEndOfArrow + M_PI;
    if (otherpar > 2 * M_PI)
      otherpar -= 2 * M_PI;
    if (DsgPrs_InDomain(fpara, lpara, otherpar))
    {
      parEndOfArrow = otherpar;
      EndOfArrow    = ElCLib::Value(parEndOfArrow, aCircle);
    }
    else
    {
      gp_Dir dir1(gp_Vec(Center, FirstPoint));
      gp_Dir dir2(gp_Vec(Center, SecondPoint));
      gp_Lin L1(Center, dir1);
      gp_Lin L2(Center, dir2);
      if (L1.Distance(AttachmentPoint) < L2.Distance(AttachmentPoint))
      {
        EndOfArrow   = FirstPoint;
        DrawPosition = ElCLib::Value(ElCLib::Parameter(L1, AttachmentPoint), L1);
      }
      else
      {
        EndOfArrow   = SecondPoint;
        DrawPosition = ElCLib::Value(ElCLib::Parameter(L2, AttachmentPoint), L2);
      }
    }
  }
  else
  {
    EndOfArrow   = ElCLib::Value(parEndOfArrow, aCircle);
    DrawPosition = AttachmentPoint;
  }

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(DrawPosition);
  aPrims->AddVertex(EndOfArrow);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  TCollection_ExtendedString Text = aText;
  if (IsDiamSymbol)
    Text = TCollection_ExtendedString("\330 ") + Text;
  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), Text, DrawPosition);

  gp_Dir DirOfArrow(gp_Vec(DrawPosition, EndOfArrow).XYZ());
  DsgPrs::ComputeSymbol(aPresentation,
                        LA,
                        EndOfArrow,
                        EndOfArrow,
                        DirOfArrow,
                        DirOfArrow,
                        ArrowPrs);
}
