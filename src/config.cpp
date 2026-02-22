#include "config.h"

namespace Config
{
  bool IsCloneHeroMode = true;
    namespace Piezo
    {
        uint16_t getCurrentThreshold()
        {
            return IsCloneHeroMode
                ? CloneHero::PiezoThreshold
                : Midi::PiezoThreshold;
        }
    }
}