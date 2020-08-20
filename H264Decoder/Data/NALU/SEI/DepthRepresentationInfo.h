#pragma once
#include <IO/BitstreamReader.h>


struct DepthRepresentationInfo
{
    struct ViewInfo
    {
        std::uint32_t depthInfoViewId = 0;
        std::uint32_t zAxisReferenceIView = 0;
        std::uint32_t disparityReferenceView = 0;
        DepthRepresentationSEIElement zNear;
        DepthRepresentationSEIElement zFar;
        DepthRepresentationSEIElement dMin;
        DepthRepresentationSEIElement dMax;

        ViewInfo() = default;
        explicit ViewInfo(BitstreamReader& reader, bool zNearFlag, bool zFarFlag, bool dMinFlag, bool dMaxFlag, bool zAxisEqualFlag)
        {
            depthInfoViewId = reader.readExpoGlomb();
            if ((zNearFlag || zFarFlag) && (!zAxisEqualFlag))
            {
                zAxisReferenceIView = reader.readExpoGlomb();
            }
            if (dMinFlag || dMaxFlag)
            {
                disparityReferenceView = reader.readExpoGlomb();
            }
            if (zNearFlag)
            {
                zNear = DepthRepresentationSEIElement{ reader };
            }
            if (zFarFlag)
            {
                zFar = DepthRepresentationSEIElement{ reader };
            }
            if (dMinFlag)
            {
                dMin = DepthRepresentationSEIElement{ reader };
            }
            if (dMaxFlag)
            {
                dMax = DepthRepresentationSEIElement{ reader };
            }
        }
    };

    bool allViewsEqualFlag = false;
    std::uint32_t numViewsMinus1 = 0;

    bool zNearFlag = false;
    bool zFarFlag = false;

    bool zAxisEqualFlag = false;
    std::uint32_t commonZAxisReferenceView = 0;
    bool dMinFlag = false;
    bool dMaxFlag = false;

    std::uint32_t depthRepresentationType = 0;
    std::vector<ViewInfo> viewInfos;
    std::uint32_t depthNonlinearRepresentationNumMinus1 = 0;
    std::vector<std::uint32_t> depthNonlinearRepresentationModel;

    DepthRepresentationInfo() = default;
    explicit DepthRepresentationInfo(BitstreamReader& reader)
    {
        allViewsEqualFlag = reader.readBits<bool, 1>();
        int numViews = 0;
        if (!allViewsEqualFlag)
        {
            numViewsMinus1 = reader.readExpoGlomb();
            numViews = numViewsMinus1 + 1;
        }
        else
        {
            numViews = 1;
        }
        zNearFlag = reader.readBits<bool, 1>();
        zFarFlag = reader.readBits<bool, 1>();
        if (zNearFlag || zFarFlag)
        {
            zAxisEqualFlag = reader.readBits<bool, 1>();
            if (zAxisEqualFlag)
            {
                commonZAxisReferenceView = reader.readExpoGlomb();
            }
        }
        dMinFlag = reader.readBits<bool, 1>();
        dMaxFlag = reader.readBits<bool, 1>();
        depthRepresentationType = reader.readExpoGlomb();
        for (auto i = 0; i < numViews; i++)
        {
            viewInfos.emplace_back(reader, zNearFlag, zFarFlag, dMinFlag, dMaxFlag, zAxisEqualFlag);
        }
        if (depthRepresentationType == 3)
        {
            depthNonlinearRepresentationNumMinus1 = reader.readExpoGlomb();
            depthNonlinearRepresentationModel.resize(depthNonlinearRepresentationNumMinus1 + 2);
            for (auto i = 1; i <= depthNonlinearRepresentationNumMinus1 + 1; i++)
            {
                depthNonlinearRepresentationModel[i] = reader.readExpoGlomb();
            }
        }
    }
};


