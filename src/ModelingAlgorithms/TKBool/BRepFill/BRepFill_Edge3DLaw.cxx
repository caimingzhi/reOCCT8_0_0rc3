#include <BRep_Tool.hpp>
#include <BRepFill_Edge3DLaw.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <Geom_Curve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepFill_Edge3DLaw, BRepFill_LocationLaw)

BRepFill_Edge3DLaw::BRepFill_Edge3DLaw(const TopoDS_Wire&                       Path,
                                       const occ::handle<GeomFill_LocationLaw>& Law)
{
  Init(Path);

  int                    ipath;
  TopAbs_Orientation     Or;
  BRepTools_WireExplorer wexp;

  TopoDS_Edge                    E;
  occ::handle<Geom_Curve>        C;
  occ::handle<GeomAdaptor_Curve> AC;
  double                         First, Last;

  for (ipath = 0, wexp.Init(myPath); wexp.More(); wexp.Next())
  {
    E = wexp.Current();

    if (!BRep_Tool::Degenerated(E))
    {
      ipath++;
      myEdges->SetValue(ipath, E);
      C  = BRep_Tool::Curve(E, First, Last);
      Or = E.Orientation();
      if (Or == TopAbs_REVERSED)
      {
        occ::handle<Geom_TrimmedCurve> CBis = new (Geom_TrimmedCurve)(C, First, Last);
        CBis->Reverse();
        C     = CBis;
        First = C->FirstParameter();
        Last  = C->LastParameter();
      }

      AC = new (GeomAdaptor_Curve)(C, First, Last);
      myLaws->SetValue(ipath, Law->Copy());
      myLaws->ChangeValue(ipath)->SetCurve(AC);
    }
  }
}
