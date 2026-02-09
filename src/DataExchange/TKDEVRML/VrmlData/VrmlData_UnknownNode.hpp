#pragma once

#include <VrmlData_Node.hpp>
#include <TCollection_AsciiString.hpp>

class VrmlData_UnknownNode : public VrmlData_Node
{
public:
  inline VrmlData_UnknownNode() = default;

  inline VrmlData_UnknownNode(const VrmlData_Scene& theScene,
                              const char*           theName  = nullptr,
                              const char*           theTitle = nullptr)
      : VrmlData_Node(theScene, theName)
  {
    if (theTitle)
      myTitle = (const char*)theTitle;
  }

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  inline const TCollection_AsciiString& GetTitle() const { return myTitle; }

  Standard_EXPORT bool IsDefault() const override;

private:
  TCollection_AsciiString myTitle;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_UnknownNode, VrmlData_Node)
};
