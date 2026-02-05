#pragma once

#include <VrmlData_Node.hpp>

/**
 *  Implementation of the Texture node
 */
class VrmlData_Texture : public VrmlData_Node
{
public:
  // ---------- PUBLIC METHODS ----------

  /**
   * Empty constructor
   */
  inline VrmlData_Texture()
      : myRepeatS(false),
        myRepeatT(false)
  {
  }

  /**
   * Constructor
   */
  inline VrmlData_Texture(const VrmlData_Scene& theScene,
                          const char*           theName,
                          const bool            theRepeatS = false,
                          const bool            theRepeatT = false)
      : VrmlData_Node(theScene, theName),
        myRepeatS(theRepeatS),
        myRepeatT(theRepeatT)
  {
  }

  /**
   * Query the RepeatS value
   */
  inline bool RepeatS() const { return myRepeatS; }

  /**
   * Query the RepeatT value
   */
  inline bool RepeatT() const { return myRepeatT; }

  /**
   * Set the RepeatS flag
   */
  inline void SetRepeatS(const bool theFlag) { myRepeatS = theFlag; }

  /**
   * Set the RepeatT flag
   */
  inline void SetRepeatT(const bool theFlag) { myRepeatT = theFlag; }

private:
  // ---------- PRIVATE FIELDS ----------

  bool myRepeatS;
  bool myRepeatT;

public:
  // Declaration of CASCADE RTTI
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Texture, VrmlData_Node)
};

// Definition of HANDLE object using Standard_DefineHandle.hpp
