#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
class TopoDS_Face;
class TopoDS_Shell;

//! Rebuilds connectivity between faces in shell
class ShapeFix_FaceConnect
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeFix_FaceConnect();

  Standard_EXPORT bool Add(const TopoDS_Face& aFirst, const TopoDS_Face& aSecond);

  Standard_EXPORT TopoDS_Shell Build(const TopoDS_Shell& shell,
                                     const double        sewtoler,
                                     const double        fixtoler);

  //! Clears internal data structure
  Standard_EXPORT void Clear();

private:
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myConnected;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myOriFreeEdges;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myResFreeEdges;
  NCollection_DataMap<TopoDS_Shape, NCollection_List<TopoDS_Shape>, TopTools_ShapeMapHasher>
    myResSharEdges;
};

