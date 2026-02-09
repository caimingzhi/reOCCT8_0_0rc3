#include <TDocStd_PathParser.hpp>

#include <TCollection_ExtendedString.hpp>

TDocStd_PathParser::TDocStd_PathParser(const TCollection_ExtendedString& path)
{
  myPath = path;
  Parse();
}

void TDocStd_PathParser::Parse()
{
  TCollection_ExtendedString temp          = myPath;
  int                        PointPosition = myPath.SearchFromEnd(TCollection_ExtendedString("."));
  if (PointPosition > 0)
    myExtension = temp.Split(PointPosition);
  else
    return;
  temp.Trunc(PointPosition - 1);
  bool isFileName = (temp.Length()) != 0;
  bool isTrek     = true;
#ifdef _WIN32
  PointPosition = temp.SearchFromEnd(TCollection_ExtendedString("\\"));
  if (!(PointPosition > 0))
    PointPosition = temp.SearchFromEnd(TCollection_ExtendedString("/"));
  if (PointPosition > 0)
    myName = temp.Split(PointPosition);
  else
  {
    if (isFileName)
    {
      myName = temp;
      isTrek = false;
    }
    else
      return;
  }
#else
  PointPosition = temp.SearchFromEnd(TCollection_ExtendedString("/"));
  if (PointPosition > 0)
    myName = temp.Split(PointPosition);
  else
  {
    if (isFileName)
    {
      myName = temp;
      isTrek = false;
    }
    else
      return;
  }
#endif
  if (isTrek)
  {
    temp.Trunc(PointPosition - 1);
    myTrek = temp;
  }
  else
#ifdef _WIN32
    myTrek = ".\\";
#else
    myTrek = "./";
#endif
}

TCollection_ExtendedString TDocStd_PathParser::Extension() const
{
  return myExtension;
}

TCollection_ExtendedString TDocStd_PathParser::Name() const
{
  return myName;
}

TCollection_ExtendedString TDocStd_PathParser::Trek() const
{
  return myTrek;
}

TCollection_ExtendedString TDocStd_PathParser::Path() const
{
  return myPath;
}

int TDocStd_PathParser::Length() const
{
  return myPath.Length();
}
