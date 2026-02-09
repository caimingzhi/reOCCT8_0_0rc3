#pragma once

#include <DE_ConfigurationNode.hpp>
#include <DE_ShapeFixParameters.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_List.hpp>

class DE_ConfigurationContext;

class DE_ShapeFixConfigurationNode : public DE_ConfigurationNode
{
  DEFINE_STANDARD_RTTIEXT(DE_ShapeFixConfigurationNode, DE_ConfigurationNode)
public:
  Standard_EXPORT DE_ShapeFixConfigurationNode();

  Standard_EXPORT DE_ShapeFixConfigurationNode(
    const occ::handle<DE_ShapeFixConfigurationNode>& theConfigurationNode);

  Standard_EXPORT bool Load(const occ::handle<DE_ConfigurationContext>& theResource) override;

  Standard_EXPORT TCollection_AsciiString Save() const override;

public:
  DE_ShapeFixParameters ShapeFixParameters;
};
