

#include <Interface_LineBuffer.hpp>
#include <Standard_OutOfRange.hpp>
#include <TCollection_AsciiString.hpp>
#include <TCollection_HAsciiString.hpp>

Interface_LineBuffer::Interface_LineBuffer(const int size)
    : myLine(1, size + 1)
{
  myLine.SetValue(1, '\0');
  myMax  = size;
  myInit = myLen = myGet = myKeep = myFriz = 0;
}

void Interface_LineBuffer::SetMax(const int theMax)
{
  if (theMax > myLine.Length())
  {
    throw Standard_OutOfRange("Interface LineBuffer : SetMax");
  }
  if (theMax <= 0)
  {
    myMax = myLine.Length();
  }
  else
  {
    myMax = theMax;
  }
}

void Interface_LineBuffer::SetInitial(const int theInitial)
{
  if (myFriz > 0)
  {
    return;
  }
  if (theInitial >= myMax)
  {
    throw Standard_OutOfRange("Interface LineBuffer : SetInitial");
  }
  if (theInitial <= 0)
  {
    myInit = 0;
  }
  else
  {
    myInit = theInitial;
  }
}

void Interface_LineBuffer::SetKeep()
{
  myKeep = -myLen;
}

bool Interface_LineBuffer::CanGet(const int theMore)
{
  myGet = theMore;
  if ((myLen + myInit + theMore) <= myMax)
  {
    return true;
  }
  if (myKeep < 0)
  {
    myKeep = -myKeep;
  }
  return false;
}

void Interface_LineBuffer::FreezeInitial()
{
  myFriz = myInit + 1;
  myInit = 0;
}

void Interface_LineBuffer::Clear()
{
  myGet = myKeep = myLen = myFriz = 0;
  myLine.SetValue(1, '\0');
}

void Interface_LineBuffer::Prepare()
{

  if (myInit > 0)
  {
    if ((myLen + myInit) > myMax)
    {
      return;
    }

    for (int i = myLen + 1; i > 0; --i)
    {
      myLine.SetValue(i + myInit, myLine.Value(i));
    }
    for (int i = 1; i <= myInit; ++i)
    {
      myLine.SetValue(i, ' ');
    }
  }

  if (myKeep > 0)
  {
    myKeep += (myInit + 1);
  }
  if (myKeep > 0)
  {
    if ((myLen + myGet + myInit - myKeep) >= myMax)
    {
      myKeep = 0;
    }
  }
  if (myKeep > 0)
  {
    myKept = myLine.Value(myKeep);
    myLine.SetValue(myKeep, '\0');
  }
}

void Interface_LineBuffer::Keep()
{

  if (myKeep > 0)
  {
    myLine.SetValue(1, myKept);
    for (int i = myKeep + 1; i <= myLen + myInit + 1; ++i)
    {
      myLine.SetValue(i - myKeep + 1, myLine.Value(i));
    }
    myLen = myLen + myInit - myKeep + 1;
  }
  else
  {
    Clear();
  }
  myGet = myKeep = 0;
  if (myFriz > 0)
  {
    myInit = myFriz - 1;
    myFriz = 0;
  }
}

void Interface_LineBuffer::Move(TCollection_AsciiString& theStr)
{
  Prepare();
  theStr.AssignCat(&myLine.First());
  Keep();
}

void Interface_LineBuffer::Move(const occ::handle<TCollection_HAsciiString>& theStr)
{
  Prepare();
  theStr->AssignCat(&myLine.First());
  Keep();
}

occ::handle<TCollection_HAsciiString> Interface_LineBuffer::Moved()
{
  Prepare();
  occ::handle<TCollection_HAsciiString> R = new TCollection_HAsciiString(&myLine.First());
  Keep();
  return R;
}

void Interface_LineBuffer::Add(const char* theText)
{
  Add(theText, (int)strlen(theText));
}

void Interface_LineBuffer::Add(const char* text, const int lntext)
{
  int lnt = (lntext > (myMax - myLen - myInit) ? (myMax - myLen - myInit) : lntext);
  for (int i = 1; i <= lnt; ++i)
  {
    myLine.SetValue(myLen + i, text[i - 1]);
  }
  myLen += lnt;
  myLine.SetValue(myLen + 1, '\0');
}

void Interface_LineBuffer::Add(const TCollection_AsciiString& theText)
{
  Add(theText.ToCString(), theText.Length());
}

void Interface_LineBuffer::Add(const char theText)
{
  myLine.SetValue(myLen + 1, theText);
  ++myLen;
  myLine.SetValue(myLen + 1, '\0');
}
