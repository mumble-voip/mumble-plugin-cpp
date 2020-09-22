// Copyright 2020 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#include "MumblePlugin.h"

MumblePlugin &MumblePlugin::getPlugin() noexcept {
	static MumblePlugin plugin("Example plugin", "Mumble Developers",
							   "This is just a tiny example plugin demonstrating how to use the cpp wrapper.");

	return plugin;
}
