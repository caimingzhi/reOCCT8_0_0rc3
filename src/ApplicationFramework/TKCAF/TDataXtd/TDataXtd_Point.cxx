#include <BRep_Tool.hpp>
#include <BRepBuilderAPI_MakeVertex.hpp>
#include <Geom_CartesianPoint.hpp>
#include <gp_Pnt.hpp>
#include <Standard_Type.hpp>
#include <TDataXtd.hpp>
#include <TDataXtd_Point.hpp>
#include <TDF_Attribute.hpp>
#include <TDF_Label.hpp>
#include <TDF_RelocationTable.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_Tool.hpp>
#include <TopoDS.hpp>
#include <TopoDS_Vertex.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE(TDataXtd_Point, TDataStd_GenericEmpty)

//=================================================================================================

const Standard_GUID& TDataXtd_Point::GetID()
{
  static Standard_GUID TDataXtd_PointID("2a96b60d-ec8b-11d0-bee7-080009dc3333");
  return TDataXtd_PointID;
}

//=================================================================================================

occ::handle<TDataXtd_Point> TDataXtd_Point::Set(const TDF_Label& L)
{
  occ::handle<TDataXtd_Point> A;
  if (!L.FindAttribute(TDataXtd_Point::GetID(), A))
  {
    A = new TDataXtd_Point();
    L.AddAttribute(A);
  }
  return A;
}

//=================================================================================================

occ::handle<TDataXtd_Point> TDataXtd_Point::Set(const TDF_Label& L, const gp_Pnt& P)
{
  occ::handle<TDataXtd_Point> A = Set(L);

  occ::handle<TNaming_NamedShape> aNS;
  if (L.FindAttribute(TNaming_NamedShape::GetID(), aNS))
  {
    if (!aNS->Get().IsNull())
      if (aNS->Get().ShapeType() == TopAbs_VERTEX)
      {
        gp_Pnt anOldPnt = BRep_Tool::Pnt(TopoDS::Vertex(aNS->Get()));
        if (anOldPnt.X() == P.X() && anOldPnt.Y() == P.Y() && anOldPnt.Z() == P.Z())
          return A;
      }
  }

  TNaming_Builder B(L);
  B.Generated(BRepBuilderAPI_MakeVertex(P));
  return A;
}

//=================================================================================================

TDataXtd_Point::TDataXtd_Point() = default;

//=================================================================================================

const Standard_GUID& TDataXtd_Point::ID() const
{
  return GetID();
}

//=================================================================================================

Standard_OStream& TDataXtd_Point::Dump(Standard_OStream& anOS) const
{
  anOS << "Point";
  return anOS;
}
