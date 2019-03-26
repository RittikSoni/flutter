// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_SHELL_PLATFORM_EMBEDDER_TESTS_EMBEDDER_CONFIG_BUILDER_H_
#define FLUTTER_SHELL_PLATFORM_EMBEDDER_TESTS_EMBEDDER_CONFIG_BUILDER_H_

#include "flutter/fml/macros.h"
#include "flutter/fml/unique_object.h"
#include "flutter/shell/platform/embedder/embedder.h"
#include "flutter/shell/platform/embedder/tests/embedder_context.h"
#include "flutter/shell/platform/embedder/tests/embedder_test.h"

namespace shell {
namespace testing {

struct UniqueEngineTraits {
  static FlutterEngine InvalidValue() { return nullptr; }

  static bool IsValid(const FlutterEngine& value) { return value != nullptr; }

  static void Free(FlutterEngine engine) {
    auto result = FlutterEngineShutdown(engine);
    FML_CHECK(result == kSuccess);
  }
};

using UniqueEngine = fml::UniqueObject<FlutterEngine, UniqueEngineTraits>;

class EmbedderConfigBuilder {
 public:
  enum class InitializationPreference {
    kInitialize,
    kNoInitialize,
  };

  EmbedderConfigBuilder(EmbedderContext& context,
                        InitializationPreference preference =
                            InitializationPreference::kInitialize);

  ~EmbedderConfigBuilder();

  void SetSoftwareRendererConfig();

  void SetAssetsPath();

  void SetSnapshots();

  void SetIsolateCreateCallbackHook();

  void SetDartEntrypoint(std::string entrypoint);

  UniqueEngine LaunchEngine() const;

 private:
  EmbedderContext& context_;
  FlutterProjectArgs project_args_ = {};
  FlutterRendererConfig renderer_config_ = {};
  FlutterSoftwareRendererConfig software_renderer_config_ = {};
  std::string dart_entrypoint_;

  FML_DISALLOW_COPY_AND_ASSIGN(EmbedderConfigBuilder);
};

}  // namespace testing
}  // namespace shell

#endif  // FLUTTER_SHELL_PLATFORM_EMBEDDER_TESTS_EMBEDDER_CONFIG_BUILDER_H_
