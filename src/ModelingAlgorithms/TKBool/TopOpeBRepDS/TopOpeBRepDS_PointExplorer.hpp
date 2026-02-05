#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_Point.hpp>
class TopOpeBRepDS_DataStructure;

class TopOpeBRepDS_PointExplorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_PointExplorer();

  Standard_EXPORT TopOpeBRepDS_PointExplorer(const TopOpeBRepDS_DataStructure& DS,
                                             const bool                        FindOnlyKeep = true);

  Standard_EXPORT void Init(const TopOpeBRepDS_DataStructure& DS, const bool FindOnlyKeep = true);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const TopOpeBRepDS_Point& Point() const;

  Standard_EXPORT bool IsPoint(const int I) const;

  Standard_EXPORT bool IsPointKeep(const int I) const;

  Standard_EXPORT const TopOpeBRepDS_Point& Point(const int I) const;

  Standard_EXPORT int NbPoint();

  Standard_EXPORT int Index() const;

private:
  Standard_EXPORT void Find();

  int                myIndex;
  int                myMax;
  void*              myDS;
  bool               myFound;
  TopOpeBRepDS_Point myEmpty;
  bool               myFindKeep;
};
