#include "../include/Server.hpp"

void	Server::_motd(int socket, std::vector<std::string>& arg) {
	if (arg.size() > 0)
		this->_mapSocketAndClients[socket].sendMessage(ERR_NOSUCHSERVER(arg[1]));
	else if (!this->_messageOfTheDay.empty())
		this->_mapSocketAndClients[socket].sendMessage(RPL_MOTD(this->_messageOfTheDay));
	else
		this->_mapSocketAndClients[socket].sendMessage(ERR_NOMOTD("There is no message of the day."));
}

