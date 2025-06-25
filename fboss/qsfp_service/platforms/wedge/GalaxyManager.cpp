#include "fboss/qsfp_service/platforms/wedge/GalaxyManager.h"

#include "fboss/agent/platforms/common/galaxy/GalaxyFCPlatformMapping.h"
#include "fboss/agent/platforms/common/galaxy/GalaxyLCPlatformMapping.h"
#include "fboss/lib/usb/GalaxyI2CBus.h"
#include "fboss/lib/usb/TransceiverPlatformI2cApi.h"
#include "fboss/qsfp_service/module/QsfpModule.h"

namespace facebook {
namespace fboss {

GalaxyManager::GalaxyManager(
    PlatformType mode,
    const std::string& /* platformMappingStr */)
    : WedgeManager(
          std::make_unique<TransceiverPlatformI2cApi>(&i2cBus_),
          (mode == PlatformType::PLATFORM_GALAXY_LC)
              ? (std::shared_ptr<PlatformMapping>)
                    std::make_shared<GalaxyLCPlatformMapping>(
                        GalaxyLCPlatformMapping::getLinecardName())
              : (std::shared_ptr<PlatformMapping>)
                    std::make_shared<GalaxyFCPlatformMapping>(
                        GalaxyFCPlatformMapping::getFabriccardName()),
          mode) {}
// TODO: Will fully migrate I2CBusApi into TransceiverPlatformApi. Then we will
// construct the bus pointer before construct WedgeManager and will get rid of
// getI2CBus at that time.
std::unique_ptr<TransceiverI2CApi> GalaxyManager::getI2CBus() {
  return std::make_unique<WedgeI2CBusLock>(std::make_unique<GalaxyI2CBus>());
}
} // namespace fboss
} // namespace facebook
