#pragma once

#include <OpenGl_Resource.hpp>
#include <TCollection_AsciiString.hpp>

class OpenGl_Buffer : public OpenGl_Resource
{
  DEFINE_STANDARD_RTTIEXT(OpenGl_Buffer, OpenGl_Resource)
public:
  static const unsigned int NO_BUFFER = 0;

  Standard_EXPORT static TCollection_AsciiString FormatTarget(unsigned int theTarget);

public:
  Standard_EXPORT OpenGl_Buffer();

  Standard_EXPORT ~OpenGl_Buffer() override;

  virtual unsigned int GetTarget() const = 0;

  virtual bool IsVirtual() const { return false; }

  bool IsValid() const { return myBufferId != NO_BUFFER; }

  unsigned int GetComponentsNb() const { return myComponentsNb; }

  int GetElemsNb() const { return myElemsNb; }

  void SetElemsNb(int theNbElems) { myElemsNb = theNbElems; }

  unsigned int GetDataType() const { return myDataType; }

  uint8_t* GetDataOffset() const { return myOffset; }

  Standard_EXPORT virtual bool Create(const occ::handle<OpenGl_Context>& theGlCtx);

  Standard_EXPORT void Release(OpenGl_Context* theGlCtx) override;

  Standard_EXPORT virtual void Bind(const occ::handle<OpenGl_Context>& theGlCtx) const;

  Standard_EXPORT virtual void Unbind(const occ::handle<OpenGl_Context>& theGlCtx) const;

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
                            const unsigned int                 theComponentsNb,
                            const int                          theElemsNb,
                            const float*                       theData);

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
                            const unsigned int                 theComponentsNb,
                            const int                          theElemsNb,
                            const unsigned int*                theData);

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
                            const unsigned int                 theComponentsNb,
                            const int                          theElemsNb,
                            const unsigned short*              theData);

  Standard_EXPORT bool Init(const occ::handle<OpenGl_Context>& theGlCtx,
                            const unsigned int                 theComponentsNb,
                            const int                          theElemsNb,
                            const uint8_t*                     theData);

  Standard_EXPORT bool SubData(const occ::handle<OpenGl_Context>& theGlCtx,
                               const int                          theElemFrom,
                               const int                          theElemsNb,
                               const float*                       theData);

  Standard_EXPORT bool GetSubData(const occ::handle<OpenGl_Context>& theGlCtx,
                                  const int                          theElemFrom,
                                  const int                          theElemsNb,
                                  float*                             theData);

  Standard_EXPORT bool SubData(const occ::handle<OpenGl_Context>& theGlCtx,
                               const int                          theElemFrom,
                               const int                          theElemsNb,
                               const unsigned int*                theData);

  Standard_EXPORT bool GetSubData(const occ::handle<OpenGl_Context>& theGlCtx,
                                  const int                          theElemFrom,
                                  const int                          theElemsNb,
                                  unsigned int*                      theData);

  Standard_EXPORT bool SubData(const occ::handle<OpenGl_Context>& theGlCtx,
                               const int                          theElemFrom,
                               const int                          theElemsNb,
                               const unsigned short*              theData);

  Standard_EXPORT bool GetSubData(const occ::handle<OpenGl_Context>& theGlCtx,
                                  const int                          theElemFrom,
                                  const int                          theElemsNb,
                                  unsigned short*                    theData);

  Standard_EXPORT bool SubData(const occ::handle<OpenGl_Context>& theGlCtx,
                               const int                          theElemFrom,
                               const int                          theElemsNb,
                               const uint8_t*                     theData);

  Standard_EXPORT bool GetSubData(const occ::handle<OpenGl_Context>& theGlCtx,
                                  const int                          theElemFrom,
                                  const int                          theElemsNb,
                                  uint8_t*                           theData);

public:
  size_t EstimatedDataSize() const override
  {
    return IsValid() ? sizeOfGlType(myDataType) * myComponentsNb * myElemsNb : 0;
  }

  Standard_EXPORT static size_t sizeOfGlType(unsigned int theType);

  Standard_EXPORT virtual bool init(const occ::handle<OpenGl_Context>& theGlCtx,
                                    const unsigned int                 theComponentsNb,
                                    const int                          theElemsNb,
                                    const void*                        theData,
                                    const unsigned int                 theDataType,
                                    const int                          theStride);

  bool init(const occ::handle<OpenGl_Context>& theGlCtx,
            const unsigned int                 theComponentsNb,
            const int                          theElemsNb,
            const void*                        theData,
            const unsigned int                 theDataType)
  {
    return init(theGlCtx,
                theComponentsNb,
                theElemsNb,
                theData,
                theDataType,
                int(theComponentsNb) * int(sizeOfGlType(theDataType)));
  }

  Standard_EXPORT virtual bool subData(const occ::handle<OpenGl_Context>& theGlCtx,
                                       const int                          theElemFrom,
                                       const int                          theElemsNb,
                                       const void*                        theData,
                                       const unsigned int                 theDataType);

  Standard_EXPORT virtual bool getSubData(const occ::handle<OpenGl_Context>& theGlCtx,
                                          const int                          theElemFrom,
                                          const int                          theElemsNb,
                                          void*                              theData,
                                          const unsigned int                 theDataType);

public:
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT void BindBufferBase(const occ::handle<OpenGl_Context>& theGlCtx,
                                      unsigned int                       theIndex);

  Standard_EXPORT void UnbindBufferBase(const occ::handle<OpenGl_Context>& theGlCtx,
                                        unsigned int                       theIndex);

  Standard_EXPORT void BindBufferRange(const occ::handle<OpenGl_Context>& theGlCtx,
                                       unsigned int                       theIndex,
                                       const intptr_t                     theOffset,
                                       const size_t                       theSize);

protected:
  uint8_t*     myOffset;
  unsigned int myBufferId;

  unsigned int myComponentsNb;
  int          myElemsNb;
  unsigned int myDataType;
};
