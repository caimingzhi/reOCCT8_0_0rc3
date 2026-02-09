#include <IMeshTools_MeshBuilder.hpp>
#include <IMeshData_Face.hpp>
#include <OSD_Parallel.hpp>

IMPLEMENT_STANDARD_RTTIEXT(IMeshTools_MeshBuilder, Message_Algorithm)

IMeshTools_MeshBuilder::IMeshTools_MeshBuilder() = default;

IMeshTools_MeshBuilder::IMeshTools_MeshBuilder(const occ::handle<IMeshTools_Context>& theContext)
    : myContext(theContext)
{
}

IMeshTools_MeshBuilder::~IMeshTools_MeshBuilder() = default;

void IMeshTools_MeshBuilder::Perform(const Message_ProgressRange& theRange)
{
  ClearStatus();

  const occ::handle<IMeshTools_Context>& aContext = GetContext();
  if (aContext.IsNull())
  {
    SetStatus(Message_Fail1);
    return;
  }

  Message_ProgressScope aPS(theRange, "Mesh Perform", 10);

  if (aContext->BuildModel())
  {
    if (aContext->DiscretizeEdges())
    {
      if (aContext->HealModel())
      {
        if (aContext->PreProcessModel())
        {
          if (aContext->DiscretizeFaces(aPS.Next(9)))
          {
            if (aContext->PostProcessModel())
            {
              SetStatus(Message_Done1);
            }
            else
            {
              SetStatus(Message_Fail7);
            }
          }
          else
          {
            if (!aPS.More())
            {
              SetStatus(Message_Fail8);
              aContext->Clean();
              return;
            }
            SetStatus(Message_Fail6);
          }
        }
        else
        {
          SetStatus(Message_Fail5);
        }
      }
      else
      {
        SetStatus(Message_Fail4);
      }
    }
    else
    {
      SetStatus(Message_Fail3);
    }
  }
  else
  {
    const occ::handle<IMeshTools_ModelBuilder>& aModelBuilder = aContext->GetModelBuilder();

    if (aModelBuilder.IsNull())
    {
      SetStatus(Message_Fail1);
    }
    else
    {

      SetStatus(aModelBuilder->GetStatus().IsSet(Message_Fail1) ? Message_Warn1 : Message_Fail2);
    }
  }
  aPS.Next(1);
  aContext->Clean();
}
