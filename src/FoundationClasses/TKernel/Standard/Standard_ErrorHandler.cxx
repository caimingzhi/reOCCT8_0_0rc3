

#include <Standard_ErrorHandler.hpp>

static thread_local Standard_ErrorHandler* Top = nullptr;

Standard_ErrorHandler::Standard_ErrorHandler()
{
  myPrevious = Top;
  Top        = this;
}

void Standard_ErrorHandler::Destroy()
{
  Unlink();
}

void Standard_ErrorHandler::Unlink()
{

  while (Top != nullptr && Top != this)
  {
    Top->Unlink();
  }

  if (Top == this)
  {
    Top = myPrevious;
  }

  myPrevious = nullptr;

  void* aPtr    = myCallbackPtr;
  myCallbackPtr = nullptr;
  while (aPtr)
  {
    Standard_ErrorHandler::Callback* aCallback = (Standard_ErrorHandler::Callback*)aPtr;
    aPtr                                       = aCallback->myNext;

    aCallback->DestroyCallback();
  }
}

bool Standard_ErrorHandler::IsInTryBlock()
{
  Standard_ErrorHandler* anActive = FindHandler();
  return anActive != nullptr;
}

void Standard_ErrorHandler::Raise()
{
  if (std::holds_alternative<std::monostate>(myCaughtError))
  {
    std::cerr << "*** Abort *** an exception handler was called, but no exception object is set."
              << std::endl;
    exit(1);
  }

  std::visit(
    [](auto&& theException)
    {
      using T = std::decay_t<decltype(theException)>;
      if constexpr (!std::is_same_v<T, std::monostate>)
      {
        throw theException;
      }
    },
    myCaughtError);
}

Standard_ErrorHandler* Standard_ErrorHandler::FindHandler()
{
  return Top;
}

#if defined(OCC_CONVERT_SIGNALS)

Standard_ErrorHandler::Callback::Callback() {}

Standard_ErrorHandler::Callback::~Callback()
{
  UnregisterCallback();
}

void Standard_ErrorHandler::Callback::RegisterCallback()
{
  if (myHandler)
    return;

  Standard_ErrorHandler* aHandler = Standard_ErrorHandler::FindHandler();

  if (aHandler)
  {
    myHandler = aHandler;
    myNext    = aHandler->myCallbackPtr;
    if (myNext)
      ((Standard_ErrorHandler::Callback*)myNext)->myPrev = this;
    aHandler->myCallbackPtr = this;
  }
}

void Standard_ErrorHandler::Callback::UnregisterCallback()
{
  if (!myHandler)
    return;
  if (myNext)
    ((Standard_ErrorHandler::Callback*)myNext)->myPrev = myPrev;
  if (myPrev)
    ((Standard_ErrorHandler::Callback*)myPrev)->myNext = myNext;
  else if (((Standard_ErrorHandler*)myHandler)->myCallbackPtr == this)
    ((Standard_ErrorHandler*)myHandler)->myCallbackPtr = (Standard_ErrorHandler::Callback*)myNext;
  myHandler = myNext = myPrev = nullptr;
}
#endif
