// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifdef ENABLE_LOGS_PREVIEW

#  include "opentelemetry/common/attribute_value.h"
#  include "opentelemetry/common/spin_lock_mutex.h"
#  include "opentelemetry/nostd/type_traits.h"
#  include "opentelemetry/sdk/common/attribute_utils.h"
#  include "opentelemetry/sdk/logs/exporter.h"

#  include "opentelemetry/version.h"

#  include <iostream>
#  include <sstream>
#  include <unordered_map>

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace logs
{
/**
 * The OStreamLogRecordExporter exports logs through an ostream (default set to std::cout)
 */
class OStreamLogRecordExporter final : public opentelemetry::sdk::logs::LogRecordExporter
{
public:
  /**
   * Create an OStreamLogRecordExporter. This constructor takes in a reference to an ostream that
   * the Export() method will send log data into. The default ostream is set to stdout.
   */
  explicit OStreamLogRecordExporter(std::ostream &sout = std::cout) noexcept;

  std::unique_ptr<sdk::logs::Recordable> MakeRecordable() noexcept override;

  /**
   * Exports a span of logs sent from the processor.
   */
  opentelemetry::sdk::common::ExportResult Export(
      const opentelemetry::nostd::span<std::unique_ptr<sdk::logs::Recordable>> &records) noexcept
      override;

  /**
   * Force flush the exporter.
   * @param timeout an option timeout, default to max.
   * @return return true when all data are exported, and false when timeout
   */
  bool ForceFlush(
      std::chrono::microseconds timeout = std::chrono::microseconds::max()) noexcept override;

  /**
   * Marks the OStream Log Exporter as shut down.
   */
  bool Shutdown(
      std::chrono::microseconds timeout = std::chrono::microseconds::max()) noexcept override;

private:
  // The OStream to send the logs to
  std::ostream &sout_;
  // Whether this exporter has been shut down
  bool is_shutdown_ = false;
  mutable opentelemetry::common::SpinLockMutex lock_;
  bool isShutdown() const noexcept;
  void printAttributes(
      const std::unordered_map<std::string, opentelemetry::sdk::common::OwnedAttributeValue> &map,
      const std::string prefix = "\n\t");
  void printAttributes(
      const std::unordered_map<std::string, opentelemetry::common::AttributeValue> &map,
      const std::string prefix = "\n\t");
};
}  // namespace logs
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
#endif
