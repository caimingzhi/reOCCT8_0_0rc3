#pragma once

#include <Graphic3d_ShaderObject.hpp>
#include <OpenGl_GlCore20.hpp>
#include <OpenGl_Resource.hpp>
#include <Quantity_Date.hpp>

class OpenGl_ShaderObject : public OpenGl_Resource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_ShaderObject, OpenGl_Resource)
  friend class OpenGl_ShaderProgram;

public:
  static const GLuint NO_SHADER = 0;

public:
  Standard_EXPORT OpenGl_ShaderObject(GLenum theType);

  Standard_EXPORT ~OpenGl_ShaderObject() override;

  Standard_EXPORT bool LoadSource(const occ::handle<OpenGl_Context>& theCtx,
                                  const TCollection_AsciiString&     theSource);

  Standard_EXPORT bool Compile(const occ::handle<OpenGl_Context>& theCtx);

  Standard_EXPORT bool LoadAndCompile(const occ::handle<OpenGl_Context>& theCtx,
                                      const TCollection_AsciiString&     theId,
                                      const TCollection_AsciiString&     theSource,
                                      bool                               theIsVerbose     = true,
                                      bool                               theToPrintSource = true);

  Standard_EXPORT void DumpSourceCode(const occ::handle<OpenGl_Context>& theCtx,
                                      const TCollection_AsciiString&     theId,
                                      const TCollection_AsciiString&     theSource) const;

  Standard_EXPORT bool FetchInfoLog(const occ::handle<OpenGl_Context>& theCtx,
                                    TCollection_AsciiString&           theLog);

  Standard_EXPORT bool Create(const occ::handle<OpenGl_Context>& theCtx);

  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  size_t EstimatedDataSize() const override { return 0; }

  GLenum Type() const { return myType; }

public:
  Standard_EXPORT bool updateDebugDump(const occ::handle<OpenGl_Context>& theCtx,
                                       const TCollection_AsciiString&     theId,
                                       const TCollection_AsciiString&     theFolder,
                                       bool                               theToBeautify,
                                       bool                               theToReset);

protected:
  Quantity_Date myDumpDate;
  GLenum        myType;
  GLuint        myShaderID;
};
