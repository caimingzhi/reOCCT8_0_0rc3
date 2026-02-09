#pragma once

#include <Standard_Integer.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_IndexedDataMap.hpp>
#include <Transfer_Binder.hpp>
#include <Message_ProgressRange.hpp>

class Message_Messenger;
class Transfer_Binder;
class Transfer_ActorOfProcessForTransient;
class Interface_InterfaceError;
class Transfer_TransferFailure;
class Transfer_IteratorOfProcessForTransient;
class Message_Msg;
class Interface_Check;
class Interface_CheckIterator;

class Transfer_ProcessForTransient : public Standard_Transient
{

public:
  Standard_EXPORT Transfer_ProcessForTransient(const int nb = 10000);

  Standard_EXPORT Transfer_ProcessForTransient(const occ::handle<Message_Messenger>& printer,
                                               const int                             nb = 10000);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Clean();

  Standard_EXPORT void Resize(const int nb);

  Standard_EXPORT void SetActor(const occ::handle<Transfer_ActorOfProcessForTransient>& actor);

  Standard_EXPORT occ::handle<Transfer_ActorOfProcessForTransient> Actor() const;

  Standard_EXPORT occ::handle<Transfer_Binder> Find(
    const occ::handle<Standard_Transient>& start) const;

  Standard_EXPORT bool IsBound(const occ::handle<Standard_Transient>& start) const;

  Standard_EXPORT bool IsAlreadyUsed(const occ::handle<Standard_Transient>& start) const;

  Standard_EXPORT void Bind(const occ::handle<Standard_Transient>& start,
                            const occ::handle<Transfer_Binder>&    binder);

  Standard_EXPORT void Rebind(const occ::handle<Standard_Transient>& start,
                              const occ::handle<Transfer_Binder>&    binder);

  Standard_EXPORT bool Unbind(const occ::handle<Standard_Transient>& start);

  Standard_EXPORT occ::handle<Transfer_Binder> FindElseBind(
    const occ::handle<Standard_Transient>& start);

  Standard_EXPORT void SetMessenger(const occ::handle<Message_Messenger>& messenger);

  Standard_EXPORT occ::handle<Message_Messenger> Messenger() const;

  Standard_EXPORT void SetTraceLevel(const int tracelev);

  Standard_EXPORT int TraceLevel() const;

  Standard_EXPORT void SendFail(const occ::handle<Standard_Transient>& start,
                                const Message_Msg&                     amsg);

  Standard_EXPORT void SendWarning(const occ::handle<Standard_Transient>& start,
                                   const Message_Msg&                     amsg);

  Standard_EXPORT void SendMsg(const occ::handle<Standard_Transient>& start,
                               const Message_Msg&                     amsg);

  Standard_EXPORT void AddFail(const occ::handle<Standard_Transient>& start,
                               const char*                            mess,
                               const char*                            orig = "");

  Standard_EXPORT void AddError(const occ::handle<Standard_Transient>& start,
                                const char*                            mess,
                                const char*                            orig = "");

  Standard_EXPORT void AddFail(const occ::handle<Standard_Transient>& start,
                               const Message_Msg&                     amsg);

  Standard_EXPORT void AddWarning(const occ::handle<Standard_Transient>& start,
                                  const char*                            mess,
                                  const char*                            orig = "");

  Standard_EXPORT void AddWarning(const occ::handle<Standard_Transient>& start,
                                  const Message_Msg&                     amsg);

  Standard_EXPORT void Mend(const occ::handle<Standard_Transient>& start, const char* pref = "");

  Standard_EXPORT occ::handle<Interface_Check> Check(
    const occ::handle<Standard_Transient>& start) const;

  Standard_EXPORT void BindTransient(const occ::handle<Standard_Transient>& start,
                                     const occ::handle<Standard_Transient>& res);

  Standard_EXPORT const occ::handle<Standard_Transient>& FindTransient(
    const occ::handle<Standard_Transient>& start) const;

  Standard_EXPORT void BindMultiple(const occ::handle<Standard_Transient>& start);

  Standard_EXPORT void AddMultiple(const occ::handle<Standard_Transient>& start,
                                   const occ::handle<Standard_Transient>& res);

  Standard_EXPORT bool FindTypedTransient(const occ::handle<Standard_Transient>& start,
                                          const occ::handle<Standard_Type>&      atype,
                                          occ::handle<Standard_Transient>&       val) const;

  Standard_EXPORT bool GetTypedTransient(const occ::handle<Transfer_Binder>& binder,
                                         const occ::handle<Standard_Type>&   atype,
                                         occ::handle<Standard_Transient>&    val) const;

  Standard_EXPORT int NbMapped() const;

  Standard_EXPORT const occ::handle<Standard_Transient>& Mapped(const int num) const;

  Standard_EXPORT int MapIndex(const occ::handle<Standard_Transient>& start) const;

  Standard_EXPORT occ::handle<Transfer_Binder> MapItem(const int num) const;

  Standard_EXPORT void SetRoot(const occ::handle<Standard_Transient>& start);

  Standard_EXPORT void SetRootManagement(const bool stat);

  Standard_EXPORT int NbRoots() const;

  Standard_EXPORT const occ::handle<Standard_Transient>& Root(const int num) const;

  Standard_EXPORT occ::handle<Transfer_Binder> RootItem(const int num) const;

  Standard_EXPORT int RootIndex(const occ::handle<Standard_Transient>& start) const;

  Standard_EXPORT int NestingLevel() const;

  Standard_EXPORT void ResetNestingLevel();

  Standard_EXPORT bool Recognize(const occ::handle<Standard_Transient>& start) const;

  Standard_EXPORT occ::handle<Transfer_Binder> Transferring(
    const occ::handle<Standard_Transient>& start,
    const Message_ProgressRange&           theProgress = Message_ProgressRange());

  Standard_EXPORT bool Transfer(const occ::handle<Standard_Transient>& start,
                                const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT void SetErrorHandle(const bool err);

  Standard_EXPORT bool ErrorHandle() const;

  Standard_EXPORT void StartTrace(const occ::handle<Transfer_Binder>&    binder,
                                  const occ::handle<Standard_Transient>& start,
                                  const int                              level,
                                  const int                              mode) const;

  Standard_EXPORT virtual void PrintTrace(const occ::handle<Standard_Transient>& start,
                                          Standard_OStream&                      S) const;

  Standard_EXPORT bool IsLooping(const int alevel) const;

  Standard_EXPORT Transfer_IteratorOfProcessForTransient
    RootResult(const bool withstart = false) const;

  Standard_EXPORT Transfer_IteratorOfProcessForTransient
    CompleteResult(const bool withstart = false) const;

  Standard_EXPORT Transfer_IteratorOfProcessForTransient AbnormalResult() const;

  Standard_EXPORT Interface_CheckIterator CheckList(const bool erronly) const;

  Standard_EXPORT Transfer_IteratorOfProcessForTransient
    ResultOne(const occ::handle<Standard_Transient>& start,
              const int                              level,
              const bool                             withstart = false) const;

  Standard_EXPORT Interface_CheckIterator CheckListOne(const occ::handle<Standard_Transient>& start,
                                                       const int                              level,
                                                       const bool erronly) const;

  Standard_EXPORT bool IsCheckListEmpty(const occ::handle<Standard_Transient>& start,
                                        const int                              level,
                                        const bool                             erronly) const;

  Standard_EXPORT void RemoveResult(const occ::handle<Standard_Transient>& start,
                                    const int                              level,
                                    const bool                             compute = true);

  Standard_EXPORT virtual int CheckNum(const occ::handle<Standard_Transient>& start) const;

  DEFINE_STANDARD_RTTI_INLINE(Transfer_ProcessForTransient, Standard_Transient)

private:
  Standard_EXPORT occ::handle<Transfer_Binder> FindAndMask(
    const occ::handle<Standard_Transient>& start);

  Standard_EXPORT occ::handle<Transfer_Binder> TransferProduct(
    const occ::handle<Standard_Transient>& start,
    const Message_ProgressRange&           theProgress = Message_ProgressRange());

  bool                                             theerrh;
  int                                              thetrace;
  occ::handle<Message_Messenger>                   themessenger;
  int                                              thelevel;
  int                                              therootl;
  bool                                             therootm;
  NCollection_IndexedMap<int>                      theroots;
  occ::handle<Standard_Transient>                  thelastobj;
  occ::handle<Transfer_Binder>                     thelastbnd;
  int                                              theindex;
  occ::handle<Transfer_ActorOfProcessForTransient> theactor;
  NCollection_IndexedDataMap<occ::handle<Standard_Transient>, occ::handle<Transfer_Binder>> themap;
};
