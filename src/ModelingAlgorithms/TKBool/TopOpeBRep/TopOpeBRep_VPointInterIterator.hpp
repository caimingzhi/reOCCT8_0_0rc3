#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopOpeBRep_PLineInter.hpp>
#include <Standard_Integer.hpp>
class TopOpeBRep_VPointInter;

class TopOpeBRep_VPointInterIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_VPointInterIterator();

  Standard_EXPORT TopOpeBRep_VPointInterIterator(const TopOpeBRep_LineInter& LI);

  Standard_EXPORT void Init(const TopOpeBRep_LineInter& LI, const bool checkkeep = false);

  Standard_EXPORT void Init();

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const TopOpeBRep_VPointInter& CurrentVP();

  Standard_EXPORT int CurrentVPIndex() const;

  Standard_EXPORT TopOpeBRep_VPointInter& ChangeCurrentVP();

  Standard_EXPORT TopOpeBRep_PLineInter PLineInterDummy() const;

private:
  TopOpeBRep_PLineInter myLineInter;
  int                   myVPointIndex;
  int                   myVPointNb;
  bool                  mycheckkeep;
};
