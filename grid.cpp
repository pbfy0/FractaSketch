#include "Grid.h"
#include <queue>
#include "config.h"

Grid::Grid(sf::RenderWindow& window, sf::Vector2f topLeft, sf::Vector2f botRight, grid_type type = gt_none):
    m_window(window),
    m_position(topLeft),
    m_size(botRight-topLeft),
    m_type(type)
{
    FillGrids();
}

Grid::~Grid()
{
    //dtor
}

void Grid::Draw() {
    std::vector<sf::CircleShape>::iterator it;
    for(it = m_grids[m_type].begin(); it != m_grids[m_type].end(); it++)
        m_window.draw(*it);
}
#include <iostream>
#include <algorithm>
void Grid::FillGrids() {
    m_grids[gt_none] = std::vector<sf::CircleShape>(0);

    sf::CircleShape point(GRID_DOT_RAD);
    point.setFillColor(sf::Color::Black);
    point.setOrigin(GRID_DOT_RAD, GRID_DOT_RAD); // Position relative to center instead of top-left corner
    // Initialize the square grid
    double rows = m_size.y / config::grid_square_scale,
           cols = m_size.x / config::grid_square_scale;
    for(int iii = 0; iii < rows; iii++) {
        for(int jjj = 0; jjj < cols; jjj++) {
            point.setPosition(m_position + sf::Vector2f(jjj*config::grid_square_scale, iii*config::grid_square_scale));
            m_grids[gt_square].push_back(point);
        }
    }

    // Initialize the hex grid
    double dy = sqrt(3)/2*config::grid_hex_scale;
    rows = m_size.y / dy;
    cols = m_size.x / 3 / config::grid_hex_scale;
    for(int iii = 0; iii < rows; iii++) {
        for(double jjj = 0; jjj < cols; jjj++) {
            if(iii % 2 == 0) {
                point.setPosition(m_position + sf::Vector2f((3*jjj + 0)* config::grid_hex_scale, iii * dy));
                m_grids[gt_hex].push_back(point);
                point.setPosition(m_position + sf::Vector2f((3*jjj + 1)* config::grid_hex_scale, iii * dy));
                m_grids[gt_hex].push_back(point);
                point.setPosition(m_position + sf::Vector2f((3*jjj + 2)* config::grid_hex_scale, iii * dy));
                m_grids[gt_hex].push_back(point);
            } else {
                point.setPosition(m_position + sf::Vector2f((3*jjj + .5)* config::grid_hex_scale, iii * dy));
                m_grids[gt_hex].push_back(point);
                point.setPosition(m_position + sf::Vector2f((3*jjj + 1.5)* config::grid_hex_scale, iii * dy));
                m_grids[gt_hex].push_back(point);
                point.setPosition(m_position + sf::Vector2f((3*jjj + 2.5)* config::grid_hex_scale, iii * dy));
                m_grids[gt_hex].push_back(point);
            }
        }
    }
}

void Grid::SetType(grid_type newType) {
    m_type = newType;
}

// Returns the point on the grid nearest to the input point.
// If there is no grid, returns the input
// TODO: The implementation for hex grids is ridiculously inefficient.
// I haven't noticed a performance hit yet, but it should be dealt with
sf::Vector2f Grid::SnapToNearest(sf::Vector2f point) {
    if(m_type == gt_none)
        return point;
    else if(m_type == gt_square) { // Round each coordinate to nearest multiple of SQUARE_SCALE
        if(point.x < m_position.x) point.x = m_position.x;
        if(point.x > (m_position+m_size).x) point.x = (m_position+m_size).x;
        if(point.y < m_position.y) point.y = m_position.y;
        if(point.y > (m_position+m_size).y) point.y = (m_position+m_size).y;
        point.x = ((int)((point.x - m_position.x)/config::grid_square_scale + .5))*config::grid_square_scale + m_position.x;
        point.y = ((int)((point.y - m_position.y)/config::grid_square_scale + .5))*config::grid_square_scale + m_position.y;
        return point;
    } else { // Hex grid
        // We literally just iterate through every point and find the minimum distance to any of them
        unsigned int minDist = -1;
        sf::Vector2f minDistPoint = point;
        std::vector<sf::CircleShape>::iterator it;
        for(it = m_grids[gt_hex].begin(); it != m_grids[gt_hex].end(); it++) {
            sf::Vector2f dist = it->getPosition()  - point;
            size_t length = sqrt(dist.x*dist.x + dist.y*dist.y);
            if(length < minDist) {
                minDist = length;
                minDistPoint = it->getPosition();
            }
        }
        return minDistPoint;
    }
}
