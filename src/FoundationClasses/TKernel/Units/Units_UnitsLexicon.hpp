#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Time.hpp>
#include <Units_Lexicon.hpp>
#include <Standard_CString.hpp>
#include <Standard_Boolean.hpp>

class Units_UnitsLexicon : public Units_Lexicon
{

public:
  Standard_EXPORT Units_UnitsLexicon();

  Standard_EXPORT void Creates(const bool amode = true);

  void Dump() const override;

  DEFINE_STANDARD_RTTIEXT(Units_UnitsLexicon, Units_Lexicon)
};

#include <Units_Lexicon.hpp>

inline void Units_UnitsLexicon::Dump() const
{
  std::cout << " UNITSLEXICON : " << std::endl;
  Units_Lexicon::Dump();
}
