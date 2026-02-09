

#include <gp_Pnt2d.hpp>
#include <IFSelect_ContextModif.hpp>
#include <IFSelect_PacketList.hpp>
#include <IGESData_IGESModel.hpp>
#include <IGESDraw_Drawing.hpp>
#include <IGESDraw_DrawingWithRotation.hpp>
#include <IGESData_ViewKindEntity.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESSelect_RebuildDrawings.hpp>
#include <IGESSelect_ViewSorter.hpp>
#include <Interface_CopyTool.hpp>
#include <Interface_EntityIterator.hpp>
#include <MoniTool_Macros.hpp>
#include <Standard_Type.hpp>
#include <gp_XY.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_Integer.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IGESSelect_RebuildDrawings, IGESSelect_ModelModifier)

#define PourDrawing 404

IGESSelect_RebuildDrawings::IGESSelect_RebuildDrawings()
    : IGESSelect_ModelModifier(true)
{
}

void IGESSelect_RebuildDrawings::Performing(IFSelect_ContextModif&                 ctx,
                                            const occ::handle<IGESData_IGESModel>& target,
                                            Interface_CopyTool&                    TC) const
{

  DeclareAndCast(IGESData_IGESModel, original, ctx.OriginalModel());
  int                     nbo = original->NbEntities();
  NCollection_Array1<int> pris(0, nbo);
  pris.Init(0);

  occ::handle<IGESSelect_ViewSorter> sorter = new IGESSelect_ViewSorter;
  sorter->SetModel(original);
  sorter->Add(original);
  for (ctx.Start(); ctx.More(); ctx.Next())
  {
    pris.SetValue(original->Number(ctx.ValueOriginal()), 1);
  }
  sorter->SortDrawings(ctx.OriginalGraph());
  occ::handle<IFSelect_PacketList> sets = sorter->Sets(true);

  int nbs = sets->NbPackets();
  for (int is = 1; is <= nbs; is++)
  {
    Interface_EntityIterator setl = sets->Entities(is);
    Interface_EntityIterator newset;
    for (setl.Start(); setl.More(); setl.Next())
    {
      occ::handle<Standard_Transient> newent;
      if (TC.Search(setl.Value(), newent))
        newset.AddItem(newent);
    }
    if (newset.NbEntities() == 0)
      continue;

    occ::handle<IGESData_IGESEntity> item = sorter->SetItem(is, true);
    if (item->TypeNumber() != PourDrawing)
      continue;
    if (item->IsKind(STANDARD_TYPE(IGESDraw_Drawing)))
    {
      DeclareAndCast(IGESDraw_Drawing, draw, item);
      int                                                                    nbv = draw->NbViews();
      occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> views;
      if (nbv > 0)
        views = new NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>(1, nbv);

      occ::handle<NCollection_HArray1<gp_XY>> origs;
      if (nbv > 0)
        origs = new NCollection_HArray1<gp_XY>(1, nbv);
      for (int iv = 1; iv <= nbv; iv++)
      {
        DeclareAndCast(IGESData_ViewKindEntity, aview, TC.Transferred(draw->ViewItem(iv)));
        views->SetValue(iv, aview);
        target->AddEntity(aview);
        origs->SetValue(iv, draw->ViewOrigin(iv).XY());
      }

      occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> frame;
      int                      nba = draw->NbAnnotations();
      Interface_EntityIterator framelist;
      int                      ia;
      for (ia = 1; ia <= nba; ia++)
      {
        occ::handle<Standard_Transient> annot;
        if (TC.Search(draw->Annotation(ia), annot))
          framelist.GetOneItem(annot);
      }
      nba = framelist.NbEntities();
      ia  = 0;
      if (nba > 0)
        frame = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, nba);
      for (framelist.Start(); framelist.More(); framelist.Next())
      {
        ia++;
        frame->SetValue(ia, GetCasted(IGESData_IGESEntity, framelist.Value()));
      }

      occ::handle<IGESDraw_Drawing> newdraw = new IGESDraw_Drawing;
      newdraw->Init(views, origs, frame);
    }
    else if (item->IsKind(STANDARD_TYPE(IGESDraw_DrawingWithRotation)))
    {
      DeclareAndCast(IGESDraw_DrawingWithRotation, draw, item);
      int                                                                    nbv = draw->NbViews();
      occ::handle<NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>> views;
      if (nbv > 0)
        views = new NCollection_HArray1<occ::handle<IGESData_ViewKindEntity>>(1, nbv);

      occ::handle<NCollection_HArray1<gp_XY>> origs;
      if (nbv > 0)
        origs = new NCollection_HArray1<gp_XY>(1, nbv);
      occ::handle<NCollection_HArray1<double>> rots;
      if (nbv > 0)
      {
        rots = new NCollection_HArray1<double>(1, nbv);
        rots->Init(0.0);
      }

      for (int iv = 1; iv <= nbv; iv++)
      {
        DeclareAndCast(IGESData_ViewKindEntity, aview, TC.Transferred(draw->ViewItem(iv)));
        views->SetValue(iv, aview);
        target->AddEntity(aview);
        rots->SetValue(iv, draw->OrientationAngle(iv));
        origs->SetValue(iv, draw->ViewOrigin(iv).XY());
      }

      occ::handle<NCollection_HArray1<occ::handle<IGESData_IGESEntity>>> frame;
      int                      nba = draw->NbAnnotations();
      Interface_EntityIterator framelist;
      int                      ia;
      for (ia = 1; ia <= nba; ia++)
      {
        occ::handle<Standard_Transient> annot;
        if (TC.Search(draw->Annotation(ia), annot))
          framelist.GetOneItem(annot);
      }
      nba = framelist.NbEntities();
      ia  = 0;
      if (nba > 0)
        frame = new NCollection_HArray1<occ::handle<IGESData_IGESEntity>>(1, nba);
      for (framelist.Start(); framelist.More(); framelist.Next())
      {
        ia++;
        frame->SetValue(ia, GetCasted(IGESData_IGESEntity, framelist.Value()));
      }

      occ::handle<IGESDraw_DrawingWithRotation> newdraw = new IGESDraw_DrawingWithRotation;
      newdraw->Init(views, origs, rots, frame);
    }

    for (setl.Start(); setl.More(); setl.Next())
    {
      DeclareAndCast(IGESData_IGESEntity, ent, setl.Value());
      occ::handle<IGESData_ViewKindEntity> vieworig = ent->View();
      if (vieworig.IsNull())
        continue;
      occ::handle<Standard_Transient> aView;
      if (!TC.Search(vieworig, aView))
        continue;
      occ::handle<IGESData_ViewKindEntity> viewnew = occ::down_cast<IGESData_ViewKindEntity>(aView);
      if (!viewnew.IsNull())
        ent->InitView(viewnew);
    }
  }
}

TCollection_AsciiString IGESSelect_RebuildDrawings::Label() const
{
  return TCollection_AsciiString("Rebuild Drawings (with empty views)");
}
