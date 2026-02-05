#pragma once

#include <Standard.hpp>

#include <ExprIntrp_Generator.hpp>
class TCollection_AsciiString;

//! Implements an interpreter for defining functions.
//! All its functionalities can be found in class
//! GenExp.
class ExprIntrp_GenFct : public ExprIntrp_Generator
{

public:
  Standard_EXPORT static occ::handle<ExprIntrp_GenFct> Create();

  Standard_EXPORT void Process(const TCollection_AsciiString& str);

  Standard_EXPORT bool IsDone() const;

  DEFINE_STANDARD_RTTIEXT(ExprIntrp_GenFct, ExprIntrp_Generator)

private:
  Standard_EXPORT ExprIntrp_GenFct();

  bool done;
};
