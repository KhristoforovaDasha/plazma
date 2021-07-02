#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace sf;
int w = 1024, h = 1024;
std::vector< std::vector<sf::Vector3i> > value(w, std::vector<sf::Vector3i>(h));
RenderWindow window(VideoMode(h, w), "SFML Works!");
double len;
double coef(int x0,int y0,int x1,int y1) {
	return 2 * double(std::abs(x1 - x0) + std::abs(y1 - y0)) / len;
	//return double(std:: sqrt((xx - x0) * (xx - x0) + (yy - y0) * (yy - y0)))/(std::sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0)));
}
void Draw_center(int x0, int y0, int xn, int yn,int xx,int yy) {
	double k = coef(x0, y0, xx, yy);
	int r = ((value[y0][x0].x + value[yn][x0].x + value[y0][xn].x + value[yn][xn].x ) / 4 + (int)(1234 * (rand()% 200/100.0 -1) *k)) ;
	int g = ((value[y0][x0].y + value[yn][x0].y + value[y0][xn].y + value[yn][xn].y ) / 4 + (int)(1000 * (rand() % 200/ 100.0 - 1) * k)) ;
	int b = ((value[y0][x0].z + value[yn][x0].z + value[y0][xn].z + value[yn][xn].z ) / 4 + (int)(1234 * (rand() % 200 / 100.0 - 1) * k));
	if (r > 255) r = 255;
	else if (r < 0) r = 0;
	if (g > 255) g = 255;
	else if (g < 0) g = 0;
	if (b > 255) b = 255;
	else if (b < 0) b = 0;
	//std:: cout << r << " " << g << " " << b << '\n';
	value[yy][xx] = Vector3i(r, g, b);
	sf::Vertex point(sf::Vector2f(double(xx), double(yy)), sf::Color(r, g, b));
	window.draw(&point, 1, sf::Points);
}
void Draw(int x0, int y0, int xn, int yn) {
	int xx = (xn + x0) / 2;
	int yy = (yn + y0) / 2;
	int r = (value[y0][x0].x + value[yn][xn].x) / 2;
	int g = (value[y0][x0].y + value[yn][xn].y) / 2;
	int b = (value[y0][x0].z + value[yn][xn].z) / 2;
	value[yy][xx] = Vector3i(r, g, b);
	sf::Vertex point(sf::Vector2f(double(xx), double(yy)), sf::Color(r, g, b));
	window.draw(&point, 1, sf::Points);
}
void begin(int x, int y) {
	int r = rand() % 256, g = rand() % 256, b = rand() % 256;
	std::cout << r << " " << g << " " << b << '\n';
	value[y][x] = sf::Vector3i(r, g, b);
	sf::Vertex point(sf::Vector2f(x, y), sf::Color(r, g, b));
	window.draw(&point, 1, sf::Points);
}
void Paint(int x0, int y0, int xn, int yn) {
	if (x0 >= xn - 1 && y0 >= yn - 1) return;
	int xx = (xn + x0) / 2;
	int yy = (yn + y0) / 2;
	Draw(x0, y0, x0, yn);
	Draw(x0, y0, xn, y0);
	Draw(x0, yn, xn, yn);
	Draw(xn, y0, xn, yn);
	Draw_center(x0, y0, xn, yn, xx, yy);
	/*int r1 = ((value[y0][x0].x + value[yn][x0].x)/2 +rand()) % 256;
	int g1 = ((value[y0][x0].y + value[yn][x0].y ) / 2 + rand()) % 256;
	int b1 = ((value[y0][x0].z + value[yn][x0].z ) / 2 + rand()) % 256;
	sf::Vertex point1(sf::Vector2f(double(x0), double(yy)), sf::Color(r1, g1, b1));
	window.draw(&point1, 1, sf::Points);
	int r2 = ((value[y0][x0].x + value[y0][xn].x) / 2 ) % 256;
	int g2 = ((value[y0][x0].y + value[y0][xn].y) / 2 ) % 256;
	int b2 = ((value[y0][x0].z + value[y0][xn].z) / 2 ) % 256;
	sf::Vertex point2(sf::Vector2f(double(xx), double(y0)), sf::Color(r2, g2, b2));
	window.draw(&point2, 1, sf::Points);
	int r3 = ((value[yn][xn].x + value[yn][x0].x) / 2 ) % 256;
	int g3 = ((value[yn][xn].y + value[yn][x0].y) / 2 ) % 256;
	int b3 = ((value[yn][xn].z + value[yn][x0].z) / 2 ) % 256;
	sf::Vertex point3(sf::Vector2f(double(xx), double(yn)), sf::Color(r3, g3, b3));
	window.draw(&point3, 1, sf::Points);
	int r4 = ((value[yn][xn].x + value[y0][xn].x) / 2 ) % 256;
	int g4 = ((value[yn][xn].y + value[y0][xn].y) / 2 ) % 256;
	int b4 = ((value[yn][xn].z + value[y0][xn].z) / 2 ) % 256;
	sf::Vertex point4(sf::Vector2f(double(xn), double(yy)), sf::Color(r4, g4, b4));
	window.draw(&point4, 1, sf::Points);
	int r = ((value[y0][x0].x + value[yn][x0].x + value[y0][xn].x + value[yn][xn].x)/4 )%256;
	int g = ((value[y0][x0].y + value[yn][x0].y + value[y0][xn].y + value[yn][xn].y) / 4)%256;
	int b = ((value[y0][x0].z + value[yn][x0].z + value[y0][xn].z + value[yn][xn].z) / 4)%256;
	sf::Vertex point(sf:: Vector2f(double(xx),double(yy)), sf::Color(r, g, b));
	window.draw(&point, 1, sf::Points);*/
	Paint(x0, y0, xx, yy);
	Paint(xx, yy, xn, yn);
	Paint(xx, y0, xn, yy);
	Paint(x0, yy, xx, yn);
}
int main()
{
	srand(time(0));
	sf::Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;
	//int x0 = 0, y0 = 0, xn = 800, yn = 600;
	int r, g, b;
	//sf::Vertex point(sf::Vector2f(100, 100), sf::Color(100,100,100));
	//window.draw(&point, 1, sf::Points);
	len = 4096;
	begin(0, 0);
	begin(0, w-2);
	begin(h-2, 0);
	begin(h-2, w-2);
	Paint(0, 0, h-2, w-2);
	window.display();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//window.clear(Color(255, 255, 255, 0));
		/*len = 2800;
		begin(0, 0);
		begin(0,600);
		begin(800, 0);
		begin(800,600);
		/*r = rand() % 256, g = rand() % 256, b = rand() % 256;
		value[0][0] = sf::Vector3i(r,g,b);
		sf::Vertex point(sf::Vector2f(0, 0), sf::Color(r,g,b));
		window.draw(&point, 1, sf::Points);
		r = rand() % 256, g = rand() % 256, b = rand() % 256;
		value[600][0] = (sf::Vector3i(r, g, b));
		sf::Vertex point1(sf::Vector2f(600, 0), sf::Color(r, g, b));
		window.draw(&point1, 1, sf::Points);
		r = rand() % 256, g = rand() % 256, b = rand() % 256;
		value[0][800] =  (sf::Vector3i(r, g, b));
		sf::Vertex point2(sf::Vector2f(0, 800), sf::Color(r, g, b));
		window.draw(&point2, 1, sf::Points);
		r = rand() % 256, g = rand() % 256, b = rand() % 256;
		value[600][800] = (sf::Vector3i(r, g, b));
		sf::Vertex point3(sf::Vector2f(600, 800), sf::Color(r, g, b));
		window.draw(&point3, 1, sf::Points);*/
		//Paint(0, 0, 800, 600);
		//window.display();
	}
	return 0;
}