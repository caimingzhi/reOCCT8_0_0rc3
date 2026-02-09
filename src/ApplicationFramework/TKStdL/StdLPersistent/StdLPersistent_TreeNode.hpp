#pragma once

#include <StdObjMgt_Attribute.hpp>

#include <TDataStd_TreeNode.hpp>
#include <Standard_GUID.hpp>

class StdLPersistent_TreeNode : public StdObjMgt_Attribute<TDataStd_TreeNode>::Static
{
public:
  Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;

  Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

  Standard_EXPORT void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override;

  const char* PName() const override { return "PDataStd_TreeNode"; }

  Standard_EXPORT occ::handle<TDF_Attribute> CreateAttribute() override;

  Standard_EXPORT void ImportAttribute() override;

private:
  struct dynamic : public Standard_Transient
  {
    occ::handle<StdLPersistent_TreeNode> First;
    Standard_GUID                        TreeID;
  };

  Handle(dynamic)                      myDynamicData;
  occ::handle<StdLPersistent_TreeNode> myNext;
};
