#include <Approx_CurvlinFunc.hpp>
#include <BRep_Tool.hpp>
#include <BRepFill.hpp>
#include <BRepFill_ACRLaw.hpp>
#include <BRepTools_WireExplorer.hpp>
#include <Geom_Curve.hpp>
#include <Geom_TrimmedCurve.hpp>
#include <GeomAdaptor_Curve.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <GeomFill_LocationGuide.hpp>
#include <Standard_Type.hpp>
#include <TopExp.hpp>
#include <TopoDS_Edge.hpp>
#include <TopoDS_Wire.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepFill_ACRLaw, BRepFill_LocationLaw)

BRepFill_ACRLaw::BRepFill_ACRLaw(const TopoDS_Wire&                         Path,
                                 const occ::handle<GeomFill_LocationGuide>& theLaw)
{
  Init(Path);

  BRepTools_WireExplorer wexp;
  int                    NbEdge = 0;
  for (wexp.Init(myPath); wexp.More(); wexp.Next())
    NbEdge++;

  OrigParam = new (NCollection_HArray1<double>)(0, NbEdge);
  NCollection_Array1<double> Orig(0, NbEdge);
  BRepFill::ComputeACR(Path, Orig);

  int                ipath;
  TopAbs_Orientation Or;

  TopoDS_Edge                    E;
  occ::handle<Geom_Curve>        C;
  occ::handle<GeomAdaptor_Curve> AC;
  double                         First, Last;

  OrigParam->SetValue(0, 0);
  for (ipath = 1; ipath <= NbEdge; ipath++)
    OrigParam->SetValue(ipath, Orig(ipath));

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

      double                              t1 = OrigParam->Value(ipath - 1);
      double                              t2 = OrigParam->Value(ipath);
      occ::handle<GeomFill_LocationGuide> Loc;
      Loc = theLaw;
      Loc->SetOrigine(t1, t2);

      myLaws->SetValue(ipath, Loc->Copy());
      myLaws->ChangeValue(ipath)->SetCurve(AC);
    }
  }
}
