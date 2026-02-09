#pragma once

#include <Standard_Integer.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Transfer_Finder.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Transfer_Binder.hpp>
#include <Transfer_FindHasher.hpp>
#include <Message_ProgressRange.hpp>

class Message_Messenger;
class Transfer_Finder;
class Transfer_Binder;
class Transfer_ActorOfProcessForFinder;
class Interface_InterfaceError;
class Transfer_TransferFailure;
class Transfer_FindHasher;
class Transfer_IteratorOfProcessForFinder;
class Message_Msg;
class Interface_Check;
class Standard_Transient;
class Interface_CheckIterator;

class Transfer_ProcessForFinder : public Standard_Transient
{

public:
  Standard_EXPORT Transfer_ProcessForFinder(const int nb = 10000);

  Standard_EXPORT Transfer_ProcessForFinder(const occ::handle<Message_Messenger>& printer,
                                            const int                             nb = 10000);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Clean();

  Standard_EXPORT void Resize(const int nb);

  Standard_EXPORT void SetActor(const occ::handle<Transfer_ActorOfProcessForFinder>& actor);

  Standard_EXPORT occ::handle<Transfer_ActorOfProcessForFinder> Actor() const;

  Standard_EXPORT occ::handle<Transfer_Binder> Find(
    const occ::handle<Transfer_Finder>& start) const;

  Standard_EXPORT bool IsBound(const occ::handle<Transfer_Finder>& start) const;

  Standard_EXPORT bool IsAlreadyUsed(const occ::handle<Transfer_Finder>& start) const;

  Standard_EXPORT void Bind(const occ::handle<Transfer_Finder>& start,
                            const occ::handle<Transfer_Binder>& binder);

  Standard_EXPORT void Rebind(const occ::handle<Transfer_Finder>& start,
                              const occ::handle<Transfer_Binder>& binder);

  Standard_EXPORT bool Unbind(const occ::handle<Transfer_Finder>& start);

  Standard_EXPORT occ::handle<Transfer_Binder> FindElseBind(
    const occ::handle<Transfer_Finder>& start);

  Standard_EXPORT void SetMessenger(const occ::handle<Message_Messenger>& messenger);

  Standard_EXPORT occ::handle<Message_Messenger> Messenger() const;

  Standard_EXPORT void SetTraceLevel(const int tracelev);

  Standard_EXPORT int TraceLevel() const;

  Standard_EXPORT void SendFail(const occ::handle<Transfer_Finder>& start, const Message_Msg& amsg);

  Standard_EXPORT void SendWarning(const occ::handle<Transfer_Finder>& start,
                                   const Message_Msg&                  amsg);

  Standard_EXPORT void SendMsg(const occ::handle<Transfer_Finder>& start, const Message_Msg& amsg);

  Standard_EXPORT void AddFail(const occ::handle<Transfer_Finder>& start,
                               const char*                         mess,
                               const char*                         orig = "");

  Standard_EXPORT void AddError(const occ::handle<Transfer_Finder>& start,
                                const char*                         mess,
                                const char*                         orig = "");

  Standard_EXPORT void AddFail(const occ::handle<Transfer_Finder>& start, const Message_Msg& amsg);

  Standard_EXPORT void AddWarning(const occ::handle<Transfer_Finder>& start,
                                  const char*                         mess,
                                  const char*                         orig = "");

  Standard_EXPORT void AddWarning(const occ::handle<Transfer_Finder>& start,
                                  const Message_Msg&                  amsg);

  Standard_EXPORT void Mend(const occ::handle<Transfer_Finder>& start, const char* pref = "");

  Standard_EXPORT occ::handle<Interface_Check> Check(
    const occ::handle<Transfer_Finder>& start) const;

  Standard_EXPORT void BindTransient(const occ::handle<Transfer_Finder>&    start,
                                     const occ::handle<Standard_Transient>& res);

  Standard_EXPORT const occ::handle<Standard_Transient>& FindTransient(
    const occ::handle<Transfer_Finder>& start) const;

  Standard_EXPORT void BindMultiple(const occ::handle<Transfer_Finder>& start);

  Standard_EXPORT void AddMultiple(const occ::handle<Transfer_Finder>&    start,
                                   const occ::handle<Standard_Transient>& res);

  Standard_EXPORT bool FindTypedTransient(const occ::handle<Transfer_Finder>& start,
                                          const occ::handle<Standard_Type>&   atype,
                                          occ::handle<Standard_Transient>&    val) const;

  template <class T>
  bool FindTypedTransient(const occ::handle<Transfer_Finder>& start,
                          const occ::handle<Standard_Type>&   atype,
                          occ::handle<T>&                     val) const
  {
    occ::handle<Standard_Transient> aVal = val;
    return FindTypedTransient(start, atype, aVal) && !(val = occ::down_cast<T>(aVal)).IsNull();
  }

  Standard_EXPORT bool GetTypedTransient(const occ::handle<Transfer_Binder>& binder,
                                         const occ::handle<Standard_Type>&   atype,
                                         occ::handle<Standard_Transient>&    val) const;

  template <class T>
  bool GetTypedTransient(const occ::handle<Transfer_Binder>& start,
                         const occ::handle<Standard_Type>&   atype,
                         occ::handle<T>&                     val) const
  {
    occ::handle<Standard_Transient> aVal = val;
    return GetTypedTransient(start, atype, aVal) && !(val = occ::down_cast<T>(aVal)).IsNull();
  }

  Standard_EXPORT int NbMapped() const;

  Standard_EXPORT const occ::handle<Transfer_Finder>& Mapped(const int num) const;

  Standard_EXPORT int MapIndex(const occ::handle<Transfer_Finder>& start) const;

  Standard_EXPORT occ::handle<Transfer_Binder> MapItem(const int num) const;

  Standard_EXPORT void SetRoot(const occ::handle<Transfer_Finder>& start);

  Standard_EXPORT void SetRootManagement(const bool stat);

  Standard_EXPORT int NbRoots() const;

  Standard_EXPORT const occ::handle<Transfer_Finder>& Root(const int num) const;

  Standard_EXPORT occ::handle<Transfer_Binder> RootItem(const int num) const;

  Standard_EXPORT int RootIndex(const occ::handle<Transfer_Finder>& start) const;

  Standard_EXPORT int NestingLevel() const;

  Standard_EXPORT void ResetNestingLevel();

  Standard_EXPORT bool Recognize(const occ::handle<Transfer_Finder>& start) const;

  Standard_EXPORT occ::handle<Transfer_Binder> Transferring(
    const occ::handle<Transfer_Finder>& start,
    const Message_ProgressRange&        theProgress = Message_ProgressRange());

  Standard_EXPORT bool Transfer(const occ::handle<Transfer_Finder>& start,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void SetErrorHandle(const bool err);

  Standard_EXPORT bool ErrorHandle() const;

  Standard_EXPORT void StartTrace(const occ::handle<Transfer_Binder>& binder,
                                  const occ::handle<Transfer_Finder>& start,
                                  const int                           level,
                                  const int                           mode) const;

  Standard_EXPORT virtual void PrintTrace(const occ::handle<Transfer_Finder>& start,
                                          Standard_OStream&                   S) const;

  Standard_EXPORT bool IsLooping(const int alevel) const;

  Standard_EXPORT Transfer_IteratorOfProcessForFinder
    RootResult(const bool withstart = false) const;

  Standard_EXPORT Transfer_IteratorOfProcessForFinder
    CompleteResult(const bool withstart = false) const;

  Standard_EXPORT Transfer_IteratorOfProcessForFinder AbnormalResult() const;

  Standard_EXPORT Interface_CheckIterator CheckList(const bool erronly) const;

  Standard_EXPORT Transfer_IteratorOfProcessForFinder
    ResultOne(const occ::handle<Transfer_Finder>& start,
              const int                           level,
              const bool                          withstart = false) const;

  Standard_EXPORT Interface_CheckIterator CheckListOne(const occ::handle<Transfer_Finder>& start,
                                                       const int                           level,
                                                       const bool erronly) const;

  Standard_EXPORT bool IsCheckListEmpty(const occ::handle<Transfer_Finder>& start,
                                        const int                           level,
                                        const bool                          erronly) const;

  Standard_EXPORT void RemoveResult(const occ::handle<Transfer_Finder>& start,
                                    const int                           level,
                                    const bool                          compute = true);

  Standard_EXPORT virtual int CheckNum(const occ::handle<Transfer_Finder>& start) const;

  DEFINE_STANDARD_RTTI_INLINE(Transfer_ProcessForFinder, Standard_Transient)

private:
  Standard_EXPORT occ::handle<Transfer_Binder> FindAndMask(
    const occ::handle<Transfer_Finder>& start);

  Standard_EXPORT occ::handle<Transfer_Binder> TransferProduct(
    const occ::handle<Transfer_Finder>& start,
    const Message_ProgressRange&        theProgress = Message_ProgressRange());

  bool                                          theerrh;
  int                                           thetrace;
  occ::handle<Message_Messenger>                themessenger;
  int                                           thelevel;
  int                                           therootl;
  bool                                          therootm;
  NCollection_IndexedMap<int>                   theroots;
  occ::handle<Transfer_Finder>                  thelastobj;
  occ::handle<Transfer_Binder>                  thelastbnd;
  int                                           theindex;
  occ::handle<Transfer_ActorOfProcessForFinder> theactor;
  NCollection_IndexedDataMap<occ::handle<Transfer_Finder>,
                             occ::handle<Transfer_Binder>,
                             Transfer_FindHasher>
    themap;
};
