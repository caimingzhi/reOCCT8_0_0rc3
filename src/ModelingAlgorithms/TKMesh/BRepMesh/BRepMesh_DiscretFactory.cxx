#include <BRepMesh_DiscretFactory.hpp>

#include <OSD_SharedLibrary.hpp>
#include <OSD_Function.hpp>
#include <BRepMesh_IncrementalMesh.hpp>
#include <BRepMesh_DiscretRoot.hpp>

namespace
{

  static TCollection_AsciiString THE_FAST_DISCRET_MESH("FastDiscret");

  static void MakeLibName(const TCollection_AsciiString& theDefaultName,
                          TCollection_AsciiString&       theLibName)
  {
    theLibName = "";
#ifndef _WIN32
    theLibName += "lib";
#endif
    theLibName += theDefaultName;
#ifdef _WIN32
    theLibName += ".dll";
#elif __APPLE__
    theLibName += ".dylib";
#elif defined(HPUX) || defined(_hpux)
    theLibName += ".sl";
#else
    theLibName += ".so";
#endif
  }
} // namespace

BRepMesh_DiscretFactory::BRepMesh_DiscretFactory()
    : myPluginEntry(nullptr),
      myErrorStatus(BRepMesh_FE_NOERROR),
      myDefaultName(THE_FAST_DISCRET_MESH),
      myFunctionName("DISCRETALGO")
{

  myNames.Add(THE_FAST_DISCRET_MESH);
}

BRepMesh_DiscretFactory::~BRepMesh_DiscretFactory()
{
  clear();
}

void BRepMesh_DiscretFactory::clear() {}

BRepMesh_DiscretFactory& BRepMesh_DiscretFactory::Get()
{

  static BRepMesh_DiscretFactory THE_GLOBAL_FACTORY;
  return THE_GLOBAL_FACTORY;
}

bool BRepMesh_DiscretFactory::SetDefault(const TCollection_AsciiString& theName,
                                         const TCollection_AsciiString& theFuncName)
{
  myErrorStatus = BRepMesh_FE_NOERROR;
  if (theName == THE_FAST_DISCRET_MESH)
  {

    myPluginEntry  = nullptr;
    myDefaultName  = theName;
    myFunctionName = theFuncName;
    return true;
  }
  else if (theName == myDefaultName && theFuncName == myFunctionName)
  {

    return myPluginEntry != nullptr;
  }

  TCollection_AsciiString  aMeshAlgoId = theName + "_" + theFuncName;
  BRepMesh_PluginEntryType aFunc       = nullptr;
  if (myFactoryMethods.IsBound(aMeshAlgoId))
  {

    aFunc = (BRepMesh_PluginEntryType)myFactoryMethods(aMeshAlgoId);
  }
  else
  {
    TCollection_AsciiString aLibName;
    MakeLibName(theName, aLibName);
    OSD_SharedLibrary aSL(aLibName.ToCString());
    if (!aSL.DlOpen(OSD_RTLD_LAZY))
    {

      myErrorStatus = BRepMesh_FE_LIBRARYNOTFOUND;
      return false;
    }

    aFunc = (BRepMesh_PluginEntryType)aSL.DlSymb(theFuncName.ToCString());
    myFactoryMethods.Bind(aMeshAlgoId, (OSD_Function)aFunc);
  }

  if (aFunc == nullptr)
  {

    myErrorStatus = BRepMesh_FE_FUNCTIONNOTFOUND;
    return false;
  }

  BRepMesh_DiscretRoot* anInstancePtr = nullptr;
  int                   anErr         = aFunc(TopoDS_Shape(), 0.001, 0.1, anInstancePtr);
  if (anErr != 0 || anInstancePtr == nullptr)
  {

    myErrorStatus = BRepMesh_FE_CANNOTCREATEALGO;
    delete anInstancePtr;
    return false;
  }
  delete anInstancePtr;

  myPluginEntry  = aFunc;
  myDefaultName  = theName;
  myFunctionName = theFuncName;
  myNames.Add(theName);
  return true;
}

occ::handle<BRepMesh_DiscretRoot> BRepMesh_DiscretFactory::Discret(const TopoDS_Shape& theShape,
                                                                   const double theDeflection,
                                                                   const double theAngle)
{
  occ::handle<BRepMesh_DiscretRoot> aDiscretRoot;
  BRepMesh_DiscretRoot*             anInstancePtr = nullptr;
  if (myPluginEntry != nullptr)
  {

    int anErr = myPluginEntry(theShape, theDeflection, theAngle, anInstancePtr);

    if (anErr != 0 || anInstancePtr == nullptr)
    {

      myErrorStatus = BRepMesh_FE_CANNOTCREATEALGO;
      return aDiscretRoot;
    }
  }
  else
  {

    BRepMesh_IncrementalMesh::Discret(theShape, theDeflection, theAngle, anInstancePtr);
  }

  aDiscretRoot = anInstancePtr;

  return aDiscretRoot;
}
