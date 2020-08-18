#pragma once
#include <Data\NALU\PPSRbsp.h>
#include <Data\NALU\SPSRbsp.h>
#include <Data\NaluTypes.h>
#include <Data\NALU\DPSContext.h>
#include <Data\NALU\DPSRbsp.h>
#include <Data\NALU\InterpretationOfPicStruct.h>
#include <Data\NALU\SliceHeader.h>
#include <Data\NALU\CurrentPictureContext.h>
#include <Data\NALU\SubsetSPSRbsp.h>


constexpr bool GetIdrPicFlag(NaluTypes nalType)
{
    return nalType == NaluTypes::CodedSliceIDRPicture;
}

struct DecodingContext
{
    struct
    {
        bool nalHrdBpPresentFlag = false;
        bool vclHrdBpPresentFlag = false;
        bool cpbDpbDelaysPresentFlag = false;

    } applicationDeterminedValues;

    std::unordered_map<int, PPSRbsp> ppsContext;
    std::unordered_map<int, std::variant<SPSRbsp, SubsetSPSRbsp>> spsContext;
    std::unordered_map<int, DPSContext> dpsContext;

    std::uint8_t numClockTs = 0;

    static inline std::vector<InterpretationOfPicStruct> interpreatationOfPicStruct
    {
        { 0, "(progressive) frame", [](const SliceHeader& sh, const CurrentPictureContext& cpc, const VuiParameters& vui) { return !sh.fieldPicFlag && cpc.bottomFieldOrderCnt == cpc.topFieldOrderCnt; }, 1 },
        { 1, "top field", [](const SliceHeader& sh, const CurrentPictureContext& cpc, const VuiParameters& vui) { return sh.fieldPicFlag && !sh.bottomFieldFlag; }, 1 },
        { 2, "bottom field", [](const SliceHeader& sh, const CurrentPictureContext& cpc, const VuiParameters& vui) { return sh.fieldPicFlag && sh.bottomFieldFlag; }, 1 },
        { 3, "top field, bottom field, in that order", [](const SliceHeader& sh, const CurrentPictureContext& cpc, const VuiParameters& vui) { return !sh.fieldPicFlag && cpc.bottomFieldOrderCnt >= cpc.topFieldOrderCnt; }, 2 },
        { 4, "bottom field, top field, in that order", [](const SliceHeader& sh, const CurrentPictureContext& cpc, const VuiParameters& vui) { return !sh.fieldPicFlag && cpc.bottomFieldOrderCnt <= cpc.topFieldOrderCnt; }, 2 },
        { 5, "top field, bottom field, top field repeated, in that order", [](const SliceHeader& sh, const CurrentPictureContext& cpc, const VuiParameters& vui) { return !sh.fieldPicFlag && cpc.bottomFieldOrderCnt >= cpc.topFieldOrderCnt; }, 3 },
        { 6, "bottom field, top field, bottom field repeated, in that order", [](const SliceHeader& sh, const CurrentPictureContext& cpc, const VuiParameters& vui) { return !sh.fieldPicFlag && cpc.bottomFieldOrderCnt <= cpc.topFieldOrderCnt; }, 3 },
        { 7, "frame doubling", [](const SliceHeader& sh, const CurrentPictureContext& cpc, const VuiParameters& vui) { return vui.timingInfoPresentFlag && vui.timingInfo.vuiFixedFrameRateFlag && !sh.fieldPicFlag && cpc.bottomFieldOrderCnt == cpc.topFieldOrderCnt; }, 2 },
        { 8, "frame tripling", [](const SliceHeader& sh, const CurrentPictureContext& cpc, const VuiParameters& vui) { return vui.timingInfoPresentFlag && vui.timingInfo.vuiFixedFrameRateFlag && !sh.fieldPicFlag && cpc.bottomFieldOrderCnt == cpc.topFieldOrderCnt; }, 3 },
    };

    int getPicWidthInMbs()
    {
        return currentSPS().picWidthInMbsMinus1 + 1;
    }

    int getPicHeightInMapUnits()
    {
        return currentSPS().picHeightInMapUnitsMinus1 + 1;
    }

    int getPicSizeInMapUnits()
    {
        return getPicHeightInMapUnits() * getPicWidthInMbs();
    }

    PPSRbsp& currentPPS()
    {
        if (activePPSId == -1)
        {
            throw std::runtime_error("no current pps");
        }
        return ppsContext.at(activePPSId);
    }

    SPSData& findSPS(int spsId)
    {
        try
        {
            return std::get<SPSRbsp>(spsContext.at(spsId)).spsData;
        }
        catch (std::bad_variant_access)
        {
            std::get<SubsetSPSRbsp>(spsContext.at(spsId)).spsData;
        }
    }

    SubsetSPSRbsp& findSubsetSPS(int spsId)
    {
        try
        {
            return std::get<SubsetSPSRbsp>(spsContext.at(spsId));
        }
        catch (std::bad_variant_access)
        {
            throw std::runtime_error("subset sps not found");
        }
    }

    SPSData& currentSPS()
    {
        if (activeSPSId == -1)
        {
            throw std::runtime_error("no current sps");
        }
        try
        {
            return std::get<SPSRbsp>(spsContext.at(activeSPSId)).spsData;
        }
        catch (std::bad_variant_access)
        {
            std::get<SubsetSPSRbsp>(spsContext.at(activeSPSId)).spsData;
        }
    }

    bool cpbDpbDelaysPresentFlag()
    {
        return (currentSPS().vuiParametersPresentFlag && (currentSPS().vuiParameters.nalHrdParametersPresentFlag ||
            currentSPS().vuiParameters.vclHrdParametersPresentFlag)) ||
            applicationDeterminedValues.cpbDpbDelaysPresentFlag;
    }

    bool mustHavePicTiming()
    {
        return cpbDpbDelaysPresentFlag() && currentSPS().vuiParametersPresentFlag && currentSPS().vuiParameters.picStructPresentFlag;
    }

    DPSContext& currentDPS()
    {
        if (activeDPSId == -1)
        {
            throw std::runtime_error("no current dps");
        }
        return dpsContext.at(activeDPSId);
    }

    const PPSRbsp& currentPPS() const
    {
        if (activePPSId == -1)
        {
            throw std::runtime_error("no current pps");
        }
        return ppsContext.at(activePPSId);
    }

    const SPSData& currentSPS() const
    {
        if (activeSPSId == -1)
        {
            throw std::runtime_error("no current sps");
        }
        try
        {
            return std::get<SPSRbsp>(spsContext.at(activeSPSId)).spsData;
        }
        catch (std::bad_variant_access)
        {
            std::get<SubsetSPSRbsp>(spsContext.at(activeSPSId)).spsData;
        }
    }

    const DPSContext& currentDPS() const
    {
        if (activeDPSId == -1)
        {
            throw std::runtime_error("no current dps");
        }
        return dpsContext.at(activeDPSId);
    }

    void addPPS(const PPSRbsp& pps)
    {
        ppsContext.insert(std::make_pair(static_cast<int>(pps.ppsId), pps));
        if (activePPSId == -1)
        {
            activePPSId = pps.ppsId;
        }

    }

    void addSPS(const SPSRbsp& sps)
    {
        spsContext.insert(std::make_pair(static_cast<int>(sps.spsData.spsId), std::variant<SPSRbsp, SubsetSPSRbsp>(sps)));
        if (activeSPSId == -1)
        {
            activeSPSId = sps.spsData.spsId;
        }

    }

    void addDPS(const DPSRbsp& dps)
    {
        dpsContext.insert(std::make_pair(static_cast<int>(dps.dpsId), DPSContext{ dps }));
        if (activeDPSId == -1)
        {
            activeDPSId = dps.dpsId;
        }

    }

private:
    int activePPSId = -1;
    int activeSPSId = -1;
    int activeDPSId = -1;
};


