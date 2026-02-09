#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
class TopoDS_Wire;
class TopoDS_Edge;
class TopoDS_Shape;
class TopoDS_Face;

class ShapeExtend_WireData : public Standard_Transient
{

public:
  Standard_EXPORT ShapeExtend_WireData();

  Standard_EXPORT ShapeExtend_WireData(const TopoDS_Wire& wire,
                                       const bool         chained         = true,
                                       const bool         theManifoldMode = true);

  Standard_EXPORT void Init(const occ::handle<ShapeExtend_WireData>& other);

  Standard_EXPORT bool Init(const TopoDS_Wire& wire,
                            const bool         chained         = true,
                            const bool         theManifoldMode = true);

  Standard_EXPORT void Clear();

  Standard_EXPORT void ComputeSeams(const bool enforce = true);

  Standard_EXPORT void SetLast(const int num);

  Standard_EXPORT void SetDegeneratedLast();

  Standard_EXPORT void Add(const TopoDS_Edge& edge, const int atnum = 0);

  Standard_EXPORT void Add(const TopoDS_Wire& wire, const int atnum = 0);

  Standard_EXPORT void Add(const occ::handle<ShapeExtend_WireData>& wire, const int atnum = 0);

  Standard_EXPORT void Add(const TopoDS_Shape& shape, const int atnum = 0);

  Standard_EXPORT void AddOriented(const TopoDS_Edge& edge, const int mode);

  Standard_EXPORT void AddOriented(const TopoDS_Wire& wire, const int mode);

  Standard_EXPORT void AddOriented(const TopoDS_Shape& shape, const int mode);

  Standard_EXPORT void Remove(const int num = 0);

  Standard_EXPORT void Set(const TopoDS_Edge& edge, const int num = 0);

  Standard_EXPORT void Reverse();

  Standard_EXPORT void Reverse(const TopoDS_Face& face);

  Standard_EXPORT int NbEdges() const;

  Standard_EXPORT int NbNonManifoldEdges() const;

  Standard_EXPORT TopoDS_Edge NonmanifoldEdge(const int num) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<TopoDS_Shape>> NonmanifoldEdges() const;

  Standard_EXPORT bool& ManifoldMode();

  Standard_EXPORT TopoDS_Edge Edge(const int num) const;

  Standard_EXPORT int Index(const TopoDS_Edge& edge);

  Standard_EXPORT bool IsSeam(const int num);

  Standard_EXPORT TopoDS_Wire Wire() const;

  Standard_EXPORT TopoDS_Wire WireAPIMake() const;

  DEFINE_STANDARD_RTTIEXT(ShapeExtend_WireData, Standard_Transient)

private:
  occ::handle<NCollection_HSequence<TopoDS_Shape>> myEdges;
  occ::handle<NCollection_HSequence<TopoDS_Shape>> myNonmanifoldEdges;
  occ::handle<NCollection_HSequence<int>>          mySeams;
  int                                              mySeamF;
  int                                              mySeamR;
  bool                                             myManifoldMode;
};
