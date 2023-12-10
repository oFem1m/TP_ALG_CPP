#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>

using namespace std;

const int SIZE = 4;

struct State {
    int board[SIZE][SIZE];
    int zeroRow, zeroCol;
    string path;

    bool operator==(const State& other) const {
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (board[i][j] != other.board[i][j])
                    return false;
        return true;
    }

    bool operator<(const State& other) const {
        for (int i = 0; i < SIZE; ++i)
            for (int j = 0; j < SIZE; ++j)
                if (board[i][j] != other.board[i][j])
                    return board[i][j] < other.board[i][j];
        return false;
    }
};

bool isGoalState(const State& state) {
    int value = 1;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (state.board[i][j] != value && (i != SIZE - 1 || j != SIZE - 1))
                return false;
            else
                ++value;
    return true;
}

vector<State> getSuccessors(const State& state) {
    vector<State> successors;

    // Possible moves: Up, Down, Left, Right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    char moves[] = {'U', 'D', 'L', 'R'};

    for (int k = 0; k < 4; ++k) {
        int newRow = state.zeroRow + dr[k];
        int newCol = state.zeroCol + dc[k];

        if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE) {
            State successor = state;
            swap(successor.board[state.zeroRow][state.zeroCol], successor.board[newRow][newCol]);
            successor.zeroRow = newRow;
            successor.zeroCol = newCol;
            successor.path += moves[k];
            successors.push_back(successor);
        }
    }

    return successors;
}

pair<int, string> solvePuzzle(const State& initialState) {
    queue<State> q;
    map<State, int> visited;

    q.push(initialState);
    visited[initialState] = 0;

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        if (isGoalState(current)) {
            return {visited[current], current.path};
        }

        vector<State> successors = getSuccessors(current);
        for (const auto& successor : successors) {
            if (visited.find(successor) == visited.end()) {
                q.push(successor);
                visited[successor] = visited[current] + 1;
            }
        }
    }

    return {-1, ""}; // Goal state is not reachable
}

int main() {
    State initialState;

    // Reading initial state
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            cin >> initialState.board[i][j];
            if (initialState.board[i][j] == 0) {
                initialState.zeroRow = i;
                initialState.zeroCol = j;
            }
        }

    pair<int, string> result = solvePuzzle(initialState);

    if (result.first == -1) {
        cout << -1 << endl;
    } else {
        cout << result.first << endl;
        cout << result.second << endl;
    }

    return 0;
}
