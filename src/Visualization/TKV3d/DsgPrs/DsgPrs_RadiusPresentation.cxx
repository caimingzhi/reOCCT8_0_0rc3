#include <DsgPrs_RadiusPresentation.hpp>

#include <DsgPrs.hpp>
#include <ElCLib.hpp>
#include <gce_MakeDir.hpp>
#include <gp_Circ.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <Graphic3d_Group.hpp>
#include <Prs3d_Arrow.hpp>
#include <Prs3d_DimensionAspect.hpp>
#include <Prs3d_LineAspect.hpp>
#include <Prs3d_Presentation.hpp>
#include <Prs3d_Text.hpp>
#include <TCollection_ExtendedString.hpp>

static bool DsgPrs_InDomain(const double fpar, const double lpar, const double para)
{
  if (fpar >= 0.)
    return ((para >= fpar) && (para <= lpar));
  if (para >= (fpar + 2. * M_PI))
    return true;
  if (para <= lpar)
    return true;
  return false;
}

void DsgPrs_RadiusPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                    const occ::handle<Prs3d_Drawer>&       aDrawer,
                                    const TCollection_ExtendedString&      aText,
                                    const gp_Pnt&                          AttachmentPoint,
                                    const gp_Circ&                         aCircle,
                                    const double                           firstparam,
                                    const double                           lastparam,
                                    const bool                             drawFromCenter,
                                    const bool                             reverseArrow)
{
  double fpara = firstparam;
  double lpara = lastparam;
  while (lpara > 2. * M_PI)
  {
    fpara -= 2. * M_PI;
    lpara -= 2. * M_PI;
  }
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  double parat     = ElCLib::Parameter(aCircle, AttachmentPoint);
  gp_Pnt attpoint  = AttachmentPoint;
  bool   otherside = false;
  if (!DsgPrs_InDomain(fpara, lpara, parat))
  {
    double otherpar = parat + M_PI;
    if (otherpar > 2. * M_PI)
      otherpar -= 2. * M_PI;
    if (DsgPrs_InDomain(fpara, lpara, otherpar))
    {
      parat     = otherpar;
      otherside = true;
    }
    else
    {
      const double ecartpar = std::min(std::abs(fpara - parat), std::abs(lpara - parat));
      const double ecartoth = std::min(std::abs(fpara - otherpar), std::abs(lpara - otherpar));
      if (ecartpar <= ecartoth)
      {
        parat = (parat < fpara) ? fpara : lpara;
      }
      else
      {
        otherside = true;
        parat     = (otherpar < fpara) ? fpara : lpara;
      }
      gp_Pnt       ptdir = ElCLib::Value(parat, aCircle);
      gp_Lin       lsup(aCircle.Location(), gp_Dir(ptdir.XYZ() - aCircle.Location().XYZ()));
      const double parpos = ElCLib::Parameter(lsup, AttachmentPoint);
      attpoint            = ElCLib::Value(parpos, lsup);
    }
  }
  gp_Pnt ptoncirc = ElCLib::Value(parat, aCircle);
  gp_Lin L(aCircle.Location(), gp_Dir(attpoint.XYZ() - aCircle.Location().XYZ()));
  gp_Pnt firstpoint  = attpoint;
  gp_Pnt drawtopoint = ptoncirc;
  if (drawFromCenter && !otherside)
  {
    const double uatt = ElCLib::Parameter(L, attpoint);
    const double uptc = ElCLib::Parameter(L, ptoncirc);
    if (std::abs(uatt) > std::abs(uptc))
      drawtopoint = aCircle.Location();
    else
      firstpoint = aCircle.Location();
  }

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(firstpoint);
  aPrims->AddVertex(drawtopoint);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  gp_Dir arrdir = L.Direction();
  if (reverseArrow)
    arrdir.Reverse();

  Prs3d_Arrow::Draw(aPresentation->CurrentGroup(),
                    ptoncirc,
                    arrdir,
                    LA->ArrowAspect()->Angle(),
                    LA->ArrowAspect()->Length());

  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, attpoint);
}

void DsgPrs_RadiusPresentation::Add(const occ::handle<Prs3d_Presentation>& aPresentation,
                                    const occ::handle<Prs3d_Drawer>&       aDrawer,
                                    const TCollection_ExtendedString&      aText,
                                    const gp_Pnt&                          AttachmentPoint,
                                    const gp_Pnt&                          Center,
                                    const gp_Pnt&                          EndOfArrow,
                                    const DsgPrs_ArrowSide                 ArrowPrs,
                                    const bool                             drawFromCenter,
                                    const bool                             reverseArrow)
{
  occ::handle<Prs3d_DimensionAspect> LA = aDrawer->DimensionAspect();
  aPresentation->CurrentGroup()->SetPrimitivesAspect(LA->LineAspect()->Aspect());

  gp_Pnt LineOrigin, LineEnd;
  DsgPrs::ComputeRadiusLine(Center,
                            EndOfArrow,
                            AttachmentPoint,
                            drawFromCenter,
                            LineOrigin,
                            LineEnd);

  occ::handle<Graphic3d_ArrayOfSegments> aPrims = new Graphic3d_ArrayOfSegments(2);
  aPrims->AddVertex(LineOrigin);
  aPrims->AddVertex(LineEnd);
  aPresentation->CurrentGroup()->AddPrimitiveArray(aPrims);

  Prs3d_Text::Draw(aPresentation->CurrentGroup(), LA->TextAspect(), aText, AttachmentPoint);

  gp_Dir ArrowDir = gce_MakeDir(LineOrigin, LineEnd);
  if (reverseArrow)
    ArrowDir.Reverse();
  DsgPrs::ComputeSymbol(aPresentation,
                        LA,
                        Center,
                        EndOfArrow,
                        ArrowDir.Reversed(),
                        ArrowDir,
                        ArrowPrs,
                        drawFromCenter);
}
