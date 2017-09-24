#include "Fractal_Element.h"
#include "config.h"

Fractal_Element::Fractal_Element(frac_list<Line>* _statics):
     m_baseline(Line::lt_base, sf::Vector2f(0,0), sf::Vector2f(0,0)),
     statics(_statics),
     m_statics_end(_statics->size()),
     m_maxLength(0),
     cached_vertices(sf::PrimitiveType::Lines)
{

}

Fractal_Element::~Fractal_Element() {

}

double Fractal_Element::BaseLength() {
    return m_baseline.Length();
}

double Fractal_Element::GetMaxLength() {
    return m_maxLength;
}

void Fractal_Element::AddLine(Line newLine) {
    switch (newLine.GetType()) {
    case Line::line_type::lt_hidden:
        // Hidden lines are useless for iteration, so don't keep track of them.
        return;
    case Line::line_type::lt_static:
        statics->push_back(newLine);
        m_statics_end++;
        break;
    default:
        if(newLine.Length() < config::infinity_stop_size) {
            newLine.SetType(Line::lt_static);
            AddLine(newLine);
        } else {
            double newLen = newLine.Length();
            m_lines.push_back(newLine);
            if(newLen > m_maxLength)
                m_maxLength = newLen;
        }
        break;
    }
    cached_vertices.clear();
}

const frac_list<Line>& Fractal_Element::GetLines() const {
    return m_lines;
}

Fractal_Element Fractal_Element::ReplaceAll(const Fractal_Template& target) const {
    Fractal_Element newFE(statics);
    for(auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
        Fractal_Template transformed = target.TransformAll(target.MatchBase(*line_it));
        frac_list<Line> transLines = transformed.GetLines();
        for(auto trans_it = transLines.begin(); trans_it != transLines.end(); trans_it++) {
            newFE.AddLine(*trans_it);
        }
    }
    newFE.SetBase(m_baseline.GetStart(), m_baseline.GetFinish());
    return newFE;
}

void Fractal_Element::Draw(sf::RenderTarget& target, Line::draw_type style) {
    if (cached_vertices.getVertexCount() == 0) {
        for (auto line_it = m_lines.begin(); line_it != m_lines.end(); line_it++) {
            line_it->Draw(cached_vertices, style);
        }
        auto line_it = statics->begin();
        for (size_t iii = 0; iii < m_statics_end; iii++) {
            line_it->Draw(cached_vertices, style);
            line_it++;
        }
    }
    target.draw(cached_vertices);
}

void Fractal_Element::SetBase(sf::Vector2f start, sf::Vector2f finish) {
    m_baseline.SetPosition(start, finish);
}
