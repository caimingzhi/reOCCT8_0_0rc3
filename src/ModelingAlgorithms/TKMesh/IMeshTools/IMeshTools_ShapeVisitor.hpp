#pragma once


#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

class TopoDS_Face;
class TopoDS_Edge;

//! Interface class for shape visitor.
class IMeshTools_ShapeVisitor : public Standard_Transient
{
public:
  //! Destructor.
  ~IMeshTools_ShapeVisitor() override = default;

  //! Handles TopoDS_Face object.
  Standard_EXPORT virtual void Visit(const TopoDS_Face& theFace) = 0;

  //! Handles TopoDS_Edge object.
  Standard_EXPORT virtual void Visit(const TopoDS_Edge& theEdge) = 0;

  DEFINE_STANDARD_RTTIEXT(IMeshTools_ShapeVisitor, Standard_Transient)

protected:
  //! Constructor.
  IMeshTools_ShapeVisitor() {}
};

