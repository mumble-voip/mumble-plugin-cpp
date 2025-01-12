// Copyright 2020 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// source tree.

#include "mumble/plugin/MumblePlugin.h"
#include "mumble/plugin/internal/MumblePlugin.h"

extern "C" {
MUMBLE_PLUGIN_EXPORT mumble_error_t MUMBLE_PLUGIN_CALLING_CONVENTION mumble_init(uint32_t id) {
	return MumblePlugin::getPlugin().internal_init(id);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_shutdown() {
	MumblePlugin::getPlugin().internal_shutdown();
}

MUMBLE_PLUGIN_EXPORT struct MumbleStringWrapper MUMBLE_PLUGIN_CALLING_CONVENTION mumble_getName() {
	return MumblePlugin::getPlugin().getName();
}

MUMBLE_PLUGIN_EXPORT mumble_version_t MUMBLE_PLUGIN_CALLING_CONVENTION mumble_getAPIVersion() {
	return MumblePlugin::getPlugin().getAPIVersion();
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_registerAPIFunctions(void *apiStruct) {
	MumblePlugin::getPlugin().registerAPIFunctions(apiStruct);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_releaseResource(const void *pointer) {
	MumblePlugin::getPlugin().releaseResource(pointer);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_setMumbleInfo(mumble_version_t mumbleVersion,
																  mumble_version_t mumbleAPIVersion,
																  mumble_version_t minimalExpectedAPIVersion) {
	MumblePlugin::getPlugin().setMumbleInfo(mumbleVersion, mumbleAPIVersion, minimalExpectedAPIVersion);
}

MUMBLE_PLUGIN_EXPORT mumble_version_t MUMBLE_PLUGIN_CALLING_CONVENTION mumble_getVersion() {
	return MumblePlugin::getPlugin().getVersion();
}

MUMBLE_PLUGIN_EXPORT struct MumbleStringWrapper MUMBLE_PLUGIN_CALLING_CONVENTION mumble_getAuthor() {
	return MumblePlugin::getPlugin().getAuthor();
}

MUMBLE_PLUGIN_EXPORT struct MumbleStringWrapper MUMBLE_PLUGIN_CALLING_CONVENTION mumble_getDescription() {
	return MumblePlugin::getPlugin().getDescription();
}

MUMBLE_PLUGIN_EXPORT uint32_t MUMBLE_PLUGIN_CALLING_CONVENTION mumble_getFeatures() {
	return MumblePlugin::getPlugin().getFeatures();
}

MUMBLE_PLUGIN_EXPORT uint32_t MUMBLE_PLUGIN_CALLING_CONVENTION mumble_deactivateFeatures(uint32_t features) {
	return MumblePlugin::getPlugin().deactivateFeatures(features);
}

#ifdef MUMBLE_PLUGIN_WRAPPER_USE_POSITIONAL_AUDIO
MUMBLE_PLUGIN_EXPORT uint8_t MUMBLE_PLUGIN_CALLING_CONVENTION mumble_initPositionalData(const char *const *programNames,
																		  const uint64_t *programPIDs,
																		  size_t programCount) {
	return MumblePlugin::getPlugin().internal_initPositionalData(programNames, programPIDs, programCount);
}

MUMBLE_PLUGIN_EXPORT bool MUMBLE_PLUGIN_CALLING_CONVENTION mumble_fetchPositionalData(float *avatarPos, float *avatarDir,
																		float *avatarAxis, float *cameraPos,
																		float *cameraDir, float *cameraAxis,
																		const char **context, const char **identity) {
	return MumblePlugin::getPlugin().fetchPositionalData(avatarPos, avatarDir, avatarAxis, cameraPos, cameraDir,
														 cameraAxis, context, identity);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_shutdownPositionalData() {
	MumblePlugin::getPlugin().shutdownPositionalData();
}

MUMBLE_PLUGIN_EXPORT MumbleStringWrapper MUMBLE_PLUGIN_CALLING_CONVENTION mumble_getPositionalDataContextPrefix() {
	return MumblePlugin::getPlugin().getPositionalDataContextPrefix();
}
#endif // MUMBLE_PLUGIN_WRAPPER_USE_POSITIONAL_AUDIO

#ifdef MUMBLE_PLUGIN_WRAPPER_USE_SERVER_EVENT_CALLBACKS
MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onServerConnected(mumble_connection_t connection) {
	MumblePlugin::getPlugin().onServerConnected(connection);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onServerDisconnected(mumble_connection_t connection) {
	MumblePlugin::getPlugin().onServerDisconnected(connection);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onServerSynchronized(mumble_connection_t connection) {
	MumblePlugin::getPlugin().onServerSynchronized(connection);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onChannelEntered(mumble_connection_t connection,
																	 mumble_userid_t userID,
																	 mumble_channelid_t previousChannelID,
																	 mumble_channelid_t newChannelID) {
	MumblePlugin::getPlugin().onChannelEntered(connection, userID, previousChannelID, newChannelID);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onChannelExited(mumble_connection_t connection,
																	mumble_userid_t userID,
																	mumble_channelid_t channelID) {
	MumblePlugin::getPlugin().onChannelExited(connection, userID, channelID);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onUserTalkingStateChanged(mumble_connection_t connection,
																			  mumble_userid_t userID,
																			  mumble_talking_state_t talkingState) {
	MumblePlugin::getPlugin().onUserTalkingStateChanged(connection, userID, talkingState);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onUserAdded(mumble_connection_t connection,
																mumble_userid_t userID) {
	MumblePlugin::getPlugin().onUserAdded(connection, userID);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onUserRemoved(mumble_connection_t connection,
																  mumble_userid_t userID) {
	MumblePlugin::getPlugin().onUserRemoved(connection, userID);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onChannelAdded(mumble_connection_t connection,
																   mumble_channelid_t channelID) {
	MumblePlugin::getPlugin().onChannelAdded(connection, channelID);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onChannelRemoved(mumble_connection_t connection,
																	 mumble_channelid_t channelID) {
	MumblePlugin::getPlugin().onChannelRemoved(connection, channelID);
}

MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onChannelRenamed(mumble_connection_t connection,
																	 mumble_channelid_t channelID) {
	MumblePlugin::getPlugin().onChannelRenamed(connection, channelID);
}
#endif // MUMBLE_PLUGIN_WRAPPER_USE_SERVER_EVENT_CALLBACKS

#ifdef MUMBLE_PLUGIN_WRAPPER_USE_AUDIO_CALLBACKS
MUMBLE_PLUGIN_EXPORT bool MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onAudioInput(short *inputPCM, uint32_t sampleCount,
																 uint16_t channelCount, uint32_t sampleRate,
																 bool isSpeech) {
	return MumblePlugin::getPlugin().onAudioInput(inputPCM, sampleCount, channelCount, sampleRate, isSpeech);
}

MUMBLE_PLUGIN_EXPORT bool MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onAudioSourceFetched(float *outputPCM, uint32_t sampleCount,
																		 uint16_t channelCount, uint32_t sampleRate,
																		 bool isSpeech, mumble_userid_t userID) {
	return MumblePlugin::getPlugin().onAudioSourceFetched(outputPCM, sampleCount, channelCount, sampleRate, isSpeech,
														  userID);
}

MUMBLE_PLUGIN_EXPORT bool MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onAudioOutputAboutToPlay(float *outputPCM, uint32_t sampleCount,
																			 uint16_t channelCount,
																			 uint32_t sampleRate) {
	return MumblePlugin::getPlugin().onAudioAboutOutputAboutToPlay(outputPCM, sampleCount, channelCount, sampleRate);
}
#endif // MUMBLE_PLUGIN_WRAPPER_USE_AUDIO_CALLBACKS

#ifdef MUMBLE_PLUGIN_WRAPPER_USE_PLUGIN_DATA_FRAMEWORK_CALLBACKS
MUMBLE_PLUGIN_EXPORT bool MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onReceiveData(mumble_connection_t connection,
																  mumble_userid_t senderID, const uint8_t *data,
																  size_t dataLength, const char *dataID) {
	return MumblePlugin::getPlugin().onReceiveData(connection, senderID, data, dataLength, dataID);
}
#endif // MUMBLE_PLUGIN_WRAPPER_USE_PLUGIN_DATA_FRAMEWORK_CALLBACKS

#ifdef MUMBLE_PLUGIN_WRAPPER_USE_KEY_EVENT_CALLBACKS
MUMBLE_PLUGIN_EXPORT void MUMBLE_PLUGIN_CALLING_CONVENTION mumble_onKeyEvent(uint32_t keyCode, bool wasPress) {
	MumblePlugin::getPlugin().onKeyEvent(keyCode, wasPress);
}
#endif // MUMBLE_PLUGIN_WRAPPER_USE_KEY_EVENT_CALLBACKS

#ifdef MUMBLE_PLUGIN_WRAPPER_USE_PLUGIN_UPDATES
MUMBLE_PLUGIN_EXPORT bool MUMBLE_PLUGIN_CALLING_CONVENTION mumble_hasUpdate() {
	return MumblePlugin::getPlugin().hasUpdate();
}

MUMBLE_PLUGIN_EXPORT struct MumbleStringWrapper MUMBLE_PLUGIN_CALLING_CONVENTION mumble_getUpdateDownloadURL() {
	return MumblePlugin::getPlugin().getUpdateDownloadURL();
}
#endif // MUMBLE_PLUGIN_WRAPPER_USE_PLUGIN_UPDATES

mumble_version_t mumble_getPluginFunctionsVersion() {
	return MUMBLE_PLUGIN_FUNCTIONS_VERSION;
}

};
