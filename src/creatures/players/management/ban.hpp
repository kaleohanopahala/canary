/**
 * Canary - A free and open-source MMORPG server emulator
 * Copyright (©) 2019-2024 OpenTibiaBR <opentibiabr@outlook.com>
 * Repository: https://github.com/opentibiabr/canary
 * License: https://github.com/opentibiabr/canary/blob/main/LICENSE
 * Contributors: https://github.com/opentibiabr/canary/graphs/contributors
 * Website: https://docs.opentibiabr.com/
 */

#pragma once

#include "server/network/connection/connection.hpp"

struct BanInfo {
	std::string bannedBy {};
	std::string reason {};
	time_t expiresAt {};
};

struct ConnectBlock {
	constexpr ConnectBlock(uint64_t lastAttempt, uint64_t blockTime, uint32_t count) :
		lastAttempt(lastAttempt), blockTime(blockTime), count(count) { }

	uint64_t lastAttempt {};
	uint64_t blockTime {};
	uint32_t count {};
};

using IpConnectMap = std::map<Connection::Address, ConnectBlock>;

class Ban {
public:
	bool acceptConnection(const Connection::Address &clientIP);

private:
	IpConnectMap ipConnectMap;
	std::recursive_mutex lock;
};

class IOBan {
public:
	static bool isAccountBanned(uint32_t accountId, BanInfo &banInfo);
	static bool isIpBanned(const Connection::Address &clientIP, BanInfo &banInfo);
	static bool isPlayerNamelocked(uint32_t playerId);
};
