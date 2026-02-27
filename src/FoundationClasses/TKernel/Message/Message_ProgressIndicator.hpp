#pragma once

#include <Standard_Handle.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

#include <mutex>

namespace System { namespace log {
class Message_ProgressRange;
}} // namespace System::log

namespace System { namespace log {
class Message_ProgressScope;
}} // namespace System::log


namespace System { namespace log {
class Message_ProgressIndicator : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Message_ProgressIndicator, Standard_Transient)
public:
  Standard_EXPORT Message_ProgressRange Start();

  Standard_EXPORT static Message_ProgressRange Start(
    const occ::handle<Message_ProgressIndicator>& theProgress);

protected:
  virtual bool UserBreak() { return false; }

  virtual void Show(const Message_ProgressScope& theScope, const bool isForce) = 0;

  virtual void Reset() {}

public:
  double GetPosition() const { return myPosition; }

  Standard_EXPORT ~Message_ProgressIndicator() override;

protected:
  Standard_EXPORT Message_ProgressIndicator();

private:
  void Increment(const double theStep, const Message_ProgressScope& theScope);

private:
  double                 myPosition;
  std::mutex             myMutex;
  Message_ProgressScope* myRootScope;

private:
  friend class Message_ProgressScope;
  friend class Message_ProgressRange;
};
}} // namespace System::log


#include <Message_ProgressScope.hpp>

inline void System::log::Message_ProgressIndicator::Increment(const double                 theStep,
                                                 const System::log::Message_ProgressScope& theScope)
{

  std::lock_guard<std::mutex> aLock(myMutex);

  myPosition = (std::min)(myPosition + theStep, 1.);

  Show(theScope, false);
}
