

#include <IGESBasic_Group.hpp>
#include <IGESBasic_SingleParent.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESGeom_BoundedSurface.hpp>
#include <IGESGeom_CompositeCurve.hpp>
#include <IGESGeom_Plane.hpp>
#include <IGESGeom_TrimmedSurface.hpp>
#include <IGESSelect_SelectBasicGeom.hpp>
#include <IGESSolid_EdgeList.hpp>
#include <IGESSolid_ManifoldSolid.hpp>
#include <IGESSolid_Shell.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SelectBasicGeom, IFSelect_SelectExplore)

IGESSelect_SelectBasicGeom::IGESSelect_SelectBasicGeom(const int mode)
    : IFSelect_SelectExplore(-1)
{
  thegeom = mode;
}

bool IGESSelect_SelectBasicGeom::Explore(const int,
                                         const occ::handle<Standard_Transient>& ent,
                                         const Interface_Graph&,
                                         Interface_EntityIterator& explored) const
{

  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return false;
  int igt = igesent->TypeNumber();

  if (igt == 102 && thegeom == 2)
  {
    DeclareAndCast(IGESGeom_CompositeCurve, cmc, ent);
    int i, nb = cmc->NbCurves();
    for (i = 1; i <= nb; i++)
      explored.AddItem(cmc->Curve(i));
    return true;
  }

  if (igt == 106)
    return (igesent->FormNumber() < 20);
  if ((igt >= 100 && igt <= 106) || igt == 110 || igt == 112 || igt == 116 || igt == 126
      || igt == 130)
    return (thegeom >= 0);

  if (igt == 114 || igt == 118 || igt == 120 || igt == 122 || igt == 128 || igt == 140
      || igt == 190)
    return (thegeom <= 0);

  if (igt == 108)
  {
    DeclareAndCast(IGESGeom_Plane, pln, ent);
    if (thegeom >= 0)
      explored.AddItem(pln->BoundingCurve());
    return pln->HasBoundingCurve();
  }

  if (igt == 116)
    return (thegeom >= 0);

  if (igt == 144)
  {
    DeclareAndCast(IGESGeom_TrimmedSurface, trs, ent);
    if (thegeom >= 0)
    {
      explored.AddItem(trs->OuterContour());
      int i, nb = trs->NbInnerContours();
      for (i = 1; i <= nb; i++)
        explored.AddItem(trs->InnerContour(i));
    }
    else
      explored.AddItem(trs->Surface());
    return true;
  }

  if (igt == 142 && thegeom >= 0)
  {
    DeclareAndCast(IGESGeom_CurveOnSurface, crf, ent);
    explored.AddItem(crf->Curve3D());
    return true;
  }

  if (igt == 141 && thegeom >= 0)
  {
    DeclareAndCast(IGESGeom_Boundary, bnd, ent);
    int i, nb = bnd->NbModelSpaceCurves();
    for (i = 1; i <= nb; i++)
      explored.AddItem(bnd->ModelSpaceCurve(i));
    return (nb > 0);
  }

  if (igt == 143)
  {
    DeclareAndCast(IGESGeom_BoundedSurface, bns, ent);
    int i, nb = 0;
    if (thegeom >= 0)
    {
      nb = bns->NbBoundaries();
      for (i = 1; i <= nb; i++)
        explored.AddItem(bns->Boundary(i));
      return (nb != 0);
    }
    else
      explored.AddItem(bns->Surface());
    return true;
  }

  if (igt == 402 && igesent->FormNumber() == 9)
  {
    DeclareAndCast(IGESBasic_SingleParent, sp, ent);
    if (sp.IsNull())
      return false;
    explored.AddItem(sp->SingleParent());
    int i, nb = sp->NbChildren();
    for (i = 1; i <= nb; i++)
      explored.AddItem(sp->Child(i));
    return true;
  }

  if (igt == 402)
  {
    DeclareAndCast(IGESBasic_Group, gr, ent);
    if (gr.IsNull())
      return false;
    int i, nb = gr->NbEntities();
    for (i = 1; i <= nb; i++)
      explored.AddItem(gr->Entity(i));
    return true;
  }

  if (igt == 186)
  {
    DeclareAndCast(IGESSolid_ManifoldSolid, msb, ent);
    explored.AddItem(msb->Shell());
    int i, nb = msb->NbVoidShells();
    for (i = 1; i <= nb; i++)
      explored.AddItem(msb->VoidShell(i));
    return true;
  }

  if (igt == 514)
  {
    DeclareAndCast(IGESSolid_Shell, sh, ent);
    int i, nb = sh->NbFaces();
    for (i = 1; i <= nb; i++)
      explored.AddItem(sh->Face(i));
    return true;
  }

  if (igt == 510)
  {
    DeclareAndCast(IGESSolid_Face, fc, ent);
    if (thegeom >= 0)
    {
      int i, nb = fc->NbLoops();
      for (i = 1; i <= nb; i++)
        explored.AddItem(fc->Loop(i));
    }
    else
      explored.AddItem(fc->Surface());
    return true;
  }

  if (igt == 508 && thegeom >= 0)
  {
    DeclareAndCast(IGESSolid_Loop, lp, ent);
    int i, nb = lp->NbEdges();
    for (i = 1; i <= nb; i++)
    {
      DeclareAndCast(IGESSolid_EdgeList, edl, lp->Edge(i));
      int ind = lp->ListIndex(i);
      if (edl.IsNull())
        continue;
      explored.AddItem(edl->Curve(ind));
    }
    return true;
  }

  return false;
}

TCollection_AsciiString IGESSelect_SelectBasicGeom::ExploreLabel() const
{
  if (thegeom == 2)
    return TCollection_AsciiString("Basic Curves 3d");
  else if (thegeom > 0)
    return TCollection_AsciiString("Curves 3d");
  else if (thegeom < 0)
    return TCollection_AsciiString("Surfaces");
  else
    return TCollection_AsciiString("Basic Geometry");
}

bool IGESSelect_SelectBasicGeom::SubCurves(const occ::handle<IGESData_IGESEntity>& ent,
                                           Interface_EntityIterator&               explored)
{
  if (ent.IsNull())
    return false;
  int igt = ent->TypeNumber();

  if (igt == 102)
  {
    DeclareAndCast(IGESGeom_CompositeCurve, cmc, ent);
    int i, nb = cmc->NbCurves();
    for (i = 1; i <= nb; i++)
      explored.AddItem(cmc->Curve(i));
    return true;
  }

  if (igt == 106)
    return (ent->FormNumber() < 20);
  if ((igt >= 100 && igt <= 106) || igt == 110 || igt == 112 || igt == 116 || igt == 126
      || igt == 130)
    return true;

  return false;
}
