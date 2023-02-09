//
// Created by Jonas Bennink Bolt on 2/3/23.
//

//#include "Graphics.hpp"
//#include "logger.hpp"
//#include <SFML/Graphics.hpp>
//#include <cmath>
//
//Graphics::Graphics() {
//    sf::RenderWindow window(sf::VideoMode(1000, 1100), "Gomoku:)", sf::Style::Default);
//    window.setVerticalSyncEnabled(true);
//    window.clear(sf::Color::White);
//
//    sf::Font arial;
//    if (not arial.loadFromFile("../resources/Arial.ttf")) {
//        LOG("font not loaded from file");
//    }
//    sf::Text topTitle;
//    topTitle.setFont(arial);
//    topTitle.setString("this is a first test with a bunch of nonsense\n\t  close with escape or clicking the x");
//    topTitle.setFillColor(sf::Color::Black);
//    topTitle.setStyle(sf::Text::Bold);
//    window.draw(topTitle);
//    auto center = topTitle.getGlobalBounds().getSize() / 2.f;
//    auto localbounds = center + topTitle.getLocalBounds().getPosition();
//    sf::Vector2f rounded = {std::round(localbounds.x), std::round(localbounds.y)};
//    topTitle.setOrigin(rounded);
//    topTitle.setPosition(sf::Vector2f{window.getSize().x / 2.f, window.getSize().y / 20.f});
//
//    while (window.isOpen()) {
//        sf::Event ev{};
//        while (window.pollEvent(ev)) {
//            switch (ev.type) {
//                case sf::Event::Closed: {
//                    window.close();
//                    break;
//                }
//                case sf::Event::KeyPressed: {
//                    if (ev.key.code == sf::Keyboard::Key::Escape) {
//                        window.close();
//                    }
//                    break;
//                }
//                case sf::Event::MouseButtonPressed: {
//                    LOG("clicked on x,y: (%d, %d)", ev.mouseButton.x, ev.mouseButton.y);
//                    break;
//                }
//                case sf::Event::KeyReleased:
//                case sf::Event::MouseButtonReleased:
//                case sf::Event::MouseMoved:
//                case sf::Event::MouseEntered:
//                case sf::Event::MouseLeft:
//                case sf::Event::MouseWheelScrolled:
//                case sf::Event::MouseWheelMoved:
//                case sf::Event::GainedFocus:
//                case sf::Event::LostFocus:
//                    break;
//                default:
//                    LOG("uncaught event %d", ev.type);
//                    break;
//
//            }
//
//            window.clear(sf::Color::White);
//            window.draw(topTitle);
//            window.display();
//        }
//    }
//}
//
//bool Graphics::updateBoardPositive() {
//    return false;
//}
//bool Graphics::updateBoardNegative() {
//    return false;
//}
