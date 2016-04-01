//
// Created by pavelgolubev345 on 01.04.16.
//

#include "OnlineMultiPlayer.h"
#include "curl/curl.h"

OnlineMultiPlayer::OnlineMultiPlayer(Board *board) : Game(board) {
    player.setTeam(0);
    board->getLayel()->schedule(schedule_selector(OnlineMultiPlayer::sync),1);
    /*CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:9000/");
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        /*curl_easy_cleanup(curl);
    }

    curl_global_cleanup();*/
}

bool OnlineMultiPlayer::getXY(int X, int Y) {
    assert(0 <= X && X <= 18 && 0 <= Y && Y <= 18);
    if (checkStep(X, Y, player.team())) {
        board->placeChip(X, Y, player.team());
        Locked = true;
        matrix[X][Y] = player.team();
        update();
        return true;
    } else {
        std::cout << "Warning cant place a chip (" << X << "," << Y << ")" << std::endl;
        return false;
    }
}

void OnlineMultiPlayer::update() {

}

void OnlineMultiPlayer::sync(float dt) {
    std::cout << dt << std::endl;
}
