#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <tuple>

const int INF = std::numeric_limits<int>::max();
std::vector<sf::Vector2i> path;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

void djikstra(std::pair<int, int> start, bool obstacle[50][50], std::vector<std::vector<int>>& distance) {
    const int rows = 50;
    const int cols = 50;    

    distance.assign(rows, std::vector<int>(cols, INF));

    using T = std::tuple<int, int, int>;
    std::priority_queue<T, std::vector<T>, std::greater<T>> pq;
 
    distance[start.second][start.first] = 0;
    pq.emplace(0, start.second, start.first);

    while (!pq.empty()) {
        auto [dist, x, y] = pq.top(); pq.pop();

        if (dist > distance[x][y]) {continue;};

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !obstacle[nx][ny]) {
                if (distance[x][y] + 1 < distance[nx][ny]) {
                    distance[nx][ny] = distance[x][y] + 1;
                    pq.emplace(distance[nx][ny], nx, ny);
                }
            }
        }
    }
}

int main() {
    const int cellsize = 10;
    const int rows = 50;
    const int cols = 50;

    sf::Vector2i start(-1, -1);
    sf::Vector2i end(-1, -1);
    bool obstacle[rows][cols] = {false};

    enum State {PlacingStart, PlacingObstacle, PlacingEnd, Done};
    State state = PlacingStart;

    sf::RenderWindow window(sf::VideoMode(cols * cellsize, rows * cellsize), "Djikstra grid");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                int col = x / cellsize;
                int row = y / cellsize;

                if (col >= 0 && col < cols && row >= 0 && row < rows) {
                    if (state == PlacingStart) {
                        std::cout << "Current state: " << state << "\n";
                        start = sf::Vector2i(col, row);
                        std::cout << "Start set to: (" << col << ", " << row << ")\n";
                        state = PlacingObstacle;
                    } else if(state == PlacingObstacle) {
                        std::cout << "Current state: " << state << "\n";
                        if(col == start.x && row == start.y) {
                            continue;}
                        obstacle[row][col] = true;
                        std::cout << "Obstacle added at: (" << col << ", " << row << ")" << std::endl;
                    } else if (state == PlacingEnd) {
                        std::cout << "Current state: " << state << std::endl;
                        if((col == start.x && row == start.y) || obstacle[row][col]) {
                            continue;}
                        end = sf::Vector2i(col, row);
                        std::cout << "End set to: (" << col << ", " << row << ")" << std::endl;
                        state = Done;
                    } else if (state == Done) {
                        std::vector<std::vector<int>> distance;
                        djikstra({start.x, start.y}, obstacle, distance);
                        if (distance[end.x][end.y] == INF) {
                            std::cout << "No path found" << std::endl;
                        } else {
                            std::cout << "Distance from the start to the end" << distance[end.x][end.y] << std::endl;
                        }
                        sf::Vector2i current = end;
                        while (current != start) {
                            int x = current.x;
                            int y = current.y;
                            int d = distance[x][y];
                            bool found = false;
                            for (int dir = 0; dir < 4; dir++) {
                                int nx = x + dx[dir];
                                int ny = y + dy[dir];
                                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && distance[nx][ny] == d - 1) {
                                    current = sf::Vector2i(nx, ny);
                                    path.push_back(current);
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) {
                                std::cout << "path blocked" << std::endl;
                                path.clear();
                                break;
                            } 
                        }
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Enter || sf::Keyboard::Space)) {
                if (state == PlacingObstacle) {
                    state = PlacingEnd;
                } else {
                    continue;
                }
            }
        }

        window.clear(sf::Color::Black);

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                sf::RectangleShape cell(sf::Vector2f(cellsize, cellsize));
                cell.setPosition(col * cellsize, row * cellsize);

                bool isPath = false;
                for (auto& p : path) {
                    if (p.x == col && p.y == row) {
                        isPath = true;
                        break;
                    }
                }

                if (start.x == col && start.y == row) {
                    cell.setFillColor(sf::Color::Green);
                } else if (end.x == col && end.y == row) {
                    cell.setFillColor(sf::Color::Red);
                } else if (obstacle[col][row]) {
                    cell.setFillColor(sf::Color(255, 165, 0));
                } else if (isPath == true) {
                    cell.setFillColor(sf::Color::Black);
                } else {
                    cell.setFillColor(sf::Color::White);
                }
                window.draw(cell);
            }
        }
        window.display();
    }
    return 0;
}