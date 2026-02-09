#pragma once

#include <VrmlData_Node.hpp>

class VrmlData_WorldInfo : public VrmlData_Node
{
public:
  inline VrmlData_WorldInfo()
      : myTitle(nullptr)
  {
  }

  Standard_EXPORT VrmlData_WorldInfo(const VrmlData_Scene& theScene,
                                     const char*           theName  = nullptr,
                                     const char*           theTitle = nullptr);

  Standard_EXPORT void SetTitle(const char* theString);

  Standard_EXPORT void AddInfo(const char* theString);

  inline const char* Title() const { return myTitle; }

  inline NCollection_List<const char*>::Iterator InfoIterator() const { return myInfo; }

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

  Standard_EXPORT bool IsDefault() const override;

private:
  const char*                   myTitle;
  NCollection_List<const char*> myInfo;

public:
  DEFINE_STANDARD_RTTIEXT(VrmlData_WorldInfo, VrmlData_Node)
};
