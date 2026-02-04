#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Wire;

//! Builds all the faces limited with a set of non
//! jointing and planars wires.
//! if <ControlOrientation> is false The Wires must have
//! correct orientations. Sinon orientation des wires
//! de telle sorte que les faces ne soient pas infinies
//! et qu'elles soient disjointes.
class BRepAlgo_FaceRestrictor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepAlgo_FaceRestrictor();

  //! the surface of <F> will be the surface of each new
  //! faces built.
  //! <Proj> is used to update pcurves on edges if necessary.
  //! See Add().
  Standard_EXPORT void Init(const TopoDS_Face& F,
                            const bool         Proj               = false,
                            const bool         ControlOrientation = false);

  //! Add the wire <W> to the set of wires.
  //!
  //! Warning:
  //! The Wires must be closed.
  //!
  //! The edges of <W> can be modified if they don't have
  //! pcurves on the surface <S> of <F>. In this case
  //! if <Proj> is false the first pcurve of the edge
  //! is positioned on <S>.
  //! if <Proj> is True, the Pcurve On <S> is the
  //! projection of the curve 3d on <F>.
  Standard_EXPORT void Add(TopoDS_Wire& W);

  //! Removes all the Wires
  Standard_EXPORT void Clear();

  //! Evaluate all the faces limited by the set of Wires.
  Standard_EXPORT void Perform();

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT TopoDS_Face Current() const;

private:
  //! Evaluate all the faces limited by the set of Wires.
  Standard_EXPORT void PerformWithCorrection();

  bool                           myDone;
  bool                           modeProj;
  TopoDS_Face                    myFace;
  NCollection_List<TopoDS_Shape> wires;
  NCollection_List<TopoDS_Shape> faces;
  bool                           myCorrection;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    keyIsIn;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    keyContains;
};

