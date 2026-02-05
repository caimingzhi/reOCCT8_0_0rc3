#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Standard_Integer.hpp>
class TopOpeBRepDS_DataStructure;
class TopOpeBRepDS_Curve;

class TopOpeBRepDS_CurveExplorer
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_CurveExplorer();

  Standard_EXPORT TopOpeBRepDS_CurveExplorer(const TopOpeBRepDS_DataStructure& DS,
                                             const bool                        FindOnlyKeep = true);

  Standard_EXPORT void Init(const TopOpeBRepDS_DataStructure& DS, const bool FindOnlyKeep = true);

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const TopOpeBRepDS_Curve& Curve() const;

  Standard_EXPORT bool IsCurve(const int I) const;

  Standard_EXPORT bool IsCurveKeep(const int I) const;

  Standard_EXPORT const TopOpeBRepDS_Curve& Curve(const int I) const;

  Standard_EXPORT int NbCurve();

  Standard_EXPORT int Index() const;

private:
  Standard_EXPORT void Find();

  int   myIndex;
  int   myMax;
  void* myDS;
  bool  myFound;
  bool  myFindKeep;
};
