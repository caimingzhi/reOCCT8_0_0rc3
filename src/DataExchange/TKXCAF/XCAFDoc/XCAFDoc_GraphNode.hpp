#pragma once


#include <Standard.hpp>

#include <NCollection_Sequence.hpp>
#include <Standard_GUID.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>

class XCAFDoc_GraphNode;
class TDF_Label;
class TDF_RelocationTable;
class TDF_DataSet;

//! This attribute allow user multirelation tree of labels.
//! This GraphNode is experimental Graph that not control looping and redundance.
//! Attribute containing sequence of father's and child's labels.
//! Provide create and work with Graph in XCAFDocument.
class XCAFDoc_GraphNode : public TDF_Attribute
{

public:
  //! class methods working on the node
  //! =================================
  //! Shortcut to search a Graph node attribute with default
  //! GraphID. Returns true if found.
  Standard_EXPORT static bool Find(const TDF_Label& L, occ::handle<XCAFDoc_GraphNode>& G);

  //! Finds or Creates a GraphNode attribute on the label <L>
  //! with the default Graph ID, returned by the method
  //! <GetDefaultGraphID>. Returns the created/found GraphNode
  //! attribute.
  Standard_EXPORT static occ::handle<XCAFDoc_GraphNode> Set(const TDF_Label& L);

  //! Finds or Creates a GraphNode attribute on the label
  //! <L>, with an explicit tree ID. <ExplicitGraphID> is
  //! the ID returned by <TDF_Attribute::ID> method.
  //! Returns the found/created GraphNode attribute.
  Standard_EXPORT static occ::handle<XCAFDoc_GraphNode> Set(const TDF_Label&     L,
                                                            const Standard_GUID& ExplicitGraphID);

  //! returns a default Graph ID. this ID is used by the
  //! <Set> method without explicit tree ID.
  //! Instance methods:
  //! ================
  Standard_EXPORT static const Standard_GUID& GetDefaultGraphID();

  Standard_EXPORT XCAFDoc_GraphNode();

  Standard_EXPORT void SetGraphID(const Standard_GUID& explicitID);

  //! Set GraphNode <F> as father of me and returns index of <F>
  //! in Sequence that containing Fathers GraphNodes.
  //! return index of <F> from GraphNodeSequnece
  Standard_EXPORT int SetFather(const occ::handle<XCAFDoc_GraphNode>& F);

  //! Set GraphNode <Ch> as child of me and returns index of <Ch>
  //! in Sequence that containing Children GraphNodes.
  //! return index of <Ch> from GraphNodeSequnece
  Standard_EXPORT int SetChild(const occ::handle<XCAFDoc_GraphNode>& Ch);

  //! Remove <F> from Fathers GraphNodeSequence.
  //! and remove link between father and child.
  Standard_EXPORT void UnSetFather(const occ::handle<XCAFDoc_GraphNode>& F);

  //! Remove Father GraphNode by index from Fathers GraphNodeSequence.
  //! and remove link between father and child.
  Standard_EXPORT void UnSetFather(const int Findex);

  //! Remove <Ch> from GraphNodeSequence.
  //! and remove link between father and child.
  Standard_EXPORT void UnSetChild(const occ::handle<XCAFDoc_GraphNode>& Ch);

  //! Remove Child GraphNode by index from Children GraphNodeSequence.
  //! and remove link between father and child.
  Standard_EXPORT void UnSetChild(const int Chindex);

  //! Return GraphNode by index from GraphNodeSequence.
  Standard_EXPORT occ::handle<XCAFDoc_GraphNode> GetFather(const int Findex) const;

  //! Return GraphNode by index from GraphNodeSequence.
  Standard_EXPORT occ::handle<XCAFDoc_GraphNode> GetChild(const int Chindex) const;

  //! Return index of <F>, or zero if there is no such Graphnode.
  Standard_EXPORT int FatherIndex(const occ::handle<XCAFDoc_GraphNode>& F) const;

  //! Return index of <Ch>, or zero if there is no such Graphnode.
  Standard_EXPORT int ChildIndex(const occ::handle<XCAFDoc_GraphNode>& Ch) const;

  //! returns TRUE if <me> is father of <Ch>.
  Standard_EXPORT bool IsFather(const occ::handle<XCAFDoc_GraphNode>& Ch) const;

  //! returns TRUE if <me> is child of <F>.
  Standard_EXPORT bool IsChild(const occ::handle<XCAFDoc_GraphNode>& F) const;

  //! return Number of Fathers GraphNodes.
  Standard_EXPORT int NbFathers() const;

  //! return Number of Childrens GraphNodes.
  //! Implementation of Attribute methods:
  //! ===================================
  Standard_EXPORT int NbChildren() const;

  //! Returns the Graph ID (default or explicit one depending
  //! on the Set method used).
  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& aDataSet) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void BeforeForget() override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(XCAFDoc_GraphNode, TDF_Attribute)

private:
  //! remove link between father and child.
  Standard_EXPORT void UnSetFatherlink(const occ::handle<XCAFDoc_GraphNode>& F);

  //! remove link between father and child.
  Standard_EXPORT void UnSetChildlink(const occ::handle<XCAFDoc_GraphNode>& C);

  NCollection_Sequence<occ::handle<XCAFDoc_GraphNode>> myFathers;
  NCollection_Sequence<occ::handle<XCAFDoc_GraphNode>> myChildren;
  Standard_GUID                                        myGraphID;
};

