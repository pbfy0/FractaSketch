#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>

struct Transform {
    double scale;
    double theta;
    sf::Vector2f origin; // For dilations and rotations
    sf::Vector2f translate;
    sf::Vector2f reflect_start;
    sf::Vector2f reflect_finish;

    Transform(double s, double th, sf::Vector2f org, sf::Vector2f tr, sf::Vector2f rs, sf::Vector2f rf) {
        scale = s;
        theta = th;
        origin = org;
        translate = tr;
        reflect_start = rs;
        reflect_finish = rf;
    }
};

class Line
{

// The first four types refer to the location of the arrow
// on horizontal line in the positive x direction
public: enum line_type {
    lt_base = 0,    // The base line on the template
    lt_topRight = 1,
    lt_botRight = 2,
    lt_topLeft = 3,
    lt_botLeft = 4,
    lt_static = 5, // Not replaced during iterations
    lt_hidden = 6 // Neither shown nor replaced during iterations
};

public: enum draw_type {
    dt_default = 0, // Draw lines according to their type
    dt_simple = 1, // Draw all lines as static
    dt_overlay = 2 // Draw all lines as dotted and colored
};

private:
    line_type m_type;
    sf::Vector2f m_start;
    sf::Vector2f m_finish;
    sf::Color m_color;

    sf::VertexArray m_body; // The thing that is actually drawn

    void ConstructBody(); // Fills out body based on m_type
public:
    Line(line_type type, sf::Vector2f start, sf::Vector2f finish);
    ~Line();

    double Length() const;

    void SetType(line_type newType);
    void SetPosition(sf::Vector2f start, sf::Vector2f finish);
    void SetColor(sf::Color color);

    line_type GetType() const;
    sf::Vector2f GetStart() const;
    sf::Vector2f GetFinish() const;
    sf::Vector2f FromOrigin() const;

    Transform Match(const Line& base) const;
    Line ApplyTransform(Transform t) const;

    void Draw(sf::RenderTarget& target, draw_type style) const;
    void Draw(sf::VertexArray& target, draw_type style) const;
};



#endif // LINE_H
