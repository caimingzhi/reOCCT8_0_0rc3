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

//! This class is used to model construction geometry.
//! The specific geometric construction of the
//! attribute is defined by an element of the
//! enumeration TDataXtd_GeometryEnum.
//! This attribute may also be used to qualify underlying
//! geometry of the associated NamedShape. for
//! Constructuion element by example.
class TDataXtd_Geometry : public TDF_Attribute
{

public:
  //! API class methods
  //! =================
  //! Finds, or creates, a Geometry attribute defined by the label label.
  //! The default type of geometry is the value
  //! ANY_GEOM of the enumeration TDataXtd_GeometryEnum.
  //! To specify another value of this enumeration, use
  //! the function SetType.
  Standard_EXPORT static occ::handle<TDataXtd_Geometry> Set(const TDF_Label& label);

  //! Returns the label L used to define the type of
  //! geometric construction for the geometry attribute.
  Standard_EXPORT static TDataXtd_GeometryEnum Type(const TDF_Label& L);

  //! Returns the topological attribute S used to define
  //! the type of geometric construction for the geometry attribute.
  Standard_EXPORT static TDataXtd_GeometryEnum Type(const occ::handle<TNaming_NamedShape>& S);

  //! Returns the point attribute defined by the label L and the point G.
  Standard_EXPORT static bool Point(const TDF_Label& L, gp_Pnt& G);

  //! Returns the point attribute defined by the topological attribute S and the point G.
  Standard_EXPORT static bool Point(const occ::handle<TNaming_NamedShape>& S, gp_Pnt& G);

  //! Returns the axis attribute defined by the label L and the axis G.
  Standard_EXPORT static bool Axis(const TDF_Label& L, gp_Ax1& G);

  //! Returns the axis attribute defined by the topological attribute S and the axis G.
  Standard_EXPORT static bool Axis(const occ::handle<TNaming_NamedShape>& S, gp_Ax1& G);

  //! Returns the line attribute defined by the label L and the line G.
  Standard_EXPORT static bool Line(const TDF_Label& L, gp_Lin& G);

  //! Returns the line attribute defined by the topological attribute S and the line G.
  Standard_EXPORT static bool Line(const occ::handle<TNaming_NamedShape>& S, gp_Lin& G);

  //! Returns the circle attribute defined by the label L and the circle G.
  Standard_EXPORT static bool Circle(const TDF_Label& L, gp_Circ& G);

  //! Returns the circle attribute defined by the topological attribute S and the circle G.
  Standard_EXPORT static bool Circle(const occ::handle<TNaming_NamedShape>& S, gp_Circ& G);

  //! Returns the ellipse attribute defined by the label L and the ellipse G.
  Standard_EXPORT static bool Ellipse(const TDF_Label& L, gp_Elips& G);

  //! Returns the ellipse attribute defined by the
  //! topological attribute S and the ellipse G.
  Standard_EXPORT static bool Ellipse(const occ::handle<TNaming_NamedShape>& S, gp_Elips& G);

  //! Returns the plane attribute defined by the label L and the plane G.
  Standard_EXPORT static bool Plane(const TDF_Label& L, gp_Pln& G);

  //! Returns the plane attribute defined by the
  //! topological attribute S and the plane G.
  Standard_EXPORT static bool Plane(const occ::handle<TNaming_NamedShape>& S, gp_Pln& G);

  //! Returns the cylinder attribute defined by the label L and the cylinder G.
  Standard_EXPORT static bool Cylinder(const TDF_Label& L, gp_Cylinder& G);

  //! Returns the cylinder attribute defined by the
  //! topological attribute S and the cylinder G.
  Standard_EXPORT static bool Cylinder(const occ::handle<TNaming_NamedShape>& S, gp_Cylinder& G);

  //! Returns the GUID for geometry attributes.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! This and the next methods are used to retrieve underlying geometry of the NamedShape,
  //! even if no Geometry Attribute is associated.
  //! if not found or not compliant geometry return False.
  Standard_EXPORT TDataXtd_Geometry();

  //! Returns the type of geometric construction T of this attribute.
  //! T will be a value of the enumeration TDataXtd_GeometryEnum.
  Standard_EXPORT void SetType(const TDataXtd_GeometryEnum T);

  //! Returns the type of geometric construction.
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
