#include <SFML/Graphics.hpp>
#include <iostream>

uint8_t is_win(uint8_t board[3][3])
{
    if (board[0][0] == board[0][1] && board[0][1] == board[0][2])
    {
        return board[0][0];
    }
    if (board[1][0] == board[1][1] && board[1][0] == board[1][2])
    {
        return board[1][0];
    }
    if (board[2][0] == board[2][1] && board[2][0] == board[2][2])
    {
        return board[2][0];
    }
    if (board[0][0] == board[1][0] && board[0][0] == board[2][0])
    {
        return board[0][0];
    }
    if (board[0][1] == board[1][1] && board[0][1] == board[2][1])
    {
        return board[0][1];
    }
    if (board[0][2] == board[1][2] && board[0][2] == board[2][2])
    {
        return board[0][2];
    }
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }
    return 0;
}
int main()
{
    const unsigned int cell_size = 100;
    const unsigned int line_thickness = 10;
    uint8_t board[3][3] = { {0,0,0},
                            {0,0,0},
                            {0,0,0}};
    sf::RenderWindow window(sf::VideoMode(3*(cell_size +line_thickness) + line_thickness, 3 * (cell_size + line_thickness) + line_thickness), "TIC-TAC-TOE");
    sf::Event event;
    sf::RenderTexture cell[3];
    if (!cell[0].create(cell_size, cell_size) || !cell[1].create(cell_size, cell_size) || !cell[2].create(cell_size, cell_size))
    {
        std::cout << "Cannot create texture" << std::endl;
        return -1;
    }
    else
    {  
        {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(0.7f * cell_size, line_thickness));
            rect.setOrigin(rect.getSize() / 2.0f);
            rect.move(sf::Vector2f(cell_size/2, cell_size / 2));
            rect.setFillColor(sf::Color::Black);
            rect.rotate(45);
            cell[1].clear(sf::Color::White);
            cell[1].draw(rect);
            rect.rotate(90);
            
            cell[1].draw(rect);
            cell[1].display();

            sf::CircleShape circle;
            circle.setRadius(cell_size/4);
            circle.setOrigin(circle.getRadius(), circle.getRadius());
            circle.setFillColor(sf::Color::White);
            circle.move(sf::Vector2f(cell_size / 2, cell_size / 2));
            circle.setOutlineThickness(line_thickness);
            circle.setOutlineColor(sf::Color::Black);
            cell[2].clear(sf::Color::White);
            cell[2].draw(circle);
            cell[2].display();

            cell[0].clear(sf::Color::White);
            cell[0].display();
        }
        uint8_t player = 0;
        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {
                // Request for closing the window
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);
                    int x = mouse.x / (cell_size + line_thickness);
                    int y = mouse.y / (cell_size + line_thickness);
                    
                    
                    if (x >= 0 && x < 3 && y >= 0 && y < 3 && board[y][x] == 0)
                    {
                        board[y][x] = player+1;
                        player = !player;
                    }
                }
            }
            window.clear(sf::Color::Black);
            sf::Sprite sprite;
            
            for (uint8_t i = 0; i < 3; i++)
            {
                for (uint8_t i2 = 0; i2 < 3; i2++)
                {

                    sprite.setTexture(cell[board[i][i2]].getTexture());
                    sprite.setPosition(i2 * (cell_size + line_thickness) + line_thickness,i*(cell_size+line_thickness)+ line_thickness);
                    window.draw(sprite);
                }
            }
            
            window.display();
            if (is_win(board) == 1)
            {
                std::cout << "X win";
                break;
            }
            if (is_win(board) == 2)
            {
                std::cout << "O win";
                break;
            }
        }
    }
    

    return 0;
}