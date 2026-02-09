#pragma once

#include <Message_Level.hpp>
#include <Message_Alert.hpp>
#include <NCollection_List.hpp>
#include <Message_MetricType.hpp>
#include <NCollection_IndexedMap.hpp>
#include <NCollection_Sequence.hpp>

#include <mutex>

class Message_CompositeAlerts;
class Message_Messenger;

class Message_Report : public Standard_Transient
{
public:
  Standard_EXPORT Message_Report();

  Standard_EXPORT void AddAlert(Message_Gravity                   theGravity,
                                const occ::handle<Message_Alert>& theAlert);

  Standard_EXPORT const NCollection_List<occ::handle<Message_Alert>>& GetAlerts(
    Message_Gravity theGravity) const;

  Standard_EXPORT bool HasAlert(const occ::handle<Standard_Type>& theType);

  Standard_EXPORT bool HasAlert(const occ::handle<Standard_Type>& theType,
                                Message_Gravity                   theGravity);

  Standard_EXPORT bool IsActiveInMessenger(
    const occ::handle<Message_Messenger>& theMessenger = nullptr) const;

  Standard_EXPORT void ActivateInMessenger(
    const bool                            toActivate,
    const occ::handle<Message_Messenger>& theMessenger = nullptr);

  Standard_EXPORT void UpdateActiveInMessenger(
    const occ::handle<Message_Messenger>& theMessenger = nullptr);

  Standard_EXPORT void AddLevel(Message_Level* theLevel, const TCollection_AsciiString& theName);

  Standard_EXPORT void RemoveLevel(Message_Level* theLevel);

  Standard_EXPORT void Clear();

  Standard_EXPORT void Clear(Message_Gravity theGravity);

  Standard_EXPORT void Clear(const occ::handle<Standard_Type>& theType);

  const NCollection_IndexedMap<Message_MetricType>& ActiveMetrics() const
  {
    return myActiveMetrics;
  }

  Standard_EXPORT void SetActiveMetric(const Message_MetricType theMetricType,
                                       const bool               theActivate);

  void ClearMetrics() { myActiveMetrics.Clear(); }

  int Limit() const { return myLimit; }

  void SetLimit(const int theLimit) { myLimit = theLimit; }

  Standard_EXPORT void Dump(Standard_OStream& theOS);

  Standard_EXPORT void Dump(Standard_OStream& theOS, Message_Gravity theGravity);

  Standard_EXPORT virtual void SendMessages(const occ::handle<Message_Messenger>& theMessenger);

  Standard_EXPORT virtual void SendMessages(const occ::handle<Message_Messenger>& theMessenger,
                                            Message_Gravity                       theGravity);

  Standard_EXPORT void Merge(const occ::handle<Message_Report>& theOther);

  Standard_EXPORT void Merge(const occ::handle<Message_Report>& theOther,
                             Message_Gravity                    theGravity);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

  DEFINE_STANDARD_RTTIEXT(Message_Report, Standard_Transient)

protected:
  Standard_EXPORT const occ::handle<Message_CompositeAlerts>& compositeAlerts(
    const bool isCreate = false);

  Standard_EXPORT void sendMessages(const occ::handle<Message_Messenger>&       theMessenger,
                                    Message_Gravity                             theGravity,
                                    const occ::handle<Message_CompositeAlerts>& theCompositeAlert);

  Standard_EXPORT void dumpMessages(Standard_OStream&                           theOS,
                                    Message_Gravity                             theGravity,
                                    const occ::handle<Message_CompositeAlerts>& theCompositeAlert);

protected:
  std::mutex myMutex;

  occ::handle<Message_CompositeAlerts> myCompositAlerts;

  NCollection_Sequence<Message_Level*> myAlertLevels;

  NCollection_IndexedMap<Message_MetricType> myActiveMetrics;

  int  myLimit;
  bool myIsActiveInMessenger;
};
