#include "game_states.h"
#include <string.h>
//#include <time.h>
//#include <mysql.h>
//#include "/usr/include/mysql/mysql.h"

#define DB_HOST "oilsaododge.czrlcuz3fj2o.ap-northeast-2.rds.amazonaws.com"
#define DB_USER "OILSAO"
#define DB_PASS "123456789"
#define DB_NAME "OILSAODODGE"
#define CHOP(x) x[x.length()-1]=' '



void db_insert(int score, std::string id, int id_count);

SDL_Rect item;
SDL_Surface* item_life;
SDL_Surface* item_shield;
SDL_Surface* item_player_speed;
SDL_Surface* item_ball_size;
SDL_Surface* item_ball_speed;
bool item_exist = false;
//const int RANKING_MODE = 3;
int BALL_SIZE = 10;
int ranking();
void save_score(int score, int quick_check);
void make_id();

void menu()
{
	int mode = INITIAL_MODE;
	int level = 0;

	while (mode != EXIT)
	{
		switch (mode)
		{
		case INITIAL_MODE:
			mode = select_mode();
			break;
		case SINGLE_MODE:
			mode = select_level();
			break;
		case MULTI_MODE:
			mode = socketing();
			break;
		case RANKING_MODE:
			mode = showRanking();
			break;
		case SEARCH_MODE:			
			mode=searchRanking();
		default:
			break;
		}
	}
}

int select_mode()
{
	bool quit = false;
	int mode = 0;
	while (quit == false)
	{
		if (SDL_PollEvent(&event))
		{
			apply_surface(0, 0, background, screen);
			title_message = TTF_RenderText_Solid(font2, "Rabbit Dream", textColor);
			apply_surface((640 - title_message->w) / 2, 80, title_message, screen);
			message = TTF_RenderText_Solid(font, "Press space to start, esc key to quit", textColor);
			apply_surface((640 - message->w) / 2, 480 / 2 - message->h, message, screen);
			message = TTF_RenderText_Solid(font, "Single     Multi        Ranking", textColor);
			apply_surface((640 - message->w) / 2, 480 / 2 + message->h, message, screen);
			message2 = TTF_RenderText_Solid(font, "Single     ", textColor);
			int tmp = message2->w;
			message2 = TTF_RenderText_Solid(font, ">", textColor);
			apply_surface((640 - message->w) / 2 - 8 + mode * tmp, 480 / 2 + message->h, message2, screen);
			SDL_Flip(screen);
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
				{
					if (mode >= 2) break;
					mode++;
					break;
				}
				case SDLK_LEFT:
				{
					if (mode <= 0) break;
					mode--;
					break;
				}
				case SDLK_SPACE:
				{
					message = NULL;
					if (mode == 1) return MULTI_MODE;
					else if (mode == 0) return SINGLE_MODE;
					else if (mode == 2) return RANKING_MODE;
					break;
				}
				case SDLK_ESCAPE://esc ?????? ????????? ??????
					return EXIT;
					break;
				default:
					break;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				return EXIT;
				quit = true;
			}
		}
	}
}

int select_level()
{
	bool quit = false;
	int selector = 0;
	while (quit == false)
	{
		if (SDL_PollEvent(&event))
		{
			message = TTF_RenderText_Solid(font, "Press space to start, esc key to quit", textColor);
			apply_surface(0, 0, background, screen);
			title_message = TTF_RenderText_Solid(font2, "Rabbit Dream", textColor);
			apply_surface((640 - title_message->w) / 2, 100, title_message, screen);
			apply_surface((640 - message->w) / 2, 480 / 2 - message->h, message, screen);
			message = TTF_RenderText_Solid(font, "level 1         level 2        level 3", textColor);
			apply_surface((640 - message->w) / 2, 480 / 2 + message->h, message, screen);
			message2 = TTF_RenderText_Solid(font, "level 1         ", textColor);
			int tmp = message2->w;
			message2 = TTF_RenderText_Solid(font, ">", textColor);
			apply_surface((640 - message->w) / 2 - 8 + selector * tmp, 480 / 2 + message->h, message2, screen);
			SDL_Flip(screen);
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
				{
					if (selector >= 2) break;
					selector++;
					break;
				}
				case SDLK_LEFT:
				{
					if (selector <= 0) break;
					selector--;
					break;
				}
				case SDLK_SPACE:
				{
					message = NULL;
					init();
					main_game(selector, SINGLE_MODE);
					return INITIAL_MODE;
					break;
				}
				case SDLK_ESCAPE://esc ?????? ????????? ??????
					return INITIAL_MODE;
					break;
				default:
					break;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				return EXIT;
				quit = true;
			}
		}
	}
}


int ranking()
{


return 2;


}


int socketing()
{
	client = socket(AF_INET, SOCK_STREAM, 0);
	int yes = 1;
	if(setsockopt(client, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) std::cout << "socket setting error" << std::endl;

	if (client < 0)
	{
		std::cout << "\n?????? ?????? ??????..." << std::endl;
	}

	std::cout << "\n=> ?????? ?????? ??????..." << std::endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNum);

	bool isServer = true;
	int count = 0;
	inet_pton(AF_INET, ip, &server_addr.sin_addr);

	bool isConnect = false;
	bool* cntPointer = &isConnect;
	std::thread waitingMassage(waiting, &cntPointer);
	while (true)
	{
		if (connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr)) != -1)
		{
			isServer = false;
			isConnect = true;
			waitingMassage.join();
		}
		count++;
		if (count == 3) break;
	}

	if (isServer)
	{
		inet_pton(AF_INET, "0.0.0.0", &server_addr.sin_addr); // ???????????? 0.0.0.0?????? ?????????

		while ((bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0)
		{
			//std::cout << "=> Error binding connection, the socket has already been established..." << std::endl;
			//count = (count + 1) % 4;

			//std::string str = "Server is Creating, Esc key to quit";
			//message = TTF_RenderText_Solid(font, str.c_str(), textColor);
			//apply_surface(0, 0, background, screen);
			//apply_surface((640 - message->w) / 2, 480 / 2 - message->h, message, screen);
			//SDL_Delay(500);
			//std::string str2 = "Waiting";
			//for (int j = 0; j < count; j++) str2 += " .";
			//message2 = TTF_RenderText_Solid(font, str2.c_str(), textColor);
			//apply_surface((640 - message2->w) / 2, 480 / 2 - message2->h + message->h + 10, message2, screen);
			SDL_Flip(screen);
			if (SDL_PollEvent(&event))
			{
				std::string str = "Server is Creating, Esc key to quit";
				message = TTF_RenderText_Solid(font, str.c_str(), textColor);
				apply_surface(0, 0, background, screen);
				apply_surface((640 - message->w) / 2, 480 / 2 - message->h, message, screen);

				if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE://esc ?????? ????????? ??????
						return INITIAL_MODE;
						break;
					default:
						break;
					}
				}
				else if (event.type == SDL_QUIT)
				{
					return EXIT;
				}
			}
		}
		server_addr.sin_addr.s_addr = htons(INADDR_ANY);

		size = sizeof(server_addr);
		std::cout << "=> Looking for clients..." << std::endl;
		server = -1;

		listen(client, 1);

		std::thread listenFor(waitClient, &cntPointer);

		while (!isConnect)
		{
			if (SDL_PollEvent(&event))
			{
				if (event.type == SDL_KEYDOWN)
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE://esc ?????? ????????? ??????
						isConnect = true;
						int tmp_client;
						tmp_client = socket(AF_INET, SOCK_STREAM, 0);
						inet_pton(AF_INET, ip, &server_addr.sin_addr);
						if (connect(tmp_client, (struct sockaddr*)&server_addr, size) == -1)
						{
							//error message
							std::cout << "Connecting Error!\nServer was not created." << std::endl;
							exit(1);
						}

						
						close(tmp_client);
						close(client);
						close(server);
						listenFor.join();
						waitingMassage.join();
						return INITIAL_MODE;
						break;
					default:
						break;
					}
				}
				else if (event.type == SDL_QUIT)
				{
					return EXIT;
				}
			}
		}
		listenFor.join();
		waitingMassage.join();

		

		buffer_int[0] = (unsigned int)time(NULL);
		send(server, buffer_int, bufsize, 0);
		srand(buffer_int[0]);
		message = NULL;
		init();
		main_game(0, SERVER_MODE);
		listenFor.~thread();
	}
	else
	{
		inet_pton(AF_INET, ip, &server_addr.sin_addr);
		
		std::cout << "?????? ??????!" << std::endl;
		std::cout << "=> ????????? ?????? ?????? ??????: " << portNum << std::endl;
		int iResult;
		struct timeval tv;
		bool timeout = false;
		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(client, &rfds);

		tv.tv_sec = 5;
		tv.tv_usec = 0;

		iResult = select(client + 1, &rfds, (fd_set *)0, (fd_set *)0, &tv);
		if (iResult > 0)
		{
			recv(client, buffer_int, bufsize, 0);
			timeout = true;
		}
		if (!timeout) return INITIAL_MODE;

		srand(buffer_int[0]);
		message = NULL;
		init();
		main_game(0, CLIENT_MODE);
	}

	return INITIAL_MODE;
}

void waiting(bool **isConnect)
{
	int count = 0;
	while (!(**isConnect))
	{
		std::string str = "Waiting";
		for (int j = 0; j < count; j++) str += " .";
		message = TTF_RenderText_Solid(font, str.c_str(), textColor);
		apply_surface(0, 0, background, screen);
		apply_surface((640 - message->w) / 2, 480 / 2 - message->h, message, screen);
		SDL_Flip(screen);
		SDL_Delay(500);
		count = (count + 1) % 4;
	}
}

void waitClient(bool **isConnect)
{
	 server = accept(client, (struct sockaddr *)&server_addr, &size);
	 **isConnect = true;
}

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (screen == NULL)
	{
		return false;
	}

	if (TTF_Init() == -1)
	{
		return false;
	}
	srand(time(NULL));
	SDL_WM_SetCaption("Rabbit Dream", NULL);

	return true;
}

bool load_files()
{

	background = load_image("assets/background.png");
	font = TTF_OpenFont("assets/BMDOHYEON_ttf.ttf", 24);
	font2 = TTF_OpenFont("assets/RaphLanokFuture.otf", 48);

	player = load_image("assets/rabbit.png");
	player2 = SDL_LoadBMP("assets/player2.bmp");
	ball = load_image("assets/ball.png");
	heart = load_image("assets/life.png");
	enemy_heart = SDL_LoadBMP("assets/enemy_heart.bmp");

        //item ?????? ???????????????
        item_life = load_image("assets/life.png");//????????? ?????? ?????????
        item_shield = load_image("assets/shield.png");//????????? ???????????? ????????????
        item_player_speed = load_image("assets/random_box.png");//????????? ???????????? ?????????
	item_ball_size = load_image("assets/mushroom.png");//????????? ???????????? ????????????
	item_ball_speed = load_image("assets/cabbage.png");//????????? ???????????? ????????????

	//item2 ?????? ???????????????
	/* item_ball_del = SDL_LoadBMP("assets/enemy_ball.bmp");//????????? ???????????? ???????????? */
	item_ball_size = load_image("assets/mushroom.png");//????????? ???????????? ????????????
	item_ball_speed = load_image("assets/cabbage.png");//????????? ???????????? ????????????

	if (background == NULL)
	{
		return false;
	}

	if (font == NULL)
	{
		return false;
	}

	return true;
}

void clean_up()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(message);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(ball);

	TTF_CloseFont(font);
	TTF_Quit();

	SDL_Quit();
}

//????????? ???????????? ???????????? ??????
int item_make()

{
	item;//header????????? SDL_Rect?????? ???????????? ??????.
	item.x = BALL_SIZE / 2 + rand() % (SCREEN_WIDTH - BALL_SIZE / 2);
//SCREEN_WIDTH/2;
	item.y = 10;
	item.w = item.h = BALL_SIZE;

        int random;
        srand(time(NULL));
        random = rand()%100+1;

        //item1
        if(random >0 && random <=10) return 1; // ????????? ?????? ????????? ??????
	else if(random >10 && random <=25) return 2; // ?????? ?????????
        else if(random >25 && random <=35) return 3; // ???????????? ?????? ??????
        else if(random >35 && random <=50) return 4; // ???????????? ?????? ??????

        //item2
	else if(random >50 && random <=60) return 5; // ??? ?????? ??????
	else if(random >60 && random <=70) return 6; // ??? ?????? ??????
	else if(random >70 && random <=90) return 7; // ??? ?????? ??????
        else if(random >90 && random <=100) return 8; // ??? ?????? ??????


}






void main_game(int selector, int mode)//????????? ?????? ??????
{
	using namespace std;
	bool quit = false;
	//client side player
	int player_position = SCREEN_WIDTH / 2;
	int player_position_y = SCREEN_HEIGHT - 3;
	//server side player
	int player2_position = SCREEN_WIDTH / 2;
	int player2_position_y = SCREEN_HEIGHT - 3;
	Uint8 *keystates = NULL;
	int start_time = SDL_GetTicks();
	int level = 1 + selector; // level ??????
	int life = 3; // life ??????
	int enemy_life = 3;
	int current_balls = 0;
	int i = 0;
	int Die_Count = 0;

	int fps_timer = 0;
	int delay = 0;
	int frames = 0;
	int fps_calc_timer = SDL_GetTicks();
	int score = 0;

        int item_num = 0;
	int item_check;
        int time2 = SDL_GetTicks();
        int random2 = 0;

	// item1
	int shield_check = 0;
	int shield_start = 0;

	int player_speed_check = 0;
	int player_speed_start = 0;

	int life_check = 0;

	//item2
	int ball_size_check = 0;
	int ball_size_start = 0;

	int ball_speed_check = 0;
	int ball_speed_start = 0;


	int randomball[MAX_BALLS]; // ???????????? ?????? ????????? ???????????? ???????????? ?????? ????????? ??????
	SDL_SetColorKey(heart, SDL_SRCCOLORKEY, SDL_MapRGB(player->format, 255, 255, 255));
	if (mode == SINGLE_MODE) srand((unsigned int)time(NULL)); //in Single Mode set random ball

	for (i = 0; i < MAX_BALLS; i++)
		randomball[i] = 0;

	init_ball();

	while (quit == false)
	{
		for (i = 0; i < current_balls; i++)
		{
			randomball[i] = (double)rand() / RAND_MAX * (level - 1) + BALL_VELOCITY; // ?????? ????????? ?????? ????????? ?????? ??????
			if(ball_speed_check == 1)
				randomball[i] *= 2;
			else if(ball_speed_check == -1)
			randomball[i] *= 0.5;
		}

		fps_timer = SDL_GetTicks();
		if (SDL_GetTicks() - start_time > 1)
		{
			start_time = SDL_GetTicks();
			for (i = 0; i < current_balls; i++)
			{
				balls[i].y += randomball[i];//level????????? ????????? ?????? ?????? level??? ?????????
			}
			item.y+= 1;//item.y ?????? 1??? ???????????? ??????
		}
		if (current_balls < MAX_BALLS)
		{
			for (i = 0; i < MAX_BALLS; i++)
			{
				if (balls[i].y > SCREEN_HEIGHT || balls[i].y == 0)
				{
					SDL_Rect new_ball;
					new_ball.x = BALL_SIZE / 2 + rand() % (SCREEN_WIDTH - BALL_SIZE / 2);
					new_ball.y = -(5 + rand() % 350);
					new_ball.w = new_ball.h = BALL_SIZE;
					balls[i] = new_ball;

				}
			}
			current_balls = MAX_BALLS;
		}
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				balls[0].x = player_position;
				balls[0].y = player_position_y;
				life = 1;
				Die_Count = 0;
			}
		}

		keystates = SDL_GetKeyState(NULL);

		if (keystates[SDLK_ESCAPE])
		{
			balls[0].x = player_position;
			balls[0].y = player_position_y;
			life = 1;
			Die_Count = 0;
		}

		if (keystates[SDLK_LEFT] && player_position > PLAYER_WIDTH / 2)
		{
			if(player_speed_check == 0)
				player_position--;
			else if(player_speed_check == 1)
				player_position -= 2;
			else // player_position == -1
				player_position -= 0.5;

		}
		if (keystates[SDLK_RIGHT] && player_position < SCREEN_WIDTH - PLAYER_WIDTH / 2 && player_speed_check == 0)
		{
			if(player_speed_check == 0)
				player_position++;
			else if(player_speed_check == 1)
				player_position += 2;
			else // player_position == -1
				player_position += 0.5;
		}

		if (keystates[SDLK_UP] && player_position_y > PLAYER_HEIGHT / 2 && player_speed_check == 0)
		{
			if(player_speed_check == 0)
				player_position_y--;
			else if(player_speed_check == 1)
				player_position_y -= 2;
			else // player_position == -1
				player_position_y -= 0.5;
		}

		if (keystates[SDLK_DOWN] && player_position_y < SCREEN_HEIGHT - PLAYER_HEIGHT / 2 && player_speed_check == 0)
		{
			if(player_speed_check == 0)
				player_position_y++;
			else if(player_speed_check == 1)
				player_position_y += 2;
			else // player_position == -1
				player_position_y += 0.5;
		}//??? ?????? ?????? ?????? //???????????? ????????? ???????????? ?????? ?????????.


		apply_surface(0, 0, background, screen);
		if (life == 3) {
			apply_surface(500, 20, heart, screen); apply_surface(540, 20, heart, screen); apply_surface(580, 20, heart, screen);
		}
		// heart decrease as life goes down
		else if (life == 2) {
			apply_surface(540, 20, heart, screen); apply_surface(580, 20, heart, screen);
		}
		else if (life == 1) {
			apply_surface(580, 20, heart, screen);
		}


		if(SDL_GetTicks()-time2 > 1){
		   time2 = SDL_GetTicks();

             	   if(item_exist == false) item_check =0;
             	   else item_check = -1;
		   if((score % 10) == 0  && (item_check == 0)){//????????? ???????????? ???????????? ????????????.

			item_num = item_make();

                        item_exist = true;

		    }

		    //item_num?????? ?????? ????????? ???????????? ????????????.
		    if(item_num == 1){
			   apply_surface(item.x, item.y, item_life, screen);
			   SDL_SetColorKey(item_life, SDL_SRCCOLORKEY, SDL_MapRGB(item_life->format, 255, 255, 255));
		    }
                    else if(item_num ==2){
			   apply_surface(item.x, item.y, item_shield, screen);
			   SDL_SetColorKey(item_shield, SDL_SRCCOLORKEY, SDL_MapRGB(item_shield->format, 255, 255, 255));
}
                    else if(item_num ==3 || item_num ==4){
			   apply_surface(item.x, item.y, item_player_speed, screen);
			     SDL_SetColorKey(item_player_speed, SDL_SRCCOLORKEY, SDL_MapRGB(item_player_speed->format, 255, 255, 255));
		    }
		  else if(item_num ==5 || item_num ==6)
		    {
			   apply_surface(item.x, item.y, item_ball_size, screen);
			   SDL_SetColorKey(item_ball_size, SDL_SRCCOLORKEY, SDL_MapRGB(item_ball_size->format, 255, 255, 255));
		    }
		    else if(item_num ==7 || item_num ==8)
		    {
			   apply_surface(item.x, item.y, item_ball_speed, screen);
			   SDL_SetColorKey(item_ball_speed, SDL_SRCCOLORKEY, SDL_MapRGB(item_ball_speed->format, 255, 255, 255));
		
}
		}


		if (item.y > SCREEN_HEIGHT) item_exist = false;

		for (i = 0; i < MAX_BALLS; i++)
		{
			// printf("ball %i: %i %i\n",i , balls[i].x, balls[i].y);
			apply_surface(balls[i].x, balls[i].y, ball, screen);//????????? ????????? ?????? ??????
			if (balls[i].y > SCREEN_HEIGHT)
			{
				current_balls--;
				score++;
				if (score > LEVEL_UP_COUNT * (level - selector))
				{
					level++;//score??? ????????? ?????? ?????? ??????
				}
			}
			SDL_Rect player_rect;
			SDL_Rect player_rect2;
			player_rect.x = player_position - PLAYER_WIDTH / 2;
			player_rect.y = player_position_y - PLAYER_HEIGHT / 2;
			player_rect.w = PLAYER_WIDTH;
			player_rect.h = PLAYER_HEIGHT;
			player_rect2.x = player2_position - PLAYER_WIDTH / 2;
			player_rect2.y = player2_position_y - PLAYER_HEIGHT / 2;
			player_rect2.w = PLAYER_WIDTH;
			player_rect2.h = PLAYER_HEIGHT;


			if(intersects(item, player_rect)){//??????????????? ???????????? ??????????????? ????????? ??????, ???????????? 1??? ???????????? ????????? ?????? ?????? ??????.
			// item_num??? ????????? ????????? ????????? ???????????? ??????.
				item_exist = false;
			    if(item_num == 1) life_check = 1;
			   //????????? ?????? ??????
         	           else if(item_num ==2){//??????
				shield_check = 1;

				shield_start = SDL_GetTicks();
			   //?????? ?????? --> ????????? ??????????????? ball??? ????????? ????????????????????? player??? life??? ???????????? ?????? ??????.
			  //????????? ??????????????? ????????? ??????????????? ???????????? ???????????? ????????? ??????.
			   }
       		           else if(item_num ==3 || item_num ==4) {
			   //???????????? ?????? ?????? ??????
				int player_speed_random = 0;
				player_speed_random = rand() % 10 + 1;
				if(player_speed_random >0 && player_speed_random <6) player_speed_check = 1;
				else player_speed_check = -1;
				player_speed_start = SDL_GetTicks();
			   }
			else if(item_num ==5 || item_num ==6) {
			   //??? ?????? ?????? ??????
				int ball_size_random = 0;
				ball_size_random = rand() % 10 + 1;
				if(ball_size_random >0 && ball_size_random <6) BALL_SIZE = 15;
				else BALL_SIZE = 5;
				ball_size_start = SDL_GetTicks();	
			   }
			   else if(item_num ==7 || item_num ==8) {
			   //??? ?????? ?????? ??????
				int ball_speed_random = 0;
				ball_speed_random = rand() % 10 + 1;
				if(ball_speed_random >0 && ball_speed_random <6) ball_speed_check = 1;
				else ball_speed_check = -1;
				ball_speed_start = SDL_GetTicks();
}

			}

			if (intersects(balls[i], player_rect) && Die_Count == 0 && shield_check == 0)
			{
				life--;


				if (life <= 0) //life????????? ??????
				{
					if (enemy_life != 0)
						switch (mode)
						{
							//server side
						case SERVER_MODE:
							std::cout << "SERVER SIDE :";
							std::cout << "Last Client: ";
							recv(server, buffer_int, bufsize, 0);
							player2_position = buffer_int[0];
							player2_position_y = buffer_int[1];
							enemy_life = buffer_int[2];
							std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
							buffer_int[0] = player_position;
							buffer_int[1] = player_position_y;
							buffer_int[2] = life;
							std::cout << "Last Server: ";
							std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
							send(server, buffer_int, bufsize, 0);
							break;
							//client side
						case CLIENT_MODE:
							std::cout << "CLIENT SIDE :";
							std::cout << "Last Client: ";
							buffer_int[0] = player_position;
							buffer_int[1] = player_position_y;
							buffer_int[2] = life;
							std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
							send(client, buffer_int, bufsize, 0);
							std::cout << "Last Server: ";
							recv(client, buffer_int, bufsize, 0);
							player2_position = buffer_int[0];
							player2_position_y = buffer_int[1];
							enemy_life = buffer_int[2];
							std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
							break;
						default:
							break;
						}
						close(server);
						close(client);

					if(mode == MULTI_MODE){
						game_over(level, score, LOSER);
						quit = true;

					}
					else if(mode == SINGLE_MODE) {
						game_over(level,score, SINGLE_MODE);
						quit = true;

					}

			}		else //life??? ??????????????? ??? ???????????? ??????
					{
						Die_Count++;
					}
				

			}
		}


		if(SDL_GetTicks() - shield_start >= 1000) shield_check = 0;//???????????? ???????????? shield_check??? 0?????? ??????.
		if(SDL_GetTicks() - player_speed_start >= 1500) player_speed_check = 0;
		if(life_check == 1 && item_exist != false) {
			if(life >=3) life_check = -1;
			else if(life == 2) {life = 3; life_check = -1; }
			else if(life == 1) {life = 2; life_check = -1; }
		}

		if (Die_Count == 0 || Die_Count % 2 == 0)
		{
			if (Die_Count >= 600) Die_Count = 0;
			if (shield_check == 0) {
			   apply_surface(player_position - PLAYER_WIDTH / 2, player_position_y - PLAYER_HEIGHT / 2/*SCREEN_HEIGHT - PLAYER_HEIGHT*/, player, screen);//player????????? ????????? ?????? ??????
			SDL_SetColorKey(player, SDL_SRCCOLORKEY, SDL_MapRGB(player->format, 0, 0, 0));
			}
			else if(shield_check == 1) {//shield??? ???????????? ???????????? player ???????????? ????????? ??????.
			  apply_surface(player_position - PLAYER_WIDTH / 2, player_position_y - PLAYER_HEIGHT / 2/*SCREEN_HEIGHT - PLAYER_HEIGHT*/, heart, screen);//player????????? ????????? ?????? ??????
			  SDL_SetColorKey(player, SDL_SRCCOLORKEY, SDL_MapRGB(player->format, 255, 255, 255));
			}
		}
		if (Die_Count > 0) Die_Count++;

		if ((mode == CLIENT_MODE || mode == SERVER_MODE) && enemy_life > 0)//Socket ?????? ??? ??????
		{
			apply_surface(player2_position - PLAYER_WIDTH / 2, player2_position_y - PLAYER_HEIGHT / 2/*SCREEN_HEIGHT - PLAYER_HEIGHT*/, player2, screen);//player2????????? ????????? ?????? ??????
			SDL_SetColorKey(player2, SDL_SRCCOLORKEY, SDL_MapRGB(player2->format, 255, 255, 255));
			// Present enemy_life on screen
			if (enemy_life == 3) {
			apply_surface(500, 60, enemy_heart, screen); apply_surface(540, 60, enemy_heart, screen); apply_surface(580, 60, enemy_heart, screen);
			}
			else if (enemy_life == 2) {
			apply_surface(540, 60, enemy_heart, screen); apply_surface(580, 60, enemy_heart, screen);
			}
			else if (enemy_life == 1) {
			apply_surface(580, 60, enemy_heart, screen);
			}

		}

		if(SDL_GetTicks() - ball_speed_start >= 1500) ball_speed_check = 0;
		if(SDL_GetTicks() - ball_size_start >= 1500)
		{
			BALL_SIZE = 10;
			ball_size_check = 0;
		}



		std::stringstream caption, caption2;
		caption << /* "FPS: " << (int)(frames*1000.0/(SDL_GetTicks() - fps_calc_timer+1)) << */"Score: " << score
			<< "       Level: " << level;//level ????????? ??????
		message = TTF_RenderText_Solid(font, caption.str().c_str(), textColor);
		caption2 << "Life: " << life;
		message2 = TTF_RenderText_Solid(font, caption2.str().c_str(), textColor);
		if (SDL_GetTicks() - fps_calc_timer > 5000)
		{
			frames = 1;
			fps_calc_timer = SDL_GetTicks();
		}
		apply_surface(10, 10, message, screen);

		SDL_Flip(screen);
		frames++;

		delay = SDL_GetTicks() - fps_timer;

		/*  Socket ????????? ?????? ?????? ??????  */
		if (enemy_life != 0 && life != 0)

			switch (mode)
			{
				//server side
			case SERVER_MODE:
				//std::cout << "Client: ";
				recv(server, buffer_int, bufsize, 0);
				player2_position = buffer_int[0];
				player2_position_y = buffer_int[1];
				enemy_life = buffer_int[2];
				//std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
				buffer_int[0] = player_position;
				buffer_int[1] = player_position_y;
				buffer_int[2] = life;
				caption2 << "Enemy Life: " << enemy_life;
				apply_surface(SCREEN_WIDTH - 10 - message2->w, 10, message2, screen);
				//std::cout << "Server: ";
				//std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
				send(server, buffer_int, bufsize, 0);
				break;

				//client side
			case CLIENT_MODE:
				//std::cout << "Client: ";
				buffer_int[0] = player_position;
				buffer_int[1] = player_position_y;
				buffer_int[2] = life;
				//std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
				send(client, buffer_int, bufsize, 0);
				//std::cout << "Server: ";
				recv(client, buffer_int, bufsize, 0);
				player2_position = buffer_int[0];
				player2_position_y = buffer_int[1];
				enemy_life = buffer_int[2];
				caption2 << "Enemy Life: " << enemy_life;
				apply_surface(SCREEN_WIDTH - 10 - message2->w, 10, message2, screen);
				//std::cout << buffer_int[0] << " " << buffer_int[1] << " " << buffer_int[2] << std::endl;
				break;
			case SINGLE_MODE:
				break;
			}

		if(life != 0 && enemy_life == 0 && (mode == SERVER_MODE || mode == CLIENT_MODE))
		{
			shutdown(client, SHUT_RDWR);
			shutdown(server, SHUT_RDWR);
			close(client);
			close(server);
			game_over(level, score, WINNER);//1 == WIN_CASE
			quit = true;
		}

		if (delay < 1000 / FRAMES_PER_SECOND)
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - delay);
		}
	}

//?????????????????? ????????? ????????????, ????????? ????????? ???????????? ?????? ????????? ??????.
	if(quit == true && mode == SINGLE_MODE) {
		int quick_check = 0;
		save_score(score, quick_check);
	while (true)
		{
			if (SDL_PollEvent(&event))
			{
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
				{
					break;
				}
			}
		}
	int id_ok_check = 0;
	Uint8 *keystates = NULL;
	std::string id = "";
	int id_count =0;

//	if(SDL_PollEvent(&event)) {
		if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
				case SDLK_SPACE: {//make id ??? ???????????? ??????.

				while(id_ok_check == 0) {

/*
					for(int i=0;i<=10;i++) {
					std::stringstream caption;
					string temp = to_string(i);
					apply_surface(0, 0, background, screen);
					message = TTF_RenderText_Solid(font, temp.c_str(), textColor);
					apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 4 - message->h, message, screen);
					SDL_Flip(screen);
					}

*/

				std::stringstream caption;
				caption << "make id (id must in 10 alpabet";
				apply_surface(0, 0, background, screen);
				message = TTF_RenderText_Solid(font, caption.str().c_str(), textColor);
				apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 3 - message->h, message, screen);
				if(id_count ==0){
					message = TTF_RenderText_Solid(font, "no id, yet", textColor);
					apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 3 + message->h, message, screen);
				}
				else {
					apply_surface(0, 0, background, screen);
					message = TTF_RenderText_Solid(font, id.c_str(), textColor);
					apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 3 + message->h, message, screen);
				}
				SDL_Flip(screen);
				if(SDL_PollEvent(&event)) {
				if(event.type == SDL_KEYDOWN) {
				keystates = SDL_GetKeyState(NULL);
				if(keystates[SDLK_a] && id_count <10) {
					id += 'a';
					id_count++;}
				else if(keystates[SDLK_b] && id_count <10){
					id += 'b';
   					id_count++;}
				else if(keystates[SDLK_c] && id_count <10){
					id += 'c';
   					id_count++;}
				else if(keystates[SDLK_d] && id_count <10){
					id += 'd';
   					id_count++;}
				else if(keystates[SDLK_e] && id_count <10){
					id += 'e';
   					id_count++;}
				else if(keystates[SDLK_f] && id_count <10){
					id += 'f';
   					id_count++;}
				else if(keystates[SDLK_g] && id_count <10){
					id += 'g';
   					id_count++;}
				else if(keystates[SDLK_h] && id_count <10){
					id += 'h';
   					id_count++;}
				else if(keystates[SDLK_i] && id_count <10){
					id += 'i';
   					id_count++;}
				else if(keystates[SDLK_j] && id_count <10){
					id += 'j';
   					id_count++;}
				else if(keystates[SDLK_k] && id_count <10){
					id += 'k';
   					id_count++;}
				else if(keystates[SDLK_l] && id_count <10){
					id += 'l';
   					id_count++;}
				else if(keystates[SDLK_m] && id_count <10){
					id += 'm';
   					id_count++;}
				else if(keystates[SDLK_n] && id_count <10){
					id += 'n';
   					id_count++;}
				else if(keystates[SDLK_o] && id_count <10){
					id += 'o';
   					id_count++;}
				else if(keystates[SDLK_p] && id_count <10){
					id += 'p';
   					id_count++;}
				else if(keystates[SDLK_q] && id_count <10){
					id += 'q';
   					id_count++;}
				else if(keystates[SDLK_r] && id_count <10){
					id += 'r';
   					id_count++;}
				else if(keystates[SDLK_s] && id_count <10){
					id += 's';
   					id_count++;}
				else if(keystates[SDLK_t] && id_count <10){
					id += 't';
   					id_count++;}
				else if(keystates[SDLK_u] && id_count <10){
					id += 'u';
   					id_count++;}
				else if(keystates[SDLK_v] && id_count <10){
					id += 'v';
   					id_count++;}
				else if(keystates[SDLK_w] && id_count <10){
					id += 'w';
   					id_count++;}
				else if(keystates[SDLK_x] && id_count <10){
					id += 'x';
   					id_count++;}
				else if(keystates[SDLK_y] && id_count <10){
					id += 'y';
   					id_count++;}
				else if(keystates[SDLK_z] && id_count <10){
					id += 'z';
   					id_count++;}
				//????????????
				else if(keystates[SDLK_0] && id_count <10){
					id += '0';
   					id_count++;}
				else if(keystates[SDLK_1] && id_count <10){
					id += '1';
   					id_count++;}
				else if(keystates[SDLK_2] && id_count <10){
					id += '2';
   					id_count++;}
				else if(keystates[SDLK_3] && id_count <10){
					id += '3';
   					id_count++;}
				else if(keystates[SDLK_4] && id_count <10){
					id += '4';
   					id_count++;}
				else if(keystates[SDLK_5] && id_count <10){
					id += '5';
   					id_count++;}
				else if(keystates[SDLK_6] && id_count <10){
					id += '6';
   					id_count++;}
				else if(keystates[SDLK_7] && id_count <10){
					id += '7';
   					id_count++;}
				else if(keystates[SDLK_8] && id_count <10){
					id += '8';
   					id_count++;}
				else if(keystates[SDLK_9] && id_count <10){
					id += '9';
   					id_count++;}
				//backspace ????????? ????????? ?????? ??????
				else if(keystates[SDLK_BACKSPACE]){
					std::string temp = id;
					id_count--;
					id = temp.substr(0, id_count);}
				//Enter ????????? ??????
				else if(keystates[SDLK_RETURN]){
					id_ok_check = 1;
					break;
				}
				//ESC????????? ??????
				else if(keystates[SDLK_ESCAPE]){
					break;}
}


	
				}//if(event.type == SDL_KEYDOWN)??? ?????? ?????? (AAAAAAAA????????????)
				}//while?????? ?????? ?????? --> ????????? ????????? ??????


				//id??? ?????? ????????????
				if(id_ok_check == 1){
					db_insert(score, id, id_count);
				}

				}//if(event.type == SDL_KEYDOWN)??? ?????? ?????? (make id????????????)

				}//case sdlk_space ?????? ??????

				//case SDLK_DOWN: {}

			}
		}
//	}



	}




void init_ball()
{
	for (int i = 0; i < MAX_BALLS; i++)
	{
		SDL_Rect new_ball;
		new_ball.x = BALL_SIZE / 2 + rand() % (SCREEN_WIDTH - BALL_SIZE / 2);
		new_ball.y = -(5 + rand() % 350);
		new_ball.w = new_ball.h = BALL_SIZE;
		balls[i] = new_ball;
SDL_SetColorKey(ball, SDL_SRCCOLORKEY, SDL_MapRGB(player->format, 255, 255, 255));
	}
}

void game_over(int level, int score, int state)
{
	std::stringstream caption;
	std::stringstream caption2;
	std::stringstream caption3;
	std::stringstream temp;
	switch (state)
	{
		//SINGLE_MODE
		case SINGLE_MODE:
		apply_surface(0, 0, background, screen);
		message = TTF_RenderText_Solid(font, "Game over", textColor);
		apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 - message->h, message, screen);
		caption << "Level : " << level;
		message = TTF_RenderText_Solid(font, caption.str().c_str(), textColor);
		apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 + message->h, message, screen);
		caption2 << "Score is : " << score;
		message = TTF_RenderText_Solid(font, caption2.str().c_str(), textColor);
		apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 + message->h + 50, message, screen);
		caption3 << "If you want to save score, press space bar";
		message = TTF_RenderText_Solid(font, caption3.str().c_str(), textColor);
		apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 + message->h + 100, message, screen);
		SDL_Flip(screen);
		break;
		// 1 == WIN_CASE
		case WINNER:
		apply_surface(0, 0, background, screen);
		message = TTF_RenderText_Solid(font, "! ! ! YOU WIN ! ! !", textColor);
		apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 - message->h, message, screen);
		SDL_Flip(screen);
		break;
		// 2 == LOSE_CASE
		case LOSER:
		apply_surface(0, 0, background, screen);
		message = TTF_RenderText_Solid(font, "( T . T ) YOU LOSE ( T . T )", textColor);
		apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 - message->h, message, screen);
		SDL_Flip(screen);
		break;
	}
/*
	if(state !=SINGLE_MODE) {
		while (true)
		{
			if (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT ||
					(event.type == SDL_KEYDOWN &&
					(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_ESCAPE)))
				{
					break;
				}
			}
		}
	}
	else if(state == SINGLE_MODE) {;


	}
*/
}


//????????? ?????? ???
void save_score(int score, int quit_check) {
	std::stringstream caption;
	std::stringstream caption2;
	std::stringstream caption3;
	std::stringstream caption4;


	apply_surface(0, 0, background, screen);
	message = TTF_RenderText_Solid(font, "Game over", textColor);
	apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 - message->h, message, screen);
	caption2 << "Score is : " << score;
	message = TTF_RenderText_Solid(font, caption2.str().c_str(), textColor);
	apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 + message->h + 50, message, screen);
	caption << "save the ID & score --> space bar";
	message = TTF_RenderText_Solid(font, caption.str().c_str(), textColor);
	apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 + message->h, message, screen);
//	caption3 << "quit --> ESC";
//	message = TTF_RenderText_Solid(font, caption3.str().c_str(), textColor);
//	apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 + message->h, message, screen);

	SDL_Flip(screen);

	int id_make_ok =0;
	int quit_timer=0;


}

//????????? ????????? ??? ?????? ???????????? ??????.
void make_id() {

	std::stringstream caption;
	std::stringstream caption2;
	std::stringstream caption3;
	std::stringstream caption4;


	apply_surface(0, 0, background, screen);
	message = TTF_RenderText_Solid(font, "make_id_fuction", textColor);
	apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 - message->h, message, screen);

	SDL_Flip(screen);

}

//????????? ????????? ?????????, SAVE ????????? ????????????, ???????????? 10?????? ????????? ????????? ????????? ????????? ?????? ???????????? ????????????.


//db????????? ????????????, db??? ???????????? ????????? ????????????.
void db_insert(int score, std::string id, int id_count) {
	MYSQL *conn = NULL;
	MYSQL *connection = NULL;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;

/*
	char* server = "localhost";
	char* user="OILSAO";
	char* password="123456789";
	char* database="OILSAODODGE";
*/
	if(!(conn = mysql_init((MYSQL*)NULL))){
		//????????? ??????. ????????? ?????????.
		exit(1);
	}



	char* id_char = new char[id_count];
	//string??? id??? char ???????????? ????????????.
	for(int i=0; i<id_count; i++) {

		id_char[i] = id[i];

	}

	std::cout <<"id = " <<id <<std::endl;

	connection = mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);
	if(connection == NULL){
		std::cout <<"\n????????? ????????? ?????? ??????..."<<mysql_error(conn) << std::endl;
	}
	else
		std::cout<<"?????????????????? ?????? ??????.."<<std::endl;


	int queryStart;
	queryStart = mysql_query(connection, "select * from DodgeRank");
	if(queryStart!=0){std::cout<<"?????? ?????? ??????"<<std::endl;fprintf(stderr, "Mysql query error : %s", mysql_error(conn));}
	else{std::cout<<"?????? ?????? ??????"<<std::endl;}


	sql_result = mysql_store_result(connection);

	apply_surface(0,0,background,screen);

	int number_count=0;	

	while((sql_row=mysql_fetch_row(sql_result))!=NULL){
		number_count++;
	}

	mysql_free_result(sql_result);


	char query[255];
	//OILSAODODGE??? db ?????? ?????? id??? score??? ????????????.
	//sprintf ??????.
	//db???????????? ?????? ????????? ????????? ??? ???????????? ???????????? ??????.

	char arr[10];

	for(int a=0;a<10-id.length();a++)
		id[id.length()+a] = ' ';
	
	sprintf(query, "insert into DodgeRank values" "('%d', '%d', '%c%c%c%c%c%c%c%c%c%c')", number_count+1 , score, id[0],id[1],id[2],id[3],id[4],id[5],id[6],id[7],id[8],id[9]);

	std::cout <<"id = " <<id<<std::endl;

	queryStart=mysql_query(connection, query);
	if(queryStart != 0) {
		fprintf(stderr,"Mysql query error : %s", mysql_error(conn));
	}

	mysql_close(connection);


	

}

int checki=0;
int i=0;

int showRanking(){
	bool quit = false;
	int rankmode = 0;
	while(quit == false)
	{
		if(SDL_PollEvent(&event))
		{
  			MYSQL *conn =NULL;
			MYSQL* connection=NULL;
  			MYSQL_RES *sql_result;
			MYSQL_ROW sql_row;
			//conn = mysql_init((MYSQL*)NULL);
			std::string DBtoArr[1000][3];
			if(!(conn = mysql_init((MYSQL*)NULL))){
				//????????? ??????. ????????? ?????????.
				//return -1;
				exit(1);
			}
			connection = mysql_real_connect(conn,DB_HOST,DB_USER, DB_PASS,DB_NAME, 3306, (char *)NULL, 0);
			if(connection==NULL){
				std::cout << "\n????????? ????????? ?????? ??????..."<<mysql_error(conn) << std::endl;
				//printf(stderr, "connect error : %s\n", mysql_error(conn));//DB?????? ??????.
				//return -1;
				//exit(1);
			}
			else std:: cout<<"?????????????????? ?????? ??????.."<<std::endl;


			//OILSAODODGE ????????? ??????????????? ?????? ????????? ????????????.
			int queryStart;
			//connection = mysql_real_connect(conn,DB_HOST,DB_USER, DB_PASS,DB_NAME, 3306, (char *)NULL, 0);
			queryStart=mysql_query(connection,"select * from DodgeRank ORDER BY score DESC");
			if(queryStart!=0){std::cout<<"?????? ?????? ??????"<<std::endl;fprintf (stderr,"Mysql query error : %s", mysql_error(conn));}
			else{std::cout<<"?????? ?????? ??????"<<std::endl;}

			sql_result=mysql_store_result(connection);

			apply_surface(0,0,background,screen);
			message=TTF_RenderText_Solid(font, "RANKING", textColor);
			apply_surface((SCREEN_WIDTH-message->w)/2,SCREEN_HEIGHT/2-message->h-150,message,screen);

			message=TTF_RenderText_Solid(font, "RANK", textColor);
			apply_surface((SCREEN_WIDTH-message->w)/5,SCREEN_HEIGHT/2-message->h-50,message,screen);
			message=TTF_RenderText_Solid(font, "SCORE", textColor);
			apply_surface((SCREEN_WIDTH-message->w)/2,SCREEN_HEIGHT/2-message->h-50,message,screen);
			message=TTF_RenderText_Solid(font, "ID", textColor);
			apply_surface((SCREEN_WIDTH-message->w)/2+200,SCREEN_HEIGHT/2-message->h-50,message,screen);

			std::string caption[10];
			int lrank=0;

			int j = 0;
			while((sql_row=mysql_fetch_row(sql_result)) != NULL){	//DB ????????? ????????? ????????? ??????
				DBtoArr[j][0]=j+1;
				DBtoArr[j][1]=sql_row[1];
				DBtoArr[j][2]=sql_row[2];
				j++;
			}
			while(lrank < 3) {
				int rank1 = i+1;
				caption[i]=std::to_string(rank1);
				message = TTF_RenderText_Solid(font, caption[i].c_str(), textColor);
				apply_surface((SCREEN_WIDTH-message->w)/5,SCREEN_HEIGHT/2-message->h+50*lrank,message,screen);
				caption[i];
				caption[i]=DBtoArr[i][1];
				message = TTF_RenderText_Solid(font, caption[i].c_str(), textColor);
				apply_surface((SCREEN_WIDTH-message->w)/2,SCREEN_HEIGHT/2-message->h+50*lrank,message,screen);
				caption[i];
				caption[i]=DBtoArr[i][2];
				message = TTF_RenderText_Solid(font, caption[i].c_str(), textColor);
				apply_surface((SCREEN_WIDTH-message->w)/2+200,SCREEN_HEIGHT/2-message->h+50*lrank,message,screen);
				i++;
				lrank++;
				}
			//}
			message = TTF_RenderText_Solid(font,  "Search           Exit", textColor);
			apply_surface((SCREEN_WIDTH-message->w)/2,SCREEN_HEIGHT/2-message->h+180,message,screen);
			message2 = TTF_RenderText_Solid(font, "Search           ", textColor);
			int tmp = message2->w;
			message2 = TTF_RenderText_Solid(font, ">", textColor);
			apply_surface((SCREEN_WIDTH-message->w)/2-8+rankmode*tmp,SCREEN_HEIGHT/2-message->h+180,message2,screen);

	// message = TTF_RenderText_Solid(font, "Game over", textColor);
	// apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 - message->h, message, screen);
	// caption2 << "Score is : " << score;
	// message = TTF_RenderText_Solid(font, caption2.str().c_str(), textColor);
	// apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 + message->h + 50, message, screen);
	// caption << "save the ID & scroe --> space bar";
	// message = TTF_RenderText_Solid(font, caption.str().c_str(), textColor);
	// apply_surface((SCREEN_WIDTH - message->w) / 2, SCREEN_HEIGHT / 2 + message->h, message, screen);
			SDL_Flip(screen);
			mysql_close(conn);

			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
				case SDLK_UP:
				{
					if(checki < 3)
					{
						i = 0;
						break;
					}
					else
					{
						i = 0;
						checki -= 3;
						i += checki;
						break;
					}
				}
				case SDLK_DOWN:
				{
					if(checki > j-9)
					{
						i = 0;
						checki = 0;
						break;
					}
					else
					{
						i = 0;
						checki += 3;
						i += checki;
						break;
					}
				}
				case SDLK_RIGHT:
				{
					if(rankmode >= 1) break;
					rankmode++;
					i = 0;
					break;
				}
				case SDLK_LEFT:
				{
					if(rankmode <= 0) break;
					rankmode--;
					i = 0;
					break;
				}
				case SDLK_SPACE:
				{
					message = NULL;
					if(rankmode == 0) {printf("searchmode\n");return SEARCH_MODE;}
					else if(rankmode == 1) {printf("initialmode\n");return INITIAL_MODE;}
					i = 0;
					checki = 0;
					break;
				}
				case SDLK_ESCAPE:
					return EXIT;
					break;
				default:
					break;
				}
			}
			else if(event.type == SDL_QUIT)
			{
				return EXIT;
				quit = true;
			}

		}
	}
}


int searchRanking(){

	 bool quit=false;
		SDL_Flip(screen);
		int id_ok_check = 0;
		Uint8 *keystates = NULL;
		char* id =new char[10];
		for(int i=0;i<10;i++)id[i]=' ';
		int id_count =0;

		MYSQL *conn =NULL;
		MYSQL* connection=NULL;
		MYSQL_RES *sql_result;
		MYSQL_ROW sql_row;
		//conn = mysql_init((MYSQL*)NULL);
		std::string DBtoArr[100][3];
		if(!(conn = mysql_init((MYSQL*)NULL))){
			//????????? ??????. ????????? ?????????.
			//return -1;
			exit(1);
		}



while(quit==false){

			if(event.type == SDL_KEYDOWN) {

					while(id_ok_check == 0) {

					std::stringstream caption;

						apply_surface(0, 0, background, screen);
						message=TTF_RenderText_Solid(font, "Search: ", textColor);
						apply_surface((SCREEN_WIDTH - message->w) / 3, SCREEN_HEIGHT / 3 + message->h, message, screen);
						message = TTF_RenderText_Solid(font, id, textColor);
						apply_surface((SCREEN_WIDTH - message->w) / 2+100, SCREEN_HEIGHT / 3 + message->h, message, screen);

				  	SDL_Flip(screen);
					 if(SDL_PollEvent(&event)) {
					if(event.type == SDL_KEYDOWN) {
					keystates = SDL_GetKeyState(NULL);
					if(keystates[SDLK_a] && id_count <10) {
						id[id_count] = 'a';
						id_count++;}
					else if(keystates[SDLK_b] && id_count <10){
					id[id_count] = 'b';
							id_count++;}
					else if(keystates[SDLK_c] && id_count <10){
						id[id_count] = 'c';
							id_count++;}
					else if(keystates[SDLK_d] && id_count <10){
					id[id_count] = 'd';
							id_count++;}
					else if(keystates[SDLK_e] && id_count <10){
						id[id_count] = 'e';
							id_count++;}
					else if(keystates[SDLK_f] && id_count <10){
						id[id_count] = 'f';
							id_count++;}
					else if(keystates[SDLK_g] && id_count <10){
						id[id_count] = 'g';
							id_count++;}
					else if(keystates[SDLK_h] && id_count <10){
						id[id_count] = 'h';
							id_count++;}
					else if(keystates[SDLK_i] && id_count <10){
						id[id_count] = 'i';
							id_count++;}
					else if(keystates[SDLK_j] && id_count <10){
						id[id_count] ='j';
							id_count++;}
					else if(keystates[SDLK_k] && id_count <10){
						id[id_count] = 'k';
							id_count++;}
					else if(keystates[SDLK_l] && id_count <10){
						id[id_count] = 'l';
							id_count++;}
					else if(keystates[SDLK_m] && id_count <10){
						id[id_count] = 'm';
							id_count++;}
					else if(keystates[SDLK_n] && id_count <10){
						id[id_count] = 'n';
							id_count++;}
					else if(keystates[SDLK_o] && id_count <10){
						id[id_count] = 'o';
							id_count++;}
					else if(keystates[SDLK_p] && id_count <10){
						id[id_count] = 'p';
							id_count++;}
					else if(keystates[SDLK_q] && id_count <10){
						id[id_count] = 'q';
							id_count++;}
					else if(keystates[SDLK_r] && id_count <10){
					id[id_count] = 'r';
							id_count++;}
					else if(keystates[SDLK_s] && id_count <10){
						id[id_count] = 's';
							id_count++;}
					else if(keystates[SDLK_t] && id_count <10){
						id[id_count] = 't';
							id_count++;}
					else if(keystates[SDLK_u] && id_count <10){
						id[id_count] = 'u';
							id_count++;}
					else if(keystates[SDLK_v] && id_count <10){
					id[id_count] = 'v';
							id_count++;}
					else if(keystates[SDLK_w] && id_count <10){
					id[id_count] = 'w';
							id_count++;}
					else if(keystates[SDLK_x] && id_count <10){
						id[id_count] = 'x';
							id_count++;}
					else if(keystates[SDLK_y] && id_count <10){
						id[id_count] = 'y';
							id_count++;}
					else if(keystates[SDLK_z] && id_count <10){
						id[id_count] = 'z';
							id_count++;}
					//????????????
					else if(keystates[SDLK_0] && id_count <10){
						id[id_count] = '0';
							id_count++;}
					else if(keystates[SDLK_1] && id_count <10){
						id[id_count] = '1';
							id_count++;}
					else if(keystates[SDLK_2] && id_count <10){
						id[id_count] = '2';
							id_count++;}
					else if(keystates[SDLK_3] && id_count <10){
						id[id_count] = '3';
							id_count++;}
					else if(keystates[SDLK_4] && id_count <10){
					id[id_count] = '4';
							id_count++;}
					else if(keystates[SDLK_5] && id_count <10){
						id[id_count] = '5';
							id_count++;}
					else if(keystates[SDLK_6] && id_count <10){
						id[id_count] = '6';
							id_count++;}
					else if(keystates[SDLK_7] && id_count <10){
						id[id_count] = '7';
							id_count++;}
					else if(keystates[SDLK_8] && id_count <10){
					id[id_count] = '8';
							id_count++;}
					else if(keystates[SDLK_9] && id_count <10){
					id[id_count] = '9';
							id_count++;}
					//backspace ????????? ????????? ?????? ??????
					else if(keystates[SDLK_BACKSPACE]){
						std::string temp = id;
						id_count--;
						id[id_count]=' ';
						//id = temp.substr(0, id_count);
					}
					//Enter ????????? ??????
					else if(keystates[SDLK_RETURN]){
						//OILSAODODGE ????????? ??????????????? ?????? ????????? ????????????.
						std::cout<<id<<"DB ??????"<<std::endl;
						connection = mysql_real_connect(conn,DB_HOST,DB_USER, DB_PASS,DB_NAME, 3306, (char *)NULL, 0);
						if(connection==NULL){
							std::cout << "\n????????? ????????? ?????? ??????..."<<mysql_error(conn) << std::endl;
							//printf(stderr, "connect error : %s\n", mysql_error(conn));//DB?????? ??????.
							//return -1;
							//exit(1);
						}
						else std:: cout<<"?????????????????? ?????? ??????.."<<std::endl;

						char buff[255];
						sprintf(buff, "select * from DodgeRank WHERE player_id = '%c%c%c%c%c%c%c%c%c%c'", id[0],id[1],id[2],id[3],id[4],id[5],id[6],id[7], id[8],id[9]);


						 int queryStart=mysql_query(connection,buff);
						if(queryStart!=0){std::cout<<"?????? ?????? ??????"<<std::endl;fprintf (stderr,"Mysql query error : %s", mysql_error(conn));}
						else{std::cout<<"?????? ?????? ??????"<<std::endl;}
						sql_result=mysql_store_result(connection);
						std::string caption[10];
						int lrank=0;

						int j = 0;

					while(quit==false){
						apply_surface(0, 0, background, screen);
						message=TTF_RenderText_Solid(font, "Search RESULT: ", textColor);
						apply_surface((SCREEN_WIDTH-message->w)/2,SCREEN_HEIGHT/3-message->h,message,screen);

						while((sql_row=mysql_fetch_row(sql_result)) != NULL){	//DB ????????? ????????? ????????? ??????
							message=TTF_RenderText_Solid(font, sql_row[2], textColor);
							apply_surface((SCREEN_WIDTH-message->w)/2-50,SCREEN_HEIGHT/2-message->h+50*j,message,screen);
							message=TTF_RenderText_Solid(font, sql_row[1], textColor);
							apply_surface((SCREEN_WIDTH-message->w)/2+50,SCREEN_HEIGHT/2-message->h+50*j,message,screen);
							j++;
						}

						if(j==0){
							message = TTF_RenderText_Solid(font, "No Result", textColor);
							apply_surface((SCREEN_WIDTH-message->w)/2+200,SCREEN_HEIGHT/2-message->h+50*lrank,message,screen);
						}

							mysql_close(conn);
							SDL_Flip(screen);

						if(SDL_PollEvent(&event)){
							quit=true;
							if(event.type == SDL_KEYDOWN){
								if(keystates[SDLK_RETURN])
									return RANKING_MODE;
						}
					}}
						break;
					}
					//ESC????????? ??????
					else if(keystates[SDLK_ESCAPE]){
						break;}


					}//if(event.type == SDL_KEYDOWN)??? ?????? ?????? (AAAAAAAA????????????)

					}//while?????? ?????? ?????? --> ????????? ????????? ??????

					}//if(event.type == SDL_KEYDOWN)??? ?????? ?????? (make id????????????)

					}//case sdlk_space ?????? ??????

				}

return RANKING_MODE;
}
