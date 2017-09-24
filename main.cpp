#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif

#include "Fractal_Iterator.h"
#include "Runner.h"
#include "config.h"
#include "logging.h"

int main() {
    logging::OpenLog();

    sf::Font inFont;
    logging::AddToLog("Loading font from VeraMono.ttf ...");
    #ifdef __APPLE__
    if(!inFont.loadFromFile(resourcePath() + "VeraMono.ttf")) {
        logging::AddToLog("Failed to load font file!");
        return -1;
    }
    #else
    if(!inFont.loadFromFile("VeraMono.ttf")) {
        logging::AddToLog("Failed to load font file!");
        return -1;
    }
    #endif
    logging::AddToLog("Font loaded successfully\n");

    logging::AddToLog("Loading config from FractaSketch_config.cfg ...");
    config::load_config();
    logging::AddToLog("Done loading config\n");

    sf::ContextSettings settings;
    settings.antialiasingLevel = config::antialias_level;
    sf::RenderWindow window(sf::VideoMode(1200, 724), "FractaSketch", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setPosition(sf::Vector2i(0, 0));

    sf::RenderWindow iter_window;
    Runner run(window, iter_window, inFont);

    run.Draw();

    while (window.isOpen()) {
        sf::Event ev;
        if (iter_window.isOpen()) {
            bool needs_redraw = false;
            while (window.pollEvent(ev)) {
                if (run.HandleEvent(ev)) needs_redraw = true;
            }
            if(needs_redraw) run.Draw();

            bool iter_needs_redraw = false;
            while (iter_window.pollEvent(ev)) {
                if (run.HandleIterEvent(ev)) iter_needs_redraw = true;
            }
            if(iter_needs_redraw) run.IterDraw();

            sf::sleep(sf::milliseconds(1000/60));
        }
        else {
            if (window.waitEvent(ev)) {
                bool needs_redraw = run.HandleEvent(ev);
                while (window.pollEvent(ev)) {
                    if (run.HandleEvent(ev)) needs_redraw = true;
                }
                if(needs_redraw) run.Draw();
            }
        }
    }

    iter_window.close();
    return 0;
}
