/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Logger/Logger.hpp"

int main() {
    using Logger = eho::CLogger<eho::LogLevel::Trace>;

    Logger::Trace("{}, {}, {}", "blah", "blih", "blog");
    Logger::Debug("{}, {}, {}", "blah", "blih", "blog");
    Logger::Info("{}, {}, {}", "blah", "blih", "blog");
    Logger::Warning("{}, {}, {}", "blah", "blih", "blog");
    Logger::Error("{}, {}, {}", "blah", "blih", "blog");
    Logger::Fatal("{}, {}, {}", "blah", "blih", "blog");
    return 0;
}
