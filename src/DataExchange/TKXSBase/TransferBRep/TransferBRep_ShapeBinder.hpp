#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TransferBRep_BinderOfShape.hpp>
#include <TopAbs_ShapeEnum.hpp>
class TopoDS_Shape;
class TopoDS_Vertex;
class TopoDS_Edge;
class TopoDS_Wire;
class TopoDS_Face;
class TopoDS_Shell;
class TopoDS_Solid;
class TopoDS_CompSolid;
class TopoDS_Compound;

//! A ShapeBinder is a BinderOfShape with some additional services
//! to cast the Result under various kinds of Shapes
class TransferBRep_ShapeBinder : public TransferBRep_BinderOfShape
{

public:
  //! Creates an empty ShapeBinder
  Standard_EXPORT TransferBRep_ShapeBinder();

  //! Creates a ShapeBinder with a result
  Standard_EXPORT TransferBRep_ShapeBinder(const TopoDS_Shape& res);

  //! Returns the Type of the Shape Result (under TopAbs form)
  Standard_EXPORT TopAbs_ShapeEnum ShapeType() const;

  Standard_EXPORT TopoDS_Vertex Vertex() const;

  Standard_EXPORT TopoDS_Edge Edge() const;

  Standard_EXPORT TopoDS_Wire Wire() const;

  Standard_EXPORT TopoDS_Face Face() const;

  Standard_EXPORT TopoDS_Shell Shell() const;

  Standard_EXPORT TopoDS_Solid Solid() const;

  Standard_EXPORT TopoDS_CompSolid CompSolid() const;

  Standard_EXPORT TopoDS_Compound Compound() const;

  DEFINE_STANDARD_RTTIEXT(TransferBRep_ShapeBinder, TransferBRep_BinderOfShape)
};
