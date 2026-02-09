#include <BRepFill_DraftLaw.hpp>
#include <GeomFill_LocationLaw.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <GeomFill_LocationDraft.hpp>
#include <gp_Mat.hpp>
#include <gp_Vec.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Wire.hpp>

IMPLEMENT_STANDARD_RTTIEXT(BRepFill_DraftLaw, BRepFill_Edge3DLaw)

static void ToG0(const gp_Mat& M1, const gp_Mat& M2, gp_Mat& T)
{
  T = M2.Inverted();
  T *= M1;
}

BRepFill_DraftLaw::BRepFill_DraftLaw(const TopoDS_Wire&                         Path,
                                     const occ::handle<GeomFill_LocationDraft>& Law)
    : BRepFill_Edge3DLaw(Path, Law)
{
}

void BRepFill_DraftLaw::CleanLaw(const double TolAngular)
{
  double First, Last;
  int    ipath;
  gp_Mat Trsf, M1, M2;
  gp_Vec V, T1, T2, N1, N2;

  myLaws->Value(1)->GetDomain(First, Last);

  for (ipath = 2; ipath <= myLaws->Length(); ipath++)
  {
    myLaws->Value(ipath - 1)->D0(Last, M1, V);
    myLaws->Value(ipath)->GetDomain(First, Last);
    myLaws->Value(ipath)->D0(First, M2, V);
    T1.SetXYZ(M1.Column(3));
    T2.SetXYZ(M2.Column(3));
    N1.SetXYZ(M1.Column(1));
    N2.SetXYZ(M2.Column(1));
    if (N1.IsParallel(N2, TolAngular))
    {
      ToG0(M1, M2, Trsf);
      myLaws->Value(ipath)->SetTrsf(Trsf);
    }
  }
}
