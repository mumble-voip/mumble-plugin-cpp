// Copyright 2020 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#include "mumble/plugin/MumblePlugin.h"

#include <iostream>

class ExamplePlugin : public MumblePlugin {
public:
	ExamplePlugin()
		: MumblePlugin("Example plugin", "Mumble Developers",
					   "This is just a tiny example plugin demonstrating how to use the cpp wrapper.") {}

	virtual void onServerSynchronized(mumble_connection_t connection) noexcept override {
		try {
			std::cout << "Server " << m_api.getServerHash(connection) << " finished synchronizing" << std::endl;
			for (auto currentUser : m_api.getAllUsers(connection)) {
				std::cout << "Found user " << m_api.getUserName(connection, currentUser) << " ("
						  << m_api.getUserHash(connection, currentUser) << ")" << std::endl;
			}
		} catch (const MumbleAPIException &e) {
			std::cerr << "onServerSynchronized: " << e.what() << " (ErrorCode " << e.errorCode() << ")" << std::endl;
		}
	}

	virtual void releaseResource(const void *ptr) noexcept override {
		// We don't allocate any resources so we can have a no-op implementation
		// We'll terminate though in case it is called as that is definitely a bug
		std::terminate();
	}
};

MumblePlugin &MumblePlugin::getPlugin() noexcept {
	static ExamplePlugin plugin;

	return plugin;
}
