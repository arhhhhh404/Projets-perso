#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>

struct Edge {
    int a, b;
};

class UnionFind {
    std::vector<int> parent, rank;
    public:
        UnionFind (int n): parent(n), rank(n, 0) {
            for (int i = 0; i < n; i++) {parent[i] = i;}
        }
        int find (int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
                return parent[x];
            }
        }
        bool unite (int x, int y) {
            int rx = find(x), ry = find(y);
            if (rx == ry) {
                return false;
            } else if (rank[rx] == rank[ry]) {
                rank[rx]++;
            } else if (rank[rx] < rank[ry]) {
                parent[rx] = ry;
            } else {
                parent[ry] = rx;
            }
            return true;
        }
};

struct Cell {
    bool top = true, right = true, bottom = true, left = true;
};

class Maze {
    int cols, rows;
    std::vector<Cell> cells;
    std::vector<Edge> edges;
    public:
    
        Maze (int w, int h): cols(w), rows(h) {
            constructor();
        }

        void constructor() {
            for (int x = 0; x < rows; x++) {
                for (int y = 0; y < cols; y++) {
                    int i = x*cols + y;
                    if (y < cols - 1) {
                        edges.push_back({i, i + 1});
                    }
                    if (x < rows - 1) {
                        edges.push_back({i, i + cols});
                    }
                }
            }
        }

        void generate() {
            UnionFind uf(rows*cols);
            std::mt19937 rng(time(nullptr));
            std::shuffle(edges.begin(), edges.end(), rng);

            for (const auto& edge : edges) {
                if (uf.unite(edge.a, edge.b)) {
                    int dx = edge.a % cols - edge.b % cols;
                    int dy = edge.a / cols - edge.b / cols;
                    if (dx == 1) {
                        cells[edge.a].right = false;
                        cells[edge.b].left = false;
                    } else if (dx == -1) {
                        cells[edge.a].left = false;
                        cells[edge.b].right = false;
                    } else if (dy == 1) {
                        cells[edge.a].bottom = false;
                        cells[edge.b].top = false;
                    } else if (dy == -1) {
                        cells[edge.a].top = false;
                        cells[edge.b].bottom = false;
                    }
                }
            }
        }

        void Draw(sf::RenderWindow& window, int cellsize) {
            sf::VertexArray lines(sf::Lines);
            for (int x = 0; x < rows; x++) {
                for (int y = 0; y < cols; y++) {
                    float px = x * cellsize;
                    float py = y * cellsize;
                    int i = x * cols + y;
                    if (cells[i].top) {
                        lines.append(sf::Vertex(sf::Vector2f(px, py), sf::Color::White));
                        lines.append(sf::Vertex(sf::Vector2f(px + cellsize, py), sf::Color::White));
                    } else if (cells[i].right) {
                        lines.append(sf::Vertex(sf::Vector2f(px + cellsize, py), sf::Color::White));
                        lines.append(sf::Vertex(sf::Vector2f(px + cellsize, py + cellsize), sf::Color::White));
                    } else if (cells[i].bottom) {
                        lines.append(sf::Vertex(sf::Vector2f(px + cellsize, py + cellsize), sf::Color::White));
                        lines.append(sf::Vertex(sf::Vector2f(px, py + cellsize), sf::Color::White));
                    } else if (cells[i].left) {
                        lines.append(sf::Vertex(sf::Vector2f(px, py + cellsize), sf::Color::White));
                        lines.append(sf::Vertex(sf::Vector2f(px, py), sf::Color::White));
                    }
                }
            }
            window.draw(lines);
        }
};

int main() {
    const int cols = 50;
    const int rows = 50;
    const int cellsize = 10;

    Maze maze(cols, rows);
    maze.generate();

    sf::RenderWindow window(sf::VideoMode(cols * cellsize, rows * cellsize), "kuskal maze");

    while (window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        maze.Draw(window, cellsize);
        window.display();
    }
    return 0;
}