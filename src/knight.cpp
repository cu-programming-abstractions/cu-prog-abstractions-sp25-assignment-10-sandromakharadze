#include "knight.h"
#include <algorithm>
#include <cmath>

using namespace std;

/* -------- minKnightMoves -------- */
int minKnightMoves(const Pos& start, const Pos& target) {
    if (start == target) return 0;

    const vector<pair<int, int>> directions = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    queue<pair<Pos, int>> q;
    q.push({start, 0});

    unordered_set<Pos, PosHash> visited;
    visited.insert(start);

    while (!q.empty()) {
        auto [current, steps] = q.front();
        q.pop();

        for (const auto& [dr, dc] : directions) {
            Pos next = {current.row + dr, current.col + dc};

            if (next == target) {
                return steps + 1;
            }

            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push({next, steps + 1});
            }
        }
    }

    return -1;
}

/* -------- getKnightPath -------- */
vector<Pos> getKnightPath(const Pos& start, const Pos& target) {
    if (start == target) return {start};

    const vector<pair<int, int>> directions = {
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    queue<Pos> q;
    q.push(start);

    unordered_set<Pos, PosHash> visited;
    unordered_map<Pos, Pos, PosHash> parent;

    visited.insert(start);

    while (!q.empty()) {
        Pos current = q.front();
        q.pop();

        for (const auto& [dr, dc] : directions) {
            Pos next = {current.row + dr, current.col + dc};

            if (visited.find(next) == visited.end()) {
                parent[next] = current;
                visited.insert(next);
                q.push(next);

                if (next == target) {
                    vector<Pos> path;
                    Pos step = target;
                    while (step != start) {
                        path.push_back(step);
                        step = parent[step];
                    }
                    path.push_back(start);
                    reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }

    return {};
}

/* -------- isValidPosition -------- */
bool isValidPosition(const Pos& pos, int boardSize) {
    if (boardSize == -1) {
        return true;
    }

    return pos.row >= 0 && pos.row < boardSize && 
           pos.col >= 0 && pos.col < boardSize;
}
