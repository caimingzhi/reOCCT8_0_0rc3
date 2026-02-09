#pragma once

#include <Standard.hpp>
#include <Standard_NullObject.hpp>
#include <Standard_Type.hpp>
#include <XCAFDoc_AssemblyIterator.hpp>
#include <XCAFDoc_AssemblyGraph.hpp>

class TDocStd_Document;
class XCAFDoc_ShapeTool;

class XCAFDoc_AssemblyTool
{
public:
  template <typename Func>
  static void Traverse(XCAFDoc_AssemblyIterator theIterator, Func theFunc)
  {
    for (; theIterator.More(); theIterator.Next())
    {
      if (!theFunc(theIterator.Current()))
        break;
    }
  }

  template <typename Func, typename Filter>
  static void Traverse(const occ::handle<XCAFDoc_AssemblyGraph>& theGraph,
                       Filter                                    theFilter,
                       Func                                      theFunc,
                       const int                                 theNode = 1)
  {
    Standard_NullObject_Raise_if(theGraph.IsNull(), "Null assembly graph!");

    for (XCAFDoc_AssemblyGraph::Iterator anIt(theGraph, theNode); anIt.More(); anIt.Next())
    {
      const int aN = anIt.Current();
      if (theFilter(theGraph, aN))
      {
        if (!theFunc(theGraph, aN))
          break;
      }
    }
  }
};
