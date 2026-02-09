

#include <VrmlConverter_Drawer.hpp>
#include <VrmlConverter_ShadedShape.hpp>
#include <Vrml_Normal.hpp>
#include <TopoDS.hpp>
#include <Poly_Connect.hpp>
#include <gp_Dir.hpp>
#include <NCollection_Array1.hpp>
#include <gp_Vec.hpp>
#include <NCollection_HArray1.hpp>
#include <BRepTools.hpp>
#include <BRep_Tool.hpp>
#include <gp_Pnt.hpp>
#include <TopExp_Explorer.hpp>
#include <TopLoc_Location.hpp>
#include <Poly_Triangle.hpp>
#include <Vrml_IndexedFaceSet.hpp>
#include <Vrml_Coordinate3.hpp>
#include <math.hpp>
#include <Standard_Integer.hpp>
#include <Geom_Surface.hpp>
#include <CSLib.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <Precision.hpp>
#include <Vrml_Material.hpp>
#include <VrmlConverter_ShadingAspect.hpp>
#include <Vrml_ShapeHints.hpp>
#include <Vrml_Separator.hpp>
#include <Vrml_NormalBinding.hpp>

void VrmlConverter_ShadedShape::Add(Standard_OStream&                        anOStream,
                                    const TopoDS_Shape&                      aShape,
                                    const occ::handle<VrmlConverter_Drawer>& aDrawer)
{
  occ::handle<Poly_Triangulation> T;
  TopLoc_Location                 theLocation;
  int                             i, j, k, decal, nnv, EI;

  int             t[3], n[3];
  gp_Pnt          p;
  TopExp_Explorer ex;

  int nbTriangles = 0, nbVertices = 0;

  int nt, nnn, n1, n2, n3;

  for (ex.Init(aShape, TopAbs_FACE); ex.More(); ex.Next())
  {

    const TopoDS_Face& F = TopoDS::Face(ex.Current());

    T = BRep_Tool::Triangulation(F, theLocation);

    if (T.IsNull())
      continue;
    nnn = T->NbTriangles();

    for (nt = 1; nt <= nnn; nt++)
    {
      if (F.Orientation() == TopAbs_REVERSED)
        T->Triangle(nt).Get(n1, n3, n2);
      else
        T->Triangle(nt).Get(n1, n2, n3);

      const gp_Pnt P1 = T->Node(n1);
      const gp_Pnt P2 = T->Node(n2);
      const gp_Pnt P3 = T->Node(n3);

      gp_Vec V1(P1, P2);
      if (V1.SquareMagnitude() > 1.e-10)
      {
        gp_Vec V2(P2, P3);
        if (V2.SquareMagnitude() > 1.e-10)
        {
          gp_Vec V3(P3, P1);
          if (V3.SquareMagnitude() > 1.e-10)
          {
            V1.Normalize();
            V2.Normalize();
            V1.Cross(V2);
            if (V1.SquareMagnitude() > 1.e-10)
            {
              nbTriangles++;
            }
          }
        }
      }
    }
    nbVertices += T->NbNodes();
  }

  if (nbVertices > 2 && nbTriangles > 0)
  {

    occ::handle<VrmlConverter_ShadingAspect> SA = new VrmlConverter_ShadingAspect;
    SA                                          = aDrawer->ShadingAspect();

    occ::handle<NCollection_HArray1<gp_Vec>> HAV1 = new NCollection_HArray1<gp_Vec>(1, nbVertices);
    occ::handle<NCollection_HArray1<gp_Vec>> HAV2 = new NCollection_HArray1<gp_Vec>(1, nbVertices);

    gp_Vec V, VV;

    occ::handle<NCollection_HArray1<int>> HAI1 = new NCollection_HArray1<int>(1, 4 * nbTriangles);
    occ::handle<NCollection_HArray1<int>> HAI3 =
      new NCollection_HArray1<int>(1, (nbVertices / 3 * 4 + nbVertices % 3));
    occ::handle<NCollection_HArray1<int>> HAI2 = new NCollection_HArray1<int>(1, 1);
    occ::handle<NCollection_HArray1<int>> HAI4 = new NCollection_HArray1<int>(1, 1);

    HAI2->SetValue(1, -1);
    HAI4->SetValue(1, -1);

    EI  = 1;
    nnv = 1;

    for (ex.Init(aShape, TopAbs_FACE); ex.More(); ex.Next())
    {
      const TopoDS_Face& F = TopoDS::Face(ex.Current());
      T                    = BRep_Tool::Triangulation(F, theLocation);
      if (!T.IsNull())
      {
        Poly_Connect pc(T);

        NCollection_Array1<gp_Dir> NORMAL(1, T->NbNodes());

        decal = nnv - 1;

        for (j = 1; j <= T->NbNodes(); j++)
        {
          p = T->Node(j).Transformed(theLocation.Transformation());

          V.SetX(p.X());
          V.SetY(p.Y());
          V.SetZ(p.Z());
          HAV1->SetValue(nnv, V);

          if (SA->HasNormals())
          {

            ComputeNormal(F, pc, NORMAL);

            VV.SetX(NORMAL(j).X());
            VV.SetY(NORMAL(j).Y());
            VV.SetZ(NORMAL(j).Z());
            HAV2->SetValue(nnv, VV);
          }
          nnv++;
        }

        nbTriangles = T->NbTriangles();
        for (i = 1; i <= nbTriangles; i++)
        {
          pc.Triangles(i, t[0], t[1], t[2]);
          if (F.Orientation() == TopAbs_REVERSED)
            T->Triangle(i).Get(n[0], n[2], n[1]);
          else
            T->Triangle(i).Get(n[0], n[1], n[2]);
          const gp_Pnt P1 = T->Node(n[0]);
          const gp_Pnt P2 = T->Node(n[1]);
          const gp_Pnt P3 = T->Node(n[2]);
          gp_Vec       V1(P1, P2);
          if (V1.SquareMagnitude() > 1.e-10)
          {
            gp_Vec V2(P2, P3);
            if (V2.SquareMagnitude() > 1.e-10)
            {
              gp_Vec V3(P3, P1);
              if (V3.SquareMagnitude() > 1.e-10)
              {
                V1.Normalize();
                V2.Normalize();
                V1.Cross(V2);
                if (V1.SquareMagnitude() > 1.e-10)
                {
                  for (j = 0; j < 3; j++)
                  {

                    HAI1->SetValue(EI, n[j] + decal - 1);
                    EI++;
                  }

                  HAI1->SetValue(EI, -1);
                  EI++;
                }
              }
            }
          }
        }
      }
    }

    if (SA->HasNormals())
    {
      j = 1;
      for (i = HAI3->Lower(); i <= HAI3->Upper(); i++)
      {
        k = i % 4;
        if (k == 0)
        {
          HAI3->SetValue(i, -1);
          j++;
        }
        else
        {
          HAI3->SetValue(i, i - j);
        }
      }
    }

    Vrml_ShapeHints SH;
    SH = SA->ShapeHints();

    if (SA->HasNormals())
    {

      Vrml_Separator SE1;
      SE1.Print(anOStream);

      if (SA->HasMaterial())
      {

        occ::handle<Vrml_Material> M;
        M = SA->FrontMaterial();

        M->Print(anOStream);
      }

      occ::handle<Vrml_Coordinate3> C3 = new Vrml_Coordinate3(HAV1);
      C3->Print(anOStream);

      SH.Print(anOStream);

      Vrml_MaterialBindingAndNormalBinding MBNB1 = Vrml_PER_VERTEX_INDEXED;
      Vrml_NormalBinding                   NB(MBNB1);
      NB.Print(anOStream);

      Vrml_Separator SE2;
      SE2.Print(anOStream);

      Vrml_Normal N(HAV2);
      N.Print(anOStream);

      Vrml_IndexedFaceSet IFS;
      IFS.SetCoordIndex(HAI1);
      IFS.SetNormalIndex(HAI3);
      IFS.Print(anOStream);

      SE2.Print(anOStream);

      SE1.Print(anOStream);
    }
    else
    {

      Vrml_Separator SE1;
      SE1.Print(anOStream);

      if (SA->HasMaterial())
      {

        occ::handle<Vrml_Material> M;
        M = SA->FrontMaterial();

        M->Print(anOStream);
      }

      occ::handle<Vrml_Coordinate3> C3 = new Vrml_Coordinate3(HAV1);
      C3->Print(anOStream);

      SH.Print(anOStream);

      Vrml_IndexedFaceSet IFS;
      IFS.SetCoordIndex(HAI1);
      IFS.Print(anOStream);

      SE1.Print(anOStream);
    }
  }
}

void VrmlConverter_ShadedShape::ComputeNormal(const TopoDS_Face&          aFace,
                                              Poly_Connect&               pc,
                                              NCollection_Array1<gp_Dir>& Nor)
{
  const occ::handle<Poly_Triangulation>& T = pc.Triangulation();
  BRepAdaptor_Surface                    S;
  bool                                   hasUV = T->HasUVNodes();
  int                                    i;
  TopLoc_Location                        l;
  occ::handle<Geom_Surface>              GS = BRep_Tool::Surface(aFace, l);

  if (hasUV && !GS.IsNull())
  {
    bool                   OK = true;
    gp_Vec                 D1U, D1V;
    gp_Vec                 D2U, D2V, D2UV;
    gp_Pnt                 P;
    double                 U, V;
    CSLib_DerivativeStatus aStatus;
    CSLib_NormalStatus     NStat;
    S.Initialize(aFace);
    for (i = 1; i <= T->NbNodes(); i++)
    {
      U = T->UVNode(i).X();
      V = T->UVNode(i).Y();
      S.D1(U, V, P, D1U, D1V);
      CSLib::Normal(D1U, D1V, Precision::Angular(), aStatus, Nor(i));
      if (aStatus != CSLib_Done)
      {
        S.D2(U, V, P, D1U, D1V, D2U, D2V, D2UV);
        CSLib::Normal(D1U, D1V, D2U, D2V, D2UV, Precision::Angular(), OK, NStat, Nor(i));
      }
      if (aFace.Orientation() == TopAbs_REVERSED)
        (Nor(i)).Reverse();
    }
  }
  else
  {
    int n[3];

    for (i = 1; i <= T->NbNodes(); i++)
    {
      gp_XYZ eqPlan(0, 0, 0);
      for (pc.Initialize(i); pc.More(); pc.Next())
      {
        T->Triangle(pc.Value()).Get(n[0], n[1], n[2]);
        gp_XYZ v1(T->Node(n[1]).Coord() - T->Node(n[0]).Coord());
        gp_XYZ v2(T->Node(n[2]).Coord() - T->Node(n[1]).Coord());
        eqPlan += (v1 ^ v2).Normalized();
      }
      Nor(i) = gp_Dir(eqPlan);
      if (aFace.Orientation() == TopAbs_REVERSED)
        (Nor(i)).Reverse();
    }
  }
}
