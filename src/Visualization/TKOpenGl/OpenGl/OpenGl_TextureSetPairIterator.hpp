#pragma once

#include <OpenGl_TextureSet.hpp>

class OpenGl_TextureSetPairIterator
{
public:
  OpenGl_TextureSetPairIterator(const occ::handle<OpenGl_TextureSet>& theSet1,
                                const occ::handle<OpenGl_TextureSet>& theSet2)
      : myIter1(theSet1),
        myIter2(theSet2),
        myTexture1(nullptr),
        myTexture2(nullptr),
        myUnitLower(IntegerLast()),
        myUnitUpper(IntegerFirst()),
        myUnitCurrent(0)
  {
    if (!theSet1.IsNull() && !theSet1->IsEmpty())
    {
      myUnitLower = (std::min)(myUnitLower, static_cast<int>(theSet1->FirstUnit()));
      myUnitUpper = (std::max)(myUnitUpper, static_cast<int>(theSet1->LastUnit()));
    }
    if (!theSet2.IsNull() && !theSet2->IsEmpty())
    {
      myUnitLower = (std::min)(myUnitLower, static_cast<int>(theSet2->FirstUnit()));
      myUnitUpper = (std::max)(myUnitUpper, static_cast<int>(theSet2->LastUnit()));
    }
    myUnitCurrent = myUnitLower;
    myTexture1 =
      (myIter1.More() && myIter1.Unit() == myUnitCurrent) ? myIter1.ChangeValue().get() : nullptr;
    myTexture2 =
      (myIter2.More() && myIter2.Unit() == myUnitCurrent) ? myIter2.ChangeValue().get() : nullptr;
  }

  bool More() const { return myUnitCurrent <= myUnitUpper; }

  Graphic3d_TextureUnit Unit() const { return (Graphic3d_TextureUnit)myUnitCurrent; }

  const OpenGl_Texture* Texture1() const { return myTexture1; }

  const OpenGl_Texture* Texture2() const { return myTexture2; }

  void Next()
  {
    ++myUnitCurrent;
    myTexture1 = myTexture2 = nullptr;
    for (; myIter1.More(); myIter1.Next())
    {
      if (myIter1.Unit() >= myUnitCurrent)
      {
        myTexture1 = myIter1.Unit() == myUnitCurrent ? myIter1.ChangeValue().get() : nullptr;
        break;
      }
    }
    for (; myIter2.More(); myIter2.Next())
    {
      if (myIter2.Unit() >= myUnitCurrent)
      {
        myTexture2 = myIter2.Unit() == myUnitCurrent ? myIter2.ChangeValue().get() : nullptr;
        break;
      }
    }
  }

private:
  OpenGl_TextureSet::Iterator myIter1;
  OpenGl_TextureSet::Iterator myIter2;
  OpenGl_Texture*             myTexture1;
  OpenGl_Texture*             myTexture2;
  int                         myUnitLower;
  int                         myUnitUpper;
  int                         myUnitCurrent;
};
