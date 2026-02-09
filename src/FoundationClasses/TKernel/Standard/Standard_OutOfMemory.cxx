#include <Standard_OutOfMemory.hpp>

#include <algorithm>
#include <cstdlib>
#include <cstring>

Standard_OutOfMemory::Standard_OutOfMemory(const char* theMessage)
{
  myBuffer[0] = '\0';

  Standard_OutOfMemory::SetMessageString(theMessage);
}

const char* Standard_OutOfMemory::what() const noexcept
{
  return myBuffer;
}

void Standard_OutOfMemory::SetMessageString(const char* theMessage)
{

  const size_t aLength = (theMessage ? std::min(std::strlen(theMessage), sizeof(myBuffer) - 1) : 0);

  myBuffer[aLength] = '\0';
  if (aLength > 0)
  {
    std::memcpy(myBuffer, theMessage, aLength);
  }
}
