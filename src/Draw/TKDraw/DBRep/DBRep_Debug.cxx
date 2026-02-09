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

#ifndef _MSC_VER

const char* DBRep_Set(char* theName, const TopoDS_Shape& theShape)
{
  return DBRep_Set(theName, (void*)&theShape);
}

#endif
