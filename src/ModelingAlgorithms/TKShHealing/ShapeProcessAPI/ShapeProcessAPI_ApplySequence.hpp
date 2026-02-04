#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_CString.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <Message_ProgressRange.hpp>

class ShapeProcess_ShapeContext;
class TopoDS_Shape;

//! Applies one of the sequence read from resource file.
class ShapeProcessAPI_ApplySequence
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates an object and loads resource file and sequence of
  //! operators given by their names.
  Standard_EXPORT ShapeProcessAPI_ApplySequence(const char* rscName, const char* seqName = "");

  //! Returns object for managing resource file and sequence of
  //! operators.
  Standard_EXPORT occ::handle<ShapeProcess_ShapeContext>& Context();

  //! Performs sequence of operators stored in myRsc.
  //! If <fillmap> is True adds history "shape-shape" into myMap
  //! for shape and its subshapes until level <until> (included).
  //! If <until> is TopAbs_SHAPE, all the subshapes are considered.
  Standard_EXPORT TopoDS_Shape
    PrepareShape(const TopoDS_Shape&          shape,
                 const bool                   fillmap     = false,
                 const TopAbs_ShapeEnum       until       = TopAbs_SHAPE,
                 const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Clears myMap with accumulated history.
  Standard_EXPORT void ClearMap();

  //! Returns myMap with accumulated history.
  Standard_EXPORT const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
                        Map() const;

  //! Prints result of preparation onto the messenger of the context.
  //! Note that results can be accumulated from previous preparations
  //! it method ClearMap was not called before PrepareShape.
  Standard_EXPORT void PrintPreparationResult() const;

private:
  occ::handle<ShapeProcess_ShapeContext>                                   myContext;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myMap;
  TCollection_AsciiString                                                  mySeq;
};

