#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Compound.hpp>
#include <TopoDS_Shape.hpp>

class ShapeFix_FreeBounds
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeFix_FreeBounds();

  Standard_EXPORT ShapeFix_FreeBounds(const TopoDS_Shape& shape,
                                      const double        sewtoler,
                                      const double        closetoler,
                                      const bool          splitclosed,
                                      const bool          splitopen);

  Standard_EXPORT ShapeFix_FreeBounds(const TopoDS_Shape& shape,
                                      const double        closetoler,
                                      const bool          splitclosed,
                                      const bool          splitopen);

  const TopoDS_Compound& GetClosedWires() const;

  const TopoDS_Compound& GetOpenWires() const;

  const TopoDS_Shape& GetShape() const;

private:
  Standard_EXPORT bool Perform();

  TopoDS_Compound myWires;
  TopoDS_Compound myEdges;
  TopoDS_Shape    myShape;
  bool            myShared;
  double          mySewToler;
  double          myCloseToler;
  bool            mySplitClosed;
  bool            mySplitOpen;
};

inline const TopoDS_Compound& ShapeFix_FreeBounds::GetClosedWires() const
{
  return myWires;
}

inline const TopoDS_Compound& ShapeFix_FreeBounds::GetOpenWires() const
{
  return myEdges;
}

inline const TopoDS_Shape& ShapeFix_FreeBounds::GetShape() const
{
  return myShape;
}
