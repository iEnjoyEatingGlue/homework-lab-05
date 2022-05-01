#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class CustomGuy: public sf::Sprite
{
public:
    CustomGuy(sf::Texture *texture)
    {
        setTexture(*texture);

    }
private:

};

class CustomGrass: public sf::Sprite
{
public:
    CustomGrass(sf::Texture* texture)
    {
        sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
        setTexture(*texture);
        texture->setRepeated(true);
        setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    }
};

class CustomWall: public sf::Sprite
{
public:
    CustomWall(sf::Texture *texture,int top, int bottom, int width, int height)
        : Top(top), Bottom(bottom), Width(width), Height(height)
    {
        sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
        setTexture(*texture);
        texture->setRepeated(true);
        setTextureRect(sf::IntRect(0,0,Width,Height));
        setPosition(Top,Bottom);
    }
private:
    int Top;
    int Bottom;
    int Width;
    int Height;
};

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Clock clock;
    float time_passed = 0.0;

    sf::Texture texture_guy;
    sf::Texture texture_grass;
    sf::Texture texture_wall;

    if(!texture_guy.loadFromFile("guy.png")) { return 1; }
    if(!texture_grass.loadFromFile("grass.png")) { return 1; }
    if(!texture_wall.loadFromFile("wall.png")) { return 1; }

    CustomGuy guy(&texture_guy);
    CustomGrass grass(&texture_grass);
    std::vector<CustomWall> walls;

    CustomWall wall_1(&texture_wall, 100, 100, 250, 50);
    CustomWall wall_2(&texture_wall, 250, 150, 100, 400);
    CustomWall wall_3(&texture_wall, 250, 550, 250, 50);
    CustomWall wall_4(&texture_wall, 450, 50, 50, 500);

    walls.emplace_back(wall_1);
    walls.emplace_back(wall_2);
    walls.emplace_back(wall_3);
    walls.emplace_back(wall_4);

    while (window.isOpen())
    {

        sf::Time elapsed = clock.restart();
        time_passed = time_passed + elapsed.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        guy.move(0.001,0.001);
        window.clear(sf::Color::Black);

        window.draw(grass);
        window.draw(guy);
        for(auto &wall: walls)
            window.draw(wall);

        window.display();
    }
    return 0;
}
















//class CustomRectangleShape: public sf::RectangleShape
//{
//public:
//    CustomRectangleShape(sf::Vector2f size,sf::Vector2f position): sf::RectangleShape(size)
//    {
//        setPosition(position);
//    }
//    void setSpeed(const int &x,const int &y)
//    {
//        m_speed_x = x;
//        m_speed_y = y;
//    }
//    void animate(const sf::Time &elapsed)
//    {
//        bounce();
//        float time = elapsed.asSeconds();
//        move(m_speed_x*time,m_speed_y*time);
//    }
//    void setBounds(const float &top,const float &bot,const float &left,const float &right)
//    {
//        bound_top = top;
//        bound_bottom = bot;
//        bound_left = left;
//        bound_right = right;
//    }
//    void moveInDirection(const sf::Time &elapsed/*, const sf::Keyboard::Key &key*/)
//    {
//        float time = elapsed.asSeconds();
//        sf::FloatRect rectangle_bounds = getGlobalBounds();

//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//        {
//            if(rectangle_bounds.top >= bound_top)
//            {
//                move(0,m_speed_y*time * -1.0);
//            }
//        }
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//        {
//            if(rectangle_bounds.top + rectangle_bounds.height <= bound_bottom)
//            {
//                move(0,m_speed_y*time);
//            }
//        }
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//        {
//            if(rectangle_bounds.left >= bound_left )
//            {
//                move(m_speed_x*time * -1.0,0);
//            }
//        }
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//        {
//            if(rectangle_bounds.left + rectangle_bounds.width <= bound_right)
//            {
//                move(m_speed_x*time,0);
//            }
//        }
//    }
//    bool isClicked(sf::Vector2i &mouse_position) const
//    {
//        bool a = false;
//        sf::FloatRect rectangle_bounds = getGlobalBounds();
//            if(rectangle_bounds.top < mouse_position.y && mouse_position.y < rectangle_bounds.top + rectangle_bounds.height
//                    && rectangle_bounds.left < mouse_position.x && mouse_position.x < rectangle_bounds.left + rectangle_bounds.width)
//            {
//                a = true;
//            }
//        return (a);
//    }
//    bool clicked_changer(sf::Vector2i &mouse_position)
//    {
//        if(isClicked(mouse_position) == true)
//        {
//            clicked = true;
//        }
//        else
//        {
//            clicked = false;
//        }
//        return clicked;
//    }

//    bool clicked_clicked(){return(clicked);};

//private:

//    bool clicked = false;

//    int m_speed_x = 0;
//    int m_speed_y = 0;

//    float bound_top = 0;
//    float bound_bottom = 0;
//    float bound_left = 0;
//    float bound_right = 0;

//    void bounce()
//    {
//        sf::FloatRect rectangle_bounds_2 = getGlobalBounds();

//        if(rectangle_bounds_2.top <= bound_top){
//            m_speed_y = abs(m_speed_y);
//            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
//        }

//        if(rectangle_bounds_2.top + rectangle_bounds_2.height >= bound_bottom){
//            m_speed_y = abs(m_speed_y) * -1;
//            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
//        }

//        if(rectangle_bounds_2.left <= bound_left ){
//           m_speed_x = abs(m_speed_x);
//           setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
//        }

//        if(rectangle_bounds_2.left + rectangle_bounds_2.width >= bound_right){
//            m_speed_x = abs(m_speed_x) * -1;
//            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
//        }
//    }
//};

//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

//    sf::Vector2f size(60.0, 120.0);
//    sf::Vector2f position(0,0);

//    CustomRectangleShape shape_guy(size,position);

//    shape_guy.setFillColor(sf::Color(0, 255, 0));
//    shape_guy.setBounds(0, window.getSize().y, 0, window.getSize().x);
//    shape_guy.setSpeed(200, 200);

//    sf::Texture texture_guy;
//    if(!texture_guy.loadFromFile("guy.png")) { return 1; }

//    sf::Sprite guy;
//    guy.setTexture(texture_guy);

//    sf::Clock clock;
//    float time_passed = 0.0;

//    sf::CircleShape circle(50.0);
//       circle.setPosition(100.0, 300.0);
//       circle.setFillColor(sf::Color(100, 250, 50));

//    while (window.isOpen())
//    {

//        sf::Time elapsed = clock.restart();
//        time_passed = time_passed + elapsed.asSeconds();

//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }

//        sf::Vector2i position = sf::Mouse::getPosition(window);

//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//        {
//            shape_guy.clicked_changer(position);
//        }

//        if(shape_guy.clicked_clicked() == true)
//        {
//            shape_guy.setFillColor(sf::Color(255, 0, 0));
//            shape_guy.moveInDirection(elapsed);
//        }
//        else
//        {
//            shape_guy.setFillColor(sf::Color(0, 255, 0));
//        }

//        window.clear(sf::Color::Black);

//        window.draw(shape_guy);
//        window.display();
//    }
//    return 0;
//}



