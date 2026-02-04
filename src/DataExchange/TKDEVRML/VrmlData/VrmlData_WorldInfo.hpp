#pragma once


#include <VrmlData_Node.hpp>

/**
 * Data type for WorldInfo node
 */

class VrmlData_WorldInfo : public VrmlData_Node
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty Constructor.
   */
  inline VrmlData_WorldInfo()
      : myTitle(nullptr)
  {
  }

  /**
   * Constructor.
   */
  Standard_EXPORT VrmlData_WorldInfo(const VrmlData_Scene& theScene,
                                     const char*           theName  = nullptr,
                                     const char*           theTitle = nullptr);

  /**
   * Set or modify the title.
   */
  Standard_EXPORT void SetTitle(const char* theString);

  /**
   * Add a string to the list of info strings.
   */
  Standard_EXPORT void AddInfo(const char* theString);

  /**
   * Query the title string.
   */
  inline const char* Title() const { return myTitle; }

  /**
   * Return the iterator of Info strings.
   */
  inline NCollection_List<const char*>::Iterator InfoIterator() const { return myInfo; }

  /**
   * Create a copy of this node.
   * If the parameter is null, a new copied node is created. Otherwise new node
   * is not created, but rather the given one is modified.
   */
  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  /**
   * Read the Node from input stream.
   */
  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  /**
   * Write the Node to the Scene output.
   */
  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

  /**
   * Returns True if the node is default, then it would not be written.
   */
  Standard_EXPORT bool IsDefault() const override;

private:
  // ---------- PRIVATE FIELDS ----------

  const char*                   myTitle;
  NCollection_List<const char*> myInfo;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(VrmlData_WorldInfo, VrmlData_Node)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
