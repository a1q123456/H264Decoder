#pragma once
#include <IO/BitstreamReader.h>


struct ScalabilityInfo
{
    struct Layer
    {
        struct Roi
        {
            std::uint8_t firstMbInRoi = 0;
            std::uint8_t roiWidthInMbsMinus1 = 0;
            std::uint8_t roiHeightInMbsMinus1 = 0;

            Roi() = default;
            explicit Roi(BitstreamReader& reader)
            {
                firstMbInRoi = reader.readExpoGlomb();
                roiWidthInMbsMinus1 = reader.readExpoGlomb();
                roiHeightInMbsMinus1 = reader.readExpoGlomb();
            }
        };

        struct RewritingInfo
        {
            bool rewritingInfoFlag = false;
            std::uint32_t rewritingProfileLevelIdc = 0;
            std::uint16_t rewritingAvgBitrate = 0;
            std::uint16_t rewritingMaxBitrate = 0;

            RewritingInfo() = default;
            explicit RewritingInfo(BitstreamReader& reader)
            {
                rewritingInfoFlag = reader.readBits<bool, 1>();
                rewritingProfileLevelIdc = reader.readBits<std::uint32_t, 24>();
                rewritingAvgBitrate = reader.readBits<std::uint16_t, 16>();
                rewritingMaxBitrate = reader.readBits<std::uint16_t, 16>();
            }
        };

        std::uint8_t layerId = 0;
        std::uint8_t priorityId = 0;
        bool discardableFlag = false;
        std::uint8_t dependencyId = 0;
        std::uint8_t qualityId = 0;
        std::uint8_t temporalId = 0;
        bool subPicLayerFlag = false;
        bool subRegionLayerFlag = false;
        bool iroiDivisionInfoPresentFlag = false;
        bool profileLevelInfoPresentFlag = false;
        bool bitrateInfoPresentFlag = false;
        bool frmRateInfoPresentFlag = false;
        bool frmSizeInfoPresentFlag = false;
        bool layerDependencyInfoPresentFLag = false;
        bool parameterSetInfoPresentFlag = false;
        bool bitstreamRestrictionInfoPresentFlag = false;
        bool exactInterLayerPredFLag = false;

        bool exactSampleValueMatchFlag = false;
        bool layerConversionFlag = false;
        bool layerOutputFlag = false;
        std::uint32_t layerProfileLevelIdc = 0;

        std::uint16_t avgBitrate = 0;
        std::uint16_t maxBitrateLayer = 0;
        std::uint16_t maxBitrateLayerRepresentation = 0;
        std::uint16_t maxBitrateCalcWindow = 0;

        std::uint8_t constantFrmRateIdc = 0;
        std::uint16_t avgFrmRate = 0;

        std::uint8_t frmWidthInMbsMinus1 = 0;
        std::uint8_t frmHeightInMbsMinus1 = 0;

        std::uint8_t baseRegionLayerId = 0;
        bool dynamicRectFlag = false;
        std::uint16_t horizontalOffset = 0;
        std::uint16_t verticalOffset = 0;
        std::uint16_t regionWidth = 0;
        std::uint16_t regionHeight = 0;

        std::uint8_t roiId = 0;

        bool iroiGridFlag = false;
        std::uint8_t gridWidthInMbsMinus1 = 0;
        std::uint8_t gridHeightInMbsMinus1 = 0;
        std::uint8_t numRoisMinus1 = 0;
        std::vector<Roi> rois;

        std::uint8_t numDirectlyDependentLayers = 0;
        std::vector<std::uint8_t> directlyDependentLayerIdDeltaMinus1;
        std::uint8_t layerDependencyInfoSrcLayerIdDelta = 0;

        std::uint8_t numSeqParameterSets = 0;
        std::vector<std::uint8_t> seqParameterSetIdDelta;

        std::uint8_t numSubsetSeqParameterSets = 0;
        std::vector<std::uint8_t> subsetSeqParameterSetIdDelta;
        std::uint8_t numPicParameterSetsMinus1 = 0;
        std::vector<std::uint32_t> picParameterSetIdDelta;
        std::uint8_t parameterSetsInfoSrcLayerIdDelta = 0;

        bool motionVectorsOverPicBoundariesFlag = false;
        std::uint8_t maxBytesPerPicDenom = 0;
        std::uint8_t maxBitsPerMbDenom = 0;
        std::uint8_t log2MaxMvLengthHorizontal = 0;
        std::uint8_t log2MaxMvLengthVertical = 0;
        std::uint8_t maxNumReorderFrames = 0;
        std::uint8_t maxDecFrameBuffering = 0;

        std::uint8_t conversionTypeIdc = 0;
        RewritingInfo rewritingInfo[2];


        Layer() = default;
        explicit Layer(BitstreamReader& reader)
        {
            layerId = reader.readExpoGlomb();
            priorityId = reader.readBits<std::uint8_t, 6>();
            discardableFlag = reader.readBits<bool, 1>();
            dependencyId = reader.readBits<std::uint8_t, 3>();
            qualityId = reader.readBits<std::uint8_t, 4>();
            temporalId = reader.readBits<std::uint8_t, 3>();
            subPicLayerFlag = reader.readBits<bool, 1>();
            subRegionLayerFlag = reader.readBits<bool, 1>();
            iroiDivisionInfoPresentFlag = reader.readBits<bool, 1>();
            profileLevelInfoPresentFlag = reader.readBits<bool, 1>();
            bitrateInfoPresentFlag = reader.readBits<bool, 1>();
            frmRateInfoPresentFlag = reader.readBits<bool, 1>();
            frmSizeInfoPresentFlag = reader.readBits<bool, 1>();
            layerDependencyInfoPresentFLag = reader.readBits<bool, 1>();
            parameterSetInfoPresentFlag = reader.readBits<bool, 1>();
            bitstreamRestrictionInfoPresentFlag = reader.readBits<bool, 1>();
            exactInterLayerPredFLag = reader.readBits<bool, 1>();

            if (subPicLayerFlag || iroiDivisionInfoPresentFlag)
            {
                exactSampleValueMatchFlag = reader.readBits<bool, 1>();
            }
            layerConversionFlag = reader.readBits<bool, 1>();
            layerOutputFlag = reader.readBits<bool, 1>();

            if (profileLevelInfoPresentFlag)
            {
                layerProfileLevelIdc = reader.readBits<std::uint32_t, 24>();
            }
            if (bitrateInfoPresentFlag)
            {
                avgBitrate = reader.readBits<std::uint16_t, 16>();
                maxBitrateCalcWindow = reader.readBits<std::uint16_t, 16>();
                maxBitrateLayerRepresentation = reader.readBits<std::uint16_t, 16>();
                maxBitrateCalcWindow = reader.readBits<std::uint16_t, 16>();
            }
            if (frmRateInfoPresentFlag)
            {
                constantFrmRateIdc = reader.readBits<std::uint8_t, 2>();
                avgFrmRate = reader.readBits<std::uint16_t, 16>();
            }
            if (frmSizeInfoPresentFlag || iroiDivisionInfoPresentFlag)
            {
                frmWidthInMbsMinus1 = reader.readExpoGlomb();
                frmHeightInMbsMinus1 = reader.readExpoGlomb();
            }
            if (subRegionLayerFlag)
            {
                baseRegionLayerId = reader.readExpoGlomb();
                dynamicRectFlag = reader.readBits<bool, 1>();
                if (!dynamicRectFlag)
                {
                    horizontalOffset = reader.readBits<std::uint16_t, 16>();
                    verticalOffset = reader.readBits<std::uint16_t, 16>();
                    regionWidth = reader.readBits<std::uint16_t, 16>();
                    regionHeight = reader.readBits<std::uint16_t, 16>();
                }
            }

            if (subPicLayerFlag)
            {
                roiId = reader.readExpoGlomb();
            }
            if (iroiDivisionInfoPresentFlag)
            {
                iroiGridFlag = reader.readBits<bool, 1>();
                if (iroiGridFlag)
                {
                    gridWidthInMbsMinus1 = reader.readExpoGlomb();
                    gridHeightInMbsMinus1 = reader.readExpoGlomb();
                }
                else
                {
                    numRoisMinus1 = reader.readExpoGlomb();
                    for (auto j = 0; j <= numRoisMinus1; j++)
                    {
                        rois.emplace_back(reader);
                    }
                }
            }
            if (layerDependencyInfoPresentFLag)
            {
                numDirectlyDependentLayers = reader.readExpoGlomb();
                for (auto j = 0; j < numDirectlyDependentLayers; j++)
                {
                    directlyDependentLayerIdDeltaMinus1.emplace_back(reader.readExpoGlomb());
                }
            }
            else
            {
                layerDependencyInfoSrcLayerIdDelta = reader.readExpoGlomb();
            }
            if (parameterSetInfoPresentFlag)
            {
                numSeqParameterSets = reader.readExpoGlomb();
                for (auto j = 0; j < numSeqParameterSets; j++)
                {
                    seqParameterSetIdDelta.emplace_back(reader.readExpoGlomb());
                }
                numSubsetSeqParameterSets = reader.readExpoGlomb();
                for (auto j = 0; j < numSubsetSeqParameterSets; j++)
                {
                    subsetSeqParameterSetIdDelta.emplace_back(reader.readExpoGlomb());
                }
                numPicParameterSetsMinus1 = reader.readExpoGlomb();
                for (auto j = 0; j <= numPicParameterSetsMinus1; j++)
                {
                    picParameterSetIdDelta.emplace_back(reader.readExpoGlomb());
                }
            }
            else
            {
                parameterSetsInfoSrcLayerIdDelta = reader.readExpoGlomb();
            }
            if (bitstreamRestrictionInfoPresentFlag)
            {
                motionVectorsOverPicBoundariesFlag = reader.readBits<bool, 1>();
                maxBytesPerPicDenom = reader.readExpoGlomb();
                maxBitsPerMbDenom = reader.readExpoGlomb();
                log2MaxMvLengthHorizontal = reader.readExpoGlomb();
                log2MaxMvLengthVertical = reader.readExpoGlomb();
                maxNumReorderFrames = reader.readExpoGlomb();
                maxDecFrameBuffering = reader.readExpoGlomb();
            }
            if (layerConversionFlag)
            {
                conversionTypeIdc = reader.readExpoGlomb();
                for (auto j = 0; j < 2; j++)
                {
                    rewritingInfo[j] = RewritingInfo{ reader };
                }
            }
        }
    };

    struct DId
    {
        struct PR
        {
            std::uint8_t prId = 0;
            std::uint32_t prProfileLevelIdc = 0;
            std::uint16_t prAvgBitrate = 0;
            std::uint16_t prMaxBitrate = 0;

            PR() = default;
            explicit PR(BitstreamReader& reader)
            {
                prId = reader.readExpoGlomb();
                prProfileLevelIdc = reader.readBits<std::uint32_t, 24>();
                prAvgBitrate = reader.readBits<std::uint16_t, 16>();
                prMaxBitrate = reader.readBits<std::uint16_t, 16>();
            }
        };

        std::uint8_t prDependencyId = 0;
        std::uint8_t prNumMinus1 = 0;

        std::vector<PR> prs;

        DId() = default;
        explicit DId(BitstreamReader& reader)
        {
            prDependencyId = reader.readBits<std::uint8_t, 3>();
            prNumMinus1 = reader.readExpoGlomb();

            for (auto j = 0; j <= prNumMinus1; j++)
            {
                prs.emplace_back(reader);
            }
        }
    };


    bool temporalIdNestingFlag = false;
    bool priorityLayerInfoPresentFlag = false;
    bool priorityIdSettingsFlag;

    std::uint8_t numLayersMinus1 = 0;
    std::vector<Layer> layers;

    std::uint8_t prNumDIdsMinus1 = 0;
    std::vector<DId> dIds;

    std::vector<Byte> priorityIdSettingUri;

    ScalabilityInfo() = default;
    explicit ScalabilityInfo(BitstreamReader& reader)
    {
        temporalIdNestingFlag = reader.readBits<bool, 1>();
        priorityLayerInfoPresentFlag = reader.readBits<bool, 1>();
        priorityIdSettingsFlag = reader.readBits<bool, 1>();
        numLayersMinus1 = reader.readExpoGlomb();

        for (auto i = 0; i <= numLayersMinus1; i++)
        {
            layers.emplace_back(reader);
        }
        if (priorityLayerInfoPresentFlag)
        {
            prNumDIdsMinus1 = reader.readExpoGlomb();
            for (auto i = 0; i <= prNumDIdsMinus1; i++)
            {
                dIds.emplace_back(reader);
            }
        }

        if (priorityIdSettingsFlag)
        {
            while (priorityIdSettingUri.emplace_back(reader.readBits<Byte, 8>()) != 0)
            {

            }
        }
    }
};

