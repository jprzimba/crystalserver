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

#include "account/account.hpp"
#include "lua/global/baseevents.hpp"
#include "utils/utils_definitions.hpp"
#include "declarations.hpp"
#include "lua/scripts/luascript.hpp"
#include "lua/scripts/scripts.hpp"

class TalkAction;
using TalkAction_ptr = std::shared_ptr<TalkAction>;

class TalkAction : public Script {
public:
	using Script::Script;

	const std::string &getWords() const {
		return m_word;
	}

	void setWords(const std::vector<std::string> &newWords) {
		for (const auto &word : newWords) {
			if (!m_word.empty()) {
				m_word.append(", ");
			}
			m_word.append(word);
		}
	}

	std::string getSeparator() const {
		return separator;
	}
	void setSeparator(std::string sep) {
		separator = sep;
	}

	// scripting
	bool executeSay(std::shared_ptr<Player> player, const std::string &words, const std::string &param, SpeakClasses type) const;
	//

	void setGroupType(uint8_t newGroupType);
	const uint8_t &getGroupType() const;

private:
	std::string getScriptTypeName() const override {
		return "onSay";
	}

	std::string m_word;
	std::string separator = "\"";
	uint8_t m_groupType = 0;
};

class TalkActions final : public Scripts {
public:
	TalkActions();
	~TalkActions();

	// non-copyable
	TalkActions(const TalkActions &) = delete;
	TalkActions &operator=(const TalkActions &) = delete;

	static TalkActions &getInstance() {
		return inject<TalkActions>();
	}

	bool checkWord(std::shared_ptr<Player> player, SpeakClasses type, const std::string &words, const std::string_view &word, const TalkAction_ptr &talkActionPtr) const;
	TalkActionResult_t checkPlayerCanSayTalkAction(std::shared_ptr<Player> player, SpeakClasses type, const std::string &words) const;

	bool registerLuaEvent(const TalkAction_ptr &talkAction);
	void clear();

	const std::map<std::string, std::shared_ptr<TalkAction>> &getTalkActionsMap() const {
		return talkActions;
	};

private:
	std::map<std::string, std::shared_ptr<TalkAction>> talkActions;
};

constexpr auto g_talkActions = TalkActions::getInstance;
