/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#pragma once

#include "fboss/agent/hw/test/HwLinkStateToggler.h"

#include <memory>

namespace facebook::fboss {

class Port;
class TestEnsembleIf;
class SaiSwitch;

class SaiLinkStateToggler : public HwLinkStateToggler {
 public:
  explicit SaiLinkStateToggler(TestEnsembleIf* ensemble)
      : HwLinkStateToggler(ensemble), saiEnsemble_(ensemble) {}

 private:
  SaiSwitch* getHw() const;
  void invokeLinkScanIfNeeded(PortID /*port*/, bool /*isUp*/) override {
    // TODO
  }
  void setPortPreemphasis(const std::shared_ptr<Port>& port, int preemphasis)
      override;

  TestEnsembleIf* saiEnsemble_;
};

} // namespace facebook::fboss
