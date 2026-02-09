

#include <RWStl_Reader.hpp>

#include <Message.hpp>
#include <Message_Messenger.hpp>
#include <Message_ProgressScope.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_IncAllocator.hpp>
#include <FSD_BinaryFile.hpp>
#include <OSD_FileSystem.hpp>
#include <OSD_Timer.hpp>
#include <Poly_MergeNodesTool.hpp>
#include <Standard_CLocaleSentry.hpp>

#include <algorithm>
#include <limits>

IMPLEMENT_STANDARD_RTTIEXT(RWStl_Reader, Standard_Transient)

namespace
{

  static const size_t THE_STL_HEADER_SIZE   = 84;
  static const size_t THE_STL_SIZEOF_FACET  = 50;
  static const size_t THE_STL_MIN_FILE_SIZE = THE_STL_HEADER_SIZE + THE_STL_SIZEOF_FACET;

  static const size_t THE_BUFFER_SIZE = 1024;

  class MergeNodeTool : public Poly_MergeNodesTool
  {
  public:
    MergeNodeTool(RWStl_Reader* theReader, const int theNbFacets = -1)
        : Poly_MergeNodesTool(theReader->MergeAngle(), 0.0, theNbFacets),
          myReader(theReader),
          myNodeIndexMap(1024, new NCollection_IncAllocator(1024 * 1024))
    {

      ChangeOutput().Nullify();
    }

    void AddTriangle(const gp_XYZ theElemNodes[3])
    {
      Poly_MergeNodesTool::AddTriangle(theElemNodes);

      int aNodesSrc[3] = {ElementNodeIndex(0), ElementNodeIndex(1), ElementNodeIndex(2)};
      int aNodesRes[3] = {-1, -1, -1};
      for (int aNodeIter = 0; aNodeIter < 3; ++aNodeIter)
      {

        if (!myNodeIndexMap.Find(aNodesSrc[aNodeIter], aNodesRes[aNodeIter]))
        {
          aNodesRes[aNodeIter] = myReader->AddNode(theElemNodes[aNodeIter]);
          myNodeIndexMap.Bind(aNodesSrc[aNodeIter], aNodesRes[aNodeIter]);
        }
      }
      if (aNodesRes[0] != aNodesRes[1] && aNodesRes[1] != aNodesRes[2]
          && aNodesRes[2] != aNodesRes[0])
      {
        myReader->AddTriangle(aNodesRes[0], aNodesRes[1], aNodesRes[2]);
      }
    }

  private:
    RWStl_Reader*                 myReader;
    NCollection_DataMap<int, int> myNodeIndexMap;
  };

  inline static float readStlFloat(const char* theData)
  {
#if OCCT_BINARY_FILE_DO_INVERSE

    union
    {
      uint32_t i;
      float    f;
    } bidargum;

    bidargum.i = theData[0] & 0xFF;
    bidargum.i |= (theData[1] & 0xFF) << 0x08;
    bidargum.i |= (theData[2] & 0xFF) << 0x10;
    bidargum.i |= (theData[3] & 0xFF) << 0x18;
    return bidargum.f;
#else

    return *reinterpret_cast<const float*>(theData);
#endif
  }

  inline static gp_XYZ readStlFloatVec3(const char* theData)
  {
    return gp_XYZ(readStlFloat(theData),
                  readStlFloat(theData + sizeof(float)),
                  readStlFloat(theData + sizeof(float) * 2));
  }

} // namespace

RWStl_Reader::RWStl_Reader()
    : myMergeAngle(M_PI / 2.0),
      myMergeTolearance(0.0)
{
}

bool RWStl_Reader::Read(const char* theFile, const Message_ProgressRange& theProgress)
{
  const occ::handle<OSD_FileSystem>& aFileSystem = OSD_FileSystem::DefaultFileSystem();
  std::shared_ptr<std::istream>      aStream =
    aFileSystem->OpenIStream(theFile, std::ios::in | std::ios::binary);
  if (aStream.get() == nullptr)
  {
    Message::SendFail(TCollection_AsciiString("Error: file '") + theFile + "' is not found");
    return false;
  }

  aStream->seekg(0, aStream->end);
  std::streampos theEnd = aStream->tellg();
  aStream->seekg(0, aStream->beg);

  bool isAscii = ((size_t)theEnd < THE_STL_MIN_FILE_SIZE || IsAscii(*aStream, true));

  Standard_ReadLineBuffer aBuffer(THE_BUFFER_SIZE);

  Message_ProgressScope aPS(theProgress, nullptr, 1, true);
  while (aStream->good())
  {
    if (isAscii)
    {
      if (!ReadAscii(*aStream, aBuffer, theEnd, aPS.Next(2)))
      {
        break;
      }
    }
    else
    {
      if (!ReadBinary(*aStream, aPS.Next(2)))
      {
        break;
      }
    }
    *aStream >> std::ws;
    AddSolid();
  }
  return !aStream->fail();
}

bool RWStl_Reader::IsAscii(Standard_IStream& theStream, const bool isSeekgAvailable)
{

  char            aBuffer[THE_STL_MIN_FILE_SIZE];
  std::streamsize aNbRead = theStream.read(aBuffer, THE_STL_MIN_FILE_SIZE).gcount();
  if (!theStream)
  {
    Message::SendFail("Error: Cannot read file");
    return true;
  }

  if (isSeekgAvailable)
  {

    theStream.seekg(0, Standard_IStream::beg);
  }
  else
  {

    for (std::streamsize aByteIter = aNbRead; aByteIter > 0; --aByteIter)
    {
      theStream.unget();
    }
  }

  if (aNbRead < std::streamsize(THE_STL_MIN_FILE_SIZE))
  {
    return true;
  }

  for (int aByteIter = 0; aByteIter < aNbRead; ++aByteIter)
  {
    if ((unsigned char)aBuffer[aByteIter] > (unsigned char)'~')
    {
      return false;
    }
  }
  return true;
}

#ifdef __APPLE__

  #define SAVE_TL()
#elif defined(_MSC_VER)

  #define SAVE_TL()
  #define sscanf_l(theBuffer, theLocale, theFormat, ...)                                           \
    _sscanf_s_l(theBuffer, theFormat, theLocale, __VA_ARGS__)
#else

  #define SAVE_TL() Standard_CLocaleSentry aLocaleSentry;
  #define sscanf_l(theBuffer, theLocale, theFormat, ...) sscanf(theBuffer, theFormat, __VA_ARGS__)
#endif

#if defined(_MSC_VER) && _MSC_VER < 1700

  #define GETPOS(aPos) aPos.seekpos()
#else
  #define GETPOS(aPos) ((int64_t)aPos)
#endif

static inline bool str_starts_with(const char* theStr, const char* theWord, int theN)
{
  while (isspace(*theStr) && *theStr != '\0')
    theStr++;
  return !strncasecmp(theStr, theWord, theN);
}

static bool ReadVertex(const char* theStr, double& theX, double& theY, double& theZ)
{
  const char* aStr = theStr;

  while (isspace((unsigned char)*aStr) || isalpha((unsigned char)*aStr))
    ++aStr;

  char* aEnd;
  theX = Strtod(aStr, &aEnd);
  theY = Strtod(aStr = aEnd, &aEnd);
  theZ = Strtod(aStr = aEnd, &aEnd);

  return aEnd != aStr;
}

bool RWStl_Reader::ReadAscii(Standard_IStream&            theStream,
                             Standard_ReadLineBuffer&     theBuffer,
                             const std::streampos         theUntilPos,
                             const Message_ProgressRange& theProgress)
{

  const int64_t aStartPos = GETPOS(theStream.tellg());
  size_t        aLineLen  = 0;
  const char*   aLine;

  aLine = theBuffer.ReadLine(theStream, aLineLen);

  while (aLine && !*aLine)
  {
    aLine = theBuffer.ReadLine(theStream, aLineLen);
  }
  if (aLine == nullptr)
  {
    Message::SendFail("Error: premature end of file");
    return false;
  }

  MergeNodeTool aMergeTool(this);
  aMergeTool.SetMergeAngle(myMergeAngle);
  aMergeTool.SetMergeTolerance(myMergeTolearance);

  Standard_CLocaleSentry::clocale_t aLocale = Standard_CLocaleSentry::GetCLocale();
  (void)aLocale;
  SAVE_TL()

  const int             aStepB   = 1024 * 1024;
  const int             aNbSteps = 1 + int((GETPOS(theUntilPos) - aStartPos) / aStepB);
  Message_ProgressScope aPS(theProgress, "Reading text STL file", aNbSteps);
  int64_t               aProgressPos = aStartPos + aStepB;
  int                   aNbLine      = 1;

  while (aPS.More())
  {
    if (GETPOS(theStream.tellg()) > aProgressPos)
    {
      aPS.Next();
      aProgressPos += aStepB;
    }

    aLine = theBuffer.ReadLine(theStream, aLineLen);
    if (aLine == nullptr)
    {
      Message::SendFail("Error: premature end of file");
      return false;
    }
    if (str_starts_with(aLine, "endsolid", 8))
    {

      break;
    }
    if (!str_starts_with(aLine, "facet", 5))
    {
      Message::SendFail(TCollection_AsciiString("Error: unexpected format of facet at line ")
                        + (aNbLine + 1));
      return false;
    }

    aLine = theBuffer.ReadLine(theStream, aLineLen);
    if (aLine == nullptr || !str_starts_with(aLine, "outer", 5))
    {
      Message::SendFail(TCollection_AsciiString("Error: unexpected format of facet at line ")
                        + (aNbLine + 1));
      return false;
    }

    gp_XYZ aVertex[3];
    bool   isEOF = false;
    for (int i = 0; i < 3; i++)
    {
      aLine = theBuffer.ReadLine(theStream, aLineLen);
      if (aLine == nullptr)
      {
        isEOF = true;
        break;
      }
      gp_XYZ aReadVertex;
      if (!ReadVertex(aLine,
                      aReadVertex.ChangeCoord(1),
                      aReadVertex.ChangeCoord(2),
                      aReadVertex.ChangeCoord(3)))
      {
        Message::SendFail(TCollection_AsciiString("Error: cannot read vertex coordinates at line ")
                          + aNbLine);
        return false;
      }
      aVertex[i] = aReadVertex;
    }

    if (isEOF)
    {
      break;
    }

    aNbLine += 5;

    aMergeTool.AddTriangle(aVertex);

    theBuffer.ReadLine(theStream, aLineLen);
    theBuffer.ReadLine(theStream, aLineLen);

    aNbLine += 2;
  }

  return aPS.More();
}

bool RWStl_Reader::ReadBinary(Standard_IStream& theStream, const Message_ProgressRange& theProgress)
{

  char aHeader[THE_STL_HEADER_SIZE + 1];
  if (theStream.read(aHeader, THE_STL_HEADER_SIZE).gcount() != std::streamsize(THE_STL_HEADER_SIZE))
  {
    Message::SendFail("Error: Corrupted binary STL file");
    return false;
  }

  const int aNbFacets = *(int32_t*)(aHeader + 80);

  MergeNodeTool aMergeTool(this, aNbFacets);
  aMergeTool.SetMergeAngle(myMergeAngle);
  aMergeTool.SetMergeTolerance(myMergeTolearance);

  Message_ProgressScope aPS(theProgress, "Reading binary STL file", aNbFacets);
  int                   aNbRead = 0;

  const int THE_CHUNK_NBFACETS = 80;
  char      aBuffer[THE_STL_SIZEOF_FACET * THE_CHUNK_NBFACETS];

  const size_t aVec3Size        = sizeof(float) * 3;
  const size_t aFaceDataLen     = aVec3Size * 4 + 2;
  const char*  aBufferPtr       = aBuffer;
  int          aNbFacesInBuffer = 0;
  for (int aNbFacetRead = 0; aNbFacetRead < aNbFacets && aPS.More();
       ++aNbFacetRead, ++aNbRead, --aNbFacesInBuffer, aBufferPtr += aFaceDataLen, aPS.Next())
  {

    if (aNbFacesInBuffer <= 0)
    {
      aNbFacesInBuffer                  = std::min(THE_CHUNK_NBFACETS, aNbFacets - aNbFacetRead);
      const std::streamsize aDataToRead = aNbFacesInBuffer * aFaceDataLen;
      if (theStream.read(aBuffer, aDataToRead).gcount() != aDataToRead)
      {
        Message::SendFail("Error: binary STL read failed");
        return false;
      }
      aBufferPtr = aBuffer;
    }

    gp_XYZ aTriNodes[3] = {readStlFloatVec3(aBufferPtr + aVec3Size),
                           readStlFloatVec3(aBufferPtr + aVec3Size * 2),
                           readStlFloatVec3(aBufferPtr + aVec3Size * 3)};
    aMergeTool.AddTriangle(aTriNodes);
  }

  return aPS.More();
}
