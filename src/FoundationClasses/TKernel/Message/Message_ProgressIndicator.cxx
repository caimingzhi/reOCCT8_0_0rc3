

#include <Message_ProgressIndicator.hpp>

IMPLEMENT_STANDARD_RTTIEXT(System::log::Message_ProgressIndicator, Standard_Transient)

System::log::Message_ProgressIndicator::Message_ProgressIndicator()
    : myPosition(0.),
      myRootScope(nullptr)
{
  myRootScope = new System::log::Message_ProgressScope(this);
}

System::log::Message_ProgressIndicator::~Message_ProgressIndicator()
{

  myRootScope->myProgress = nullptr;
  myRootScope->myIsActive = false;
  delete myRootScope;
}

System::log::Message_ProgressRange System::log::Message_ProgressIndicator::Start()
{
  myPosition           = 0.;
  myRootScope->myValue = 0.;
  Reset();
  Show(*myRootScope, false);
  return myRootScope->Next();
}

System::log::Message_ProgressRange System::log::Message_ProgressIndicator::Start(
  const occ::handle<System::log::Message_ProgressIndicator>& theProgress)
{
  return theProgress.IsNull() ? System::log::Message_ProgressRange() : theProgress->Start();
}
