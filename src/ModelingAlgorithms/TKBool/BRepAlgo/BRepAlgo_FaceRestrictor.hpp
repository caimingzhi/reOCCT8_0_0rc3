#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Face.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Wire;

class BRepAlgo_FaceRestrictor
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepAlgo_FaceRestrictor();

  Standard_EXPORT void Init(const TopoDS_Face& F,
                            const bool         Proj               = false,
                            const bool         ControlOrientation = false);

  Standard_EXPORT void Add(TopoDS_Wire& W);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Perform();

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT TopoDS_Face Current() const;

private:
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
