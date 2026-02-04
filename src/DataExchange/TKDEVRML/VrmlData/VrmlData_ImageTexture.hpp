#pragma once


#include <VrmlData_Texture.hpp>

/**
 *  Implementation of the ImageTexture node
 */
class VrmlData_ImageTexture : public VrmlData_Texture
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty constructor
   */
  inline VrmlData_ImageTexture() = default;

  /**
   * Constructor
   */
  Standard_EXPORT VrmlData_ImageTexture(const VrmlData_Scene& theScene,
                                        const char*           theName,
                                        const char*           theURL  = nullptr,
                                        const bool            theRepS = false,
                                        const bool            theRepT = false);

  /**
   * Query the associated URL.
   */
  inline const NCollection_List<TCollection_AsciiString>& URL() const { return myURL; }

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
   * Write the Node to output stream.
   */
  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

private:
  // ---------- PRIVATE FIELDS ----------

  NCollection_List<TCollection_AsciiString> myURL;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_ImageTexture, VrmlData_Texture)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
