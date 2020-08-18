#include "pch.h"
#include "DecRefPicMarking.h"
#include <Data\NaluTypes.h>
#include <Data\DecodingContext.h>

DecRefPicMarking::DecRefPicMarking(NaluTypes nalType, BitstreamReader& reader)
{
    if (GetIdrPicFlag(nalType))
    {
        noOutputOfPriorPicsFlag = reader.readBits<bool, 1>();
        longTermReferenceFlag = reader.readBits<bool, 1>();
    }
    else
    {
        adaptiveRefPicMarkingModeFlag = reader.readBits<bool, 1>();
        if (adaptiveRefPicMarkingModeFlag)
        {
            do
            {
                memoryManagementControlOperation = reader.readExpoGlomb();
                if (memoryManagementControlOperation == 1 || memoryManagementControlOperation == 3)
                {
                    differenceOfPicNumsMinus1 = reader.readExpoGlomb();
                }
                if (memoryManagementControlOperation == 2)
                {
                    longTermPicNum = reader.readExpoGlomb();
                }
                if (memoryManagementControlOperation == 3 || memoryManagementControlOperation == 6)
                {
                    longTermFrameIdx = reader.readExpoGlomb();
                }
                if (memoryManagementControlOperation == 4)
                {
                    maxLongTermFrameIdxPlus1 = reader.readExpoGlomb();
                }

            } while (memoryManagementControlOperation != 0);
        }
    }
}
