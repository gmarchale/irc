#pragma once

#include "./config.hpp"

#define	ERR_NOSUCHNICK(nickname) (std::string(":") + " 401 " + nickname + " No such nick\r\n")
#define ERR_NOSUCHSERVER(server) (std::string(":") + " 403 " + server + " No such server\r\n")
#define ERR_NOSUCHCHANNEL(nickname, channel) (std::string(":") + " 403 " + nickname + " " + channel + " No such channel\r\n")
#define	ERR_UNKNOWNCOMMAND(command, reason) ("421 " + command + " :" + reason + "\r\n")
#define ERR_NOMOTD(reason) (std::string(":") + SERVER_NAME + " 422 " + reason + "\r\n")
#define	ERR_NONICKNAMEGIVEN(nickname) (std::string(":") + SERVER_NAME + " 431 *" + nickname + " :No nickname given\r\n")
#define	ERR_ERRONEUSNICKNAME(nickname) ("432 " + nickname + " :Erroneus nickname\r\n")
#define	ERR_NICKNAMEINUSE(nick) ("433 " + nick + " :Nickname is already in use\r\n")
#define ERR_USERNOTINCHANNEL(nickname, channel, userTarget) (std::string(":") + SERVER_NAME + " 441 " + nickname + " " + channel + " :" + userTarget + " are not on that channel\r\n")
#define ERR_NOTONCHANNEL(nickname, channel) (std::string(":") + SERVER_NAME + " 442 " + nickname + " " + channel + " :You are not on that channel\r\n")
#define ERR_NEEDMOREPARAMS(reason) (std::string(":") + SERVER_NAME + " 461 :" + reason + "\r\n")
#define ERR_ALREADYREGISTERED(reason) (std::string("462 :") + reason + "\r\n")
#define ERR_PASSWDMISMATCH(nickname) (std::string(":") + SERVER_NAME + " 464 " + nickname + SERVER_NAME + " :Password incorrect\r\n")
#define ERR_KEYSET(nickname, channel, reason) (std::string(":") + SERVER_NAME + " 467 " + nickname + " " + channel + " :" + reason + "\r\n")
#define ERR_CHANNELISFULL(nickname, channel) (std::string(":") + SERVER_NAME + " 471 " + nickname + " :Channel " + channel + " is full.\r\n")
#define ERR_UNKNOWNMODE(nickname, channel, char) (std::string(":") + SERVER_NAME + " 472 " + nickname + " " + channel + " :" + "\"" + char + "\"" + " is an unknown mode.\r\n")
#define ERR_CHANOPRIVSNEEDED(nickname, channel) (std::string(":") + SERVER_NAME + " 482 " + nickname + " :You must be an operator to run this command in " + channel + ".\r\n")
#define ERR_UMODEUNKNOWNFLAG(nickname, reason) (std::string(":") + SERVER_NAME + " 501 " + nickname + " :" + reason + "\r\n")