#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <AIS_TypeFilter.hpp>
#include <AIS_KindOfInteractive.hpp>
class SelectMgr_EntityOwner;

//! Selects Interactive Objects through their signatures
//! and types. The signature provides an
//! additional characterization of an object's type, and
//! takes the form of an index. The filter questions each
//! Interactive Object in local context to determine
//! whether it has an non-null owner, and if so, whether
//! it has the desired signature. If the object returns true
//! in each case, it is kept. If not, it is rejected.
//! By default, the interactive object has a None type
//! and a signature of 0. If you want to give a particular
//! type and signature to your Interactive Object, you
//! must redefine two virtual methods: Type and Signature.
//! This filter is only used in an open local contexts.
//! In the Collector viewer, you can only locate
//! Interactive Objects which answer positively to the
//! positioned filters when a local context is open.
//! Warning
//! Some signatures have already been used by standard
//! objects delivered in AIS. These include:
//! -   signature 0 - Shape
//! -   signature 1 - Point
//! -   signature 2 - Axis
//! -   signature 3 - Trihedron
//! -   signature 4 - PlaneTrihedron
//! -   signature 5 - Line
//! -   signature 6 - Circle
//! -   signature 7 - Plane
class AIS_SignatureFilter : public AIS_TypeFilter
{

public:
  //! Initializes the signature filter, adding the signature
  //! specification, aGivenSignature, to that for type,
  //! aGivenKind, in AIS_TypeFilter.
  Standard_EXPORT AIS_SignatureFilter(const AIS_KindOfInteractive aGivenKind,
                                      const int                   aGivenSignature);

  //! Returns False if the transient is not an AIS_InteractiveObject.
  //! Returns False if the signature of InteractiveObject
  //! is not the same as the stored one in the filter...
  Standard_EXPORT bool IsOk(const occ::handle<SelectMgr_EntityOwner>& anobj) const override;

  DEFINE_STANDARD_RTTIEXT(AIS_SignatureFilter, AIS_TypeFilter)

private:
  int mySig;
};
