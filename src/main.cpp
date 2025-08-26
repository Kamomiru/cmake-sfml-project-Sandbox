#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include "promptWindow.h"

int counter = 0;
int enterCounter = 0;

void appendObject(std::vector<sf::CircleShape>& objectContainer, sf::Vector2f pos) {
    sf::CircleShape shape(80.0f);
    sf::Color color;
    switch (counter) {
    case 0:
        color = sf::Color::Blue;
        break;
    case 1:
        color = sf::Color::Red;
        break;
    case 2:
        color = sf::Color::Green;
        break;
    case 3:
        color = sf::Color::Magenta;
        break;
    case 4:
        color = sf::Color::Yellow;
        break;
    default:
        color = sf::Color::White;
        break;
    }
    shape.setFillColor(color);
    shape.setOrigin({ 80.0f, 80.0f });
    shape.setPosition(pos);
    objectContainer.push_back(shape);

    if (counter == 5) {
        counter = 0;
    }
    else {
        counter++;
    }
}

sf::Vector2f rotateAroundPoint(sf::Vector2f pointToRotate, sf::Vector2f centerPoint, float angleGrad) {
    sf::Vector2f rotatingVector = pointToRotate - centerPoint;
    sf::Vector2f rotatedVector;
    sf::Vector2f rotatedPoint;

    //right angle exceptions:
    if (angleGrad == 90.0f || angleGrad == -270.0f) {
        rotatedVector.x = -rotatingVector.y;
        rotatedVector.y = rotatingVector.x;
    }
    else if (angleGrad == 180.0f || angleGrad == -180.0f) {
        rotatedVector.x = -1.0f * rotatingVector.y;
        rotatedVector.y = -1.0 * rotatingVector.x;
    }
    else if (angleGrad == 270.0f || angleGrad == -90.0f) {
        rotatedVector.x = -rotatingVector.y;
        rotatedVector.y = rotatingVector.x;
    }
    else if (angleGrad == 0.0f) {
        return pointToRotate;
    }

    //handling all other angles
    float angleRad = angleGrad * (3.14159265f / 180.0f); // Convert angle from degrees to radians
    float s = std::sin(angleRad);
    float c = std::cos(angleRad);

    rotatedVector.x = rotatingVector.x * c - rotatingVector.y * s;
    rotatedVector.y = rotatingVector.x * s + rotatingVector.y * c;

    rotatedPoint = centerPoint + rotatedVector;

    return rotatedPoint;

}

void rotateAroundPoint(sf::VertexArray& vertexArrayToRotate, sf::Vector2f centerPoint, float angleGrad) {
    for (int i = 0; i < vertexArrayToRotate.getVertexCount(); i++) {
        vertexArrayToRotate[i].position = rotateAroundPoint(vertexArrayToRotate[i].position, centerPoint, angleGrad);
    }
}

void drawVector(sf::Vector2f startPos, float length, float angleGrad, sf::RenderWindow* window) {
    float lineWidth = 1.5f;
    
    //Check for negative Length
    if (length < 0) {
        length = abs(length);
        angleGrad += 180;
    }

    //Scale vectorTip When below 100px length
    float vectorTipScaler;
    if (length < 100.0f) {
         vectorTipScaler = (1 - abs(length) / 100.0f) * 1.8;
    }
    else {
        vectorTipScaler = 0;
    }

    //Create VectorTip
    sf::Vector2f endPos;
    endPos.x = startPos.x + length;
    endPos.y = startPos.y;

    sf::VertexArray vectorTip(sf::PrimitiveType::Triangles, 3);
    vectorTip[0].position = sf::Vector2f({ endPos.x, endPos.y });
    vectorTip[1].position = sf::Vector2f({ endPos.x - (10.0f - vectorTipScaler), endPos.y + (5.0f - vectorTipScaler) });
    vectorTip[2].position = sf::Vector2f({ endPos.x - (10.0f - vectorTipScaler), endPos.y - (5.0f - vectorTipScaler) });

    //Create VectorLine
    sf::RectangleShape vectorLine({ length - 1, lineWidth });
    vectorLine.setOrigin({ 0.0f, lineWidth / 2 }); //adjust line origin so it rotation point is inside its long axis
    vectorLine.setPosition(startPos);

    //Handle Vector rotation
    rotateAroundPoint(vectorTip, startPos, angleGrad);
    vectorLine.rotate(sf::degrees(angleGrad));

    window->draw(vectorLine);
    window->draw(vectorTip);
}

void checkForNumericalInput(std::optional<sf::Event> event, std::string& input) {

    if (event->getIf<sf::Event::TextEntered>()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
            input += '1';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
            input += '2';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
            input += '3';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
            input += '4';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) {
            input += '5';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) {
            input += '6';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7)) {
            input += '7';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8)) {
            input += '8';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9)) {
            input += '9';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0)) {
            input += '0';
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) {
            if (input.length() != 0) {
                input.pop_back();
            }
            std::cout << "DeletePressed!" << '\n';
        }
    }
}



int main() {
    //Init SFML Window and View
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "CMake SFML Project", sf::State::Windowed, settings);
    window.setFramerateLimit(144);

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::View desktopView(sf::FloatRect({ 0.0f, 0.0f }, static_cast<sf::Vector2f>(desktop.size)));


    //Init objectContainer
    std::vector<sf::CircleShape> objectContainer;

    //Init Top left Circle
    sf::CircleShape circle(80.0f, 36);
    circle.setFillColor(sf::Color::Cyan);
    circle.setOrigin({ 80.0f, 80.0f });
    circle.setPosition({ 0,0 });

    //Init Mouse Pos
    sf::Vector2f mousePos;

    //Init Font
    sf::Font font("Roboto-Medium.ttf");

    //Init Text
    sf::Text inputText(font);
    inputText.setCharacterSize(14);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition({ 50, 50 });

    //prompt Window test
    promptWindow prompt("Hallo Hier bin ich! Ich bin ein Ganz schön wilder gnom! Also pass lieber auf was du sagst du frechdachs! Mein name ist Camillo, ich programmiere sehr gerne und studiere nebenbei. Meine Freundin heißt Eve ich hab sie sehr sehr gerne!", { 400.0f, 400.0f }, 400.0f);

    std::string input;
    int angle = 0;




    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (event->getIf<sf::Event::MouseButtonPressed>()) {
                mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), desktopView);
                appendObject(objectContainer, mousePos);
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                if (enterCounter == 9) {
                    enterCounter = 0;
                }
                else {
                    enterCounter++;
                }
            }


            checkForNumericalInput(event, input);

        }


        //Input Border Test
        inputText.setString(input);
        sf::FloatRect boundsRect(inputText.getGlobalBounds());

        float padding = 10.0f;
        sf::RectangleShape inputTextBorder({ boundsRect.size.x + padding, boundsRect.size.y + padding});
        inputTextBorder.setPosition({ boundsRect.position.x - padding / 2, boundsRect.position.y - padding /2 });
        inputTextBorder.setFillColor(sf::Color::Transparent);
        inputTextBorder.setOutlineThickness(3.0f);

        

        
        


        window.clear();

        //Draw Calls
        for (sf::CircleShape element : objectContainer) {
            window.draw(element);
        }
        drawVector({ 200.0f,200.0f }, (100 - enterCounter * 10), angle, &window);
        //window.draw(circle);
        window.draw(inputText);
        if (input.length() != 0) {
            window.draw(inputTextBorder);
        }
        prompt.draw(window);
        

        window.display();



        if (angle == 359) {
            angle = 0;
        }
        else {
            //angle++;

        }

    }
}

