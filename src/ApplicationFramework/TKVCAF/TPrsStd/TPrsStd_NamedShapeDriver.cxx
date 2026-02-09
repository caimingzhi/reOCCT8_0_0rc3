

#include <AIS_InteractiveContext.hpp>
#include <AIS_InteractiveObject.hpp>
#include <AIS_Shape.hpp>
#include <PrsMgr_PresentationManager.hpp>
#include <Standard_Type.hpp>
#include <TDataStd.hpp>
#include <TDF_Label.hpp>
#include <TNaming_Tool.hpp>
#include <TopLoc_Location.hpp>
#include <TPrsStd_DriverTable.hpp>
#include <TPrsStd_NamedShapeDriver.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TPrsStd_NamedShapeDriver, TPrsStd_Driver)

#undef OPTIM_UPDATE

TPrsStd_NamedShapeDriver::TPrsStd_NamedShapeDriver() = default;

bool TPrsStd_NamedShapeDriver::Update(const TDF_Label&                    aLabel,
                                      occ::handle<AIS_InteractiveObject>& AIS)
{
  occ::handle<TNaming_NamedShape> NS;

  if (!aLabel.FindAttribute(TNaming_NamedShape::GetID(), NS))
  {
    return false;
  }

  TopoDS_Shape S = TNaming_Tool::GetShape(NS);
  if (S.IsNull())
  {
    return false;
  }
  TopLoc_Location L = S.Location();

  occ::handle<AIS_Shape> AISShape;
  if (AIS.IsNull())
    AISShape = new AIS_Shape(S);
  else
  {
    AISShape = occ::down_cast<AIS_Shape>(AIS);
    if (AISShape.IsNull())
    {
      AISShape = new AIS_Shape(S);
    }
    else
    {
      TopoDS_Shape oldShape = AISShape->Shape();
      if (oldShape != S)
      {
        AISShape->ResetTransformation();

#ifdef OPTIM_UPDATE
        occ::handle<AIS_InteractiveContext> ctx = AISShape->GetContext();
        if (S.IsPartner(oldShape) && (!ctx.IsNull() && !ctx->IsDisplayed(AISShape)))
        {
          if (L != oldShape.Location())
            ctx->SetLocation(AISShape, L);
        }
        else
        {
          AISShape->Set(S);
          AISShape->UpdateSelection();
          AISShape->SetToUpdate();
        }
#else
        AISShape->Set(S);
        AISShape->UpdateSelection();
        AISShape->SetToUpdate();
#endif
      }
    }

    AISShape->SetInfiniteState(S.Infinite());
  }
  AIS = AISShape;
  return true;
}
