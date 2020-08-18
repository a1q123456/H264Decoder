#pragma once
#include <IO/BitstreamReader.h>


struct SpsMvcdExtension
{
    std::uint8_t numViewsMinus1 = 0;
    std::vector<VuiView> depthViews;

    std::vector<AnchorRef> anchorRefs;
    std::vector<AnchorRef> nonAnchorRefs;

    std::uint8_t numLevelValuesSignalledMinus1 = 0;
    std::vector<SpsMvcdLevelValuesSignalled> levelValuesSignalled;

    bool mvcdVuiParametersPresentFlag = false;
    MvcdVuiParametersExtension mvcdVuiParametersExtension;

    bool textureVuiParametersPresentFlag = false;
    MvcVuiParametersExtension mvcVuiParametersExtension;

    SpsMvcdExtension() = default;
    explicit SpsMvcdExtension(BitstreamReader& reader)
    {
        numViewsMinus1 = reader.readExpoGlomb();
        for (auto i = 0, numDepthViews = 0; i <= numViewsMinus1; i++)
        {
            auto&& view = depthViews.emplace_back();;
            view.viewId = reader.readExpoGlomb();
            view.depthViewPresentFlag = reader.readBits<std::uint8_t, 1>();
            view.textureViewPresentFlag = reader.readBits<std::uint8_t, 1>();
            depthViews[numDepthViews].depthViewId = view.viewId;
            numDepthViews += view.depthViewPresentFlag ? 1 : 0;
        }
        anchorRefs.resize(numViewsMinus1 + 1);
        nonAnchorRefs.resize(numViewsMinus1 + 1);
        for (auto i = 1; i <= numViewsMinus1; i++)
        {
            if (depthViews[i].depthViewPresentFlag)
            {
                anchorRefs[i] = AnchorRef{ reader };
            }
        }
        for (auto i = 1; i <= numViewsMinus1; i++)
        {
            if (depthViews[i].depthViewPresentFlag)
            {
                nonAnchorRefs[i] = AnchorRef{ reader };
            }
        }
        numLevelValuesSignalledMinus1 = reader.readExpoGlomb();
        for (auto i = 0; i <= numLevelValuesSignalledMinus1; i++)
        {
            levelValuesSignalled.emplace_back(reader);
        }
        mvcdVuiParametersPresentFlag = reader.readBits<std::uint8_t, 1>();
        if (mvcdVuiParametersPresentFlag)
        {
            mvcdVuiParametersExtension = MvcdVuiParametersExtension{ reader };
        }
        textureVuiParametersPresentFlag = reader.readBits<std::uint8_t, 1>();
        if (textureVuiParametersPresentFlag)
        {
            mvcVuiParametersExtension = MvcVuiParametersExtension{ reader };
        }
    }
};

