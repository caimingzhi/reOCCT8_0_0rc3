#pragma once

#include <Message_ProgressRange.hpp>

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
class BRepAlgo_AsDes;
class BRepAlgo_Image;
class BRepOffset_Analyse;

class BRepOffset_MakeLoops
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepOffset_MakeLoops();

  Standard_EXPORT void Build(const NCollection_List<TopoDS_Shape>& LF,
                             const occ::handle<BRepAlgo_AsDes>&    AsDes,
                             BRepAlgo_Image&                       Image,
                             BRepAlgo_Image&                       theImageVV,
                             const Message_ProgressRange&          theRange);

  Standard_EXPORT void BuildOnContext(const NCollection_List<TopoDS_Shape>& LContext,
                                      const BRepOffset_Analyse&             Analyse,
                                      const occ::handle<BRepAlgo_AsDes>&    AsDes,
                                      BRepAlgo_Image&                       Image,
                                      const bool                            InSide,
                                      const Message_ProgressRange&          theRange);

  Standard_EXPORT void BuildFaces(const NCollection_List<TopoDS_Shape>& LF,
                                  const occ::handle<BRepAlgo_AsDes>&    AsDes,
                                  BRepAlgo_Image&                       Image,
                                  const Message_ProgressRange&          theRange);

private:
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myVerVerMap;
};
