#include "../include/Server.hpp"

bool	Server::_nickAlreadyTaken(std::string& newNick, Client cl) {
	for (size_t i = 0; i < this->_mapSocketAndClients.size(); ++i) {
		if (newNick == this->_mapSocketAndClients[i].getNickname()) {
			cl.sendMessage(ERR_NICKNAMEINUSE(newNick));			
			return true;
		}
	}
	return false;
}

bool Server::_isSpecialCharForNickname(std::string& nickname) const {
    const std::string specialChar("-_[]{}|`");

    for (size_t i = 0; i < nickname.size(); ++i) {
        bool isSpecial = false;
        for (size_t j = 0; j < specialChar.size(); ++j) {
            if (nickname[i] == specialChar[j]) {
                isSpecial = true;
                break;
            }
        }
        if (!isalnum(nickname[i]) && !isSpecial)
            return false;
    }
    return true;
}

bool	Server::_isValidNickname(std::string& nickname, Client cl) {
	if (nickname.length() > NICK_LIMIT_CHAR)
		nickname = nickname.substr(0, NICK_LIMIT_CHAR);
	if (nickname.empty() || nickname == "anonymous"
		|| !isalpha(nickname[0]) || !this->_isSpecialCharForNickname(nickname)) {
		cl.sendMessage(ERR_ERRONEUSNICKNAME(nickname));
		return false;
	}
	return true;
}

bool	Server::_checkNickname(std::string& nickname, Client cl) {
	return !this->_nickAlreadyTaken(nickname, cl) && this->_isValidNickname(nickname, cl);
}

void	Server::_changeNickFromAllActiveChannel(Client cl, const std::string newNick) {
	std::vector<std::string>	channelName;

	channelName = cl.getAllChanWithRight();
	if (channelName.size()) {
		for (size_t i = 0; i < channelName.size(); ++i) {
			if (this->_channels[channelName[i]].isInOpVector(cl.getNickname())) {
				this->_channels[channelName[i]].delOperator(cl.getNickname());
				this->_channels[channelName[i]].addOperator(newNick);
			}
			if (this->_channels[channelName[i]].checkIsInvited(cl.getNickname())) {
				this->_channels[channelName[i]].delNicknameInInviteList(cl.getNickname());
				this->_channels[channelName[i]].addNicknameInInviteList(newNick);
			}
		}
	}
}

void	Server::_nick(int socket, std::vector<std::string>& arg) {
	if (!arg.size())
		return this->_mapSocketAndClients[socket].sendMessage(ERR_NONICKNAMEGIVEN());
	if (!this->_mapSocketAndClients[socket].getPassword().empty()) {
		if (!this->_checkNickname(arg[0], this->_mapSocketAndClients[socket]))
			return;
		if (!this->_mapSocketAndClients[socket].getIsRegistered()) {
			this->_mapSocketAndClients[socket].setNickname(arg[0]);
		} else {
			if (this->_mapSocketAndClients[socket].getIsRegistered()) {
				std::string	msg = this->_mapSocketAndClients[socket].getPrefix() + " NICK :" + arg[0] + "\r\n";
				this->_mapSocketAndClients[socket].sendMessage(msg);
			}
			this->_changeNickFromAllActiveChannel(this->_mapSocketAndClients[socket], arg[0]);
			this->_mapSocketAndClients[socket].setNickname(arg[0]);
		}
	}
}
