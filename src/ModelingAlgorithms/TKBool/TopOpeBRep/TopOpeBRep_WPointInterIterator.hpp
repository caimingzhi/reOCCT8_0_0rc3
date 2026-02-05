#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopOpeBRep_PLineInter.hpp>
#include <Standard_Integer.hpp>
class TopOpeBRep_WPointInter;

class TopOpeBRep_WPointInterIterator
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRep_WPointInterIterator();

  Standard_EXPORT TopOpeBRep_WPointInterIterator(const TopOpeBRep_LineInter& LI);

  Standard_EXPORT void Init(const TopOpeBRep_LineInter& LI);

  Standard_EXPORT void Init();

  Standard_EXPORT bool More() const;

  Standard_EXPORT void Next();

  Standard_EXPORT const TopOpeBRep_WPointInter& CurrentWP();

  Standard_EXPORT TopOpeBRep_PLineInter PLineInterDummy() const;

private:
  TopOpeBRep_PLineInter myLineInter;
  int                   myWPointIndex;
  int                   myWPointNb;
};
