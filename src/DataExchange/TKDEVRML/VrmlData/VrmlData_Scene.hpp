#pragma once

#include <NCollection_List.hpp>
#include <VrmlData_Node.hpp>
#include <NCollection_Map.hpp>
#include <VrmlData_ErrorStatus.hpp>
#include <VrmlData_WorldInfo.hpp>
#include <TopoDS_Shape.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
#include <TCollection_ExtendedString.hpp>
#include <NCollection_IncAllocator.hpp>
#include <NCollection_DataMap.hpp>
#include <VrmlData_Appearance.hpp>
#include <TopoDS_TShape.hpp>

#include <mutex>

#ifdef Status
  #undef Status
#endif

struct VrmlData_InBuffer;

class VrmlData_Scene
{
public:
  typedef NCollection_List<occ::handle<VrmlData_Node>>::Iterator Iterator;

  Standard_EXPORT VrmlData_Scene(const occ::handle<NCollection_IncAllocator>& = nullptr);

  inline VrmlData_ErrorStatus Status() const { return myStatus; }

  Standard_EXPORT void SetVrmlDir(const TCollection_ExtendedString&);

  inline void SetLinearScale(const double theScale) { myLinearScale = theScale; }

  inline NCollection_List<TCollection_ExtendedString>::Iterator VrmlDirIterator() const
  {
    return NCollection_List<TCollection_ExtendedString>::Iterator(myVrmlDir);
  }

  inline Iterator GetIterator() const { return Iterator(myLstNodes); }

  inline NCollection_Map<occ::handle<VrmlData_Node>>::Iterator NamedNodesIterator() const
  {
    return myNamedNodes;
  }

  inline const occ::handle<NCollection_IncAllocator>& Allocator() const { return myAllocator; }

  Standard_EXPORT const occ::handle<VrmlData_Node>& AddNode(const occ::handle<VrmlData_Node>& theN,
                                                            const bool isTopLevel = true);

  Standard_EXPORT occ::handle<VrmlData_Node> FindNode(
    const char*                       theName,
    const occ::handle<Standard_Type>& theType = nullptr) const;

  Standard_EXPORT occ::handle<VrmlData_Node> FindNode(const char* theName,
                                                      gp_Trsf&    theLocation) const;

  friend Standard_EXPORT Standard_OStream& operator<<(Standard_OStream&     theOutput,
                                                      const VrmlData_Scene& theScene);

  Standard_EXPORT VrmlData_Scene& operator<<(Standard_IStream& theInput);

  Standard_EXPORT operator TopoDS_Shape() const;

  Standard_EXPORT TopoDS_Shape
    GetShape(NCollection_DataMap<occ::handle<TopoDS_TShape>, occ::handle<VrmlData_Appearance>>& M);

  Standard_EXPORT const occ::handle<VrmlData_WorldInfo>& WorldInfo() const;

  Standard_EXPORT static VrmlData_ErrorStatus ReadLine(VrmlData_InBuffer& theBuffer);

  Standard_EXPORT static VrmlData_ErrorStatus ReadWord(VrmlData_InBuffer&       theBuffer,
                                                       TCollection_AsciiString& theStr);

  Standard_EXPORT void Dump(Standard_OStream& theStream) const;

  Standard_EXPORT VrmlData_ErrorStatus ReadReal(VrmlData_InBuffer& theBuffer,
                                                double&            theResult,
                                                bool               isApplyScale,
                                                bool               isOnlyPositive) const;

  Standard_EXPORT VrmlData_ErrorStatus ReadXYZ(VrmlData_InBuffer& theBuffer,
                                               gp_XYZ&            theXYZ,
                                               bool               isApplyScale,
                                               bool               isOnlyPositive) const;

  Standard_EXPORT VrmlData_ErrorStatus ReadXY(VrmlData_InBuffer& theBuffer,
                                              gp_XY&             theXYZ,
                                              bool               isApplyScale,
                                              bool               isOnlyPositive) const;

  Standard_EXPORT VrmlData_ErrorStatus ReadArrIndex(VrmlData_InBuffer& theBuffer,
                                                    const int**&       theArr,
                                                    size_t&            theNBl) const;

  inline int GetLineError() const { return myLineError; }

  inline void SetIndent(const int nSpc) { myIndent = nSpc; }

  Standard_EXPORT VrmlData_ErrorStatus WriteXYZ(const gp_XYZ& theXYZ,
                                                const bool    isScale,
                                                const char*   thePostfix = nullptr) const;

  Standard_EXPORT VrmlData_ErrorStatus WriteArrIndex(const char*  thePrefix,
                                                     const int**  theArr,
                                                     const size_t theNbBl) const;

  Standard_EXPORT VrmlData_ErrorStatus WriteLine(const char* theLine0,
                                                 const char* theLine1  = nullptr,
                                                 const int   theIndent = 0) const;

  Standard_EXPORT VrmlData_ErrorStatus WriteNode(const char* thePrefix,
                                                 const occ::handle<VrmlData_Node>&) const;

  inline bool IsDummyWrite() const { return myOutput == nullptr; }

private:
  VrmlData_Scene(const VrmlData_Scene&)            = delete;
  VrmlData_Scene& operator=(const VrmlData_Scene&) = delete;

protected:
  Standard_EXPORT static VrmlData_ErrorStatus readLine(VrmlData_InBuffer& theBuffer);

  Standard_EXPORT static VrmlData_ErrorStatus readHeader(VrmlData_InBuffer& theBuffer);

  Standard_EXPORT VrmlData_ErrorStatus createNode(VrmlData_InBuffer&                theBuffer,
                                                  occ::handle<VrmlData_Node>&       theNode,
                                                  const occ::handle<Standard_Type>& Type);

  Standard_EXPORT static void createShape(
    TopoDS_Shape& outShape,
    const NCollection_List<occ::handle<VrmlData_Node>>&,
    NCollection_DataMap<occ::handle<TopoDS_TShape>, occ::handle<VrmlData_Appearance>>*);

private:
  double                                       myLinearScale;
  NCollection_List<occ::handle<VrmlData_Node>> myLstNodes;
  NCollection_List<occ::handle<VrmlData_Node>> myAllNodes;
  VrmlData_ErrorStatus                         myStatus;
  occ::handle<NCollection_IncAllocator>        myAllocator;
  occ::handle<VrmlData_WorldInfo>              myWorldInfo;
  NCollection_Map<occ::handle<VrmlData_Node>>  myNamedNodes;

  NCollection_List<TCollection_ExtendedString> myVrmlDir;
  std::mutex                                   myMutex;
  int                                          myLineError;

  Standard_OStream* myOutput;
  int               myIndent;
  int               myCurrentIndent;

  NCollection_Map<occ::handle<VrmlData_Node>> myNamedNodesOut;

  NCollection_Map<void*> myUnnamedNodesOut;
  int                    myAutoNameCounter;
  friend class VrmlData_Group;
  friend class VrmlData_Node;
};
