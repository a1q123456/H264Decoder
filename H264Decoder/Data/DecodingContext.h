#pragma once
#include <Data\NALU\PPSRbsp.h>
#include <Data\NALU\SPSRbsp.h>
#include <Data\NaluTypes.h>
#include <Data\NALU\DPSContext.h>
#include <Data\NALU\DPSRbsp.h>
#include <Data\NALU\InterpretationOfPicStruct.h>
#include <Data\NALU\CurrentPictureContext.h>
#include <Data\NALU\SubsetSPSRbsp.h>
#include <Data/SliceType.h>


constexpr bool getIdrPicFlag(NaluTypes nalType)
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

    int getPicWidthInMbs()
    {
        return currentSPS().picWidthInMbsMinus1 + 1;
    }

    int getPicHeightInMapUnits()
    {
        return currentSPS().picHeightInMapUnitsMinus1 + 1;
    }

    int getFrameHeightInMbs()
    {
        return (2 - currentSPS().frameMbsOnlyFlag) * getPicHeightInMapUnits();
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
            return std::get<SubsetSPSRbsp>(spsContext.at(spsId)).spsData;
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

    SubsetSPSRbsp& currentSubsetSPS()
    {
        if (activeSPSId == -1)
        {
            throw std::runtime_error("no current sps");
        }
        return std::get<SubsetSPSRbsp>(spsContext.at(activeSPSId));
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
            return std::get<SubsetSPSRbsp>(spsContext.at(activeSPSId)).spsData;
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

    void activePPS(int id)
    {
        if (ppsContext.find(id) == ppsContext.end())
        {
            throw std::out_of_range("no such id");
        }
        activePPSId = id;
    }

    void activeDPS(int id)
    {
        if (dpsContext.find(id) == dpsContext.end())
        {
            throw std::out_of_range("no such id");
        }
        activeDPSId = id;
    }
    
    void activeSPS(int id)
    {
        if (spsContext.find(id) == spsContext.end())
        {
            throw std::out_of_range("no such id");
        }
        activeSPSId = id;
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

    const SubsetSPSRbsp& currentSubsetSPS() const
    {
        if (activeSPSId == -1)
        {
            throw std::runtime_error("no current sps");
        }
        return std::get<SubsetSPSRbsp>(spsContext.at(activeSPSId));
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


