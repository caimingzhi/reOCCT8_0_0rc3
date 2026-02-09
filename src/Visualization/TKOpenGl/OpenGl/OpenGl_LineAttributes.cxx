#include <OpenGl_GlCore11.hpp>

#include <OpenGl_LineAttributes.hpp>
#include <OpenGl_Context.hpp>

IMPLEMENT_STANDARD_RTTIEXT(OpenGl_LineAttributes, OpenGl_Resource)

OpenGl_LineAttributes::OpenGl_LineAttributes() = default;

OpenGl_LineAttributes::~OpenGl_LineAttributes()
{
  Release(nullptr);
}

void OpenGl_LineAttributes::Release(OpenGl_Context* theGlCtx)
{
  if (theGlCtx != nullptr && theGlCtx->IsValid())
  {
    for (NCollection_DataMap<occ::handle<Graphic3d_HatchStyle>, unsigned int>::Iterator anIter(
           myStyles);
         anIter.More();
         anIter.Next())
    {
      theGlCtx->core11ffp->glDeleteLists((GLuint)anIter.Value(), 1);
    }
  }
  myStyles.Clear();
}

unsigned int OpenGl_LineAttributes::init(const OpenGl_Context*                    theGlCtx,
                                         const occ::handle<Graphic3d_HatchStyle>& theStyle)
{
  const unsigned int aListId = theGlCtx->core11ffp->glGenLists(1);
  theGlCtx->core11ffp->glNewList((GLuint)aListId, GL_COMPILE);
  theGlCtx->core11ffp->glPolygonStipple((const GLubyte*)theStyle->Pattern());
  theGlCtx->core11ffp->glEndList();
  return aListId;
}

bool OpenGl_LineAttributes::SetTypeOfHatch(const OpenGl_Context*                    theGlCtx,
                                           const occ::handle<Graphic3d_HatchStyle>& theStyle)
{
  if (theStyle.IsNull() || theStyle->HatchType() == Aspect_HS_SOLID
      || theGlCtx->core11ffp == nullptr)
  {
    return false;
  }

  unsigned int aGpuListId = 0;
  if (!myStyles.Find(theStyle, aGpuListId))
  {
    aGpuListId = init(theGlCtx, theStyle);
    myStyles.Bind(theStyle, aGpuListId);
  }

  theGlCtx->core11ffp->glCallList((GLuint)aGpuListId);
  return true;
}
