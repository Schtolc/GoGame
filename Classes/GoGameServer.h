//
// Created by pavelgolubev345 on 02.04.16.
//

#ifndef MYGAME_GOGAMESERVER_H
#define MYGAME_GOGAMESERVER_H

#include <string>
#include <string.h>
#include <curl/curl.h>

using std::string;

struct step {
    int x;
    int y;
    int team;

    step() : x(0), y(0), team(0) { }

    step(int X, int Y, int T) : x(X), y(Y), team(T) { }

    bool operator==(const step& other) const {
        return (x == other.x && y==other.y && team==other.team);
    }
};

class GoGameServer {
private:
    CURL *curl;
    CURLcode res;

    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    string HTTPGet(string url);

public:
    GoGameServer() = default;

    int ServerGetPlayerTeam(int token);
    void ServerMakeStep(int X, int Y, int team, int token);
    step ServerGetLastStep(int token);
    bool ServerIsPlayerLocked(int token);
    void ServerPassStep(int token);

};
#endif //MYGAME_GOGAMESERVER_H
