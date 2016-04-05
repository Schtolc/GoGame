//
// Created by pavelgolubev345 on 02.04.16.
//

#include "GoGameServer.h"
#include <iostream>

string GoGameServer::HTTPGet(string query) {
    string readBuffer;
    curl = curl_easy_init();
    const char *url = (string("http://127.0.0.1:9000/?") + query).c_str();
    if (curl) {
//        char* url = curl_easy_escape(curl,(string("http://127.0.0.1:9000/?") + query).c_str(),0);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GoGameServer::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        return readBuffer;
    } else {
        std::cout << "curl error" << std::endl;
    }
}

size_t GoGameServer::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

int GoGameServer::ServerGetPlayerTeam(int token) {
    return std::stoi(HTTPGet(string("register=") + std::to_string(token)));
}

void GoGameServer::ServerMakeStep(int X, int Y, int team, int token) {
    HTTPGet(string("makestep=x") + std::to_string(X) + string("y") + std::to_string(Y) + string("t") +
            std::to_string(team) + string("p") + std::to_string(token));
}

step GoGameServer::ServerGetLastStep(int token) {
    string lastStep = HTTPGet(string("getstep=") + std::to_string(token));
    if (lastStep == "None") {
        return step(-1, -1, -1);
    } else {
        step result;
        lastStep.erase(0, 1);
        result.x = std::stoi(lastStep);
        lastStep.erase(0, lastStep.find("y") + 1);
        result.y = std::stoi(lastStep);
        lastStep.erase(0, lastStep.find("t") + 1);
        result.team = std::stoi(lastStep);
        return result;
    }
}

void GoGameServer::ServerPassStep(int token) {
    HTTPGet(string("passstep=") + std::to_string(token));
}

bool GoGameServer::ServerIsPlayerLocked(int token) {
    string answer = HTTPGet(string("isLocked=" + std::to_string(token)));
    return answer == "Locked";
}

bool GoGameServer::ServerIsReady() {
    string answer = HTTPGet(string("waiting=p"));
    return answer == "ready";
}