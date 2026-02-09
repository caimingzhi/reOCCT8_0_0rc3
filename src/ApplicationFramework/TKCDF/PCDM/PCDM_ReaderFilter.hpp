#pragma once

#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_List.hpp>

class PCDM_ReaderFilter : public Standard_Transient
{
public:
  enum AppendMode
  {
    AppendMode_Forbid    = 0,
    AppendMode_Protect   = 1,
    AppendMode_Overwrite = 2,
  };

  inline PCDM_ReaderFilter()
      : myAppend(AppendMode_Forbid)
  {
  }

  Standard_EXPORT PCDM_ReaderFilter(const occ::handle<Standard_Type>& theSkipped);

  Standard_EXPORT PCDM_ReaderFilter(const TCollection_AsciiString& theEntryToRead);

  Standard_EXPORT PCDM_ReaderFilter(const AppendMode theAppend);

  Standard_EXPORT ~PCDM_ReaderFilter() override;

  Standard_EXPORT void AddSkipped(const occ::handle<Standard_Type>& theSkipped)
  {
    mySkip.Add(theSkipped->Name());
  }

  Standard_EXPORT void AddSkipped(const TCollection_AsciiString& theSkipped)
  {
    mySkip.Add(theSkipped);
  }

  Standard_EXPORT void AddRead(const occ::handle<Standard_Type>& theRead)
  {
    myRead.Add(theRead->Name());
  }

  Standard_EXPORT void AddRead(const TCollection_AsciiString& theRead) { myRead.Add(theRead); }

  Standard_EXPORT void AddPath(const TCollection_AsciiString& theEntryToRead)
  {
    mySubTrees.Append(theEntryToRead);
  }

  Standard_EXPORT void Clear();

  Standard_EXPORT virtual bool IsPassed(const occ::handle<Standard_Type>& theAttributeID) const;

  Standard_EXPORT virtual bool IsPassedAttr(const TCollection_AsciiString& theAttributeType) const;

  Standard_EXPORT virtual bool IsPassed(const TCollection_AsciiString& theEntry) const;

  Standard_EXPORT virtual bool IsSubPassed(const TCollection_AsciiString& theEntry) const;

  Standard_EXPORT virtual bool IsPartTree();

  Standard_EXPORT AppendMode& Mode() { return myAppend; }

  Standard_EXPORT bool IsAppendMode() { return myAppend != PCDM_ReaderFilter::AppendMode_Forbid; }

  Standard_EXPORT virtual void StartIteration();

  Standard_EXPORT virtual void Up();

  Standard_EXPORT virtual void Down(const int& theTag);

  Standard_EXPORT virtual bool IsPassed() const;

  Standard_EXPORT virtual bool IsSubPassed() const;

  DEFINE_STANDARD_RTTIEXT(PCDM_ReaderFilter, Standard_Transient)

private:
  Standard_EXPORT void ClearTree();

  Standard_EXPORT static void ClearSubTree(void* const theMap);

protected:
  AppendMode myAppend;

  NCollection_Map<TCollection_AsciiString> mySkip;

  NCollection_Map<TCollection_AsciiString> myRead;

  NCollection_List<TCollection_AsciiString> mySubTrees;

  typedef NCollection_DataMap<int, void*> TagTree;

  TagTree myTree;

  TagTree* myCurrent;

  int myCurrentDepth;
};
