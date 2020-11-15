/*
** EPITECH PROJECT, 2020
** B-CPP-501-MPL-5-1-rtype-antoine.maillard
** File description:
** request
*/

#ifndef REQUEST_H_
#define REQUEST_H_

namespace req {
    enum Type {
        LogIn,
        CreateRoom,
        JoinRoom,
        ChangeUserStatus,
        DisconnectRoom,
        StartGame,
        Quit
    };
};

#endif /* !REQUEST_H_ */
