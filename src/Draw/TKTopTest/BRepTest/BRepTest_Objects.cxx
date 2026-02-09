#include <BRepTest_Objects.hpp>

class BRepTest_Session
{
public:
  BRepTest_Session() { SetDefaultValues(); }

  void SetDefaultValues() { myFillHistory = true; }

  void SetHistory(const occ::handle<BRepTools_History>& theHistory) { myHistory = theHistory; }

  void AddHistory(const occ::handle<BRepTools_History>& theHistory)
  {
    if (myHistory.IsNull())
      myHistory = new BRepTools_History;
    myHistory->Merge(theHistory);
  }

  const occ::handle<BRepTools_History>& History() const { return myHistory; }

  void SetToFillHistory(const bool theFillHist) { myFillHistory = theFillHist; }

  bool IsHistoryNeeded() const { return myFillHistory; }

private:
  occ::handle<BRepTools_History> myHistory;
  bool                           myFillHistory;
};

static BRepTest_Session& GetSession()
{
  static BRepTest_Session* pSession = new BRepTest_Session();
  return *pSession;
}

void BRepTest_Objects::SetHistory(const occ::handle<BRepTools_History>& theHistory)
{
  GetSession().SetHistory(theHistory);
}

void BRepTest_Objects::AddHistory(const occ::handle<BRepTools_History>& theHistory)
{
  GetSession().AddHistory(theHistory);
}

occ::handle<BRepTools_History> BRepTest_Objects::History()
{
  return GetSession().History();
}

void BRepTest_Objects::SetToFillHistory(const bool theFillHist)
{
  return GetSession().SetToFillHistory(theFillHist);
}

bool BRepTest_Objects::IsHistoryNeeded()
{
  return GetSession().IsHistoryNeeded();
}
