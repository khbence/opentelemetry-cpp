// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifdef ENABLE_LOGS_PREVIEW

#  include <string>

#  include "opentelemetry/logs/event_logger.h"
#  include "opentelemetry/nostd/shared_ptr.h"
#  include "opentelemetry/nostd/string_view.h"
#  include "opentelemetry/nostd/unique_ptr.h"
#  include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace logs
{
class Logger;
class LogRecord;

class EventLogger final : public opentelemetry::logs::EventLogger
{
public:
  /**
   * Initialize a new Eventlogger.
   * @param delegate_logger The delegate logger instance
   * @param event_domain Event domain
   */
  explicit EventLogger(nostd::shared_ptr<opentelemetry::logs::Logger> delegate_logger,
                       nostd::string_view event_domain) noexcept;

  /**
   * Returns the name of this logger.
   */
  const opentelemetry::nostd::string_view GetName() noexcept override;

  nostd::shared_ptr<opentelemetry::logs::Logger> GetDelegateLogger() noexcept override;

  using opentelemetry::logs::EventLogger::EmitEvent;

  void EmitEvent(nostd::string_view event_name,
                 nostd::unique_ptr<opentelemetry::logs::LogRecord> &&log_record) noexcept override;

private:
  nostd::shared_ptr<opentelemetry::logs::Logger> delegate_logger_;
  std::string event_domain_;
};

}  // namespace logs
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
#endif
