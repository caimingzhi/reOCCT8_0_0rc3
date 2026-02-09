#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <IGESToBRep_CurveAndSurface.hpp>
#include <Standard_Integer.hpp>
#include <Message_ProgressRange.hpp>

class TopoDS_Shape;
class IGESData_IGESEntity;
class TopoDS_Vertex;
class IGESSolid_VertexList;
class IGESSolid_EdgeList;
class IGESSolid_Loop;
class TopoDS_Face;
class gp_Trsf2d;
class IGESSolid_Face;
class IGESSolid_Shell;
class IGESSolid_ManifoldSolid;

class IGESToBRep_BRepEntity : public IGESToBRep_CurveAndSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IGESToBRep_BRepEntity();

  Standard_EXPORT IGESToBRep_BRepEntity(const IGESToBRep_CurveAndSurface& CS);

  Standard_EXPORT IGESToBRep_BRepEntity(const double eps,
                                        const double epsGeom,
                                        const double epsCoeff,
                                        const bool   mode,
                                        const bool   modeapprox,
                                        const bool   optimized);

  Standard_EXPORT TopoDS_Shape
    TransferBRepEntity(const occ::handle<IGESData_IGESEntity>& start,
                       const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT TopoDS_Vertex TransferVertex(const occ::handle<IGESSolid_VertexList>& start,
                                               const int                                index);

  Standard_EXPORT TopoDS_Shape TransferEdge(const occ::handle<IGESSolid_EdgeList>& start,
                                            const int                              index);

  Standard_EXPORT TopoDS_Shape TransferLoop(const occ::handle<IGESSolid_Loop>& start,
                                            const TopoDS_Face&                 Face,
                                            const gp_Trsf2d&                   trans,
                                            const double                       uFact);

  Standard_EXPORT TopoDS_Shape TransferFace(const occ::handle<IGESSolid_Face>& start);

  Standard_EXPORT TopoDS_Shape
    TransferShell(const occ::handle<IGESSolid_Shell>& start,
                  const Message_ProgressRange&        theProgress = Message_ProgressRange());

  Standard_EXPORT TopoDS_Shape
    TransferManifoldSolid(const occ::handle<IGESSolid_ManifoldSolid>& start,
                          const Message_ProgressRange& theProgress = Message_ProgressRange());
};
