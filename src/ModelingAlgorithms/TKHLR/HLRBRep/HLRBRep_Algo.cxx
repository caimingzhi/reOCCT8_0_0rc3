#define No_Standard_OutOfRange

#include <HLRBRep_Algo.hpp>
#include <HLRBRep_ShapeBounds.hpp>
#include <HLRTopoBRep_OutLiner.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <TopoDS_Shape.hpp>

IMPLEMENT_STANDARD_RTTIEXT(HLRBRep_Algo, HLRBRep_InternalAlgo)

HLRBRep_Algo::HLRBRep_Algo() = default;

HLRBRep_Algo::HLRBRep_Algo(const occ::handle<HLRBRep_Algo>& A)
    : HLRBRep_InternalAlgo(A)
{
}

void HLRBRep_Algo::Add(const TopoDS_Shape&                    S,
                       const occ::handle<Standard_Transient>& SData,
                       const int                              nbIso)
{
  Load(new HLRTopoBRep_OutLiner(S), SData, nbIso);
}

void HLRBRep_Algo::Add(const TopoDS_Shape& S, const int nbIso)
{
  Load(new HLRTopoBRep_OutLiner(S), nbIso);
}

int HLRBRep_Algo::Index(const TopoDS_Shape& S)
{
  int n = NbShapes();

  for (int i = 1; i <= n; i++)
  {
    if (ShapeBounds(i).Shape()->OriginalShape() == S)
      return i;
    if (ShapeBounds(i).Shape()->OutLinedShape() == S)
      return i;
  }

  return 0;
}

void HLRBRep_Algo::OutLinedShapeNullify()
{
  int n = NbShapes();

  for (int i = 1; i <= n; i++)
  {
    ShapeBounds(i).Shape()->OutLinedShape(TopoDS_Shape());
    ShapeBounds(i).Shape()->DataStructure().Clear();
  }
}
