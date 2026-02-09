#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ExprIntrp_Generator.hpp>
class Expr_GeneralRelation;
class TCollection_AsciiString;

class ExprIntrp_GenRel : public ExprIntrp_Generator
{

public:
  Standard_EXPORT static occ::handle<ExprIntrp_GenRel> Create();

  Standard_EXPORT void Process(const TCollection_AsciiString& str);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT occ::handle<Expr_GeneralRelation> Relation() const;

  DEFINE_STANDARD_RTTIEXT(ExprIntrp_GenRel, ExprIntrp_Generator)

private:
  Standard_EXPORT ExprIntrp_GenRel();

  bool                              done;
  occ::handle<Expr_GeneralRelation> myRelation;
};
