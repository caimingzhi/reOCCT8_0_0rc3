#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <HLRAlgo_Intersection.hpp>
#include <TopAbs_State.hpp>
#include <Standard_Transient.hpp>

//! The private nested class AreaLimit represents a
//! vertex on the Edge with the state on the left and
//! the right.
class HLRBRep_AreaLimit : public Standard_Transient
{

public:
  //! The previous and next field are set to NULL.
  Standard_EXPORT HLRBRep_AreaLimit(const HLRAlgo_Intersection& V,
                                    const bool                  Boundary,
                                    const bool                  Interference,
                                    const TopAbs_State          StateBefore,
                                    const TopAbs_State          StateAfter,
                                    const TopAbs_State          EdgeBefore,
                                    const TopAbs_State          EdgeAfter);

  Standard_EXPORT void StateBefore(const TopAbs_State St);

  Standard_EXPORT void StateAfter(const TopAbs_State St);

  Standard_EXPORT void EdgeBefore(const TopAbs_State St);

  Standard_EXPORT void EdgeAfter(const TopAbs_State St);

  Standard_EXPORT void Previous(const occ::handle<HLRBRep_AreaLimit>& P);

  Standard_EXPORT void Next(const occ::handle<HLRBRep_AreaLimit>& N);

  Standard_EXPORT const HLRAlgo_Intersection& Vertex() const;

  Standard_EXPORT bool IsBoundary() const;

  Standard_EXPORT bool IsInterference() const;

  Standard_EXPORT TopAbs_State StateBefore() const;

  Standard_EXPORT TopAbs_State StateAfter() const;

  Standard_EXPORT TopAbs_State EdgeBefore() const;

  Standard_EXPORT TopAbs_State EdgeAfter() const;

  Standard_EXPORT occ::handle<HLRBRep_AreaLimit> Previous() const;

  Standard_EXPORT occ::handle<HLRBRep_AreaLimit> Next() const;

  Standard_EXPORT void Clear();

  DEFINE_STANDARD_RTTIEXT(HLRBRep_AreaLimit, Standard_Transient)

private:
  HLRAlgo_Intersection           myVertex;
  bool                           myBoundary;
  bool                           myInterference;
  TopAbs_State                   myStateBefore;
  TopAbs_State                   myStateAfter;
  TopAbs_State                   myEdgeBefore;
  TopAbs_State                   myEdgeAfter;
  occ::handle<HLRBRep_AreaLimit> myPrevious;
  occ::handle<HLRBRep_AreaLimit> myNext;
};
