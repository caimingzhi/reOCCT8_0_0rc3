

#include <Bnd_Box.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <BRepBndLib.hpp>
#include <gp_Pnt.hpp>
#include <Poly_PolygonOnTriangulation.hpp>
#include <Precision.hpp>
#include <StdPrs_ShapeTool.hpp>
#include <TopoDS_Shape.hpp>
#include <Vrml_Coordinate3.hpp>
#include <Vrml_Material.hpp>
#include <Vrml_PointSet.hpp>
#include <Vrml_Separator.hpp>
#include <VrmlConverter_DeflectionCurve.hpp>
#include <VrmlConverter_Drawer.hpp>
#include <VrmlConverter_LineAspect.hpp>
#include <VrmlConverter_PointAspect.hpp>
#include <VrmlConverter_WFDeflectionShape.hpp>

void VrmlConverter_WFDeflectionShape::Add(Standard_OStream&                        anOStream,
                                          const TopoDS_Shape&                      aShape,
                                          const occ::handle<VrmlConverter_Drawer>& aDrawer)
{

  StdPrs_ShapeTool Tool(aShape);

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

  int qnt = 0;
  for (Tool.InitCurve(); Tool.MoreCurve(); Tool.NextCurve())
  {
    qnt++;
  }

  occ::handle<Poly_PolygonOnTriangulation> aPT;
  occ::handle<Poly_Triangulation>          aT;
  TopLoc_Location                          aL;

  if (aDrawer->WireDraw())
  {
    if (qnt != 0)
    {
      occ::handle<VrmlConverter_LineAspect> latmp = new VrmlConverter_LineAspect;
      latmp->SetMaterial(aDrawer->LineAspect()->Material());
      latmp->SetHasMaterial(aDrawer->LineAspect()->HasMaterial());

      aDrawer->SetLineAspect(aDrawer->WireAspect());

      for (Tool.InitCurve(); Tool.MoreCurve(); Tool.NextCurve())
      {
        if (Tool.Neighbours() == 0)
        {
          if (Tool.HasCurve())
          {
            BRepAdaptor_Curve C(Tool.GetCurve());
            BRep_Tool::PolygonOnTriangulation(Tool.GetCurve(), aPT, aT, aL);
            if (!aPT.IsNull() && !aT.IsNull() && aPT->HasParameters())
              VrmlConverter_DeflectionCurve::Add(anOStream,
                                                 C,
                                                 aPT->Parameters(),
                                                 aPT->NbNodes(),
                                                 aDrawer);
            else
              VrmlConverter_DeflectionCurve::Add(anOStream, C, theRequestedDeflection, aDrawer);
          }
        }
      }
      aDrawer->SetLineAspect(latmp);
    }
  }

  if (aDrawer->FreeBoundaryDraw())
  {
    if (qnt != 0)
    {
      occ::handle<VrmlConverter_LineAspect> latmp = new VrmlConverter_LineAspect;
      latmp->SetMaterial(aDrawer->LineAspect()->Material());
      latmp->SetHasMaterial(aDrawer->LineAspect()->HasMaterial());

      aDrawer->SetLineAspect(aDrawer->FreeBoundaryAspect());

      for (Tool.InitCurve(); Tool.MoreCurve(); Tool.NextCurve())
      {
        if (Tool.Neighbours() == 1)
        {
          if (Tool.HasCurve())
          {
            BRepAdaptor_Curve C(Tool.GetCurve());
            BRep_Tool::PolygonOnTriangulation(Tool.GetCurve(), aPT, aT, aL);
            if (!aPT.IsNull() && !aT.IsNull() && aPT->HasParameters())
              VrmlConverter_DeflectionCurve::Add(anOStream,
                                                 C,
                                                 aPT->Parameters(),
                                                 aPT->NbNodes(),
                                                 aDrawer);
            else
              VrmlConverter_DeflectionCurve::Add(anOStream, C, theRequestedDeflection, aDrawer);
          }
        }
      }
      aDrawer->SetLineAspect(latmp);
    }
  }

  if (aDrawer->UnFreeBoundaryDraw())
  {
    if (qnt != 0)
    {
      occ::handle<VrmlConverter_LineAspect> latmp = new VrmlConverter_LineAspect;
      latmp->SetMaterial(aDrawer->LineAspect()->Material());
      latmp->SetHasMaterial(aDrawer->LineAspect()->HasMaterial());

      aDrawer->SetLineAspect(aDrawer->UnFreeBoundaryAspect());

      for (Tool.InitCurve(); Tool.MoreCurve(); Tool.NextCurve())
      {
        if (Tool.Neighbours() >= 2)
        {
          if (Tool.HasCurve())
          {
            BRepAdaptor_Curve C(Tool.GetCurve());
            BRep_Tool::PolygonOnTriangulation(Tool.GetCurve(), aPT, aT, aL);
            if (!aPT.IsNull() && !aT.IsNull() && aPT->HasParameters())
              VrmlConverter_DeflectionCurve::Add(anOStream,
                                                 C,
                                                 aPT->Parameters(),
                                                 aPT->NbNodes(),
                                                 aDrawer);
            else
              VrmlConverter_DeflectionCurve::Add(anOStream, C, theRequestedDeflection, aDrawer);
          }
        }
      }
      aDrawer->SetLineAspect(latmp);
    }
  }

  qnt = 0;
  for (Tool.InitVertex(); Tool.MoreVertex(); Tool.NextVertex())
  {
    qnt++;
  }

  if (qnt != 0)
  {
    occ::handle<NCollection_HArray1<gp_Vec>> HAV = new NCollection_HArray1<gp_Vec>(1, qnt);
    gp_Vec                                   V;
    gp_Pnt                                   P;
    int                                      i = 0;

    for (Tool.InitVertex(); Tool.MoreVertex(); Tool.NextVertex())
    {
      i++;
      P = BRep_Tool::Pnt(Tool.GetVertex());
      V.SetX(P.X());
      V.SetY(P.Y());
      V.SetZ(P.Z());
      HAV->SetValue(i, V);
    }

    occ::handle<VrmlConverter_PointAspect> PA = new VrmlConverter_PointAspect;
    PA                                        = aDrawer->PointAspect();

    Vrml_Separator SEP;
    SEP.Print(anOStream);

    if (PA->HasMaterial())
    {

      occ::handle<Vrml_Material> MP;
      MP = PA->Material();

      MP->Print(anOStream);
    }

    occ::handle<Vrml_Coordinate3> C3 = new Vrml_Coordinate3(HAV);
    C3->Print(anOStream);

    Vrml_PointSet PS;
    PS.Print(anOStream);

    SEP.Print(anOStream);
  }
}
