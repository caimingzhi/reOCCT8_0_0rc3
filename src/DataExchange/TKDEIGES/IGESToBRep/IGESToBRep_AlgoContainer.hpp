#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class IGESToBRep_ToolContainer;

class IGESToBRep_AlgoContainer : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT IGESToBRep_AlgoContainer();

  //! Sets ToolContainer
  void SetToolContainer(const occ::handle<IGESToBRep_ToolContainer>& TC);

  //! Returns ToolContainer
  occ::handle<IGESToBRep_ToolContainer> ToolContainer() const;

  DEFINE_STANDARD_RTTIEXT(IGESToBRep_AlgoContainer, Standard_Transient)

private:
  occ::handle<IGESToBRep_ToolContainer> myTC;
};

#include <IGESToBRep_AlgoContainer.hpp>

//=================================================================================================

inline void IGESToBRep_AlgoContainer::SetToolContainer(
  const occ::handle<IGESToBRep_ToolContainer>& TC)
{
  myTC = TC;
}

//=================================================================================================

inline occ::handle<IGESToBRep_ToolContainer> IGESToBRep_AlgoContainer::ToolContainer() const
{
  return myTC;
}
