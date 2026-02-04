#pragma once


// disable warnings, occurs in rapidjson
#include <Standard_WarningsDisable.hpp>
#include <rapidjson/prettywriter.h>
#include <rapidjson/ostreamwrapper.h>
#include <Standard_WarningsRestore.hpp>

//! rapidjson::Writer wrapper for forward declaration.
class RWGltf_GltfOStreamWriter : public rapidjson::Writer<rapidjson::OStreamWrapper>
{
public:
  //! Main constructor.
  RWGltf_GltfOStreamWriter(rapidjson::OStreamWrapper& theOStream)
      : rapidjson::Writer<rapidjson::OStreamWrapper>(theOStream)
  {
  }
};

