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
    void setBounds(const float &top_,const float &bot_,const float &left_,const float &right_)
    {
        bound_top = top_;
        bound_bottom = bot_;
        bound_left = left_;
        bound_right = right_;
    }
    void moveInDirection(const sf::Time &elapsed, bool colision)
    {
        float time = elapsed.asSeconds();
        sf::FloatRect guy = getGlobalBounds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(guy.top >= bound_top && colision == false)
            {
                move(0,m_speed_y*time * -1.0);
            }
            else
            {
                move(0,1);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(guy.top + guy.height <= bound_bottom && colision == false)
            {
                move(0,m_speed_y*time);
                move(0,-1*time);
            }
            else
            {

            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(guy.left >= bound_left && colision == false)
            {
                move(m_speed_x*time * -1.0,0);
            }
            else
            {
                move(1,0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(guy.left + guy.width <= bound_right && colision == false)
            {
                move(m_speed_x*time,0);
            }
            else
            {
                move(-1,0);
            }
        }
    }
    void setSpeed(const int &x,const int &y)
    {
        m_speed_x = x;
        m_speed_y = y;
    }

private:
    int m_speed_x = 0;
    int m_speed_y = 0;

    int bound_top = 0;
    int bound_bottom = 0;
    int bound_left = 0;
    int bound_right = 0;

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
    CustomWall(sf::Texture *texture,int left, int Top, int width, int height)
        : Left(left), Top(Top), Width(width), Height(height)
    {
        sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
        setTexture(*texture);
        texture->setRepeated(true);
        setTextureRect(sf::IntRect(0,0,Width,Height));
        setPosition(Left,Top);
    }
    int WallLeft()
    {
        return Left;
    }
    int WallTop()
    {
        return Top;
    }
    int WallBottom()
    {
        return Top + Height;
    }

    int WallRight()
    {
        return Left + Width;
    }
private:
    int Left;
    int Top;
    int Width;
    int Height;
};

bool ColisionCheck(const CustomGuy &guy, const std::vector<CustomWall> &walls)
{
    bool x = false;
    sf::FloatRect guy_bounds = guy.getGlobalBounds();
    for(auto &wall: walls)
    {
        sf::FloatRect wall_bounds = wall.getGlobalBounds();
        if(guy_bounds.intersects(wall_bounds))
        {
        x = true;
        return x;
        break;
        }

    }
    return x;
}

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
    CustomWall wall_4(&texture_wall, 450, 100, 50, 450);

    walls.emplace_back(wall_1);
    walls.emplace_back(wall_2);
    walls.emplace_back(wall_3);
    walls.emplace_back(wall_4);

    guy.setSpeed(200,200);
    guy.setBounds(0, window.getSize().y, 0, window.getSize().x);
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
        guy.moveInDirection(elapsed,ColisionCheck(guy,walls));
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



