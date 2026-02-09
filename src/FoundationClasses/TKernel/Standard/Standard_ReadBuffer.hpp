#pragma once

#include <Standard_ProgramError.hpp>

#include <iostream>

class Standard_ReadBuffer
{
public:
  Standard_ReadBuffer(int64_t theDataLen, size_t theChunkLen, bool theIsPartialPayload = false)
      : myBufferPtr(nullptr),
        myBufferEnd(nullptr),
        myDataLen(0),
        myDataRead(0),
        myChunkLen(0),
        myNbChunks(0),
        myBufferLen(0)
  {
    Init(theDataLen, theChunkLen, theIsPartialPayload);
  }

  void Init(int64_t theDataLen, size_t theChunkLen, bool theIsPartialPayload = false)
  {
    myDataRead = 0;
    if (theIsPartialPayload)
    {
      myDataLen = theDataLen;
    }
    else
    {
      myDataLen = theDataLen - theDataLen % int64_t(theChunkLen);
    }
    myChunkLen  = theChunkLen;
    myNbChunks  = sizeof(myBuffer) / theChunkLen;
    myBufferLen = theChunkLen * myNbChunks;

    myBufferEnd = myBuffer + sizeof(myBuffer);
    myBufferPtr = myBuffer + sizeof(myBuffer);
    memset(myBuffer, 0, sizeof(myBuffer));

    if (theChunkLen > sizeof(myBuffer))
    {
      throw Standard_ProgramError(
        "Internal error - chunk size is greater then preallocated buffer");
    }
  }

  bool IsDone() const { return myDataRead == myDataLen; }

  template <typename Chunk_T, typename Stream_T>
  Chunk_T* ReadChunk(Stream_T& theStream)
  {
    return reinterpret_cast<Chunk_T*>(readRawDataChunk(theStream));
  }

  template <typename Stream_T>
  char* ReadDataChunk(Stream_T& theStream)
  {
    return readRawDataChunk(theStream);
  }

private:
  template <typename Stream_T>
  char* readRawDataChunk(Stream_T& theStream)
  {
    if (myBufferPtr == nullptr)
    {
      return nullptr;
    }

    myBufferPtr += myChunkLen;
    if (myBufferPtr < myBufferEnd)
    {
      return myBufferPtr;
    }

    const int64_t aDataLeft = myDataLen - myDataRead;
    if (aDataLeft <= 0)

    {
      myBufferPtr = nullptr;
      return nullptr;
    }

    const size_t aDataToRead = int64_t(myBufferLen) > aDataLeft ? size_t(aDataLeft) : myBufferLen;
    if (!readStream(theStream, aDataToRead))
    {
      myBufferPtr = nullptr;
      return nullptr;
    }

    myBufferPtr = myBuffer;
    myBufferEnd = myBuffer + aDataToRead;
    myDataRead += aDataToRead;
    return myBufferPtr;
  }

  bool readStream(std::istream& theStream, size_t theLen)
  {
    theStream.read(myBuffer, theLen);
    return theStream.good();
  }

  bool readStream(FILE* theStream, size_t theLen)
  {
    return ::fread(myBuffer, 1, theLen, theStream) == theLen;
  }

private:
  char        myBuffer[4096];
  char*       myBufferPtr;
  const char* myBufferEnd;
  int64_t     myDataLen;
  int64_t     myDataRead;

  size_t myChunkLen;
  size_t myNbChunks;
  size_t myBufferLen;
};
