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

#include "pch.hpp"

#include "lua/functions/core/network/webhook_functions.hpp"
#include "server/network/webhook/webhook.hpp"

int WebhookFunctions::luaWebhookSendMessage(lua_State* L) {
	// Webhook.sendMessage(title, message, color, url = "WEBHOOK_DISCORD_URL") |
	// Webhook.sendMessage(message, url = "WEBHOOK_DISCORD_URL")
	std::string title = getString(L, 1);
	std::string message = getString(L, 2);
	uint32_t color = getNumber<uint32_t>(L, 3, 0);
	std::string url = getString(L, -1);
	if (url == title) {
		g_webhook().sendMessage(title);
	} else if (url == message) {
		g_webhook().sendMessage(title, url);
	} else {
		g_webhook().sendMessage(title, message, color, url);
	}
	lua_pushnil(L);

	return 1;
}
