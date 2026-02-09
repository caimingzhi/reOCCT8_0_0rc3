#pragma once

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

class LDOM_BasicElement;
class LDOM_MemManager;
class LDOMBasicString;

class LDOM_MemManager : public Standard_Transient
{
public:
  Standard_EXPORT LDOM_MemManager(const int aBlockSize);

  Standard_EXPORT ~LDOM_MemManager() override;

  Standard_EXPORT void* Allocate(const int aSize);

  const char* HashedAllocate(const char* aString, const int theLen, int& theHash);

  void HashedAllocate(const char* aString, const int theLen, LDOMBasicString& theResult);

  static int Hash(const char* theString, const int theLen)
  {
    return HashTable::Hash(theString, theLen);
  }

  static bool CompareStrings(const char* theString,
                             const int   theHashValue,
                             const char* theHashedStr);

  const LDOM_MemManager& Self() const { return *this; }

  const LDOM_BasicElement* RootElement() const { return myRootElement; }

private:
  friend class LDOM_Document;
  friend class LDOMParser;

  class MemBlock
  {
    friend class LDOM_MemManager;
    inline MemBlock(const int aSize, MemBlock* aFirst);
    inline void* Allocate(const int aSize);
    void*        AllocateAndCheck(const int aSize, const MemBlock*&);
    ~MemBlock();

    MemBlock* Next() { return myNext; }

    int*      myBlock;
    int*      myEndBlock;
    int*      myFreeSpace;
    MemBlock* myNext;
  };

  class HashTable
  {
    friend class LDOM_MemManager;
    HashTable(LDOM_MemManager& theMemManager);
    const char* AddString(const char* theString, const int theLen, int& theHashIndex);
    static int  Hash(const char* theString, const int theLen);

    struct TableItem
    {
      char*             str;
      struct TableItem* next;
    }* myTable;

    LDOM_MemManager& myManager;
    void             operator=(const HashTable&) = delete;
  };

  LDOM_MemManager(const LDOM_MemManager& theOther) = delete;

  LDOM_MemManager& operator=(const LDOM_MemManager& theOther) = delete;

  const LDOM_BasicElement* myRootElement;
  MemBlock*                myFirstBlock;
  MemBlock*                myFirstWithoutRoom;
  int                      myBlockSize;
  HashTable*               myHashTable;

public:
  DEFINE_STANDARD_RTTIEXT(LDOM_MemManager, Standard_Transient)
};
