

#include <Bnd_Box.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Curve.hpp>
#include <gp_Pnt.hpp>
#include <StdPrs_ShapeTool.hpp>
#include <TopoDS_Shape.hpp>
#include <Vrml_Coordinate3.hpp>
#include <Vrml_Material.hpp>
#include <Vrml_PointSet.hpp>
#include <Vrml_Separator.hpp>
#include <VrmlConverter_Curve.hpp>
#include <VrmlConverter_Drawer.hpp>
#include <VrmlConverter_IsoAspect.hpp>
#include <VrmlConverter_LineAspect.hpp>
#include <VrmlConverter_PointAspect.hpp>
#include <VrmlConverter_WFRestrictedFace.hpp>
#include <VrmlConverter_WFShape.hpp>

void VrmlConverter_WFShape::Add(Standard_OStream&                        anOStream,
                                const TopoDS_Shape&                      aShape,
                                const occ::handle<VrmlConverter_Drawer>& aDrawer)
{

  StdPrs_ShapeTool Tool(aShape);

  if (aDrawer->UIsoAspect()->Number() != 0 || aDrawer->VIsoAspect()->Number() != 0)
  {

    BRepAdaptor_Surface S;
    bool                isoU, isoV;
    for (Tool.InitFace(); Tool.MoreFace(); Tool.NextFace())
    {
      isoU = (aDrawer->UIsoAspect()->Number() != 0);
      isoV = (aDrawer->VIsoAspect()->Number() != 0);
      if (Tool.HasSurface())
      {
        if (Tool.IsPlanarFace())
        {
          isoU = (isoU && aDrawer->IsoOnPlane());
          isoV = (isoV && aDrawer->IsoOnPlane());
        }
        if (isoU || isoV)
        {
          S.Initialize(Tool.GetFace());
          occ::handle<BRepAdaptor_Surface> HS = new BRepAdaptor_Surface(S);
          VrmlConverter_WFRestrictedFace::Add(anOStream,
                                              HS,
                                              isoU,
                                              isoV,
                                              aDrawer->UIsoAspect()->Number(),
                                              aDrawer->VIsoAspect()->Number(),
                                              aDrawer);
        }
      }
    }
  }

  else
  {

    if (aDrawer->UIsoAspect()->Number() != 0)
    {

      BRepAdaptor_Surface S;
      for (Tool.InitFace(); Tool.MoreFace(); Tool.NextFace())
      {
        bool isoU = true;
        if (Tool.HasSurface())
        {
          if (Tool.IsPlanarFace())
            isoU = aDrawer->IsoOnPlane();
          if (isoU)
          {
            S.Initialize(Tool.GetFace());
            occ::handle<BRepAdaptor_Surface> HS = new BRepAdaptor_Surface(S);
            VrmlConverter_WFRestrictedFace::Add(anOStream,
                                                HS,
                                                isoU,
                                                false,
                                                aDrawer->UIsoAspect()->Number(),
                                                0,
                                                aDrawer);
          }
        }
      }
    }

    if (aDrawer->VIsoAspect()->Number() != 0)
    {

      BRepAdaptor_Surface S;
      for (Tool.InitFace(); Tool.MoreFace(); Tool.NextFace())
      {
        bool isoV = true;
        if (Tool.HasSurface())
        {
          if (Tool.IsPlanarFace())
            isoV = aDrawer->IsoOnPlane();
          if (isoV)
          {
            S.Initialize(Tool.GetFace());
            occ::handle<BRepAdaptor_Surface> HS = new BRepAdaptor_Surface(S);
            VrmlConverter_WFRestrictedFace::Add(anOStream,
                                                HS,
                                                false,
                                                isoV,
                                                0,
                                                aDrawer->VIsoAspect()->Number(),
                                                aDrawer);
          }
        }
      }
    }
  }

  int qnt = 0;
  for (Tool.InitCurve(); Tool.MoreCurve(); Tool.NextCurve())
  {
    qnt++;
  }

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
            VrmlConverter_Curve::Add(C, aDrawer, anOStream);
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
            VrmlConverter_Curve::Add(C, aDrawer, anOStream);
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
            VrmlConverter_Curve::Add(C, aDrawer, anOStream);
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
