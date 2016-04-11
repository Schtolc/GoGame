//
// Created by pavelgolubev345 on 02.04.16.
//

#ifndef MYGAME_GOGAMESERVER_H
#define MYGAME_GOGAMESERVER_H

#include <boost/asio.hpp>
#include <iostream>
#include <array>

#define BUFFER_SIZE 6
#define WAITING 0
#define SEVERREADY 1
#define SERVERFULL 2
#define GAMEOVER 3

#define IS_WAITING 10
#define IS_LOCKED 11
#define REGISTER 12
#define MAKESTEP 13
#define GETSTEP 14
#define PASSSTEP 15

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
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint ep;

    std::array<int, BUFFER_SIZE> make_request(std::array<int, BUFFER_SIZE> &msg);

    GoGameServer() = default;

public:
    GoGameServer(boost::asio::ip::tcp::endpoint);

    int ServerGetPlayerTeam(int token);

    void ServerMakeStep(int X, int Y, int team, int token);

    Step ServerGetLastStep(int token);

    bool ServerIsPlayerLocked(int token);

    void ServerPassStep(int token);

    bool ServerIsReady();

};

#endif //MYGAME_GOGAMESERVER_H
