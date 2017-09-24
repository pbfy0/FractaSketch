#ifndef FRACTAL_ELEMENT_H
#define FRACTAL_ELEMENT_H

#include "frac_list.h"
#include "line.h"
#include "Fractal_Template.h"

class Fractal_Element {
private:
    Line m_baseline;
    frac_list<Line> m_lines;
    // This pointer is shared between all Fractal_Elements for a given Fractal_Iterator
    frac_list<Line>* statics;

    sf::VertexArray cached_vertices;
    // The place in statics to stop drawing lines. Lines past this point
    // were added by a later, more complicated FE.
    size_t m_statics_end;

    double m_maxLength; // Maximum length of any non-static line in the element
public:
    Fractal_Element(frac_list<Line>* statics);
    ~Fractal_Element();

    void AddLine(Line newLine);
    const frac_list<Line>& GetStatics() const;
    const frac_list<Line>& GetLines() const;

    double GetMaxLength();

    Fractal_Element ReplaceAll(const Fractal_Template& target) const;

    void Draw(sf::RenderTarget& target, Line::draw_type style);
    void SetBase(sf::Vector2f start, sf::Vector2f finish);

    double BaseLength();

};
#endif // FRACTAL_ELEMENT_H
