#pragma once

#include <iostream>
#include <vector>

class Standard_ReadLineBuffer
{
public:
  Standard_ReadLineBuffer(size_t theMaxBufferSizeBytes)
      : myUseReadBufferLastStr(false),
        myIsMultilineMode(false),
        myToPutGapInMultiline(true),
        myBufferPos(0),
        myBytesLastRead(0)
  {

    myReadBuffer.resize(theMaxBufferSizeBytes);
  }

  virtual ~Standard_ReadLineBuffer() = default;

  void Clear()
  {
    myReadBufferLastStr.clear();
    myUseReadBufferLastStr = false;
    myIsMultilineMode      = false;
    myToPutGapInMultiline  = true;
    myBufferPos            = 0;
    myBytesLastRead        = 0;
  }

  template <typename Stream_T>
  const char* ReadLine(Stream_T& theStream, size_t& theLineLength)
  {
    int64_t aReadData = 0;
    return ReadLine(theStream, theLineLength, aReadData);
  }

  template <typename Stream_T>
  const char* ReadLine(Stream_T& theStream, size_t& theLineLength, int64_t& theReadData)
  {
    char* aResultLine = nullptr;
    bool  isMultiline = false;
    theLineLength     = 0;
    theReadData       = 0;

    while (aResultLine == nullptr)
    {
      if (myBufferPos == 0 || myBufferPos >= (myBytesLastRead))
      {

        if (!readStream(theStream, myReadBuffer.size(), myBytesLastRead))
        {

          break;
        }

        theReadData = myBytesLastRead;

        if (myBytesLastRead > 0)
        {
          myBufferPos = 0;
        }
        else
        {

          if (myUseReadBufferLastStr)
          {
            theLineLength          = myReadBufferLastStr.size();
            aResultLine            = &myReadBufferLastStr.front();
            myUseReadBufferLastStr = false;
          }
          break;
        }
      }

      size_t aStartLinePos  = myBufferPos;
      bool   isEndLineFound = false;

      while (myBufferPos < myBytesLastRead)
      {
        if (myIsMultilineMode && myReadBuffer[myBufferPos] == '\\')
        {

          if (myBufferPos + 1 == myBytesLastRead
              || (myBufferPos + 2 == myBytesLastRead && myReadBuffer[myBufferPos + 1] == '\r'))
          {
            isMultiline = true;
            if (myToPutGapInMultiline)
            {
              myReadBuffer[myBufferPos] = ' ';
              if (myBufferPos + 1 != myBytesLastRead)
              {
                myReadBuffer[myBufferPos + 1] = ' ';
              }
            }
          }
          else if (myReadBuffer[myBufferPos + 1] == '\n'
                   || (myReadBuffer[myBufferPos + 1] == '\r'
                       && myReadBuffer[myBufferPos + 2] == '\n'))
          {
            size_t aBufferPos = myBufferPos;
            myBufferPos       = aBufferPos + (myReadBuffer[aBufferPos + 1] == '\r' ? 2 : 1);
            if (myToPutGapInMultiline)
            {
              myReadBuffer[aBufferPos] = ' ';
              ++aBufferPos;
            }

            if (myUseReadBufferLastStr)
            {
              myReadBufferLastStr.insert(myReadBufferLastStr.end(),
                                         myReadBuffer.begin() + aStartLinePos,
                                         myReadBuffer.begin() + aBufferPos);
            }
            else
            {
              myReadBufferLastStr    = std::vector<char>(myReadBuffer.begin() + aStartLinePos,
                                                      myReadBuffer.begin() + aBufferPos);
              myUseReadBufferLastStr = true;
            }

            aStartLinePos = myBufferPos + 1;
          }
        }
        else if (myReadBuffer[myBufferPos] == '\n')
        {
          if (!isMultiline)
          {
            isEndLineFound = true;
          }
          else if (myBufferPos == 1 && myReadBuffer[0] == '\r')
          {
            myReadBufferLastStr.erase(myReadBufferLastStr.end() - 1);
            aStartLinePos += 2;
            isMultiline = false;
          }
          else if (myBufferPos == 0)
          {
            aStartLinePos += 1;
            if (myReadBufferLastStr[myReadBufferLastStr.size() - 1] == '\\')
            {
              myReadBufferLastStr.erase(myReadBufferLastStr.end() - 1);
            }
            else
            {
              myReadBufferLastStr.erase(myReadBufferLastStr.end() - 2, myReadBufferLastStr.end());
            }
            isMultiline = false;
          }
        }

        ++myBufferPos;

        if (isEndLineFound)
          break;
      }

      if (isEndLineFound)
      {
        if (myUseReadBufferLastStr)
        {

          myReadBufferLastStr.insert(myReadBufferLastStr.end(),
                                     myReadBuffer.begin() + aStartLinePos,
                                     myReadBuffer.begin() + myBufferPos);
          myUseReadBufferLastStr = false;
          theLineLength          = myReadBufferLastStr.size();
          aResultLine            = &myReadBufferLastStr.front();
        }
        else
        {
          if (myReadBufferLastStr.size() > 0)
          {
            myReadBufferLastStr.clear();
          }
          theLineLength = myBufferPos - aStartLinePos;
          aResultLine   = &myReadBuffer.front() + aStartLinePos;
        }

        if (theLineLength > 1 && aResultLine[theLineLength - 2] == '\r')
        {
          aResultLine[theLineLength - 2] = '\0';
          theLineLength -= 2;
        }
        else
        {
          aResultLine[theLineLength - 1] = '\0';
          theLineLength -= 1;
        }
      }
      else
      {

        if (aStartLinePos != myBufferPos)
        {
          if (myUseReadBufferLastStr)
          {
            myReadBufferLastStr.insert(myReadBufferLastStr.end(),
                                       myReadBuffer.begin() + aStartLinePos,
                                       myReadBuffer.begin() + myBufferPos);
          }
          else
          {
            myReadBufferLastStr    = std::vector<char>(myReadBuffer.begin() + aStartLinePos,
                                                    myReadBuffer.begin() + myBufferPos);
            myUseReadBufferLastStr = true;
          }
        }
      }
    }
    return aResultLine;
  }

  bool IsMultilineMode() const { return myIsMultilineMode; }

  bool ToPutGapInMultiline() const { return myToPutGapInMultiline; }

  void SetMultilineMode(bool theMultilineMode, bool theToPutGap = true)
  {
    myIsMultilineMode     = theMultilineMode;
    myToPutGapInMultiline = theToPutGap;
  }

protected:
  bool readStream(std::istream& theStream, size_t theLen, size_t& theReadLen)
  {
    theReadLen = (size_t)theStream.read(&myReadBuffer.front(), theLen).gcount();
    return !theStream.bad();
  }

  bool readStream(FILE* theStream, size_t theLen, size_t& theReadLen)
  {
    theReadLen = ::fread(&myReadBuffer.front(), 1, theLen, theStream);
    return ::ferror(theStream) == 0;
  }

protected:
  std::vector<char> myReadBuffer;
  std::vector<char> myReadBufferLastStr;

  bool   myUseReadBufferLastStr;
  bool   myIsMultilineMode;
  bool   myToPutGapInMultiline;
  size_t myBufferPos;
  size_t myBytesLastRead;
};
