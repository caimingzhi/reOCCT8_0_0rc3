#include <LDOM_CharReference.hpp>

#include <Standard_CString.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace
{
  constexpr int NORMAL_C  = 0;
  constexpr int CHAR_REF  = -1;
  constexpr int ENTI_AMP  = 1;
  constexpr int ENTI_LT   = 2;
  constexpr int ENTI_GT   = 3;
  constexpr int ENTI_QUOT = 4;

  struct entityRef
  {
    const char* name;
    int         length;

    entityRef(const char* aName, const int aLen)
        : name(aName),
          length(aLen)
    {
    }
  };
} // namespace

char* LDOM_CharReference::Decode(char* theSrc, int& theLen)
{
#define IS_EQUAL(_ptr, _string) (!memcmp(_ptr, _string, sizeof(_string) - 1))

  char *aSrcPtr = theSrc, *aDstPtr = theSrc;
  int   anIncrCount = 0;
  for (;;)
  {
    char* aPtr = strchr(aSrcPtr, '&');
    if (aPtr == nullptr)
    {

      aPtr = strchr(aSrcPtr, '\0');
      if (anIncrCount == 0)
        theLen = (int)(aPtr - theSrc);
      else
      {
        int aByteCount = (int)(aPtr - aSrcPtr);
        memmove(aDstPtr, aSrcPtr, aByteCount + 1);
        theLen = (int)(aDstPtr - theSrc) + aByteCount;
      }
      break;
    }
    int aByteCount = (int)(aPtr - aSrcPtr);
    if (aByteCount > 0 && aDstPtr != aSrcPtr)
      memmove(aDstPtr, aSrcPtr, aByteCount);
    aSrcPtr = aPtr;
    if (aSrcPtr[1] == '#')
    {
      unsigned long aChar;
      char*         aNewPtr;
      aDstPtr = aSrcPtr - anIncrCount + 1;
      if (aSrcPtr[2] == 'x')
        aChar = strtoul(&aSrcPtr[3], &aNewPtr, 16);
      else
        aChar = strtoul(&aSrcPtr[2], &aNewPtr, 10);
      if (aNewPtr[0] != ';' || aChar == 0 || aChar > 255UL)

        return nullptr;
      aDstPtr[-1] = (char)aChar;
      anIncrCount += (int)(aNewPtr - aSrcPtr);
      aSrcPtr = &aNewPtr[1];
    }
    else if (IS_EQUAL(aSrcPtr + 1, "amp;"))
    {
      aDstPtr     = aSrcPtr - anIncrCount + 1;
      aDstPtr[-1] = '&';
      anIncrCount += 4;
      aSrcPtr += 5;
    }
    else if (IS_EQUAL(aSrcPtr + 1, "lt;"))
    {
      aDstPtr     = aSrcPtr - anIncrCount + 1;
      aDstPtr[-1] = '<';
      anIncrCount += 3;
      aSrcPtr += 4;
    }
    else if (IS_EQUAL(aSrcPtr + 1, "gt;"))
    {
      aDstPtr     = aSrcPtr - anIncrCount + 1;
      aDstPtr[-1] = '>';
      anIncrCount += 3;
      aSrcPtr += 4;
    }
    else if (IS_EQUAL(aSrcPtr + 1, "quot;"))
    {
      aDstPtr     = aSrcPtr - anIncrCount + 1;
      aDstPtr[-1] = '\"';
      anIncrCount += 5;
      aSrcPtr += 6;
    }
    else if (IS_EQUAL(aSrcPtr + 1, "apos;"))
    {
      aDstPtr     = aSrcPtr - anIncrCount + 1;
      aDstPtr[-1] = '\'';
      anIncrCount += 5;
      aSrcPtr += 6;
    }
    else
    {
      aDstPtr    = aSrcPtr - anIncrCount;
      *aDstPtr++ = *aSrcPtr++;
      continue;
    }
  }
  return theSrc;
}

char* LDOM_CharReference::Encode(const char* theSrc, int& theLen, const bool isAttribute)
{

  static const struct entityRef entity_ref[6] = {entityRef(nullptr, 0),
                                                 entityRef("&amp;", 5),
                                                 entityRef("&lt;", 4),
                                                 entityRef("&gt;", 4),
                                                 entityRef("&quot;", 6),
                                                 entityRef("&apos;", 6)};

  const char *endSrc, *ptrSrc = theSrc;
  char*       aDest  = (char*)theSrc;
  int         aCount = 0;

  for (;;)
  {
    const unsigned int iSrc = (unsigned int)*(const unsigned char*)ptrSrc;
    if (iSrc == 0)
    {
      endSrc = ptrSrc;
      break;
    }
    if (myTab[iSrc] != NORMAL_C)
      if (isAttribute || myTab[iSrc] != ENTI_QUOT)
        aCount++;
    ptrSrc++;
  }

  if (!aCount)
    theLen = (int)(endSrc - theSrc);
  else
  {
    char* ptrDest = new char[(endSrc - theSrc) + aCount * 5 + 1];
    aDest         = ptrDest;
    for (ptrSrc = theSrc; ptrSrc < endSrc; ptrSrc++)
    {
      const unsigned int iSrc  = (unsigned int)*(const unsigned char*)ptrSrc;
      const int          aCode = myTab[iSrc];
      if (aCode == NORMAL_C)
        *ptrDest++ = *ptrSrc;
      else if (aCode == CHAR_REF)
      {
        Sprintf(ptrDest, "&#x%02x;", iSrc);
        ptrDest += 6;
      }
      else if (!isAttribute && aCode == ENTI_QUOT)
        *ptrDest++ = *ptrSrc;
      else
      {
        memcpy(ptrDest, entity_ref[aCode].name, entity_ref[aCode].length + 1);
        ptrDest += entity_ref[aCode].length;
      }
    }
    theLen   = (int)(ptrDest - aDest);
    *ptrDest = '\0';
  }
  return aDest;
}

int LDOM_CharReference::myTab[256] = {
  NORMAL_C, CHAR_REF, CHAR_REF,  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,
  CHAR_REF, NORMAL_C, NORMAL_C,  CHAR_REF, CHAR_REF, NORMAL_C, CHAR_REF, CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,
  NORMAL_C, NORMAL_C, ENTI_QUOT, NORMAL_C, NORMAL_C, NORMAL_C, ENTI_AMP,

  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, ENTI_LT,  NORMAL_C, ENTI_GT,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, CHAR_REF, CHAR_REF,  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,
  CHAR_REF,
#ifdef LDOM_ALLOW_LATIN_1
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,

  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,

  NORMAL_C, NORMAL_C, NORMAL_C,  NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C, NORMAL_C,
  NORMAL_C
#else
  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF,
  CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF, CHAR_REF,  CHAR_REF,
  CHAR_REF
#endif
};
