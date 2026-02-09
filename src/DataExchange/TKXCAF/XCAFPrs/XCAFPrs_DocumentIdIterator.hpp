#pragma once

#include <XCAFPrs_Style.hpp>

class XCAFPrs_DocumentIdIterator
{
public:
  XCAFPrs_DocumentIdIterator(const TCollection_AsciiString& thePath)
      : myPath(thePath),
        myPosition(0)
  {
    Next();
  }

  bool More() const { return !mySubId.IsEmpty(); }

  const TCollection_AsciiString& Value() const { return mySubId; }

  void Next();

private:
  XCAFPrs_DocumentIdIterator& operator=(const XCAFPrs_DocumentIdIterator&) = delete;

private:
  const TCollection_AsciiString& myPath;
  TCollection_AsciiString        mySubId;
  int                            myPosition;
};

inline void XCAFPrs_DocumentIdIterator::Next()
{
  for (int aCharIndex = myPosition + 1; aCharIndex <= myPath.Length(); ++aCharIndex)
  {
    if (myPath.Value(aCharIndex) == '/')
    {

      const int aLen = aCharIndex - myPosition - 2;
      if (aLen < 1)
      {
        return;
      }

      mySubId    = myPath.SubString(myPosition + 1, aCharIndex - 2);
      myPosition = aCharIndex;
      return;
    }
  }
  if (myPosition < myPath.Length())
  {

    mySubId    = myPath.SubString(myPosition + 1, myPath.Length() - 1);
    myPosition = myPath.Length();
  }
  else
  {
    mySubId.Clear();
    myPosition = myPath.Length();
  }
}
