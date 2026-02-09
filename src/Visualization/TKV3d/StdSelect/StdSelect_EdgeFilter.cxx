#include <BRepAdaptor_Curve.hpp>
#include <Standard_Type.hpp>
#include <StdSelect_BRepOwner.hpp>
#include <StdSelect_EdgeFilter.hpp>
#include <TopAbs.hpp>
#include <TopoDS.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StdSelect_EdgeFilter, SelectMgr_Filter)

StdSelect_EdgeFilter ::StdSelect_EdgeFilter(const StdSelect_TypeOfEdge Edge)
    : mytype(Edge)
{
}

void StdSelect_EdgeFilter ::SetType(const StdSelect_TypeOfEdge aNewType)
{
  mytype = aNewType;
}

StdSelect_TypeOfEdge StdSelect_EdgeFilter::Type() const
{
  return mytype;
}

bool StdSelect_EdgeFilter::IsOk(const occ::handle<SelectMgr_EntityOwner>& EO) const
{
  occ::handle<StdSelect_BRepOwner> aBO(occ::down_cast<StdSelect_BRepOwner>(EO));
  if (aBO.IsNull())
    return false;

  const TopoDS_Shape& sh = aBO->Shape();
  if (sh.ShapeType() != TopAbs_EDGE)
    return false;

  switch (mytype)
  {
    case StdSelect_AnyEdge:
      return true;
    case StdSelect_Line:
    {
      BRepAdaptor_Curve curv(TopoDS::Edge(sh));
      return (curv.GetType() == GeomAbs_Line);
    }
    break;
    case StdSelect_Circle:
      BRepAdaptor_Curve curv(TopoDS::Edge(sh));
      return (curv.GetType() == GeomAbs_Circle);
  }

  return false;
}

bool StdSelect_EdgeFilter::ActsOn(const TopAbs_ShapeEnum aStandardMode) const
{
  return aStandardMode == TopAbs_EDGE;
}
