//
// Created by Egor Chunaev on 14.06.2021.
//

#include "game_map.h"

#include <cmath>
#include <stdexcept>
#include <string>

TGameMap LoadPlanarGraph(int maxDistBetweenPlanets, std::function<int()> readInt) {
    TGameMap gameMap;

    int planetCount = readInt();
    int playerCount = readInt();

    for (int i = 0; i < playerCount; ++i) {
        gameMap.StartPlanets_.push_back(readInt());
    }

    gameMap.Points_ = std::vector<TGameMap::TPoint>();
    gameMap.Points_->resize(planetCount);
    for (int i = 0; i < planetCount; ++i) {
        gameMap.Points_->at(i).x = readInt();
        gameMap.Points_->at(i).y = readInt();
    }

    gameMap.Dists_.resize(planetCount, std::vector<int>(planetCount, 0));

    for (int i = 0; i < planetCount; ++i) {
        for (int j = i + 1; j < planetCount; ++j) {
            long long int dx = gameMap.Points_->at(i).x - gameMap.Points_->at(j).x;
            long long int dy = gameMap.Points_->at(i).y - gameMap.Points_->at(j).y;
            long long int sqDist = dx * dx + dy * dy;
            int dist = std::round(sqrtl(sqDist));
            if (dist <= 0 || dist > maxDistBetweenPlanets) {
                throw std::runtime_error(
                    "distance between "
                    + std::to_string(i + 1)
                    + " and "
                    + std::to_string(j + 1)
                    + " is " + std::to_string(dist)
                    + " but allowed distance range is "
                    + "[" + std::to_string(1) + "; " + std::to_string(maxDistBetweenPlanets) + "]"
                );
            }

            gameMap.Dists_[i][j] = gameMap.Dists_[j][i] = dist;
        }
    }

    return gameMap;
}
