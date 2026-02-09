

#include <PCDM_ReaderFilter.hpp>

IMPLEMENT_STANDARD_RTTIEXT(PCDM_ReaderFilter, Standard_Transient)

PCDM_ReaderFilter::PCDM_ReaderFilter(const occ::handle<Standard_Type>& theSkipped)
    : myAppend(AppendMode_Forbid)
{
  mySkip.Add(theSkipped->Name());
}

PCDM_ReaderFilter::PCDM_ReaderFilter(const TCollection_AsciiString& theEntryToRead)
    : myAppend(AppendMode_Forbid)
{
  mySubTrees.Append(theEntryToRead);
}

PCDM_ReaderFilter::PCDM_ReaderFilter(const AppendMode theAppend)
    : myAppend(theAppend)
{
}

void PCDM_ReaderFilter::Clear()
{
  mySkip.Clear();
  myRead.Clear();
  mySubTrees.Clear();
}

PCDM_ReaderFilter::~PCDM_ReaderFilter()
{
  ClearTree();
}

bool PCDM_ReaderFilter::IsPassed(const occ::handle<Standard_Type>& theAttributeID) const
{
  return IsPassedAttr(theAttributeID->Name());
}

bool PCDM_ReaderFilter::IsPassedAttr(const TCollection_AsciiString& theAttributeType) const
{
  return myRead.IsEmpty() ? !mySkip.Contains(theAttributeType) : myRead.Contains(theAttributeType);
}

bool PCDM_ReaderFilter::IsPassed(const TCollection_AsciiString& theEntry) const
{
  if (mySubTrees.IsEmpty())
    return true;
  for (NCollection_List<TCollection_AsciiString>::Iterator anEntry(mySubTrees); anEntry.More();
       anEntry.Next())
  {
    if (theEntry.StartsWith(anEntry.Value()))
    {
      if (theEntry.Length() > anEntry.Value().Length()
          && theEntry.Value(anEntry.Value().Length() + 1) != ':')
        continue;
      return true;
    }
  }
  return false;
}

bool PCDM_ReaderFilter::IsSubPassed(const TCollection_AsciiString& theEntry) const
{
  if (mySubTrees.IsEmpty() || theEntry.Length() == 2)
    return true;
  for (NCollection_List<TCollection_AsciiString>::Iterator anEntry(mySubTrees); anEntry.More();
       anEntry.Next())
  {
    if (theEntry.Length() < anEntry.Value().Length()
        && anEntry.Value().Value(theEntry.Length() + 1) == ':'
        && anEntry.Value().StartsWith(theEntry))
      return true;
  }
  return false;
}

bool PCDM_ReaderFilter::IsPartTree()
{
  return !mySubTrees.IsEmpty() && (mySubTrees.Size() != 1 || mySubTrees.First().Length() >= 3);
}

void PCDM_ReaderFilter::StartIteration()
{
  myCurrent      = &myTree;
  myCurrentDepth = 0;
  ClearTree();
  myTree.Bind(-1, nullptr);
  if (mySubTrees.IsEmpty())
    return;

  for (NCollection_List<TCollection_AsciiString>::Iterator aTreeIter(mySubTrees); aTreeIter.More();
       aTreeIter.Next())
  {
    TagTree*                aMap = &myTree;
    TCollection_AsciiString aTagStr, anEntry = aTreeIter.Value();
    for (int aTagIndex = 2; !anEntry.IsEmpty(); ++aTagIndex)
    {
      aTagStr = anEntry.Token(":", aTagIndex);
      if (aTagStr.IsEmpty())
        break;
      int aTag = aTagStr.IntegerValue();
      if (aMap->IsBound(aTag))
      {
        aMap = (TagTree*)aMap->Find(aTag);
      }
      else
      {
        TagTree* aNewMap = new TagTree;
        aNewMap->Bind(-1, aMap);
        aMap->Bind(aTag, aNewMap);
        aMap = aNewMap;
      }
    }
    aMap->Bind(-2, nullptr);
  }
}

void PCDM_ReaderFilter::Up()
{
  if (myCurrentDepth == 0)
    myCurrent = (TagTree*)myCurrent->Find(-1);
  else
    myCurrentDepth--;
}

void PCDM_ReaderFilter::Down(const int& theTag)
{
  if (myCurrentDepth == 0)
  {
    if (myCurrent->IsBound(theTag))
      myCurrent = (TagTree*)myCurrent->Find(theTag);
    else
      ++myCurrentDepth;
  }
  else
    ++myCurrentDepth;
}

bool PCDM_ReaderFilter::IsPassed() const
{
  return myCurrent->IsBound(-2);
}

bool PCDM_ReaderFilter::IsSubPassed() const
{
  return myCurrentDepth == 0;
}

void PCDM_ReaderFilter::ClearSubTree(void* const theMap)
{
  if (theMap)
  {
    TagTree* aMap = (TagTree*)theMap;
    for (TagTree::Iterator aTagIter(*aMap); aTagIter.More(); aTagIter.Next())
      if (aTagIter.Key() != -1)
        ClearSubTree(aTagIter.Value());
    delete aMap;
  }
}

void PCDM_ReaderFilter::ClearTree()
{
  for (TagTree::Iterator aTagIter(myTree); aTagIter.More(); aTagIter.Next())
    if (aTagIter.Key() != -1)
      ClearSubTree(aTagIter.Value());
  myTree.Clear();
}
