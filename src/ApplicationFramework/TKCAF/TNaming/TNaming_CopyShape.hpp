#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_IndexedDataMap.hpp>
class TopoDS_Shape;
class TNaming_TranslateTool;
class TopLoc_Location;

class TNaming_CopyShape
{
public:
  DEFINE_STANDARD_ALLOC

  //! Makes copy a set of shape(s), using the aMap
  Standard_EXPORT static void CopyTool(
    const TopoDS_Shape& aShape,
    NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>&
                  aMap,
    TopoDS_Shape& aResult);

  //! Translates a Transient shape(s) to Transient
  Standard_EXPORT static void Translate(
    const TopoDS_Shape& aShape,
    NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>&
                                              aMap,
    TopoDS_Shape&                             aResult,
    const occ::handle<TNaming_TranslateTool>& TrTool);

  //! Translates a Topological Location to an other Top.
  //! Location
  Standard_EXPORT static TopLoc_Location Translate(
    const TopLoc_Location& L,
    NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Standard_Transient>>&
      aMap);
};

