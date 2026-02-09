#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepOffset_Status.hpp>
#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <GeomAbs_JoinType.hpp>
#include <GeomAbs_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Edge;
class TopoDS_Vertex;

#ifdef Status
  #undef Status
#endif

class BRepOffset_Offset
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffset_Offset();

  Standard_EXPORT BRepOffset_Offset(const TopoDS_Face&     Face,
                                    const double           Offset,
                                    const bool             OffsetOutside = true,
                                    const GeomAbs_JoinType JoinType      = GeomAbs_Arc);

  Standard_EXPORT BRepOffset_Offset(
    const TopoDS_Face&                                                              Face,
    const double                                                                    Offset,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& Created,
    const bool             OffsetOutside = true,
    const GeomAbs_JoinType JoinType      = GeomAbs_Arc);

  Standard_EXPORT BRepOffset_Offset(const TopoDS_Edge&  Path,
                                    const TopoDS_Edge&  Edge1,
                                    const TopoDS_Edge&  Edge2,
                                    const double        Offset,
                                    const bool          Polynomial = false,
                                    const double        Tol        = 1.0e-4,
                                    const GeomAbs_Shape Conti      = GeomAbs_C1);

  Standard_EXPORT BRepOffset_Offset(const TopoDS_Edge&  Path,
                                    const TopoDS_Edge&  Edge1,
                                    const TopoDS_Edge&  Edge2,
                                    const double        Offset,
                                    const TopoDS_Edge&  FirstEdge,
                                    const TopoDS_Edge&  LastEdge,
                                    const bool          Polynomial = false,
                                    const double        Tol        = 1.0e-4,
                                    const GeomAbs_Shape Conti      = GeomAbs_C1);

  Standard_EXPORT BRepOffset_Offset(const TopoDS_Vertex&                  Vertex,
                                    const NCollection_List<TopoDS_Shape>& LEdge,
                                    const double                          Offset,
                                    const bool                            Polynomial = false,
                                    const double                          Tol        = 1.0e-4,
                                    const GeomAbs_Shape                   Conti      = GeomAbs_C1);

  Standard_EXPORT void Init(const TopoDS_Face&     Face,
                            const double           Offset,
                            const bool             OffsetOutside = true,
                            const GeomAbs_JoinType JoinType      = GeomAbs_Arc);

  Standard_EXPORT void Init(
    const TopoDS_Face&                                                              Face,
    const double                                                                    Offset,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>& Created,
    const bool             OffsetOutside = true,
    const GeomAbs_JoinType JoinType      = GeomAbs_Arc);

  Standard_EXPORT void Init(const TopoDS_Edge&  Path,
                            const TopoDS_Edge&  Edge1,
                            const TopoDS_Edge&  Edge2,
                            const double        Offset,
                            const bool          Polynomial = false,
                            const double        Tol        = 1.0e-4,
                            const GeomAbs_Shape Conti      = GeomAbs_C1);

  Standard_EXPORT void Init(const TopoDS_Edge&  Path,
                            const TopoDS_Edge&  Edge1,
                            const TopoDS_Edge&  Edge2,
                            const double        Offset,
                            const TopoDS_Edge&  FirstEdge,
                            const TopoDS_Edge&  LastEdge,
                            const bool          Polynomial = false,
                            const double        Tol        = 1.0e-4,
                            const GeomAbs_Shape Conti      = GeomAbs_C1);

  Standard_EXPORT void Init(const TopoDS_Vertex&                  Vertex,
                            const NCollection_List<TopoDS_Shape>& LEdge,
                            const double                          Offset,
                            const bool                            Polynomial = false,
                            const double                          Tol        = 1.0e-4,
                            const GeomAbs_Shape                   Conti      = GeomAbs_C1);

  Standard_EXPORT void Init(const TopoDS_Edge& Edge, const double Offset);

  const TopoDS_Shape& InitialShape() const;

  Standard_EXPORT const TopoDS_Face& Face() const;

  Standard_EXPORT TopoDS_Shape Generated(const TopoDS_Shape& Shape) const;

  Standard_EXPORT BRepOffset_Status Status() const;

private:
  TopoDS_Shape                                                             myShape;
  BRepOffset_Status                                                        myStatus;
  TopoDS_Face                                                              myFace;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
};

inline const TopoDS_Shape& BRepOffset_Offset::InitialShape() const
{
  return myShape;
}
