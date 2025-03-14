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

#include "lib/logging/textlogger.hpp"
#include "utils/tools.hpp"
#include "config/configmanager.hpp"

void GameLogger::open() {
	m_files[LOGFILE_ASSERTIONS] = fopen("data/logs/client_assertions.txt", "a");

	m_loaded = true;
}

void GameLogger::close() {
	m_loaded = false;
	for (uint8_t i = 0; i <= LOGFILE_LAST; i++) {
		if (m_files[i]) {
			fclose(m_files[i]);
		}
	}
}

void GameLogger::iFile(LogFile_t file, std::string output, bool newLine) {
	if (!m_loaded || !m_files[file]) {
		return;
	}

	internal(m_files[file], output, newLine);
	fflush(m_files[file]);
}

void GameLogger::eFile(std::string file, std::string output, bool newLine) {
	const auto &coreFolder = g_configManager().getString(CORE_DIRECTORY);
	std::string filePath = coreFolder + "/logs/" + file;
	FILE* f = fopen(filePath.c_str(), "a");
	if (!f) {
		return;
	}

	internal(f, "[" + formatDateEx() + "] " + output, newLine);
	fclose(f);
}

void GameLogger::internal(FILE* file, std::string output, bool newLine) {
	if (!file) {
		return;
	}

	if (newLine) {
		output += "\n";
	}

	fprintf(file, "%s", output.c_str());
}

OutputHandler::OutputHandler() {
	log = std::clog.rdbuf(this);
	err = std::cerr.rdbuf(this);
}

OutputHandler::~OutputHandler() {
	std::clog.rdbuf(log);
	std::cerr.rdbuf(err);
}

std::streambuf::int_type OutputHandler::overflow(std::streambuf::int_type c /* = traits_type::eof()*/) {
	m_cache += c;
	if (c != '\n' && c != '\r') {
		return c;
	}

	if (m_cache.size() > 1) {
		std::cout << "[" << formatTimeEx(0, true) << "] ";
	}

	std::cout.write(m_cache.c_str(), m_cache.size());
	if (GameLogger::getInstance()->isLoaded()) {
		std::stringstream s;
		if (m_cache.size() > 1) {
			s << "[" << formatDateEx() << "] ";
		}

		s.write(m_cache.c_str(), m_cache.size());
		GameLogger::getInstance()->iFile(LOGFILE_OUTPUT, s.str(), false);
	}

	m_cache.clear();
	return c;
}
