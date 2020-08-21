#pragma once
#include <IO/BitstreamReader.h>


struct SceneInfo
{
    bool sceneInfoPresentFlag = false;
    std::uint16_t sceneId = 0;
    std::uint16_t sceneTransitionType = 0;
    std::uint16_t secondSceneId = 0;

    SceneInfo() = default;
    explicit SceneInfo(BitstreamReader& reader)
    {
        sceneInfoPresentFlag = reader.readBits<bool, 1>();
        if (sceneInfoPresentFlag)
        {
            sceneId = reader.readExpoGlomb();
            sceneTransitionType = reader.readExpoGlomb();
            if (sceneTransitionType > 3)
            {
                secondSceneId = reader.readExpoGlomb();
            }
        }
    }
};


