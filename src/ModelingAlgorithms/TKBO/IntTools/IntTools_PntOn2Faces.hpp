#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <IntTools_PntOnFace.hpp>

//! Contains two points PntOnFace from IntTools and a flag
class IntTools_PntOn2Faces
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT IntTools_PntOn2Faces();

  //! Initializes me by two points aP1 and aP2
  Standard_EXPORT IntTools_PntOn2Faces(const IntTools_PntOnFace& aP1,
                                       const IntTools_PntOnFace& aP2);

  //! Modifier
  Standard_EXPORT void SetP1(const IntTools_PntOnFace& aP1);

  //! Modifier
  Standard_EXPORT void SetP2(const IntTools_PntOnFace& aP2);

  //! Modifier
  Standard_EXPORT void SetValid(const bool bF);

  //! Selector
  Standard_EXPORT const IntTools_PntOnFace& P1() const;

  //! Selector
  Standard_EXPORT const IntTools_PntOnFace& P2() const;

  //! Selector
  Standard_EXPORT bool IsValid() const;

private:
  bool               myIsValid;
  IntTools_PntOnFace myPnt1;
  IntTools_PntOnFace myPnt2;
};

