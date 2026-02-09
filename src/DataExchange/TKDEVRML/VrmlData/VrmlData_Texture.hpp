#pragma once

#include <VrmlData_Node.hpp>

class VrmlData_Texture : public VrmlData_Node
{
public:
  inline VrmlData_Texture()
      : myRepeatS(false),
        myRepeatT(false)
  {
  }

  inline VrmlData_Texture(const VrmlData_Scene& theScene,
                          const char*           theName,
                          const bool            theRepeatS = false,
                          const bool            theRepeatT = false)
      : VrmlData_Node(theScene, theName),
        myRepeatS(theRepeatS),
        myRepeatT(theRepeatT)
  {
  }

  inline bool RepeatS() const { return myRepeatS; }

  inline bool RepeatT() const { return myRepeatT; }

  inline void SetRepeatS(const bool theFlag) { myRepeatS = theFlag; }

  inline void SetRepeatT(const bool theFlag) { myRepeatT = theFlag; }

private:
  bool myRepeatS;
  bool myRepeatT;

public:
  DEFINE_STANDARD_RTTI_INLINE(VrmlData_Texture, VrmlData_Node)
};
