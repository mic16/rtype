/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** response
*/

#ifndef RESPONSE_H_
#define RESPONSE_H_

namespace res {
    enum Type {
        LogIn,
        CreateRoom,
        JoinRoom,
        listPlayersInRoom,
        StartGame,
        SendInfoServer
    };
};

#endif /* !RESPONSE_H_ */
