

#include <AIS_BaseAnimationObject.hpp>

#include <V3d_View.hpp>

IMPLEMENT_STANDARD_RTTIEXT(AIS_BaseAnimationObject, AIS_Animation)

AIS_BaseAnimationObject::AIS_BaseAnimationObject(
  const TCollection_AsciiString&             theAnimationName,
  const occ::handle<AIS_InteractiveContext>& theContext,
  const occ::handle<AIS_InteractiveObject>&  theObject)
    : AIS_Animation(theAnimationName),
      myContext(theContext),
      myObject(theObject)
{
}

void AIS_BaseAnimationObject::updateTrsf(const gp_Trsf& theTrsf)
{
  if (!myContext.IsNull())
  {
    myContext->SetLocation(myObject, theTrsf);
    invalidateViewer();
  }
  else
  {
    myObject->SetLocalTransformation(theTrsf);
  }
}

void AIS_BaseAnimationObject::invalidateViewer()
{
  if (myContext.IsNull())
  {
    return;
  }

  const bool isImmediate =
    myContext->CurrentViewer()->ZLayerSettings(myObject->ZLayer()).IsImmediate();
  if (!isImmediate)
  {
    myContext->CurrentViewer()->Invalidate();
    return;
  }

  for (NCollection_List<occ::handle<V3d_View>>::Iterator aDefViewIter =
         myContext->CurrentViewer()->DefinedViewIterator();
       aDefViewIter.More();
       aDefViewIter.Next())
  {
    const occ::handle<V3d_View>& aView       = aDefViewIter.Value();
    const Bnd_Box                aMinMaxBox  = aView->View()->MinMaxValues(false);
    const Bnd_Box                aGraphicBox = aView->View()->MinMaxValues(true);
    double                       aZNear      = 0.0;
    double                       aZFar       = 0.0;
    if (aView->Camera()->ZFitAll(aDefViewIter.Value()->AutoZFitScaleFactor(),
                                 aMinMaxBox,
                                 aGraphicBox,
                                 aZNear,
                                 aZFar))
    {
      if (aZNear < aView->Camera()->ZNear() || aZFar > aView->Camera()->ZFar())
      {
        aDefViewIter.Value()->Invalidate();
      }
    }
  }
}
