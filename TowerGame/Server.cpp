#include "Server.h" 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>

using namespace std;

void Server::RunServer()
{
    cout << "Server.cpp" << endl;
    bool ifNext = false;
    clock.restart();

    sf::Thread thread1([&](){
	    while(window.isOpen())
	    {
		sf::Packet packet;
		string data;
		packet.clear();
		socketP1.receive(packet);
		if(packet.getDataSize() > 0)
		{
		    cout << "Packet Size:" << packet.getDataSize() << endl;
		
		    stringstream ss;
		    float coins; 
		    float income;
		    int option;
		    int x;
		    int y;
		    while (packet >> data)
		    {
			ss << data << " ";
		    }
		    string data = ss.str();
		    ss >> coins >> income >> option >> x >> y;
		    cout << "Packet data: " << ss.str() << endl;
		    if (SGM.Run(coins, income, option, x, y, groundP1))
		    {
			socketP1.send(packet);
			packet << "2";
			socketP2.send(packet);
		    }
		} 
	    }
	});

    sf::Thread thread2([&](){
	    while(window.isOpen())
	    {
		sf::Packet packet;
		string data;
		packet.clear();
		socketP2.receive(packet);
		if(packet.getDataSize() > 0)
		{
		    cout << "Packet Size:" << packet.getDataSize() << endl;
		
		    stringstream ss;
		    float coins; 
		    float income;
		    int option;
		    int x;
		    int y;
		    while (packet >> data)
		    {
			ss << data << " ";
		    }
		    string data = ss.str();
		    ss >> coins >> income >> option >> x >> y;
		    cout << "Packet data: " << ss.str() << endl;
		    if (SGM.Run(coins, income, option, x, y, groundP2))
		    {
			socketP2.send(packet);
			packet << "2";
			socketP1.send(packet);
		    }
		}
	    } 
	});

    thread1.launch();
    thread2.launch(); 
    while(window.isOpen() && !ifNext)
    {
	sf::Event event;
	while(window.pollEvent(event))
	{
	    if (event.type == sf::Event::Closed)
		window.close();
	    else if (event.type == sf::Event::KeyPressed)
	    {
		if (event.key.code == sf::Keyboard::Escape)
		    window.close();
	    }
	}	
	sf::Time time = clock.getElapsedTime();

	window.clear();
	window.display();
    }
}

