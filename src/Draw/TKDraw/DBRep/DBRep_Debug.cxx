#include <DBRep.hpp>
#include <Standard_Failure.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_Vector.hpp>
#include <BRep_Builder.hpp>

// This file defines global functions not declared in any public header,
// intended for use from debugger prompt (Command Window in Visual Studio)

//! Save shape identified by pointer
Standard_EXPORT const char* DBRep_Set(const char* theNameStr, void* theShapePtr)
{
  if (theNameStr == nullptr || theShapePtr == nullptr)
  {
    return "Error: name or shape is null";
  }
  try
  {
    DBRep::Set(theNameStr, *(TopoDS_Shape*)theShapePtr);
    return theNameStr;
  }
  catch (Standard_Failure const& anException)
  {
    return anException.what();
  }
}

//=======================================================================
// function : fromContainer
// purpose  : static function to copy shapes from container into compound
//=======================================================================
template <class T>
static bool fromContainer(void* theContainer, TopoDS_Compound& theShape)
{
  try
  {
    T* pContainer = (T*)theContainer;
    for (typename T::Iterator it(*pContainer); it.More(); it.Next())
    {
      BRep_Builder().Add(theShape, it.Value());
    }
    return true;
  }
  catch (Standard_Failure const&)
  {
    return false;
  }
}

//=======================================================================
// function : DBRep_SetComp
// purpose  : make compound from the given container of shapes
//=======================================================================
Standard_EXPORT const char* DBRep_SetComp(const char* theNameStr, void* theListPtr)
{
  if (theNameStr == nullptr || theListPtr == nullptr)
  {
    return "Error: name or list of shapes is null";
  }

  TopoDS_Compound aC;
  BRep_Builder().MakeCompound(aC);

  if (fromContainer<NCollection_List<TopoDS_Shape>>(theListPtr, aC)
      || fromContainer<NCollection_Map<TopoDS_Shape, TopTools_ShapeMapHasher>>(theListPtr, aC)
      || fromContainer<NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher>>(theListPtr,
                                                                                      aC)
      || fromContainer<NCollection_Sequence<TopoDS_Shape>>(theListPtr, aC)
      || fromContainer<NCollection_Array1<TopoDS_Shape>>(theListPtr, aC)
      || fromContainer<NCollection_Vector<TopoDS_Shape>>(theListPtr, aC))
  {
    DBRep::Set(theNameStr, aC);
    return theNameStr;
  }
  else
  {
    return "Error: Invalid type";
  }
}

// MSVC debugger cannot deal correctly with functions whose argunments
// have non-standard types. Here we define alternative to the above functions
// with good types with the hope that GDB on Linux or other debugger could
// work with them (DBX could, on SUN Solaris).
#ifndef _MSC_VER

const char* DBRep_Set(char* theName, const TopoDS_Shape& theShape)
{
  return DBRep_Set(theName, (void*)&theShape);
}

#endif /* _MSC_VER */

// old function, perhaps too dangerous to be used
/*
void DBRep_Get(char* name, TopoDS_Shape& S)
{
  char n[255];
  strcpy(n,name);
  const char* cs = (const char*)n;
  S = DBRep::Get(cs);
  if (*name == '.')
    std::cout << "Name : " << n << std::endl;
}
*/
