#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TDataXtd_GeometryEnum.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class TNaming_NamedShape;
class gp_Pnt;
class gp_Ax1;
class gp_Lin;
class gp_Circ;
class gp_Elips;
class gp_Pln;
class gp_Cylinder;
class Standard_GUID;
class TDF_RelocationTable;

class TDataXtd_Geometry : public TDF_Attribute
{

public:
  Standard_EXPORT static occ::handle<TDataXtd_Geometry> Set(const TDF_Label& label);

  Standard_EXPORT static TDataXtd_GeometryEnum Type(const TDF_Label& L);

  Standard_EXPORT static TDataXtd_GeometryEnum Type(const occ::handle<TNaming_NamedShape>& S);

  Standard_EXPORT static bool Point(const TDF_Label& L, gp_Pnt& G);

  Standard_EXPORT static bool Point(const occ::handle<TNaming_NamedShape>& S, gp_Pnt& G);

  Standard_EXPORT static bool Axis(const TDF_Label& L, gp_Ax1& G);

  Standard_EXPORT static bool Axis(const occ::handle<TNaming_NamedShape>& S, gp_Ax1& G);

  Standard_EXPORT static bool Line(const TDF_Label& L, gp_Lin& G);

  Standard_EXPORT static bool Line(const occ::handle<TNaming_NamedShape>& S, gp_Lin& G);

  Standard_EXPORT static bool Circle(const TDF_Label& L, gp_Circ& G);

  Standard_EXPORT static bool Circle(const occ::handle<TNaming_NamedShape>& S, gp_Circ& G);

  Standard_EXPORT static bool Ellipse(const TDF_Label& L, gp_Elips& G);

  Standard_EXPORT static bool Ellipse(const occ::handle<TNaming_NamedShape>& S, gp_Elips& G);

  Standard_EXPORT static bool Plane(const TDF_Label& L, gp_Pln& G);

  Standard_EXPORT static bool Plane(const occ::handle<TNaming_NamedShape>& S, gp_Pln& G);

  Standard_EXPORT static bool Cylinder(const TDF_Label& L, gp_Cylinder& G);

  Standard_EXPORT static bool Cylinder(const occ::handle<TNaming_NamedShape>& S, gp_Cylinder& G);

  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TDataXtd_Geometry();

  Standard_EXPORT void SetType(const TDataXtd_GeometryEnum T);

  Standard_EXPORT TDataXtd_GeometryEnum GetType() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_STANDARD_RTTIEXT(TDataXtd_Geometry, TDF_Attribute)

private:
  TDataXtd_GeometryEnum myType;
};
