#include <BRepFill_EdgeOnSurfLaw.hpp>

#include <Adaptor3d_CurveOnSurface.hpp>
#include <BRep_Tool.hpp>
#include <BRepAdaptor_Surface.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <Geom2d_Curve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <GeomFill_CurveAndTrihedron.hpp>
#include <GeomFill_Darboux.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Type.hpp>
#include <TopExp_Explorer.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Shape.hpp>
#include <TopoDS_Wire.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepFill_EdgeOnSurfLaw, BRepFill_LocationLaw)

BRepFill_EdgeOnSurfLaw::BRepFill_EdgeOnSurfLaw(const TopoDS_Wire& Path, const TopoDS_Shape& Surf)
{
  hasresult = true;
  Init(Path);

  bool                   Trouve;
  int                    ipath;
  TopAbs_Orientation     Or;
  BRepTools_WireExplorer wexp;
  TopExp_Explorer        exp;

  TopoDS_Edge                             E;
  occ::handle<Geom2d_Curve>               C;
  occ::handle<Geom2dAdaptor_Curve>        AC2d;
  occ::handle<Adaptor3d_CurveOnSurface>   AC;
  occ::handle<BRepAdaptor_Surface>        AS;
  double                                  First = 0., Last = 0.;
  occ::handle<GeomFill_Darboux>           TLaw = new (GeomFill_Darboux)();
  occ::handle<GeomFill_CurveAndTrihedron> Law  = new (GeomFill_CurveAndTrihedron)(TLaw);

  for (ipath = 0, wexp.Init(myPath); wexp.More(); wexp.Next())
  {
    E = wexp.Current();

    if (!BRep_Tool::Degenerated(E))
    {
      ipath++;
      myEdges->SetValue(ipath, E);
      for (Trouve = false, exp.Init(Surf, TopAbs_FACE); exp.More() && !Trouve; exp.Next())
      {
        const TopoDS_Face& F = TopoDS::Face(exp.Current());
        C                    = BRep_Tool::CurveOnSurface(E, F, First, Last);
        if (!C.IsNull())
        {
          Trouve = true;
          AS     = new (BRepAdaptor_Surface)(F);
        }
      }
      if (!Trouve)
      {
        hasresult = false;
        myLaws.Nullify();
        return;
      }

      Or = E.Orientation();
      if (Or == TopAbs_REVERSED)
      {
        occ::handle<Geom2d_TrimmedCurve> CBis = new (Geom2d_TrimmedCurve)(C, First, Last);
        CBis->Reverse();
        C     = CBis;
        First = C->FirstParameter();
        Last  = C->LastParameter();
      }

      AC2d = new (Geom2dAdaptor_Curve)(C, First, Last);
      AC   = new (Adaptor3d_CurveOnSurface)(Adaptor3d_CurveOnSurface(AC2d, AS));
      myLaws->SetValue(ipath, Law->Copy());
      myLaws->ChangeValue(ipath)->SetCurve(AC);
    }
  }
}

bool BRepFill_EdgeOnSurfLaw::HasResult() const
{
  return hasresult;
}
