#pragma once

#include <Standard_WarningsDisable.hpp>
#include <rapidjson/prettywriter.h>
#include <rapidjson/ostreamwrapper.h>
#include <Standard_WarningsRestore.hpp>

class RWGltf_GltfOStreamWriter : public rapidjson::Writer<rapidjson::OStreamWrapper>
{
public:
  RWGltf_GltfOStreamWriter(rapidjson::OStreamWrapper& theOStream)
      : rapidjson::Writer<rapidjson::OStreamWrapper>(theOStream)
  {
  }
};
