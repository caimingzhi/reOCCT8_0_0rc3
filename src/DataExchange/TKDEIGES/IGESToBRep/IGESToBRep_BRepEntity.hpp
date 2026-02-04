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

//! Provides methods to transfer BRep entities
//! ( VertexList 502, EdgeList 504, Loop 508,
//! Face 510, Shell 514, ManifoldSolid 186)
//! from IGES to CASCADE.
class IGESToBRep_BRepEntity : public IGESToBRep_CurveAndSurface
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a tool BRepEntity ready to run, with
  //! epsilons set to 1.E-04, TheModeTopo to True, the
  //! optimization of the continuity to False.
  Standard_EXPORT IGESToBRep_BRepEntity();

  //! Creates a tool BRepEntity ready to run and sets its
  //! fields as CS's.
  Standard_EXPORT IGESToBRep_BRepEntity(const IGESToBRep_CurveAndSurface& CS);

  //! Creates a tool BRepEntity ready to run.
  Standard_EXPORT IGESToBRep_BRepEntity(const double eps,
                                        const double epsGeom,
                                        const double epsCoeff,
                                        const bool   mode,
                                        const bool   modeapprox,
                                        const bool   optimized);

  //! Transfer the BRepEntity" : Face, Shell or ManifoldSolid.
  Standard_EXPORT TopoDS_Shape
    TransferBRepEntity(const occ::handle<IGESData_IGESEntity>& start,
                       const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Transfer the entity number "index" of the VertexList "start"
  Standard_EXPORT TopoDS_Vertex TransferVertex(const occ::handle<IGESSolid_VertexList>& start,
                                               const int                                index);

  //! Transfer the entity number "index" of the EdgeList "start".
  Standard_EXPORT TopoDS_Shape TransferEdge(const occ::handle<IGESSolid_EdgeList>& start,
                                            const int                              index);

  //! Transfer the Loop Entity
  Standard_EXPORT TopoDS_Shape TransferLoop(const occ::handle<IGESSolid_Loop>& start,
                                            const TopoDS_Face&                 Face,
                                            const gp_Trsf2d&                   trans,
                                            const double                       uFact);

  //! Transfer the Face Entity
  Standard_EXPORT TopoDS_Shape TransferFace(const occ::handle<IGESSolid_Face>& start);

  //! Transfer the Shell Entity
  Standard_EXPORT TopoDS_Shape
    TransferShell(const occ::handle<IGESSolid_Shell>& start,
                  const Message_ProgressRange&        theProgress = Message_ProgressRange());

  //! Transfer the ManifoldSolid Entity
  Standard_EXPORT TopoDS_Shape
    TransferManifoldSolid(const occ::handle<IGESSolid_ManifoldSolid>& start,
                          const Message_ProgressRange& theProgress = Message_ProgressRange());
};

