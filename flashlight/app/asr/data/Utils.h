/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <string>
#include <vector>

#include "flashlight/app/asr/data/FeatureTransforms.h"
#include "flashlight/lib/audio/feature/FeatureParams.h"
#include "flashlight/lib/text/dictionary/Dictionary.h"
#include "flashlight/lib/text/dictionary/Utils.h"

namespace fl {
namespace app {
namespace asr {

std::vector<std::string> wrd2Target(
    const std::string& word,
    const lib::text::LexiconMap& lexicon,
    const lib::text::Dictionary& dict,
    const std::string& wordSeparator = "",
    float targetSamplePct = 0,
    bool fallback2LtrWordSepLeft = false,
    bool fallback2LtrWordSepRight = false,
    bool skipUnk = false);

std::vector<std::string> wrd2Target(
    const std::vector<std::string>& words,
    const lib::text::LexiconMap& lexicon,
    const lib::text::Dictionary& dict,
    const std::string& wordSeparator = "",
    float targetSamplePct = 0,
    bool fallback2LtrWordSepLeft = false,
    bool fallback2LtrWordSepRight = false,
    bool skipUnk = false);

std::pair<int, FeatureType> getFeatureType(
    const std::string& featuresType,
    int channels,
    const fl::lib::audio::FeatureParams& featParams);

} // namespace asr
} // namespace app
} // namespace fl
