#pragma once


#include <GeomAbs_Shape.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Wire;
class TopoDS_Edge;
class TopoDS_Face;
class TopoDS_Shape;

//! The BRepAlgo class provides the following tools for:
//! - Checking validity of the shape;
//! - Concatenation of the edges of the wire.
class BRepAlgo
{
public:
  //! this method makes a wire whose edges are C1 from
  //! a Wire whose edges could be G1. It removes a vertex
  //! between G1 edges.
  //! Option can be G1 or C1.
  Standard_EXPORT static TopoDS_Wire ConcatenateWire(const TopoDS_Wire&  Wire,
                                                     const GeomAbs_Shape Option,
                                                     const double        AngularTolerance = 1.0e-4);

  //! this method makes an edge from a wire.
  //! Junction points between edges of wire may be sharp,
  //! resulting curve of the resulting edge may be C0.
  Standard_EXPORT static TopoDS_Edge ConcatenateWireC0(const TopoDS_Wire& Wire);

  //! Method of wire conversion, calls BRepAlgo_Approx internally.
  //! @param theWire
  //!   Input Wire object.
  //! @param theAngleTolerance
  //!   Angle (in radians) defining the continuity of the wire: if two vectors
  //!   differ by less than this angle, the result will be smooth (zero angle of
  //!   tangent lines between curve elements).
  //! @return
  //!   The new TopoDS_Wire object consisting of edges each representing an arc
  //!   of circle or a linear segment. The accuracy of conversion is defined
  //!   as the maximal tolerance of edges in theWire.
  static Standard_EXPORT TopoDS_Wire ConvertWire(const TopoDS_Wire& theWire,
                                                 const double       theAngleTolerance,
                                                 const TopoDS_Face& theFace);

  //! Method of face conversion. The API corresponds to the method ConvertWire.
  //! This is a shortcut for calling ConvertWire() for each wire in theFace.
  static Standard_EXPORT TopoDS_Face ConvertFace(const TopoDS_Face& theFace,
                                                 const double       theAngleTolerance);

  //! Checks if the shape is "correct". If not, returns
  //! <false>, else returns <true>.
  Standard_EXPORT static bool IsValid(const TopoDS_Shape& S);

  //! Checks if the Generated and Modified Faces from
  //! the shapes <arguments> in the shape <result> are
  //! "correct". The args may be empty, then all faces
  //! will be checked.
  //! If <Closed> is True, only closed shape are valid.
  //! If <GeomCtrl> is False the geometry of new
  //! vertices and edges are not verified and the
  //! auto-intersection of new wires are not searched.
  Standard_EXPORT static bool IsValid(const NCollection_List<TopoDS_Shape>& theArgs,
                                      const TopoDS_Shape&                   theResult,
                                      const bool                            closedSolid = false,
                                      const bool                            GeomCtrl    = true);

  //! Checks if the shape is "correct".
  //! If not, returns FALSE, else returns TRUE.
  //! This method differs from the previous one in the fact that no geometric controls
  //! (intersection of wires, pcurve validity) are performed.
  Standard_EXPORT static bool IsTopologicallyValid(const TopoDS_Shape& S);
};

