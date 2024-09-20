////////////////////////////////////////////////////////////////////////
// Crystal Server - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////

#pragma once

#include "utils/utils_definitions.hpp"
#include "lib/di/container.hpp"
#include "lua/scripts/luascript.hpp"

class Party;
class Player;

using UsersMap = std::map<uint32_t, std::shared_ptr<Player>>;
using InvitedMap = std::map<uint32_t, std::shared_ptr<Player>>;

class ChatChannel {
public:
	ChatChannel() = default;
	ChatChannel(uint16_t channelId, std::string channelName) :
		name(std::move(channelName)),
		id(channelId) { }

	virtual ~ChatChannel() = default;

	bool addUser(const std::shared_ptr<Player> &player);
	bool removeUser(const std::shared_ptr<Player> &player);
	bool hasUser(const std::shared_ptr<Player> &player);

	bool talk(const std::shared_ptr<Player> &fromPlayer, SpeakClasses type, const std::string &text);
	void sendToAll(const std::string &message, SpeakClasses type) const;

	const std::string &getName() const {
		return name;
	}
	uint16_t getId() const {
		return id;
	}
	const UsersMap &getUsers() const {
		return users;
	}
	virtual const InvitedMap* getInvitedUsers() const {
		return nullptr;
	}

	virtual uint32_t getOwner() const {
		return 0;
	}

	bool isPublicChannel() const {
		return publicChannel;
	}

	bool executeOnJoinEvent(const std::shared_ptr<Player> &player);
	bool executeCanJoinEvent(const std::shared_ptr<Player> &player);
	bool executeOnLeaveEvent(const std::shared_ptr<Player> &player);
	bool executeOnSpeakEvent(const std::shared_ptr<Player> &player, SpeakClasses &type, const std::string &message);

protected:
	UsersMap users;

	std::string name;

	int32_t canJoinEvent = -1;
	int32_t onJoinEvent = -1;
	int32_t onLeaveEvent = -1;
	int32_t onSpeakEvent = -1;

	uint16_t id {};
	bool publicChannel = false;

	friend class Chat;
};

class PrivateChatChannel final : public ChatChannel {
public:
	PrivateChatChannel(uint16_t channelId, [[maybe_unused]] std::string channelName) :
		ChatChannel(channelId, std::move(channelName)) { }

	uint32_t getOwner() const override {
		return owner;
	}
	void setOwner(uint32_t newOwner) {
		this->owner = newOwner;
	}

	bool isInvited(uint32_t guid) const;

	void invitePlayer(const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &invitePlayer);
	void excludePlayer(const std::shared_ptr<Player> &player, const std::shared_ptr<Player> &excludePlayer);

	bool removeInvite(uint32_t guid);

	void closeChannel() const;

	[[nodiscard]] const InvitedMap* getInvitedUsers() const override {
		return &invites;
	}

private:
	InvitedMap invites;
	uint32_t owner = 0;
};

using ChannelList = std::list<std::shared_ptr<ChatChannel>>;

class Chat {
public:
	Chat();

	// non-copyable
	Chat(const Chat &) = delete;
	Chat &operator=(const Chat &) = delete;

	static Chat &getInstance() {
		return inject<Chat>();
	}

	bool load();

	std::shared_ptr<ChatChannel> createChannel(const std::shared_ptr<Player> &player, uint16_t channelId);
	bool deleteChannel(const std::shared_ptr<Player> &player, uint16_t channelId);

	std::shared_ptr<ChatChannel> addUserToChannel(const std::shared_ptr<Player> &player, uint16_t channelId);
	bool removeUserFromChannel(const std::shared_ptr<Player> &player, uint16_t channelId);
	void removeUserFromAllChannels(const std::shared_ptr<Player> &player);

	bool talkToChannel(const std::shared_ptr<Player> &player, SpeakClasses type, const std::string &text, uint16_t channelId);

	ChannelList getChannelList(const std::shared_ptr<Player> &player);

	std::shared_ptr<ChatChannel> getChannel(const std::shared_ptr<Player> &player, uint16_t channelId);
	std::shared_ptr<ChatChannel> getChannelById(uint16_t channelId);
	std::shared_ptr<ChatChannel> getGuildChannelById(uint32_t guildId);
	std::shared_ptr<PrivateChatChannel> getPrivateChannel(const std::shared_ptr<Player> &player);

	LuaScriptInterface* getScriptInterface() {
		return &scriptInterface;
	}

private:
	std::map<uint16_t, std::shared_ptr<ChatChannel>> normalChannels;
	std::map<uint16_t, std::shared_ptr<PrivateChatChannel>> privateChannels;
	std::map<std::shared_ptr<Party>, std::shared_ptr<ChatChannel>> partyChannels;
	std::map<uint32_t, std::shared_ptr<ChatChannel>> guildChannels;

	LuaScriptInterface scriptInterface;

	std::shared_ptr<PrivateChatChannel> dummyPrivate;
};

constexpr auto g_chat = Chat::getInstance;
