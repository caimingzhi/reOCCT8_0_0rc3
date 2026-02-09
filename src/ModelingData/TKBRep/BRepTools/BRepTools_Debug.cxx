#include <BRepTools.hpp>
#include <Standard_ErrorHandler.hpp>
#include <Standard_Failure.hpp>
#include <TopTools_LocationSet.hpp>

const char* BRepTools_Write(const char* theFileStr, void* theShapePtr)
{
  if (theFileStr == nullptr || theShapePtr == nullptr)
  {
    return "Error: name or shape is null";
  }
  try
  {
    OCC_CATCH_SIGNALS
    if (BRepTools::Write(*(TopoDS_Shape*)theShapePtr, theFileStr))
      return theFileStr;
    else
      return "Error: write failed";
  }
  catch (Standard_Failure const& anException)
  {
    return anException.what();
  }
}

const char* BRepTools_Dump(void* theShapePtr)
{
  if (theShapePtr == nullptr)
  {
    return "Error: name or shape is null";
  }
  try
  {
    OCC_CATCH_SIGNALS

    std::cout << "\n\n";
    BRepTools::Dump(*(TopoDS_Shape*)theShapePtr, std::cout);
    std::cout << std::endl;

    return "Shape dumped to std::cout";
  }
  catch (Standard_Failure const& anException)
  {
    return anException.what();
  }
}

const char* BRepTools_DumpLoc(void* theLocationPtr)
{
  if (theLocationPtr == nullptr)
  {
    return "Error: name or shape is null";
  }
  try
  {
    OCC_CATCH_SIGNALS

    std::cout << "\n\n";
    TopTools_LocationSet LS;
    LS.Add(*(TopLoc_Location*)theLocationPtr);
    LS.Dump(std::cout);
    std::cout << std::endl;

    return "Location dumped to std::cout";
  }
  catch (Standard_Failure const& anException)
  {
    return anException.what();
  }
}

#ifndef _MSC_VER

const char* BRepTools_Write(const char* theFileNameStr, const TopoDS_Shape& theShape)
{
  return BRepTools_Write(theFileNameStr, (void*)&theShape);
}

const char* BRepTools_Dump(const TopoDS_Shape& theShape)
{
  return BRepTools_Dump((void*)&theShape);
}

const char* BRepTools_DumpLoc(const TopoDS_Shape& theShape)
{
  return BRepTools_DumpLoc((void*)&theShape);
}

#endif
