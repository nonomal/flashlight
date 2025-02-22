/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "flashlight/app/asr/augmentation/SoundEffect.h"
#include "flashlight/app/asr/augmentation/SoundEffectConfig.h"
#include "flashlight/app/asr/data/Sound.h"

DEFINE_string(input, "", "Sound file to augment.");
DEFINE_string(
    output,
    "augmented.flac",
    "Path to store result of augmenting the input file");
DEFINE_string(config, "", "Path to a sound effect json config file");

using namespace ::fl::app::asr::sfx;
using ::fl::app::asr::loadSound;
using ::fl::app::asr::loadSoundInfo;
using ::fl::app::asr::saveSound;

int main(int argc, char** argv) {
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  std::string exec(argv[0]);

  gflags::SetUsageMessage(
      "Usage: \n " + exec +
      " --input=[path to input file] --output=[path to output file] " +
      "--config=[path to config file]");

  if (argc <= 1) {
    LOG(FATAL) << gflags::ProgramUsage();
  }

  gflags::ParseCommandLineFlags(&argc, &argv, false);

  if (FLAGS_config.empty()) {
    LOG(FATAL) << "flag --config must point to sound effect config file";
  }
  if (FLAGS_input.empty()) {
    LOG(FATAL) << "flag --input must point to input file";
  }

  auto sound = loadSound<float>(FLAGS_input);
  auto info = loadSoundInfo(FLAGS_input);

  std::shared_ptr<SoundEffect> sfx =
      createSoundEffect(readSoundEffectConfigFile(FLAGS_config));
  sfx->apply(sound);

  saveSound(
      FLAGS_output,
      sound,
      info.samplerate,
      info.channels,
      fl::app::asr::SoundFormat::FLAC,
      fl::app::asr::SoundSubFormat::PCM_16);

  LOG(INFO) << "Saving augmented file to=" << FLAGS_output;

  return 0;
}
