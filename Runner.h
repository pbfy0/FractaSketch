#ifndef RUNNER_H
#define RUNNER_H

#include "grid.h"
#include "Iter_Window.h"
#include "Fractal_Template.h"

class Runner {
private:
    sf::RenderWindow& m_window;
    sf::Font& m_font;
    Iter_Window m_iter_window;

    Fractal_Template m_base;
    Line::line_type m_currentLine;
    size_t m_activeBox;

    std::vector<GUI_Element*> m_elements;
    InputBox m_success; // Reports success/failure of file save/load

    // The grid itself
    Grid m_grid;

    bool m_startedTemplate;
    bool m_finishedTemplate;
    bool m_drawingLine;
    Line m_line;

    bool m_mouseHeld;

    void LoadFile();
    void SaveFile();

public:
    Runner(sf::RenderWindow& window, sf::RenderWindow& iter_window, sf::Font& font);
    ~Runner();

    void UpdateLineType(int newTypeButton);

    bool HandleEvent(const sf::Event &event);
    bool HandleIterEvent(const sf::Event &event);
    void Draw();
    void IterDraw();
};

#endif // RUNNER_H
