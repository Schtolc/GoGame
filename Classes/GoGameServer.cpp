//
// Created by pavelgolubev345 on 02.04.16.
//

#include "GoGameServer.h"
#include <iostream>

GoGameServer::GoGameServer(boost::asio::ip::tcp::endpoint endpoint)
        : io_service(), ep(endpoint) {

}

//string GoGameServer::HTTPGet(string query) {
//    string readBuffer;
//    curl = curl_easy_init();
//    const char *url = (string("http://127.0.0.1:9000/?") + query).c_str();
//    if (curl) {
////        char* url = curl_easy_escape(curl,(string("http://127.0.0.1:9000/?") + query).c_str(),0);
//        curl_easy_setopt(curl, CURLOPT_URL, url);
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, GoGameServer::WriteCallback);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
//        res = curl_easy_perform(curl);
//        curl_easy_cleanup(curl);
//
//        return readBuffer;
//    } else {
//        std::cout << "curl error" << std::endl;
//    }
//}

//size_t GoGameServer::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
//    ((std::string *) userp)->append((char *) contents, size * nmemb);
//    return size * nmemb;
//}

int GoGameServer::ServerGetPlayerTeam(int token) {
    std::array<int, BUFFER_SIZE> request = std::array<int, BUFFER_SIZE>();
    request[0] = REGISTER;
    request[1] = token;
    return make_request(request)[0];
}

void GoGameServer::ServerMakeStep(int X, int Y, int team, int token) {
    std::array<int, BUFFER_SIZE> request = std::array<int, BUFFER_SIZE>();
    request[0] = MAKESTEP;
    request[1] = token;
    request[2] = X;
    request[3] = Y;
    request[4] = team;
    make_request(request);
}

Step GoGameServer::ServerGetLastStep(int token) {
    std::array<int, BUFFER_SIZE> request = std::array<int, BUFFER_SIZE>();
    request[0] = GETSTEP;
    request[1] = token;
    std::array<int, BUFFER_SIZE> response = make_request(request);
    if (response[0] == -1) {
        return Step(-1, -1, -1);
    } else {
        return Step(response[0], response[1], response[2]);
    }
}

void GoGameServer::ServerPassStep(int token) {
    std::array<int, BUFFER_SIZE> request = std::array<int, BUFFER_SIZE>();
    request[0] = PASSSTEP;
    request[1] = token;
    make_request(request);
}

bool GoGameServer::ServerIsPlayerLocked(int token) {
    std::array<int, BUFFER_SIZE> request = std::array<int, BUFFER_SIZE>();
    request[0] = IS_LOCKED;
    request[1] = token;
    return make_request(request)[0] == 1;
}

bool GoGameServer::ServerIsReady() {
    std::array<int, BUFFER_SIZE> request = std::array<int, BUFFER_SIZE>();
    request[0] = IS_WAITING;
    return make_request(request)[0] == 0;
}


std::array<int, BUFFER_SIZE> GoGameServer::make_request(std::array<int, BUFFER_SIZE> &msg) {
    boost::asio::ip::tcp::socket sock(io_service);
    sock.connect(ep);
    sock.write_some(boost::asio::buffer(msg));
    std::array<int, 6> buf;
    sock.read_some(boost::asio::buffer(buf));
    return buf;
}
