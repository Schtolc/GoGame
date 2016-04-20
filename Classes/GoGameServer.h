//
// Created by pavelgolubev345 on 02.04.16.
//

#ifndef MYGAME_GOGAMESERVER_H
#define MYGAME_GOGAMESERVER_H

#include "Defenitions.h"
#include <boost/asio.hpp>
#include <iostream>
#include <array>


struct Step {
    int x;
    int y;
    int team;

    Step() : x(0), y(0), team(0) { }

    Step(int X, int Y, int T) : x(X), y(Y), team(T) { }

    bool operator==(const Step &other) const {
        return (x == other.x && y == other.y && team == other.team);
    }
};

class GoGameServer {
private:
    static const int FlagServerState = 10;
    static const int FlagPlayerLocked = 11;
    static const int FlagRegistration = 12;
    static const int FlagMakeStep = 13;
    static const int FlagGetStep = 14;
    static const int FlagPassStep = 15;
    static const int FLagGameOver = 16;


    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint ep;
    int lobby_id;

    std::array<int, IO_BUFFER> make_request(std::array<int, IO_BUFFER> &msg);

    GoGameServer() = default;


public:
    GoGameServer(boost::asio::ip::tcp::endpoint);

    void setLobbyId(int id);

    std::pair<int,int> ServerGetPlayerTeam(int token);

    bool ServerMakeStep(int X, int Y, int team, int token);

    Step ServerGetLastStep(int token);

    bool ServerIsPlayerLocked(int token);

    bool ServerPassStep(int token);

    bool ServerPassGameOver();

    int ServerState();

};

#endif //MYGAME_GOGAMESERVER_H
