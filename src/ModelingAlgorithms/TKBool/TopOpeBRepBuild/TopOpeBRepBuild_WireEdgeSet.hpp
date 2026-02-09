#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <TopOpeBRepBuild_ShapeSet.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopAbs_Orientation.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
class TopoDS_Shape;
class gp_Pnt2d;
class gp_Vec2d;
class TopoDS_Edge;
class TCollection_AsciiString;

class TopOpeBRepBuild_WireEdgeSet : public TopOpeBRepBuild_ShapeSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_WireEdgeSet(const TopoDS_Shape& F, void* const Addr = nullptr);

  Standard_EXPORT const TopoDS_Face& Face() const;

  Standard_EXPORT void AddShape(const TopoDS_Shape& S) override;

  Standard_EXPORT void AddStartElement(const TopoDS_Shape& S) override;

  Standard_EXPORT void AddElement(const TopoDS_Shape& S) override;

  Standard_EXPORT void InitNeighbours(const TopoDS_Shape& E) override;

  Standard_EXPORT void FindNeighbours() override;

  Standard_EXPORT const NCollection_List<TopoDS_Shape>& MakeNeighboursList(
    const TopoDS_Shape& E,
    const TopoDS_Shape& V) override;

  Standard_EXPORT static void IsUVISO(const TopoDS_Edge& E,
                                      const TopoDS_Face& F,
                                      bool&              uiso,
                                      bool&              viso);

  Standard_EXPORT void DumpSS() override;

  Standard_EXPORT TCollection_AsciiString
    SName(const TopoDS_Shape&            S,
          const TCollection_AsciiString& sb = "",
          const TCollection_AsciiString& sa = "") const override;

  Standard_EXPORT TCollection_AsciiString
    SName(const NCollection_List<TopoDS_Shape>& S,
          const TCollection_AsciiString&        sb = "",
          const TCollection_AsciiString&        sa = "") const override;

  Standard_EXPORT TCollection_AsciiString
    SNameori(const TopoDS_Shape&            S,
             const TCollection_AsciiString& sb = "",
             const TCollection_AsciiString& sa = "") const override;

  Standard_EXPORT TCollection_AsciiString
    SNameori(const NCollection_List<TopoDS_Shape>& S,
             const TCollection_AsciiString&        sb = "",
             const TCollection_AsciiString&        sa = "") const override;

private:
  Standard_EXPORT bool VertexConnectsEdges(const TopoDS_Shape& V,
                                           const TopoDS_Shape& E1,
                                           const TopoDS_Shape& E2,
                                           TopAbs_Orientation& O1,
                                           TopAbs_Orientation& O2) const;

  Standard_EXPORT bool VertexConnectsEdgesClosing(const TopoDS_Shape& V,
                                                  const TopoDS_Shape& E1,
                                                  const TopoDS_Shape& E2) const;

  Standard_EXPORT int NbClosingShapes(const NCollection_List<TopoDS_Shape>& L) const;

  Standard_EXPORT void LocalD1(const TopoDS_Shape& F,
                               const TopoDS_Shape& E,
                               const TopoDS_Shape& V,
                               gp_Pnt2d&           p2,
                               gp_Vec2d&           v2) const;

  Standard_EXPORT bool IsClosed(const TopoDS_Shape& E) const;

  Standard_EXPORT bool IsUClosed(const TopoDS_Shape& E) const;

  Standard_EXPORT bool IsVClosed(const TopoDS_Shape& E) const;

  Standard_EXPORT TCollection_AsciiString SNameVEE(const TopoDS_Shape& V,
                                                   const TopoDS_Shape& E1,
                                                   const TopoDS_Shape& E2) const;

  Standard_EXPORT TCollection_AsciiString SNameVEL(const TopoDS_Shape&                   V,
                                                   const TopoDS_Shape&                   E,
                                                   const NCollection_List<TopoDS_Shape>& L) const;

  TopoDS_Face myFace;
};
