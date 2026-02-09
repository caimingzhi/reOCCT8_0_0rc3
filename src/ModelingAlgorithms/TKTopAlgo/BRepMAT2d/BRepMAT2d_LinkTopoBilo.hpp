#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <MAT_BasicElt.hpp>
#include <NCollection_Sequence.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Integer.hpp>
class BRepMAT2d_Explorer;
class BRepMAT2d_BisectingLocus;
class MAT_BasicElt;
class TopoDS_Wire;

class BRepMAT2d_LinkTopoBilo
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepMAT2d_LinkTopoBilo();

  Standard_EXPORT BRepMAT2d_LinkTopoBilo(const BRepMAT2d_Explorer&       Explo,
                                         const BRepMAT2d_BisectingLocus& BiLo);

  Standard_EXPORT void Perform(const BRepMAT2d_Explorer&       Explo,
                               const BRepMAT2d_BisectingLocus& BiLo);

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  Standard_EXPORT bool More();

  Standard_EXPORT void Next();

  Standard_EXPORT occ::handle<MAT_BasicElt> Value() const;

  Standard_EXPORT TopoDS_Shape GeneratingShape(const occ::handle<MAT_BasicElt>& aBE) const;

private:
  Standard_EXPORT void LinkToWire(const TopoDS_Wire&              W,
                                  const BRepMAT2d_Explorer&       Explo,
                                  const int                       IndexContour,
                                  const BRepMAT2d_BisectingLocus& BiLo);

  NCollection_DataMap<TopoDS_Shape,
                      NCollection_Sequence<occ::handle<MAT_BasicElt>>,
                      TopTools_ShapeMapHasher>
                                                               myMap;
  NCollection_DataMap<occ::handle<MAT_BasicElt>, TopoDS_Shape> myBEShape;
  TopoDS_Shape                                                 myKey;
  int                                                          current;
  bool                                                         isEmpty;
};
