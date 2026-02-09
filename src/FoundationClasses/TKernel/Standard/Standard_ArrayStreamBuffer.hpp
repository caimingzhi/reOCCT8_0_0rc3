#pragma once

#include <Standard_Type.hpp>

#include <fstream>

#ifdef _MSC_VER
  #pragma warning(push)
  #pragma warning(disable : 4996)
#endif

class Standard_ArrayStreamBuffer : public std::streambuf
{
public:
  Standard_EXPORT Standard_ArrayStreamBuffer(const char* theBegin, const size_t theSize);

  Standard_EXPORT ~Standard_ArrayStreamBuffer() override;

  Standard_EXPORT virtual void Init(const char* theBegin, const size_t theSize);

protected:
  Standard_EXPORT int_type underflow() override;

  Standard_EXPORT int_type uflow() override;

  Standard_EXPORT int_type pbackfail(int_type ch) override;

  Standard_EXPORT std::streamsize showmanyc() override;

  Standard_EXPORT pos_type seekoff(off_type                theOff,
                                   std::ios_base::seekdir  theWay,
                                   std::ios_base::openmode theWhich) override;

  Standard_EXPORT pos_type seekpos(pos_type thePosition, std::ios_base::openmode theWhich) override;

public:
  Standard_EXPORT std::streamsize xsgetn(char* thePtr, std::streamsize theCount) override;

private:
  Standard_ArrayStreamBuffer(const Standard_ArrayStreamBuffer&)            = delete;
  Standard_ArrayStreamBuffer& operator=(const Standard_ArrayStreamBuffer&) = delete;

protected:
  const char* myBegin;
  const char* myEnd;
  const char* myCurrent;
};

#ifdef _MSC_VER
  #pragma warning(pop)
#endif
