

#include <Message_ProgressIndicator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Message_ProgressIndicator, Standard_Transient)

Message_ProgressIndicator::Message_ProgressIndicator()
    : myPosition(0.),
      myRootScope(nullptr)
{
  myRootScope = new Message_ProgressScope(this);
}

Message_ProgressIndicator::~Message_ProgressIndicator()
{

  myRootScope->myProgress = nullptr;
  myRootScope->myIsActive = false;
  delete myRootScope;
}

Message_ProgressRange Message_ProgressIndicator::Start()
{
  myPosition           = 0.;
  myRootScope->myValue = 0.;
  Reset();
  Show(*myRootScope, false);
  return myRootScope->Next();
}

Message_ProgressRange Message_ProgressIndicator::Start(
  const occ::handle<Message_ProgressIndicator>& theProgress)
{
  return theProgress.IsNull() ? Message_ProgressRange() : theProgress->Start();
}
