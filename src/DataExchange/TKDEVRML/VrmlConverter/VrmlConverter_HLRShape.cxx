

#include <Bnd_Box.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepBndLib.hpp>
#include <Precision.hpp>
#include <StdPrs_HLRToolShape.hpp>
#include <TopoDS_Shape.hpp>
#include <Vrml_Material.hpp>
#include <Vrml_Separator.hpp>
#include <VrmlConverter_DeflectionCurve.hpp>
#include <VrmlConverter_Drawer.hpp>
#include <VrmlConverter_HLRShape.hpp>
#include <VrmlConverter_LineAspect.hpp>
#include <VrmlConverter_Projector.hpp>

void VrmlConverter_HLRShape::Add(Standard_OStream&                           anOStream,
                                 const TopoDS_Shape&                         aShape,
                                 const occ::handle<VrmlConverter_Drawer>&    aDrawer,
                                 const occ::handle<VrmlConverter_Projector>& aProjector)
{
  StdPrs_HLRToolShape Tool(aShape, aProjector->Projector());

  int               NbEdge = Tool.NbEdges();
  int               i;
  double            U1, U2;
  BRepAdaptor_Curve TheCurve;

  double theRequestedDeflection;
  if (aDrawer->TypeOfDeflection() == Aspect_TOD_RELATIVE)
  {
    Bnd_Box box;
    BRepBndLib::AddClose(aShape, box);

    double Xmin, Xmax, Ymin, Ymax, Zmin, Zmax, diagonal;
    box.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);
    if (!(box.IsOpenXmin() || box.IsOpenXmax() || box.IsOpenYmin() || box.IsOpenYmax()
          || box.IsOpenZmin() || box.IsOpenZmax()))
    {

      diagonal = std::sqrt((Xmax - Xmin) * (Xmax - Xmin) + (Ymax - Ymin) * (Ymax - Ymin)
                           + (Zmax - Zmin) * (Zmax - Zmin));
      diagonal = std::max(diagonal, Precision::Confusion());
      theRequestedDeflection = aDrawer->DeviationCoefficient() * diagonal;
    }
    else
    {
      diagonal               = 1000000.;
      theRequestedDeflection = aDrawer->DeviationCoefficient() * diagonal;
    }
  }
  else
  {
    theRequestedDeflection = aDrawer->MaximalChordialDeviation();
  }

  occ::handle<VrmlConverter_LineAspect> latmp = new VrmlConverter_LineAspect;
  latmp->SetMaterial(aDrawer->LineAspect()->Material());
  latmp->SetHasMaterial(aDrawer->LineAspect()->HasMaterial());

  occ::handle<VrmlConverter_LineAspect> laHL = new VrmlConverter_LineAspect;
  occ::handle<VrmlConverter_LineAspect> laSL = new VrmlConverter_LineAspect;

  laHL = aDrawer->HiddenLineAspect();
  laSL = aDrawer->SeenLineAspect();

  Vrml_Separator SE1;
  Vrml_Separator SE2;
  Vrml_Separator SE3;

  bool flag = false;

  SE1.Print(anOStream);

  aProjector->Add(anOStream);

  if (laSL->HasMaterial())
  {

    occ::handle<Vrml_Material> MSL;
    MSL = laSL->Material();

    MSL->Print(anOStream);
    laSL->SetHasMaterial(false);

    flag = true;

    SE2.Print(anOStream);
  }
  aDrawer->SetLineAspect(laSL);

  for (i = 1; i <= NbEdge; i++)
  {
    for (Tool.InitVisible(i); Tool.MoreVisible(); Tool.NextVisible())
    {
      Tool.Visible(TheCurve, U1, U2);
      VrmlConverter_DeflectionCurve::Add(anOStream, TheCurve, U1, U2, theRequestedDeflection);
    }
  }

  if (flag)
  {

    SE2.Print(anOStream);
    flag = false;
  }

  if (aDrawer->DrawHiddenLine())
  {

    if (laHL->HasMaterial())
    {

      occ::handle<Vrml_Material> MHL;
      MHL = laHL->Material();

      MHL->Print(anOStream);
      laHL->SetHasMaterial(false);

      flag = true;

      SE3.Print(anOStream);
    }
    aDrawer->SetLineAspect(laHL);

    for (i = 1; i <= NbEdge; i++)
    {
      for (Tool.InitHidden(i); Tool.MoreHidden(); Tool.NextHidden())
      {
        Tool.Hidden(TheCurve, U1, U2);
        VrmlConverter_DeflectionCurve::Add(anOStream, TheCurve, U1, U2, theRequestedDeflection);
      }
    }
    if (flag)
    {

      SE3.Print(anOStream);
      flag = false;
    }
  }

  SE1.Print(anOStream);

  aDrawer->SetLineAspect(latmp);
}
