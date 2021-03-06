#ifndef FRACTAL_TEMPLATE_H
#define FRACTAL_TEMPLATE_H

#include <vector>
#include "frac_list.h"
#include "Line.h"


class Fractal_Template {
private:
    Line m_baseline;
    // We need to be able to manipulate both the lines and their endpoints, but
    // endpoints correspond to more than one line. Thus for ease of access we
    // track them separately. The relationship is as follows:
    // m_lines[index] is the line from m_points[index] to m_points[index + 1]
    frac_list<Line> m_lines;
    std::vector<sf::Vector2f> m_points;
    size_t m_activeLine;
    size_t m_activePoint;

    void SetBase(sf::Vector2f start, sf::Vector2f finish);
    void RemoveLine(size_t index);
    void RemovePoint(size_t index);
    void SplitLine(size_t index); // Splits the active line into to lines of half length
    void TranslateAll(sf::Vector2f displacement);

    // Selects a line if there is one close enough to the given position
    void SelectNear(sf::Vector2f clickPos);
public:
    Fractal_Template();
    ~Fractal_Template();

    const frac_list<Line>& GetLines() const;
    const Line& GetBase() const;

    void OnClick(sf::Vector2f clickPos);

    void StartAtPoint(sf::Vector2f startPoint); // Adds the given point to m_points
    void AddLine(sf::Vector2f endpoint, Line::line_type ltype);
    void RemoveSelected();
    void ChangeType(Line::line_type newType); // Change the type of the selected line if there is one
    void Translate(sf::Vector2f displacement);
    void MovePoint(sf::Vector2f newPos);
    void Clear();

    Transform MatchBase(const Line& base) const;
    Fractal_Template TransformAll(Transform t) const;

    void Draw(sf::RenderWindow& window, bool simple) const;
    void DrawBaseline();

    bool SaveToFile(std::string filename);
    bool LoadFromFile(std::string filename);
};
#endif // FRACTAL_TEMPLATE_H

