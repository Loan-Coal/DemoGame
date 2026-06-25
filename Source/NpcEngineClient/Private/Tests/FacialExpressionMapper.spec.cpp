// File: FacialExpressionMapper.spec.cpp
// Module: NpcEngineClient
// Purpose: Verifies FacialExpressionMapper mapping and null-safety contract.
// Net I/O: no

#include "Misc/AutomationTest.h"
#include "FacialExpressionMapper.h"
#include "NpcEngineTypes.h"

DEFINE_SPEC(FFacialExpressionMapperSpec, "NpcEngine.Client.FacialExpressionMapper",
    EAutomationTestFlags::ProductFilter | EAutomationTestFlags_ApplicationContextMask)

void FFacialExpressionMapperSpec::Define()
{
    Describe("GetMorphEntry", [this]()
    {
        It("Neutral expression returns a non-empty morph target name", [this]()
        {
            UFacialExpressionMapper* Mapper = NewObject<UFacialExpressionMapper>();
            const FFacialMorphEntry Entry =
                Mapper->GetMorphEntry(ENpcFacialExpression::Neutral);
            TestFalse("Neutral morph target name must not be empty",
                Entry.MorphTargetName.IsNone());
        });

        It("every known enum value returns a non-empty morph target name", [this]()
        {
            UFacialExpressionMapper* Mapper = NewObject<UFacialExpressionMapper>();
            const TArray<ENpcFacialExpression> KnownValues = {
                ENpcFacialExpression::Neutral,
                ENpcFacialExpression::Happy,
                ENpcFacialExpression::Sad,
                ENpcFacialExpression::Angry,
                ENpcFacialExpression::Fearful,
                ENpcFacialExpression::Surprised,
                ENpcFacialExpression::Disgusted,
                ENpcFacialExpression::Contempt,
            };
            for (ENpcFacialExpression Expr : KnownValues)
            {
                const FFacialMorphEntry Entry = Mapper->GetMorphEntry(Expr);
                TestFalse(
                    FString::Printf(TEXT("Expression %d must map to a non-empty morph name"),
                        static_cast<int32>(Expr)),
                    Entry.MorphTargetName.IsNone());
            }
        });

        It("Unknown expression falls back to Neutral morph target", [this]()
        {
            UFacialExpressionMapper* Mapper = NewObject<UFacialExpressionMapper>();
            const FFacialMorphEntry NeutralEntry =
                Mapper->GetMorphEntry(ENpcFacialExpression::Neutral);
            const FFacialMorphEntry UnknownEntry =
                Mapper->GetMorphEntry(ENpcFacialExpression::Unknown);
            TestEqual("Unknown falls back to Neutral morph name",
                UnknownEntry.MorphTargetName, NeutralEntry.MorphTargetName);
        });
    });

    Describe("ApplyExpression", [this]()
    {
        It("null SkeletalMeshComponent logs a warning and does not crash", [this]()
        {
            UFacialExpressionMapper* Mapper = NewObject<UFacialExpressionMapper>();
            // AddExpectedError so the test framework counts this as expected, not an error.
            AddExpectedError(TEXT("ApplyExpression: null SkeletalMesh"), EAutomationExpectedErrorFlags::Contains);
            // Must not crash.
            Mapper->ApplyExpression(nullptr, ENpcFacialExpression::Happy, 80);
            TestTrue("reached here without crash", true);
        });
    });
}
