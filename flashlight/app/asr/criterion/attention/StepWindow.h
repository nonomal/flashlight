/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "flashlight/app/asr/criterion/attention/WindowBase.h"

namespace fl {
namespace app {
namespace asr {

class StepWindow : public WindowBase {
 public:
  StepWindow();
  StepWindow(int sMin, int sMax, double vMin, double vMax);

  Variable computeWindow(
      const Variable& prevAttn,
      int step,
      int targetLen,
      int inputSteps,
      int batchSize,
      const af::array& inputSizes = af::array(),
      const af::array& targetSizes = af::array()) const override;

  Variable computeVectorizedWindow(
      int targetLen,
      int inputSteps,
      int batchSize,
      const af::array& inputSizes = af::array(),
      const af::array& targetSizes = af::array()) const override;

 private:
  int sMin_;
  int sMax_;
  double vMin_;
  double vMax_;

  Variable compute(
      int targetLen,
      int inputSteps,
      int batchSize,
      const af::array& inputSizes,
      const af::array& targetSizes,
      af::array& decoderSteps) const;

  FL_SAVE_LOAD_WITH_BASE(WindowBase, sMin_, sMax_, vMin_, vMax_)
};
} // namespace asr
} // namespace app
} // namespace fl

CEREAL_REGISTER_TYPE(fl::app::asr::StepWindow)
