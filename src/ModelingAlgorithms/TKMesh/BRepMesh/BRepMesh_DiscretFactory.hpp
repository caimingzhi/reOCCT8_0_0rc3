#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Macro.hpp>

class TopoDS_Shape;
class BRepMesh_DiscretRoot;

typedef int (*BRepMesh_PluginEntryType)(const TopoDS_Shape&    theShape,
                                        const double           theLinDeflection,
                                        const double           theAngDeflection,
                                        BRepMesh_DiscretRoot*& theMeshAlgoInstance);

#include <BRepMesh_FactoryError.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Map.hpp>
#include <OSD_Function.hpp>
#include <NCollection_DataMap.hpp>
#include <BRepMesh_DiscretRoot.hpp>

class TopoDS_Shape;

class BRepMesh_DiscretFactory
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static BRepMesh_DiscretFactory& Get();

  const NCollection_Map<TCollection_AsciiString>& Names() const { return myNames; }

  bool SetDefaultName(const TCollection_AsciiString& theName)
  {
    return SetDefault(theName, myFunctionName);
  }

  const TCollection_AsciiString& DefaultName() const { return myDefaultName; }

  bool SetFunctionName(const TCollection_AsciiString& theFuncName)
  {
    return SetDefault(myDefaultName, theFuncName);
  }

  const TCollection_AsciiString& FunctionName() const { return myFunctionName; }

  BRepMesh_FactoryError ErrorStatus() const { return myErrorStatus; }

  Standard_EXPORT bool SetDefault(const TCollection_AsciiString& theName,
                                  const TCollection_AsciiString& theFuncName = "DISCRETALGO");

  Standard_EXPORT occ::handle<BRepMesh_DiscretRoot> Discret(const TopoDS_Shape& theShape,
                                                            const double        theLinDeflection,
                                                            const double        theAngDeflection);

protected:
  Standard_EXPORT BRepMesh_DiscretFactory();

  Standard_EXPORT virtual ~BRepMesh_DiscretFactory();

  Standard_EXPORT void clear();

  BRepMesh_PluginEntryType                                   myPluginEntry;
  BRepMesh_FactoryError                                      myErrorStatus;
  NCollection_Map<TCollection_AsciiString>                   myNames;
  TCollection_AsciiString                                    myDefaultName;
  TCollection_AsciiString                                    myFunctionName;
  NCollection_DataMap<TCollection_AsciiString, OSD_Function> myFactoryMethods;
};
