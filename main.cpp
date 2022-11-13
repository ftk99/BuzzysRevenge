/*
Author: Ashaan Facey
Class: ECE4122 or ECE6122
Last Date Modified: 10/27/2021

Description: Lab3

What is the purpose of this file? Buzzy's Revenge

*/
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include "Collision.h" //https://github.com/SFML/SFML/wiki/Source:-Simple-Collision-Detection-for-SFML-2
#include <sstream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <iostream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	sf::Font MyFont;
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Buzz vengance");// , Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);



	/***********Text stuff***********/
	//draw text
	Text title;
	Text message;
	Text power;
	Text lives;
	Text score;
	Text points;
	Text end;

	//choose front 
	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	//setfont to title
	title.setFont(font);
	message.setFont(font);
	power.setFont(font);
	lives.setFont(font);
	score.setFont(font);
	points.setFont(font);
	end.setFont(font);

	//set color
	title.setFillColor(Color::Red);
	message.setFillColor(Color::White);
	power.setFillColor(Color::White);
	lives.setFillColor(Color::White);
	score.setFillColor(Color::White);
	points.setFillColor(Color::White);
	end.setFillColor(Color::Red);
	//make it big
	title.setCharacterSize(65);
	message.setCharacterSize(40);
	power.setCharacterSize(30);
	lives.setCharacterSize(30);
	score.setCharacterSize(30);
	points.setCharacterSize(30);
	end.setCharacterSize(100);
	//Position the text
	FloatRect textRect = title.getLocalBounds();
	title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	title.setPosition(600, 200);
	//title.setPosition(1920/2.0f , 1080/2.0f);
	message.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	message.setPosition(600, 300);
	power.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	power.setPosition(0, 900);
	lives.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	lives.setPosition(10,15);
	score.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	score.setPosition(1700, 10);
	points.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	points.setPosition(1850, 10);
	end.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	end.setPosition(700, 500);
	int score_points = 0;
	
	//assign the actual message		
	title.setString(" Buzzy's Revenge");
	message.setString("Press Enter to Restart Game\nPress Esc to Exit\nPress Space to Powerup\nPress up/down arrow to aim");
	power.setString("Power:");
	lives.setString("Lives ");
	score.setString("Score : ");
	points.setString(to_string(score_points));
	end.setString("GAME OVER");

	/***************Power Bar**************/
	// Variables to control time itself
	//Clock clock;

	/************buzzy*************/
	// Prepare the bee
	Texture buzzy;
	buzzy.loadFromFile("graphics/smallbuzzy.png");
	Sprite buzzySprite;
	buzzySprite.setTexture(buzzy);
	buzzySprite.setPosition(0, 450);
	buzzySprite.setScale(.75, .75);
	//buzzySprite.setRotation(315);

	Texture life;
	life.loadFromFile("graphics/life.png");
	Sprite lifeSprite;
	lifeSprite.setTexture(life);
	//lifeSprite.setPosition(400, 10);
	lifeSprite.setScale(.35, .35);

	Sprite life_array[5];
	int lifex = 100;
	for (int g = 0; g < 5; g++) 
	{
		life_array[g] = lifeSprite;
		life_array[g].setPosition(lifex, 10);
		lifex += 50;		
	}

	//sprite vecor

	//an unordered_map<int, Sprite> for (number key, spriteAnimal).Then another array randomly shuffled with all the number keys
	//arrays index 0-4 had animals in column 1 and 5-9 had animals in column 2.
	//helper function to check if the tiger index and bulldog index mod 5 is the same (both in first half of array or both in second half of array).
	//Then draw animals based off their key value with the key as the position of the corresponding number in the shuffled array.

	Sprite animals[10];

	Texture dog;
	dog.loadFromFile("graphics/dog.png");
	Sprite dogSprite;
	dogSprite.setTexture(dog);	

	Texture chicken;
	chicken.loadFromFile("graphics/chicken.png");
	Sprite chickenSprite;
	chickenSprite.setTexture(chicken);

	Texture sheep;
	sheep.loadFromFile("graphics/sheep.png");
	Sprite sheepSprite;
	sheepSprite.setTexture(sheep);	

	Texture frog;
	frog.loadFromFile("graphics/frog.png");
	Sprite frogSprite;
	frogSprite.setTexture(frog);	

	Texture bunny;
	bunny.loadFromFile("graphics/bunny.png");
	Sprite bunnySprite;
	bunnySprite.setTexture(bunny);	

	Texture unicorn;
	unicorn.loadFromFile("graphics/angry_unicorn.png");
	Sprite unicornSprite;
	unicornSprite.setTexture(unicorn);	

	Texture bulldog;
	bulldog.loadFromFile("graphics/bulldog.png");
	Sprite bulldogSprite;
	bulldogSprite.setTexture(bulldog);

	Texture tiger;
	tiger.loadFromFile("graphics/tiger.png");
	Sprite tigerSprite;
	tigerSprite.setTexture(tiger);
	tigerSprite.setScale(.1, .1);

	Texture mouse;
	mouse.loadFromFile("graphics/mouse.png");
	Sprite mouseSprite;
	mouseSprite.setTexture(mouse); ;

	Texture pig;
	pig.loadFromFile("graphics/pig.png");
	Sprite pigSprite;
	pigSprite.setTexture(pig);
	
	animals[0] = pigSprite;
	animals[1] = mouseSprite;
	animals[2] = unicornSprite;
	animals[3] = bunnySprite;
	animals[4] = frogSprite;
	animals[5] = sheepSprite;
	animals[6] = chickenSprite;
	animals[7] = dogSprite;
	//set last two array sport to tiger and bulldog
	animals[8] = bulldogSprite;
	animals[9] = tigerSprite;

	//A column disappears when the mascot in it is hit.  This allows you  get to the second column.

	int idx[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> tig_rand(0, 4);
	std::uniform_int_distribution<> bull_rand(5, 9);
	int tiger_idx = tig_rand(gen);	
	int bull_idx = bull_rand(gen);
	idx[tiger_idx] = 9;//place tiger
	 // they are in same column
	
	idx[bull_idx] = 8; // place bull idx

	for (int l = 0; l < 10; l++)
	{
		printf("idx[%d] = %d \n", l, idx[l]);
	}
	printf("************************\n");
	//std::uniform_int_distribution<> other_distr(0, 7);
	
	int nums[8] = { 0 , 1, 2, 3, 4, 5, 6, 7 };
	srand(time(0));
	std::random_shuffle(nums, nums + 8);
	int j = 0;
	for (int i = 0; i < 10; i++) // 
	{
		int others = nums[j];// assuming this doesnt repeat numbers
		//use random number
		printf("%d*", others);
		
		if (idx[i] == 8 || idx[i] == 9)
		{
			//others = nums[i - 1];
			continue;
		}
		if (idx[i] == -1) //space is empty
		{
			idx[i] = others;
			j++;
		}				
		
	}
	for (int l = 0; l < 10; l++)
	{
		printf("idx[%d] = %d \n", l, idx[l]);
	}
	

	
	//rand number from 0 to 9 - sprite indx
	// use that for tiger for eg 6
	//test to see if tig and bulldog in same col
	//if tig i
	int col = 1400;
	int row = 300;
	animals[idx[0]].setPosition(col, row);
	animals[idx[1]].setPosition(col, row += 120);
	animals[idx[2]].setPosition(col, row += 120);
	animals[idx[3]].setPosition(col, row += 120);
	animals[idx[4]].setPosition(col, row += 120);
	col = 1600;
	row = 300;
	animals[idx[5]].setPosition(col, row);
	animals[idx[6]].setPosition(col, row += 120);
	animals[idx[7]].setPosition(col, row += 120);
	animals[idx[8]].setPosition(col, row += 120);
	animals[idx[9]].setPosition(col, row += 120);
	//create a static array of sprites that have the mascots as either the last two or first two elements.  Then put the woodland creatures in the other spots.
	

	

	Texture texturesmallbee;
	texturesmallbee.loadFromFile("graphics/bee.png");
	Sprite spritesmallbee;
	spritesmallbee.setTexture(texturesmallbee);
	spritesmallbee.setPosition(1600, 100); //1600,100
	//spritesmallbee.setPosition(1700, 730);

	// Is the bee currently moving?
	bool beeActive = false;

	// How fast can the bee fly
	float beeSpeed = 0.0f;

	// do bull dog and tiger separate
	//place at inx 8 and 9


	float max = 250;
	
	//Texture bartex;
	//bartex.loadFromFile("graphics/background.png");
	//bar.setTexture( bartex);

	float powerx = 25;
	bool playing = false;
	bool start = true;
	bool spaceinput = false;
	float buzzyAngle = 0.0;
	float speed = 0.0;
	bool startbee = false;
	float sum_dt = 0;
	const int life_max = 5;
	int life_count = life_max ;
	bool tiger_hit = false;
	bool bullg_hit = false;
	bool unicorn_hit = false;
	bool smallbee_hit = false;
	Time beedt;
	bool recreate = false;
	//cout << buzzySprite.getRotation() << endl;
	//sf::Event event;
	//clock.restart();
	bool end_game = false;
	Clock clock;
	float time_fly = 0;
	Time dt;

	Sprite animals_reset[10];
	

	while (window.isOpen()) { //gameloop

		sf::Event event;		
		
		//time += dt.asSeconds();
		sf::RectangleShape powerbar;
		powerbar.setFillColor(sf::Color::Red);
		powerbar.setSize(sf::Vector2f(powerx, 50));
		powerbar.setPosition(155, 900);

		/*
		****************************************
		Handle the players input
		****************************************
		*/
		
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == (Keyboard::Escape))
				{
					window.close();
				}
				if (event.key.code == (Keyboard::Return))
				{
					start = false;
					playing = true;	
					startbee = true;
				}				
				if (event.key.code == (Keyboard::Up) && playing)
				{
					buzzyAngle -= 1;
					buzzySprite.setRotation(buzzyAngle);
				}
				if (event.key.code == (Keyboard::C) && playing)//test to stop bee
				{
					startbee = false;
				}
				if (event.key.code == (Keyboard::Down) && playing)
				{
					buzzyAngle += 1;
					buzzySprite.setRotation(buzzyAngle);
				}
				if (event.key.code == (Keyboard::Space) && playing)
				{
					dt = clock.restart();
					beedt = dt;
					powerx += 5;
					if (powerx > max)
					{
						powerx = max;
					}
					//printf("%f", powerx);
					powerbar.setSize(sf::Vector2f(powerx, 50));
						
					speed = powerx /90;
				}
			}

			if (event.type == sf::Event::KeyReleased) 
			{
				if (event.key.code == sf::Keyboard::Space && playing)
				{
					//do clock restart
					clock.restart();
					spaceinput = true;
					
				}
			}
		}	
			

		if (spaceinput) //launch
		{
			float x = 0;
			float y = 0;
			dt = clock.getElapsedTime();
			time_fly = dt.asSeconds();

			float prevx = buzzySprite.getPosition().x;
			float prevy = buzzySprite.getPosition().y;
			float newAngle_x = 0;
			float newAngle_y = 0;


			float vX = speed * cos((( buzzyAngle) * 3.14159) / 180);
			float vY = speed * sin((( buzzyAngle) * 3.14159) / 180);
			

			x = prevx + (vX * time_fly);
			y = prevy + (vY * time_fly) + 0.5 * (9.8 * time_fly * time_fly);
			//play aroudn with speed and acc
			//y = 700;
			buzzySprite.setPosition(x, y);
				
			

			//buzzy rotation change
			// You can get buzzy changing angle as it flies by saving the previous (x,y) position
			//  and substracting it from the current position. Use the dx and dy values in the atan2 
			//  to determine the rotation angle.
			newAngle_x = x - prevx;
			newAngle_y = y - prevy;		
			buzzySprite.setRotation((atan2(newAngle_y, newAngle_x)*180)/3.14159);
			
		}	

		/*
		****************************************
		Update the scene
		****************************************
		*/
		//bee
		
		if (startbee) {
			if (!beeActive)
			{
				// How fast is the bee
				srand((int)time(0)* 10);
				//beeSpeed = (rand() % 5) + .7;
				beeSpeed = .5;
				//beeSpeed = 1;
				srand((int)time(0) * 10);
				// How high is the be
				srand((int)time(0) *10);
				float height = (rand() % 200) + 50 ;
				spritesmallbee.setPosition(2000, height);
				beeActive = true;
			}
			else //move bee
			{
				spritesmallbee.setPosition(
					spritesmallbee.getPosition().x -
					(beeSpeed * beedt.asSeconds()),
					spritesmallbee.getPosition().y);

				// Has the bee reached the right hand edge of the screen?
				if (spritesmallbee.getPosition().x < -100)
				{
					// Set it up ready to be a bee next frame
					beeActive = false;
				}
			}
		}

		//collision detectiong
		//for (auto& sprites : animals)
		int uni_idx = 0; // unicorn indx place holder
		for(int j = 0; j < 10; j++)
		{			
			if (Collision::PixelPerfectTest(buzzySprite, animals[j]) )
			{
				//if (unicorn_hit = true && j < uni_idx) //if unicorn was hit and current sprite was above unicorn
				//{
				//	animals[j].setPosition(animals[j].getPosition().x, animals[j].getPosition().y - 120);
				//}
				//when mad unicorn is hit
				if (animals[j].getTexture() == unicornSprite.getTexture())
				{
					unicorn_hit = true;					
					//tprintf("\n****unicorn hit****\n");
					//user gets extra life
					life_count++;
					if (life_count > life_max)
					{
						life_count = life_max; //max life is 5
					}
					animals[j].setPosition(-200, -200); //unicorn disappear
					uni_idx = j;
					//printf("\nunicorn idx = %d\n", uni_idx);

				}
				if (animals[j].getTexture() == tigerSprite.getTexture()) //when tiger hit
				{
					//printf("tiger hit\n");						
					tiger_hit = true;
					score_points += 25;
					points.setString(to_string(score_points));
					
					for (int f = 0; f < 5; f++) 
					{
						animals[idx[f]].setPosition(-200, 0);//ofscreen
					
					}					
					
				}
				if (animals[j].getTexture() == bulldogSprite.getTexture())
				{					
					//printf("bulldog hit\n");
					bullg_hit = true;
					score_points += 25;
					points.setString(to_string(score_points));
					for (int f = 5; f < 10; f++)
					{
						animals[idx[f]].setPosition(-200, 0);//ofscreen
					}
									
				}
				
				
				if (!(animals[j].getTexture() == unicornSprite.getTexture()) && !(animals[j].getTexture() == tigerSprite.getTexture()) && !(animals[j].getTexture() == bulldogSprite.getTexture()))
				{
					//printf("sprite hit **");
					life_count--;
				}
				
				buzzySprite.setPosition(0, 450);
				buzzySprite.setRotation(buzzyAngle);
				speed = 0;
				spaceinput = false;
				powerx = 25;
			}
		}

		// when small bee is hit
		if (Collision::PixelPerfectTest(buzzySprite, spritesmallbee))
		{
			//printf("bee hit \n");
			score_points += 75;
			points.setString(to_string(score_points));
			startbee = false;
			spritesmallbee.setPosition(-200, -100);
			smallbee_hit = true;			
		}
		
		if ((buzzySprite.getPosition().y > 1800) || (buzzySprite.getPosition().y < 0) || (buzzySprite.getPosition().x < 0) || (buzzySprite.getPosition().y > 1800))
		{
			printf("out of bounds");			
			life_count--;
			buzzySprite.setPosition(0, 450);
			buzzySprite.setRotation(buzzyAngle);
			speed = 0;
			spaceinput = false;
			powerx = 25;
		}

		if (life_count == 0) 
		{
			end_game = true;
		}
		if ((tiger_hit && bullg_hit))
		{
			recreate = true;
		}
		if (recreate == true)
		{
			animals_reset[0] = pigSprite;
			animals_reset[1] = mouseSprite;
			animals_reset[2] = unicornSprite;
			animals_reset[3] = bunnySprite;
			animals_reset[4] = frogSprite;
			animals_reset[5] = sheepSprite;
			animals_reset[6] = chickenSprite;
			animals_reset[7] = dogSprite;
			//remake creature columns
			animals_reset[8] = bulldogSprite;
			animals_reset[9] = tigerSprite;

			int idx_reset[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
			int tiger_idx_reset = tig_rand(gen);
			int bull_idx_reset = bull_rand(gen);
			idx_reset[tiger_idx_reset] = 9;
			idx_reset[bull_idx_reset] = 8;
			int nums_reset [8] = {0 ,1, 2, 3, 4, 5, 6, 7 };
			srand(time(0));
			std::random_shuffle(nums_reset, nums_reset + 8);
			j = 0;
			for (int i = 0; i < 10; i++) // 
			{
				int others = nums_reset[j];// assuming this doesnt repeat numbers
				//use random number
				//printf("%d*", others);

				if (idx_reset[i] == 8 || idx_reset[i] == 9)
				{
					//others = nums[i - 1];
					continue;
				}
				if (idx_reset[i] == -1) //space is empty
				{
					idx_reset[i] = others;
					j++;
				}
				
			}
			
			int col = 1400;
			int row = 300;
			animals_reset[idx_reset[0]].setPosition(col, row);
			animals_reset[idx_reset[1]].setPosition(col, row += 120);
			animals_reset[idx_reset[2]].setPosition(col, row += 120);
			animals_reset[idx_reset[3]].setPosition(col, row += 120);
			animals_reset[idx_reset[4]].setPosition(col, row += 120);
			col = 1600;
			row = 300;
			animals_reset[idx_reset[5]].setPosition(col, row);
			animals_reset[idx_reset[6]].setPosition(col, row += 120);
			animals_reset[idx_reset[7]].setPosition(col, row += 120);
			animals_reset[idx_reset[8]].setPosition(col, row += 120);
			animals_reset[idx_reset[9]].setPosition(col, row += 120);
			//printf("\n recreated**");

			//apply reset
			for (int l = 0; l < 10; l++)
			{
				animals[l] = animals_reset[l];
				idx[l] = idx_reset[l];

			//	printf("idx[%d] = %d \n", l, idx[l]);
			}
			//printf("************************\n");

			life_count = life_max;
			tiger_hit = false;
			bullg_hit = false;
			unicorn_hit = false;
			smallbee_hit = false;
			recreate = false;
		}
		/*
		****************************************
		Draw the scene
		****************************************
		*/


		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);
		if (end_game)
		{
			window.draw(end);
			playing = false;
			beeActive = false;

		}
		if (start)
		{
			window.draw(title);
			window.draw(message);			
		}
		
		//drawbee and buzzy
		window.draw(buzzySprite);
		window.draw(spritesmallbee);
		//draw animals
		for (auto& sprites : animals)
		{
			window.draw(sprites);
		}
		//powerbar
		//window.draw(bar);
		window.draw(powerbar);
		window.draw(power);
		window.draw(lives);
		window.draw(score);
		window.draw(points);
		
		for (int f = 0; f < life_count; f++)
		{
			window.draw(life_array[f]);
			//lifeSprite.setPosition(lifeSprite.getPosition().x - 50, 10);
		}
		// Show everything we just drew
		window.display();
	}

	

	return 0;
}


