#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
#include <TopOpeBRepDS_Surface.hpp>
class TopOpeBRepDS_DataStructure;

class TopOpeBRepDS_SurfaceExplorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_SurfaceExplorer();

  Standard_EXPORT TopOpeBRepDS_SurfaceExplorer(const TopOpeBRepDS_DataStructure& DS,
                                               const bool FindOnlyKeep = true);

  Standard_EXPORT void Init(const TopOpeBRepDS_DataStructure& DS, const bool FindOnlyKeep = true);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const TopOpeBRepDS_Surface& Surface() const;

  Standard_EXPORT bool IsSurface(const int I) const;

  Standard_EXPORT bool IsSurfaceKeep(const int I) const;

  Standard_EXPORT const TopOpeBRepDS_Surface& Surface(const int I) const;

  Standard_EXPORT int NbSurface();

  Standard_EXPORT int Index() const;

private:
  Standard_EXPORT void Find();

  int                  myIndex;
  int                  myMax;
  void*                myDS;
  bool                 myFound;
  TopOpeBRepDS_Surface myEmpty;
  bool                 myFindKeep;
};

