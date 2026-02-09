#pragma once

#include <memory>
#include <string>

template <typename T>
class OSD_StreamBuffer : public T
{
public:
  OSD_StreamBuffer(const std::string& theUrl, const std::shared_ptr<std::streambuf>& theBuffer)
      : T(theBuffer.get()),
        myUrl(theUrl),
        myBuffer(theBuffer)
  {
  }

  const std::string& Url() const { return myUrl; }

protected:
  std::string                     myUrl;
  std::shared_ptr<std::streambuf> myBuffer;
};

typedef OSD_StreamBuffer<std::istream>  OSD_IStreamBuffer;
typedef OSD_StreamBuffer<std::ostream>  OSD_OStreamBuffer;
typedef OSD_StreamBuffer<std::iostream> OSD_IOStreamBuffer;
