#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TCollection_AsciiString.hpp>

enum Vrml_Texture2Wrap
{
  Vrml_REPEAT,
  Vrml_CLAMP
};

#include <Standard_OStream.hpp>
class Vrml_SFImage;

//! defines a Texture2 node of VRML specifying properties of geometry
//! and its appearance.
//! This property node defines a texture map and parameters for that map
//! The texture can be read from the URL specified by the filename field.
//! To turn off texturing, set the filename field to an empty string ("").
//! Textures can alsobe specified inline by setting the image field
//! to contain the texture data.
//! By default:
//! myFilename ("")
//! myImage (0 0 0)
//! myWrapS (Vrml_REPEAT)
//! myWrapT (Vrml_REPEAT)
class Vrml_Texture2
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Vrml_Texture2();

  Standard_EXPORT Vrml_Texture2(const TCollection_AsciiString&   aFilename,
                                const occ::handle<Vrml_SFImage>& aImage,
                                const Vrml_Texture2Wrap          aWrapS,
                                const Vrml_Texture2Wrap          aWrapT);

  Standard_EXPORT void SetFilename(const TCollection_AsciiString& aFilename);

  Standard_EXPORT TCollection_AsciiString Filename() const;

  Standard_EXPORT void SetImage(const occ::handle<Vrml_SFImage>& aImage);

  Standard_EXPORT occ::handle<Vrml_SFImage> Image() const;

  Standard_EXPORT void SetWrapS(const Vrml_Texture2Wrap aWrapS);

  Standard_EXPORT Vrml_Texture2Wrap WrapS() const;

  Standard_EXPORT void SetWrapT(const Vrml_Texture2Wrap aWrapT);

  Standard_EXPORT Vrml_Texture2Wrap WrapT() const;

  Standard_EXPORT Standard_OStream& Print(Standard_OStream& anOStream) const;

private:
  TCollection_AsciiString   myFilename;
  occ::handle<Vrml_SFImage> myImage;
  Vrml_Texture2Wrap         myWrapS;
  Vrml_Texture2Wrap         myWrapT;
};
