#pragma once


#include <OSD_File.hpp>
#include <OSD_Error.hpp>
#include <TCollection_AsciiString.hpp>

class OSD_Path;

//! Manages a breadth-only search for files in the specified Path.
//! There is no specific order of results.
class OSD_FileIterator
{
public:
  DEFINE_STANDARD_ALLOC

  //! Instantiates Object as empty Iterator;
  Standard_EXPORT OSD_FileIterator();

  //! Instantiates Object as Iterator;
  //! Wild-card "*" can be used in Mask the same way it
  //! is used by unix shell for file names
  Standard_EXPORT OSD_FileIterator(const OSD_Path& where, const TCollection_AsciiString& Mask);

  Standard_EXPORT void Destroy();

  ~OSD_FileIterator() { Destroy(); }

  //! Initializes the current File Iterator
  Standard_EXPORT void Initialize(const OSD_Path& where, const TCollection_AsciiString& Mask);

  //! Returns TRUE if there are other items using the 'Tree'
  //! method.
  Standard_EXPORT bool More();

  //! Sets the iterator to the next item.
  //! Returns the item value corresponding to the current
  //! position of the iterator.
  Standard_EXPORT void Next();

  //! Returns the next file found .
  Standard_EXPORT OSD_File Values();

  //! Returns TRUE if an error occurs
  Standard_EXPORT bool Failed() const;

  //! Resets error counter to zero
  Standard_EXPORT void Reset();

  //! Raises OSD_Error
  Standard_EXPORT void Perror();

  //! Returns error number if 'Failed' is TRUE.
  Standard_EXPORT int Error() const;

private:
  OSD_File                TheIterator;
  bool                    myFlag;
  TCollection_AsciiString myMask;
  TCollection_AsciiString myPlace;
  OSD_Error               myError;

  // platform-specific fields
#ifdef _WIN32
  void* myHandle;
  void* myData;
  bool  myFirstCall;
#else
  void* myDescr;
  void* myEntry;
  int   myInit;
#endif
};

