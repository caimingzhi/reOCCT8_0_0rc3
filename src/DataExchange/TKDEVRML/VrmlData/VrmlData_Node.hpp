#pragma once

#include <NCollection_List.hpp>
#include <Standard_Type.hpp>
#include <Standard_TypeDef.hpp>
#include <TCollection_AsciiString.hpp>
#include <Standard_CStringHasher.hpp>
#include <VrmlData_ErrorStatus.hpp>

#define VRMLDATA_LCOMPARE(aa, bb) ((strncmp(aa, bb, sizeof(bb) - 1)) ? 0L : (aa += sizeof(bb) - 1))

struct VrmlData_InBuffer;
class VrmlData_Scene;
class TCollection_AsciiString;

class VrmlData_Node : public Standard_Transient
{
public:
  Standard_EXPORT VrmlData_Node();

  ~VrmlData_Node() override = default;

  inline const VrmlData_Scene& Scene() const { return *myScene; }

  inline const char* Name() const { return myName; }

  Standard_EXPORT VrmlData_ErrorStatus ReadNode(VrmlData_InBuffer&                theBuffer,
                                                occ::handle<VrmlData_Node>&       theNode,
                                                const occ::handle<Standard_Type>& Type = nullptr);

  Standard_EXPORT virtual VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) = 0;

  Standard_EXPORT virtual VrmlData_ErrorStatus Write(const char* thePrefix) const;

  Standard_EXPORT virtual bool IsDefault() const;

  Standard_EXPORT VrmlData_ErrorStatus WriteClosing() const;

  Standard_EXPORT virtual occ::handle<VrmlData_Node> Clone(const occ::handle<VrmlData_Node>&) const;

  Standard_EXPORT static VrmlData_ErrorStatus ReadBoolean(VrmlData_InBuffer& theBuffer,
                                                          bool&              theResult);

  Standard_EXPORT static VrmlData_ErrorStatus ReadString(VrmlData_InBuffer&       theBuffer,
                                                         TCollection_AsciiString& theRes);

  Standard_EXPORT static VrmlData_ErrorStatus ReadMultiString(
    VrmlData_InBuffer&                         theBuffer,
    NCollection_List<TCollection_AsciiString>& theRes);

  Standard_EXPORT static VrmlData_ErrorStatus ReadInteger(VrmlData_InBuffer& theBuffer,
                                                          long&              theResult);

  static inline bool OK(const VrmlData_ErrorStatus theStat) { return theStat == VrmlData_StatusOK; }

  static inline bool OK(VrmlData_ErrorStatus& outStat, const VrmlData_ErrorStatus theStat)
  {
    return (outStat = theStat) == VrmlData_StatusOK;
  }

  static inline int GlobalIndent() { return 2; }

protected:
  Standard_EXPORT VrmlData_Node(const VrmlData_Scene& theScene, const char* theName);

  Standard_EXPORT static VrmlData_ErrorStatus readBrace(VrmlData_InBuffer& theBuffer);

private:
  Standard_EXPORT void setName(const char* theName, const char* theSuffix = nullptr);

private:
  const VrmlData_Scene* myScene;
  const char*           myName;
#ifdef OCCT_DEBUG
  int myLineCount;
#endif

  friend class VrmlData_Group;
  friend class VrmlData_Scene;

public:
  DEFINE_STANDARD_RTTIEXT(VrmlData_Node, Standard_Transient)
};

Standard_EXPORT bool IsEqual(const occ::handle<VrmlData_Node>& theOne,
                             const occ::handle<VrmlData_Node>& theTwo);

namespace std
{
  template <>
  struct hash<occ::handle<VrmlData_Node>>
  {
    size_t operator()(const occ::handle<VrmlData_Node>& theNode) const
    {
      if (!theNode->Name())
      {
        return 1;
      }
      return Standard_CStringHasher{}(theNode->Name());
    }
  };

  template <>
  struct equal_to<occ::handle<VrmlData_Node>>
  {
    bool operator()(const occ::handle<VrmlData_Node>& theNode1,
                    const occ::handle<VrmlData_Node>& theNode2) const noexcept
    {
      return IsEqual(theNode1, theNode2);
    }
  };
} // namespace std
