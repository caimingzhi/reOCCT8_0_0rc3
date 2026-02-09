

#include <IGESBasic_Group.hpp>
#include <IGESData_IGESEntity.hpp>
#include <IGESGeom_BoundedSurface.hpp>
#include <IGESGeom_TrimmedSurface.hpp>
#include <IGESSelect_SelectBasicGeom.hpp>
#include <IGESSelect_SelectPCurves.hpp>
#include <IGESSolid_ManifoldSolid.hpp>
#include <IGESSolid_Shell.hpp>
#include <Interface_EntityIterator.hpp>
#include <Interface_Graph.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TCollection_AsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_SelectPCurves, IFSelect_SelectExplore)

IGESSelect_SelectPCurves::IGESSelect_SelectPCurves(const bool basic)
    : IFSelect_SelectExplore(-1),
      thebasic(basic)
{
}

bool IGESSelect_SelectPCurves::Explore(const int                              level,
                                       const occ::handle<Standard_Transient>& ent,
                                       const Interface_Graph&,
                                       Interface_EntityIterator& explored) const
{
  DeclareAndCast(IGESData_IGESEntity, igesent, ent);
  if (igesent.IsNull())
    return false;
  int igt = igesent->TypeNumber();

  if (igt == 144)
  {
    DeclareAndCast(IGESGeom_TrimmedSurface, trs, ent);
    explored.AddItem(trs->OuterContour());
    int i, nb = trs->NbInnerContours();
    for (i = 1; i <= nb; i++)
      explored.AddItem(trs->InnerContour(i));
    return true;
  }

  if (igt == 142)
  {
    DeclareAndCast(IGESGeom_CurveOnSurface, crf, ent);
    explored.AddItem(crf->CurveUV());
    if (thebasic)
      IGESSelect_SelectBasicGeom::SubCurves(crf->CurveUV(), explored);
    return true;
  }

  if (igt == 141)
  {
    DeclareAndCast(IGESGeom_Boundary, bnd, ent);
    int i, nb = bnd->NbModelSpaceCurves();
    for (i = 1; i <= nb; i++)
    {
      int j, np = bnd->NbParameterCurves(i);
      for (j = 1; j <= np; j++)
      {
        explored.AddItem(bnd->ParameterCurve(i, j));
      }
    }
    return (nb > 0);
  }

  if (igt == 143)
  {
    DeclareAndCast(IGESGeom_BoundedSurface, bns, ent);
    int i, nb = bns->NbBoundaries();
    for (i = 1; i <= nb; i++)
      explored.AddItem(bns->Boundary(i));
    return (nb != 0);
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
    int i, nb = fc->NbLoops();
    for (i = 1; i <= nb; i++)
      explored.AddItem(fc->Loop(i));
    return true;
  }

  if (igt == 508)
  {
    DeclareAndCast(IGESSolid_Loop, lp, ent);
    int i, nb = lp->NbEdges();
    for (i = 1; i <= nb; i++)
    {
      int j, np = lp->NbParameterCurves(i);
      for (j = 1; j <= np; j++)
        explored.AddItem(lp->ParametricCurve(i, j));
    }
    return true;
  }

  if (level < 3)
    return false;

  if (igt == 106)
    return (igesent->FormNumber() < 20);
  if ((igt >= 100 && igt <= 106) || igt == 110 || igt == 112 || igt == 116 || igt == 126
      || igt == 130)
    return true;

  return false;
}

TCollection_AsciiString IGESSelect_SelectPCurves::ExploreLabel() const
{
  if (thebasic)
    return TCollection_AsciiString("Basic PCurves");
  else
    return TCollection_AsciiString("Global PCurves");
}
