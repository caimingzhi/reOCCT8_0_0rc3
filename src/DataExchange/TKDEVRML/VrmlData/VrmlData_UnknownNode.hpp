#pragma once


#include <VrmlData_Node.hpp>
#include <TCollection_AsciiString.hpp>

/**
 * Definition of UnknownNode -- placeholder for node types that
 * are not processed now.
 */

class VrmlData_UnknownNode : public VrmlData_Node
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty Constructor.
   */
  inline VrmlData_UnknownNode() = default;

  /**
   * Constructor.
   */
  inline VrmlData_UnknownNode(const VrmlData_Scene& theScene,
                              const char*           theName  = nullptr,
                              const char*           theTitle = nullptr)
      : VrmlData_Node(theScene, theName)
  {
    if (theTitle)
      myTitle = (const char*)theTitle;
  }

  /**
   * Read the unknown node, till the last closing brace of it.
   */
  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  /**
   * Query the title of the unknown node.
   */
  inline const TCollection_AsciiString& GetTitle() const { return myTitle; }

  /**
   * Check if the Node is non-writeable -- always returns true.
   */
  Standard_EXPORT bool IsDefault() const override;

private:
  // ---------- PRIVATE FIELDS ----------

  TCollection_AsciiString myTitle;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_UnknownNode, VrmlData_Node)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
