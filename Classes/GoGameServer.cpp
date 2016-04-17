//
// Created by pavelgolubev345 on 02.04.16.
//

#include "GoGameServer.h"
#include <iostream>

GoGameServer::GoGameServer(boost::asio::ip::tcp::endpoint endpoint)
        : io_service(), ep(endpoint) {
}


int GoGameServer::ServerGetPlayerTeam(int token) {
    assert(0 <= token && token <= 1000);
    std::array<int, IO_BUFFER> request = std::array<int, IO_BUFFER>();
    request[0] = FlagRegistration;
    request[1] = token;
    return make_request(request)[0];
}

bool GoGameServer::ServerMakeStep(int X, int Y, int team, int token) {
    assert(0 <= token && token <= 1000 && 0 <= X && X <= 18 && 0 <= Y && Y <= 18 && 0 <= team && team <= PLAYER_AMOUNT);
    std::array<int, IO_BUFFER> request = std::array<int, IO_BUFFER>();
    request[0] = FlagMakeStep;
    request[1] = token;
    request[2] = X;
    request[3] = Y;
    request[4] = team;
    return make_request(request)[0] == 1;
}

Step GoGameServer::ServerGetLastStep(int token) {
    assert(0 <= token && token <= 1000);
    std::array<int, IO_BUFFER> request = std::array<int, IO_BUFFER>();
    request[0] = FlagGetStep;
    request[1] = token;
    std::array<int, IO_BUFFER> response = make_request(request);
    if (response[0] == -1) {
        return Step(-1, -1, -1);
    } else {
        return Step(response[0], response[1], response[2]);
    }
}

bool GoGameServer::ServerPassStep(int token) {
    assert(0 <= token && token <= 1000);
    std::array<int, IO_BUFFER> request = std::array<int, IO_BUFFER>();
    request[0] = FlagPassStep;
    request[1] = token;
    return make_request(request)[0] == 1;
}

bool GoGameServer::ServerIsPlayerLocked(int token) {
    assert(0 <= token && token <= 1000);
    std::array<int, IO_BUFFER> request = std::array<int, IO_BUFFER>();
    request[0] = FlagPlayerLocked;
    request[1] = token;
    return make_request(request)[0] == 1;
}

int GoGameServer::ServerState() {
    std::array<int, IO_BUFFER> request = std::array<int, IO_BUFFER>();
    request[0] = FlagServerState;
    return make_request(request)[0];
}


bool GoGameServer::ServerPassGameOver() {
    std::array<int, IO_BUFFER> request = std::array<int, IO_BUFFER>();
    request[0] = FLagGameOver;
    return make_request(request)[0] == 1;
}


std::array<int, IO_BUFFER> GoGameServer::make_request(std::array<int, IO_BUFFER> &msg) {
    boost::asio::ip::tcp::socket sock(io_service);
    sock.connect(ep);
    sock.write_some(boost::asio::buffer(msg));
    std::array<int, 6> buf;
    sock.read_some(boost::asio::buffer(buf));
    return buf;
}
