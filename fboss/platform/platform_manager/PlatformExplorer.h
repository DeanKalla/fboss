// Copyright (c) 2004-present, Meta Platforms, Inc. and affiliates.
// All Rights Reserved.

#pragma once

#include <folly/experimental/FunctionScheduler.h>

#include "fboss/platform/platform_manager/PlatformI2cExplorer.h"
#include "fboss/platform/platform_manager/PresenceDetector.h"
#include "fboss/platform/platform_manager/gen-cpp2/platform_manager_config_types.h"

namespace facebook::fboss::platform::platform_manager {
class PlatformExplorer {
 public:
  explicit PlatformExplorer(
      std::chrono::seconds exploreInterval,
      const PlatformConfig& config);
  void explore();
  void explorePmUnit(
      const std::string& parentPmUnitPath,
      const std::string& parentSlotName,
      const SlotConfig& parentSlot,
      const std::string& pmUnitName);
  void exploreSlot(
      const std::string& pmUnitPath,
      const std::string& slotName,
      const SlotConfig& slotConfig);
  std::optional<std::string> getPmUnitNameFromSlot(
      const SlotConfig& slotConfig,
      const std::string& pmUnitPath);
  void exploreI2cDevices(
      const std::string& pmUnitPath,
      const std::vector<I2cDeviceConfig>& i2cDeviceConfigs);
  uint16_t getI2cBusNum(
      const std::string& pmUnitPath,
      const std::string& pmUnitScopeBusName) const;
  void updateI2cBusNum(
      const std::string& pmUnitPath,
      const std::string& pmUnitScopeBusName,
      uint16_t busNum);

 private:
  folly::FunctionScheduler scheduler_;
  PlatformConfig platformConfig_{};
  PlatformI2cExplorer i2cExplorer_{};
  PresenceDetector presenceDetector_{};
  // Map from <pmUnitName, pmUnitScopeBusName> to kernel i2c bus name.
  // Example: <CHASSIS/PIMSlot0:PIM-8DD, INCOMING@3> -> i2c-54
  std::map<std::pair<std::string, std::string>, uint16_t> i2cBusNamesToNums_{};
};

} // namespace facebook::fboss::platform::platform_manager
