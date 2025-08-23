#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>


int main()
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "CMake SFML Project", sf::State::Windowed, settings);
    window.setFramerateLimit(144);

    sf::View view({ 860.f, 540.f }, { 1920.0f, 1080.0f });

    sf::CircleShape triangle(80.0f, 3);
    triangle.setFillColor(sf::Color::Cyan);
    triangle.setPosition({ 860.f, 540.f - 80.f});

    bool mouseDragged = false;
    sf::Vector2f lastMousePos;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) 
            {
                window.close();
            }
            if (event->is<sf::Event::MouseButtonPressed>()) //In conditional statement we dont need the event anymore, so we can simply use is<T>()
            {
                std::cout << "Mouse is dragged\n";
                mouseDragged = true;
                lastMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
            }
            if (event->is<sf::Event::MouseButtonReleased>()) {
                mouseDragged = false;
                std::cout << "Mouse is not dragged\n";
            }
            if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>()) { //Here we DO need the event later in our program. so we have to get it using the getIf<T>() function
                if (mouseWheelScrolled->delta > 0 ) { //here "mouseWheelScrolled" is an event pointer so it could also be dereferenced by (*mouseWheelScrolled).delta
                    view.zoom(0.9f);
                }
                if (mouseWheelScrolled->delta < 0) {
                    view.zoom(1.1f);
                }
                
            }


        }

        if (mouseDragged) {
            sf::Vector2f currentMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
            sf::Vector2f delta = lastMousePos - currentMousePos;
            view.move(delta);
            lastMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
            

        }

        
        window.setView(view);
        
        window.clear();
        window.draw(triangle);
        window.display();
    }
}
