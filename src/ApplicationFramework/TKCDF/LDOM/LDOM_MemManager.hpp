#pragma once


#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

class LDOM_BasicElement;
class LDOM_MemManager;
class LDOMBasicString;

// Define handle class for LDOM_MemManager
//  Class LDOM_MemManager (underlying structure of LDOM_Document)
//

class LDOM_MemManager : public Standard_Transient
{
public:
  // ---------- PUBLIC METHODS ----------

  Standard_EXPORT LDOM_MemManager(const int aBlockSize);
  // Constructor

  Standard_EXPORT ~LDOM_MemManager() override;
  // Destructor

  Standard_EXPORT void* Allocate(const int aSize);
  // General Memory allocator

  const char* HashedAllocate(const char* aString, const int theLen, int& theHash);
  // Memory allocation with access via hash table. No new allocation
  // if already present

  void HashedAllocate(const char* aString, const int theLen, LDOMBasicString& theResult);

  // Memory allocation with access via hash table. No new allocation
  // if already present

  static int Hash(const char* theString, const int theLen)
  {
    return HashTable::Hash(theString, theLen);
  }

  static bool CompareStrings(const char* theString,
                             const int   theHashValue,
                             const char* theHashedStr);

  //  LDOM_Document           Doc           () const
  //                                { return LDOM_Document (* this); }

  const LDOM_MemManager& Self() const { return *this; }

  const LDOM_BasicElement* RootElement() const { return myRootElement; }

private:
  friend class LDOM_Document;
  friend class LDOMParser;

  // ---- CLASS MemBlock ----
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

  // ---- CLASS HashTable ----
  class HashTable
  {
    friend class LDOM_MemManager;
    HashTable(/* const int theMask, */
              LDOM_MemManager& theMemManager);
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

  // ---- PROHIBITED (PRIVATE) METHODS ----
  LDOM_MemManager(const LDOM_MemManager& theOther) = delete;
  // Copy constructor

  LDOM_MemManager& operator=(const LDOM_MemManager& theOther) = delete;
  // Assignment

  // ---------- PRIVATE FIELDS ----------

  const LDOM_BasicElement* myRootElement;
  MemBlock*                myFirstBlock;
  MemBlock*                myFirstWithoutRoom;
  int                      myBlockSize;
  HashTable*               myHashTable;

public:
  // CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(LDOM_MemManager, Standard_Transient)
};

