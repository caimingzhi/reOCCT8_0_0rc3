#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Standard_Boolean.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>
#include <Draw_Interpretor.hpp>
class TDataStd_Real;
class TFunction_Function;
class TDataStd_Integer;
class TDataStd_Name;
class TNaming_NamedShape;
class gp_Ax1;
class TDataStd_UAttribute;
class TopoDS_Shape;
class BRepBuilderAPI_MakeShape;
class TNaming_Builder;
class TDF_Label;
class BRepAlgoAPI_BooleanOperation;
class TDF_Data;
class TCollection_AsciiString;

class DNaming
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<TDataStd_Real> GetReal(
    const occ::handle<TFunction_Function>& theFunction,
    const int                              thePosition);

  Standard_EXPORT static occ::handle<TDataStd_Integer> GetInteger(
    const occ::handle<TFunction_Function>& theFunction,
    const int                              thePosition);

  Standard_EXPORT static occ::handle<TDataStd_Name> GetString(
    const occ::handle<TFunction_Function>& theFunction,
    const int                              thePosition);

  Standard_EXPORT static bool ComputeAxis(const occ::handle<TNaming_NamedShape>& theNS,
                                          gp_Ax1&                                theAx1);

  Standard_EXPORT static occ::handle<TNaming_NamedShape> GetFunctionResult(
    const occ::handle<TFunction_Function>& theFunction);

  Standard_EXPORT static occ::handle<TDataStd_UAttribute> GetObjectArg(
    const occ::handle<TFunction_Function>& theFunction,
    const int                              thePosition);

  Standard_EXPORT static void SetObjectArg(const occ::handle<TFunction_Function>&  theFunction,
                                           const int                               thePosition,
                                           const occ::handle<TDataStd_UAttribute>& theNewValue);

  Standard_EXPORT static occ::handle<TNaming_NamedShape> GetObjectValue(
    const occ::handle<TDataStd_UAttribute>& theObject);

  Standard_EXPORT static occ::handle<TFunction_Function> GetLastFunction(
    const occ::handle<TDataStd_UAttribute>& theObject);

  Standard_EXPORT static occ::handle<TFunction_Function> GetFirstFunction(
    const occ::handle<TDataStd_UAttribute>& theObject);

  Standard_EXPORT static occ::handle<TFunction_Function> GetPrevFunction(
    const occ::handle<TFunction_Function>& theFunction);

  Standard_EXPORT static occ::handle<TDataStd_UAttribute> GetObjectFromFunction(
    const occ::handle<TFunction_Function>& theFunction);

  Standard_EXPORT static bool IsAttachment(const occ::handle<TDataStd_UAttribute>& theObject);

  Standard_EXPORT static occ::handle<TNaming_NamedShape> GetAttachmentsContext(
    const occ::handle<TDataStd_UAttribute>& theObject);

  Standard_EXPORT static bool ComputeSweepDir(const TopoDS_Shape& theShape, gp_Ax1& theAxis);

  Standard_EXPORT static void LoadAndOrientModifiedShapes(
    BRepBuilderAPI_MakeShape& MakeShape,
    const TopoDS_Shape&       ShapeIn,
    const TopAbs_ShapeEnum    GeneratedFrom,
    TNaming_Builder&          Builder,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
      SubShapesOfResult);

  Standard_EXPORT static void LoadAndOrientGeneratedShapes(
    BRepBuilderAPI_MakeShape& MakeShape,
    const TopoDS_Shape&       ShapeIn,
    const TopAbs_ShapeEnum    GeneratedFrom,
    TNaming_Builder&          Builder,
    const NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher>&
      SubShapesOfResult);

  Standard_EXPORT static void LoadDeletedShapes(BRepBuilderAPI_MakeShape& MakeShape,
                                                const TopoDS_Shape&       ShapeIn,
                                                const TopAbs_ShapeEnum    KindOfDeletedShape,
                                                TNaming_Builder&          Builder);

  Standard_EXPORT static void LoadResult(const TDF_Label&              theLabel,
                                         BRepAlgoAPI_BooleanOperation& MS);

  Standard_EXPORT static TopoDS_Shape CurrentShape(const char*                  ShapeEntry,
                                                   const occ::handle<TDF_Data>& Data);

  Standard_EXPORT static void GetShape(const char*                     ShapeEntry,
                                       const occ::handle<TDF_Data>&    Data,
                                       NCollection_List<TopoDS_Shape>& Shapes);

  //! theStatus = 0  Not  found,
  //! theStatus = 1  One  shape,
  //! theStatus = 2  More than one shape.
  Standard_EXPORT static TCollection_AsciiString GetEntry(const TopoDS_Shape&          Shape,
                                                          const occ::handle<TDF_Data>& Data,
                                                          int&                         theStatus);

  //! Loads the Shape to DF
  Standard_EXPORT static void LoadImportedShape(const TDF_Label&    theResultLabel,
                                                const TopoDS_Shape& theShape);

  //! Reloads sub-shapes of the Shape to DF
  Standard_EXPORT static void LoadPrime(const TDF_Label&    theResultLabel,
                                        const TopoDS_Shape& theShape);

  Standard_EXPORT static void AllCommands(Draw_Interpretor& DI);

  //! commands relatives to NamedShape
  Standard_EXPORT static void BasicCommands(Draw_Interpretor& DI);

  Standard_EXPORT static void ToolsCommands(Draw_Interpretor& DI);

  //! commands relatives to Naming
  Standard_EXPORT static void SelectionCommands(Draw_Interpretor& DI);

  //! commands for testing Naming
  Standard_EXPORT static void ModelingCommands(Draw_Interpretor& DI);
};

