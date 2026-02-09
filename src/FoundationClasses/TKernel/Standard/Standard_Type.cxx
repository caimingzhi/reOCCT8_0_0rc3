

#include <Standard_Type.hpp>

#include <NCollection_DataMap.hpp>
#include <Standard_HashUtils.hpp>
#include <Standard_Assert.hpp>

#include <mutex>

IMPLEMENT_STANDARD_RTTIEXT(Standard_Type, Standard_Transient)

Standard_Type::Standard_Type(const char*                       theSystemName,
                             const char*                       theName,
                             size_t                            theSize,
                             const occ::handle<Standard_Type>& theParent)
    : mySystemName(theSystemName),
      myName(theName),
      mySize(theSize),
      myParent(theParent)
{
}

bool Standard_Type::SubType(const occ::handle<Standard_Type>& theOther) const
{
  if (theOther.IsNull())
  {
    return false;
  }
  const Standard_Type* aTypeIter = this;
  while (aTypeIter && theOther->mySize <= aTypeIter->mySize)
  {
    if (theOther.get() == aTypeIter)
    {
      return true;
    }
    aTypeIter = aTypeIter->Parent().get();
  }
  return false;
}

bool Standard_Type::SubType(const char* theName) const
{
  if (!theName)
  {
    return false;
  }
  const Standard_Type* aTypeIter = this;
  while (aTypeIter)
  {
    if (IsEqual(theName, aTypeIter->Name()))
    {
      return true;
    }
    aTypeIter = aTypeIter->Parent().get();
  }
  return false;
}

void Standard_Type::Print(Standard_OStream& AStream) const
{
  AStream << std::hex << (void*)this << " : " << std::dec << myName;
}

namespace
{

  struct typeNameHasher
  {
    size_t operator()(const char* theType) const noexcept
    {
      const int aLen = static_cast<int>(strlen(theType));
      return opencascade::hashBytes(theType, aLen);
    }

    bool operator()(const char* theType1, const char* theType2) const noexcept
    {
      return strcmp(theType1, theType2) == 0;
    }
  };

  using registry_type = NCollection_DataMap<const char*, Standard_Type*, typeNameHasher>;

  registry_type& GetRegistry()
  {
    static registry_type theRegistry(2048, NCollection_BaseAllocator::CommonBaseAllocator());
    return theRegistry;
  }

  occ::handle<Standard_Type> theType = STANDARD_TYPE(Standard_Transient);
} // namespace

Standard_Type* Standard_Type::Register(const std::type_info&             theInfo,
                                       const char*                       theName,
                                       size_t                            theSize,
                                       const occ::handle<Standard_Type>& theParent)
{

  static std::mutex           aMutex;
  std::lock_guard<std::mutex> aLock(aMutex);

  registry_type& aRegistry = GetRegistry();
  Standard_Type* aType;
  if (aRegistry.Find(theInfo.name(), aType))
  {
    return aType;
  }

  const size_t anInfoNameLen = strlen(theInfo.name()) + 1;
  const size_t aNameLen      = strlen(theName) + 1;

  char* aMemoryBlock =
    static_cast<char*>(Standard::AllocateOptimal(sizeof(Standard_Type) + anInfoNameLen + aNameLen));

  char* anInfoNameCopy = aMemoryBlock + sizeof(Standard_Type);
  char* aNameCopy      = anInfoNameCopy + anInfoNameLen;

  strncpy(anInfoNameCopy, theInfo.name(), anInfoNameLen);
  strncpy(aNameCopy, theName, aNameLen);

  aType = new (aMemoryBlock) Standard_Type(anInfoNameCopy, aNameCopy, theSize, theParent);

  aRegistry.Bind(anInfoNameCopy, aType);
  return aType;
}

Standard_Type::~Standard_Type()
{

  registry_type& aRegistry = GetRegistry();
  Standard_ASSERT(aRegistry.UnBind(mySystemName),
                  "Standard_Type::~Standard_Type() cannot find itself in registry",
                  Standard_VOID_RETURN);
}
