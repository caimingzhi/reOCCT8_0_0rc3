#pragma once


#include <DE_ConfigurationNode.hpp>
#include <DE_ShapeFixParameters.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_List.hpp>

class DE_ConfigurationContext;

//! Base class to work with shape healing parameters for child classes.
class DE_ShapeFixConfigurationNode : public DE_ConfigurationNode
{
  DEFINE_STANDARD_RTTIEXT(DE_ShapeFixConfigurationNode, DE_ConfigurationNode)
public:
  //! Initializes all field by default
  Standard_EXPORT DE_ShapeFixConfigurationNode();

  //! Copies values of all fields
  //! @param[in] theConfigurationNode object to copy
  Standard_EXPORT DE_ShapeFixConfigurationNode(
    const occ::handle<DE_ShapeFixConfigurationNode>& theConfigurationNode);

  //! Updates values according the resource
  //! @param[in] theResource input resource to use
  //! @return True if Load was successful
  Standard_EXPORT bool Load(const occ::handle<DE_ConfigurationContext>& theResource) override;

  //! Writes configuration to the string
  //! @return result resource string
  Standard_EXPORT TCollection_AsciiString Save() const override;

public:
  DE_ShapeFixParameters ShapeFixParameters; //!< Shape healing parameters
};

