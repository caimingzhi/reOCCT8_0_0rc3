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

class XCAFDoc_GraphNode : public TDF_Attribute
{

public:
  Standard_EXPORT static bool Find(const TDF_Label& L, occ::handle<XCAFDoc_GraphNode>& G);

  Standard_EXPORT static occ::handle<XCAFDoc_GraphNode> Set(const TDF_Label& L);

  Standard_EXPORT static occ::handle<XCAFDoc_GraphNode> Set(const TDF_Label&     L,
                                                            const Standard_GUID& ExplicitGraphID);

  Standard_EXPORT static const Standard_GUID& GetDefaultGraphID();

  Standard_EXPORT XCAFDoc_GraphNode();

  Standard_EXPORT void SetGraphID(const Standard_GUID& explicitID);

  Standard_EXPORT int SetFather(const occ::handle<XCAFDoc_GraphNode>& F);

  Standard_EXPORT int SetChild(const occ::handle<XCAFDoc_GraphNode>& Ch);

  Standard_EXPORT void UnSetFather(const occ::handle<XCAFDoc_GraphNode>& F);

  Standard_EXPORT void UnSetFather(const int Findex);

  Standard_EXPORT void UnSetChild(const occ::handle<XCAFDoc_GraphNode>& Ch);

  Standard_EXPORT void UnSetChild(const int Chindex);

  Standard_EXPORT occ::handle<XCAFDoc_GraphNode> GetFather(const int Findex) const;

  Standard_EXPORT occ::handle<XCAFDoc_GraphNode> GetChild(const int Chindex) const;

  Standard_EXPORT int FatherIndex(const occ::handle<XCAFDoc_GraphNode>& F) const;

  Standard_EXPORT int ChildIndex(const occ::handle<XCAFDoc_GraphNode>& Ch) const;

  Standard_EXPORT bool IsFather(const occ::handle<XCAFDoc_GraphNode>& Ch) const;

  Standard_EXPORT bool IsChild(const occ::handle<XCAFDoc_GraphNode>& F) const;

  Standard_EXPORT int NbFathers() const;

  Standard_EXPORT int NbChildren() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void References(const occ::handle<TDF_DataSet>& aDataSet) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  Standard_EXPORT void BeforeForget() override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(XCAFDoc_GraphNode, TDF_Attribute)

private:
  Standard_EXPORT void UnSetFatherlink(const occ::handle<XCAFDoc_GraphNode>& F);

  Standard_EXPORT void UnSetChildlink(const occ::handle<XCAFDoc_GraphNode>& C);

  NCollection_Sequence<occ::handle<XCAFDoc_GraphNode>> myFathers;
  NCollection_Sequence<occ::handle<XCAFDoc_GraphNode>> myChildren;
  Standard_GUID                                        myGraphID;
};
