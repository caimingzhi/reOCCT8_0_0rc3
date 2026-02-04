#pragma once


#include <Standard.hpp>
#include <Standard_NullObject.hpp>
#include <Standard_Type.hpp>
#include <XCAFDoc_AssemblyIterator.hpp>
#include <XCAFDoc_AssemblyGraph.hpp>

class TDocStd_Document;
class XCAFDoc_ShapeTool;

//! Provides generic methods for traversing assembly tree and graph
class XCAFDoc_AssemblyTool
{
public:
  //! \brief Generic method for traversing assembly tree.
  //! Performs in-depth traversing of the assembly tree and calls
  //! user defined function for each assembly tree node.
  //! User function takes single argument of XCAFDoc_AssemblyItemId type
  //! and returns true/false to continue/break.
  //! ~~~~~{.cpp}
  //! bool Print(const XCAFDoc_AssemblyItemId& theItem)
  //! {
  //!   std::cout << theItem.ToString() << std::endl;
  //!   return true;
  //! }
  //! ~~~~~
  //! \param[in]  theIterator - starting position in the assembly tree.
  //! \param[in]  theFunc     - user function called for each assembly tree node.
  template <typename Func>
  static void Traverse(XCAFDoc_AssemblyIterator theIterator, Func theFunc)
  {
    for (; theIterator.More(); theIterator.Next())
    {
      if (!theFunc(theIterator.Current()))
        break;
    }
  }

  //! \brief Generic method for traversing assembly graph.
  //! Performs in-depth traversing of the assembly graph beginning from root nodes
  //! and calls user defined function for each assembly graph node accepted
  //! by the user defined filtering function. Filtering function takes
  //! the assembly graph passed for traversing, current graph node ID
  //! and returns true/false to accept/reject node.
  //! ~~~~~{.cpp}
  //! bool AcceptPartOnly(const occ::handle<XCAFDoc_AssemblyGraph>& theGraph,
  //!                                 const int               theNode)
  //! {
  //!   return (theGraph->GetNodeType(theNode) == XCAFDoc_AssemblyGraph::NodeType_Part);
  //! }
  //! ~~~~~
  //! User function theFunc takes the assembly graph passed for traversing, current
  //! graph node ID and returns true/false to continue/break.
  //! \param[in]  theGraph  - assembly graph.
  //! \param[in]  theFilter - user filtering function called for each assembly graph node.
  //! \param[in]  theFunc   - user function called for accepted assembly graph node.
  //! \param[in]  theNode   - starting positive one-based graph node ID.
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

