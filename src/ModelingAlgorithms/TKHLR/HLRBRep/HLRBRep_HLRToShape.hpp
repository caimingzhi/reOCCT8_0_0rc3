#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <HLRBRep_TypeOfResultingEdge.hpp>
class HLRBRep_Algo;
class TopoDS_Shape;
class HLRBRep_Data;
class HLRBRep_EdgeData;

class HLRBRep_HLRToShape
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT HLRBRep_HLRToShape(const occ::handle<HLRBRep_Algo>& A);

  TopoDS_Shape VCompound();

  TopoDS_Shape VCompound(const TopoDS_Shape& S);

  TopoDS_Shape Rg1LineVCompound();

  TopoDS_Shape Rg1LineVCompound(const TopoDS_Shape& S);

  TopoDS_Shape RgNLineVCompound();

  TopoDS_Shape RgNLineVCompound(const TopoDS_Shape& S);

  TopoDS_Shape OutLineVCompound();

  TopoDS_Shape OutLineVCompound3d();

  TopoDS_Shape OutLineVCompound(const TopoDS_Shape& S);

  TopoDS_Shape IsoLineVCompound();

  TopoDS_Shape IsoLineVCompound(const TopoDS_Shape& S);

  TopoDS_Shape HCompound();

  TopoDS_Shape HCompound(const TopoDS_Shape& S);

  TopoDS_Shape Rg1LineHCompound();

  TopoDS_Shape Rg1LineHCompound(const TopoDS_Shape& S);

  TopoDS_Shape RgNLineHCompound();

  TopoDS_Shape RgNLineHCompound(const TopoDS_Shape& S);

  TopoDS_Shape OutLineHCompound();

  TopoDS_Shape OutLineHCompound(const TopoDS_Shape& S);

  TopoDS_Shape IsoLineHCompound();

  TopoDS_Shape IsoLineHCompound(const TopoDS_Shape& S);

  TopoDS_Shape CompoundOfEdges(const HLRBRep_TypeOfResultingEdge type,
                               const bool                        visible,
                               const bool                        In3d);

  TopoDS_Shape CompoundOfEdges(const TopoDS_Shape&               S,
                               const HLRBRep_TypeOfResultingEdge type,
                               const bool                        visible,
                               const bool                        In3d);

private:
  Standard_EXPORT TopoDS_Shape InternalCompound(const int           typ,
                                                const bool          visible,
                                                const TopoDS_Shape& S,
                                                const bool          In3d = false);

  Standard_EXPORT void DrawFace(const bool                 visible,
                                const int                  typ,
                                const int                  iface,
                                occ::handle<HLRBRep_Data>& DS,
                                TopoDS_Shape&              Result,
                                bool&                      added,
                                const bool                 In3d = false) const;

  Standard_EXPORT void DrawEdge(const bool        visible,
                                const bool        inFace,
                                const int         typ,
                                HLRBRep_EdgeData& ed,
                                TopoDS_Shape&     Result,
                                bool&             added,
                                const bool        In3d = false) const;

  occ::handle<HLRBRep_Algo> myAlgo;
};

#include <TopoDS_Shape.hpp>

inline TopoDS_Shape HLRBRep_HLRToShape::VCompound()
{
  return InternalCompound(5, true, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_HLRToShape::VCompound(const TopoDS_Shape& S)
{
  return InternalCompound(5, true, S);
}

inline TopoDS_Shape HLRBRep_HLRToShape::Rg1LineVCompound()
{
  return InternalCompound(3, true, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_HLRToShape::Rg1LineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(3, true, S);
}

inline TopoDS_Shape HLRBRep_HLRToShape::RgNLineVCompound()
{
  return InternalCompound(4, true, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_HLRToShape::RgNLineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(4, true, S);
}

inline TopoDS_Shape HLRBRep_HLRToShape::OutLineVCompound()
{
  return InternalCompound(2, true, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_HLRToShape::OutLineVCompound3d()
{
  return InternalCompound(2, true, TopoDS_Shape(), true);
}

inline TopoDS_Shape HLRBRep_HLRToShape::OutLineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(2, true, S);
}

inline TopoDS_Shape HLRBRep_HLRToShape::IsoLineVCompound()
{
  return InternalCompound(1, true, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_HLRToShape::IsoLineVCompound(const TopoDS_Shape& S)
{
  return InternalCompound(1, true, S);
}

inline TopoDS_Shape HLRBRep_HLRToShape::HCompound()
{
  return InternalCompound(5, false, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_HLRToShape::HCompound(const TopoDS_Shape& S)
{
  return InternalCompound(5, false, S);
}

inline TopoDS_Shape HLRBRep_HLRToShape::Rg1LineHCompound()
{
  return InternalCompound(3, false, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_HLRToShape::Rg1LineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(3, false, S);
}

inline TopoDS_Shape HLRBRep_HLRToShape::RgNLineHCompound()
{
  return InternalCompound(4, false, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_HLRToShape::RgNLineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(4, false, S);
}

inline TopoDS_Shape HLRBRep_HLRToShape::OutLineHCompound()
{
  return InternalCompound(2, false, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_HLRToShape::OutLineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(2, false, S);
}

inline TopoDS_Shape HLRBRep_HLRToShape::IsoLineHCompound()
{
  return InternalCompound(1, false, TopoDS_Shape());
}

inline TopoDS_Shape HLRBRep_HLRToShape::IsoLineHCompound(const TopoDS_Shape& S)
{
  return InternalCompound(1, false, S);
}

inline TopoDS_Shape HLRBRep_HLRToShape::CompoundOfEdges(const HLRBRep_TypeOfResultingEdge type,
                                                        const bool                        visible,
                                                        const bool                        In3d)
{
  return InternalCompound(type, visible, TopoDS_Shape(), In3d);
}

inline TopoDS_Shape HLRBRep_HLRToShape::CompoundOfEdges(const TopoDS_Shape&               S,
                                                        const HLRBRep_TypeOfResultingEdge type,
                                                        const bool                        visible,
                                                        const bool                        In3d)
{
  return InternalCompound(type, visible, S, In3d);
}
