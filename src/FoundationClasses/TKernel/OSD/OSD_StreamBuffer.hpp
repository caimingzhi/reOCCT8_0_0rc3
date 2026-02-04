#pragma once


#include <memory>
#include <string>

//! A file stream implementation initialized from std::shared_ptr<std::streambuf>.
template <typename T>
class OSD_StreamBuffer : public T
{
public:
  //! Main constructor.
  OSD_StreamBuffer(const std::string& theUrl, const std::shared_ptr<std::streambuf>& theBuffer)
      : T(theBuffer.get()),
        myUrl(theUrl),
        myBuffer(theBuffer)
  {
  }

  //! Return an opened URL.
  const std::string& Url() const { return myUrl; }

protected:
  std::string                     myUrl;
  std::shared_ptr<std::streambuf> myBuffer;
};

typedef OSD_StreamBuffer<std::istream>  OSD_IStreamBuffer;
typedef OSD_StreamBuffer<std::ostream>  OSD_OStreamBuffer;
typedef OSD_StreamBuffer<std::iostream> OSD_IOStreamBuffer;

