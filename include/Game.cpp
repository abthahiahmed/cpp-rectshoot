#include "Game.h"

Game::Game(){
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	this->win = SDL_CreateWindow("Rect Shoot | Abthahi Ahmed Rifat", 100, 100, 510, 700, SDL_WINDOW_SHOWN);
	this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_SOFTWARE);
	SDL_SetRenderDrawBlendMode(this->ren, SDL_BLENDMODE_BLEND);
	
}

char getColor(int a){
	char rectT;
	
	if (a == 0) rectT = 'r';
	else if (a == 1) rectT = 'y';
	else if (a == 2) rectT = 'b';
	else if (a == 3) rectT = 'g';
	
	return rectT;
}


void Game::drawText(int x, int y, int font_size, string text, SDL_Color color){
	
	TTF_Font *font = TTF_OpenFont(this->font_path.c_str(), font_size);
	
	SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(this->ren, surface);
	
	SDL_Rect rect = {x, y, surface->w, surface->h};
	
	SDL_RenderCopy(this->ren, texture, NULL, &rect);
	
	TTF_CloseFont(font);
	SDL_FreeSurface(surface);
	
}

void Game::drawTextCenter(int x, int y, int font_size, string text, SDL_Color color){
	
	TTF_Font *font = TTF_OpenFont(this->font_path.c_str(), font_size);
	
	SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(this->ren, surface);
	
	SDL_Rect rect = {x - surface->w / 2, y, surface->w, surface->h};
	
	SDL_RenderCopy(this->ren, texture, NULL, &rect);
	
	TTF_CloseFont(font);
	SDL_FreeSurface(surface);
	
}


void Game::setup(){
	
	
	this->isRunning = true;
	this->fps = 60;
	
	this->bgColor = {29, 53, 87};
	
	
	SDL_GetRendererOutputSize(this->ren, &this->width, &this->height);
	
	this->rectColors.push_back({239, 35, 60}); // Red
	this->rectColors.push_back({255, 190, 11}); // Yellow
	this->rectColors.push_back({58, 134, 255}); // Blue
	this->rectColors.push_back({85, 166, 48}); // Green
	
	this->fontColors.push_back({239, 255, 255}); // white(ish)

	this->lvl = 1;
	this->score = 0;
	
	for (int i = 0; i < 23; i++){
		for (int j = 0; j < 18; j++){
			this->field[i][j] = this->lvl1[i][j];
		}
	}
	
	this->rect_lvl = {3, 3, 0, 3, 1 , 1, 2, 0, 0, 3, 3, 1, 2, 0, 0, 2, 1, 1, 3, 0, 0, 1, 1, 0, 0, 2, 2};
	
	
	
	for (int my = 0; my < 23; ++my)
		for (int mx = 0; mx < 18; ++mx){
			
			if (this->field[my][mx] == '#')
				this->bounds.push_back(Bound(mx * 30 + 15, my * 30 + 15));
			if (this->field[my][mx] == '=')
				this->bounds.push_back(Bound(mx * 30 + 15, my * 30 + 15));
				
			if (this->field[my][mx] == 'r')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[0], 'r'));
			if (this->field[my][mx] == 'y')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[1], 'y'));
			if (this->field[my][mx] == 'b')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[2], 'b'));
			if (this->field[my][mx] == 'g')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[3], 'g'));
			
		}

	this->current = 1;

	int colorIndex = this->rect_lvl[this->current - 1];
	
	this->rects.push_back(Rect(this->width/2, this->height-100, this->rectColors[colorIndex], getColor(colorIndex)));
	
	this->lastRect = this->rects.size() - 1;
	
	this->isAssembled = true;
	
	this->font_path = "fonts/Saira-Regular.ttf";
	
	this->isGameOver = false;
	this->isGameDone = false;

}
void Game::start(){
	
	this->run();
	
}

void Game::nextLVL(){

	this->rects.clear();
	this->bounds.clear();
	this->current = 1;
	
	this->rect_lvl.clear();
	
	for (int i = 0; i < 23; i++){
		for (int j = 0; j < 18; j++){
			switch(this->lvl){
				case 2:
					this->rect_lvl = {2, 2, 2, 0, 0, 3, 0, 3, 0, 1, 3, 3, 1};
					this->field[i][j] = this->lvl2[i][j];
					break;
				case 3:
					this->field[i][j] = this->lvl3[i][j];
					this->rect_lvl = {2, 2, 1, 0,0, 2, 1, 0, 0, 0};
					break;	
				case 4:
					this->field[i][j] = this->lvl4[i][j];
					this->rect_lvl = {0, 3, 0, 3, 1, 1, 3, 3};
					break;
				case 5:
					this->field[i][j] = this->lvl5[i][j];
					this->rect_lvl = {2, 2, 2, 0, 0, 3, 0, 3, 0, 1, 3, 3, 1};
					break;				
			}
		}
	}
	


	
	for (int my = 0; my < 23; ++my)
		for (int mx = 0; mx < 18; ++mx){
			
			if (this->field[my][mx] == '#')
				this->bounds.push_back(Bound(mx * 30 + 15, my * 30 + 15));
			if (this->field[my][mx] == '=')
				this->bounds.push_back(Bound(mx * 30 + 15, my * 30 + 15));
				
			if (this->field[my][mx] == 'r')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[0], 'r'));
			if (this->field[my][mx] == 'y')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[1], 'y'));
			if (this->field[my][mx] == 'b')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[2], 'b'));
			if (this->field[my][mx] == 'g')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[3], 'g'));
			
		}

	
	int colorIndex = this->rect_lvl[this->current - 1];
	this->rects.push_back(Rect(this->width/2, this->height-100, this->rectColors[colorIndex], getColor(colorIndex)));
	
	
	this->lastRect = this->rects.size() - 1;
	
	this->isAssembled = true;
	
	
}

void Game::reset(){
	
	this->rects.clear();
	this->bounds.clear();
	this->current = 1;
	
	this->lvl = 1;
	this->score = 0;
	
	
	for (int i = 0; i < 23; i++){
		for (int j = 0; j < 18; j++){
			this->field[i][j] = this->lvl1[i][j];
		}
	}
	
	this->rect_lvl = {3, 3, 0, 3, 1 , 1, 2, 0, 0, 3, 3, 1, 2, 0, 0, 2, 1, 1, 3, 0, 0, 1, 1, 0, 0, 2, 2};
	
	
	
	for (int my = 0; my < 23; ++my)
		for (int mx = 0; mx < 18; ++mx){
			
			if (this->field[my][mx] == '#')
				this->bounds.push_back(Bound(mx * 30 + 15, my * 30 + 15));
			if (this->field[my][mx] == '=')
				this->bounds.push_back(Bound(mx * 30 + 15, my * 30 + 15));
				
			if (this->field[my][mx] == 'r')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[0], 'r'));
			if (this->field[my][mx] == 'y')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[1], 'y'));
			if (this->field[my][mx] == 'b')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[2], 'b'));
			if (this->field[my][mx] == 'g')
				this->rects.push_back(Rect(mx * 30 + 15, my * 30 + 15, this->rectColors[3], 'g'));
			
		}

	this->current = 1;
	
	int colorIndex = this->rect_lvl[this->current - 1];
	
	this->rects.push_back(Rect(this->width/2, this->height-100, this->rectColors[colorIndex], getColor(colorIndex)));
	
	this->lastRect = this->rects.size() - 1;
	
	this->isAssembled = true;
	
	this->isGameOver = false;
	this->isGameDone = false;
	
	
	
}

void Game::run(){
	
	while(this->isRunning){
		
		SDL_SetRenderDrawColor(this->ren, this->bgColor.r, this->bgColor.g, this->bgColor.b, 255);
		SDL_RenderClear(this->ren);
		
		this->update();
		this->draw();
		this->handleEvent();
		
		SDL_RenderPresent(this->ren);
		SDL_Delay(1000/this->fps);
	}
}

void Game::handleEvent(){
	
	SDL_GetMouseState(&this->mouseX, &this->mouseY);
	
	while(SDL_PollEvent(&this->event)){
		if (this->event.type == SDL_QUIT){
			this->isRunning = false;
		}
		
		if (this->event.type == SDL_MOUSEBUTTONDOWN){
			if (!this->isGameOver && !this->isGameDone){
				this->rects[this->lastRect].shoot(this->mouseX, this->mouseY);
				this->isAssembled = false;
			}
		}
		
		if (this->event.type == SDL_KEYDOWN){
			
			switch(this->event.key.keysym.sym){
				
				case SDLK_RETURN:
					if (this->isGameDone){
						this->lvl++;
						this->isGameDone = false;
						this->nextLVL();
					}
					if (this->isGameOver){
						this->reset();
					}
					break;
				
			}
		}		
	}
	
}


void Game::draw(){
	

	
	int sx = this->width / 2;
	int sy = this->height - 100;
	
	int dx = sx - this->mouseX;
	int dy = sy - this->mouseY;
	
	float d = sqrt(pow(dx, 2) + pow(dy, 2));

	float tx = dx / d * -1;
	float ty = dy / d * -1;
	
	cout<<tx<<ty<<endl;
	
	SDL_SetRenderDrawColor(this->ren, 255, 255, 255, 100);
	SDL_RenderDrawLine(this->ren, sx - 2, sy, sx + tx * 100, sy + ty * 100);
	SDL_RenderDrawLine(this->ren, sx + 2, sy, sx + tx * 100, sy + ty * 100);
	
	
	
	
	
	for (unsigned int b = 0; b < this->bounds.size(); ++b){
		this->bounds[b].draw(this->ren);
	}
	
	SDL_SetRenderDrawColor(this->ren, 65, 90, 119, 255);
	SDL_Rect bottom = {0, this->height - 100, this->width, 100};
	SDL_RenderFillRect(this->ren, &bottom);
	
	
	
	for (unsigned int r = 0; r < this->rects.size(); ++r){
		this->rects[r].draw(this->ren);
	}
	
	for (unsigned int e = 0; e < this->explodes.size(); ++e){
		this->explodes[e].draw(this->ren);
	}
	
	this->drawTextCenter(this->width / 2, this->height - 90, 30, "Score " + to_string(this->score), this->fontColors[0]);
	this->drawTextCenter(this->width / 2, this->height - 55, 20, "Level " + to_string(this->lvl), this->fontColors[0]);
	
	if ((int)this->rect_lvl.size() - this->current > -1)
		this->drawTextCenter(this->width / 2, this->height - 35, 16, "Rect Remain " + to_string((int)this->rect_lvl.size() - this->current), this->fontColors[0]);

	
	
	if (this->isGameDone){
		SDL_SetRenderDrawColor(this->ren, 0, 0, 0, 90);
		SDL_Rect overlay = {0, 0, this->width, this->height};
		SDL_RenderFillRect(this->ren, &overlay);
		this->drawTextCenter(this->width / 2, this->height / 2 - 100, 50, "Well Done!", this->fontColors[0]);
		this->drawTextCenter(this->width / 2, this->height / 2 - 10, 30, "Your Score " + to_string(this->score), this->fontColors[0]);
		this->drawTextCenter(this->width / 2, this->height / 2 + 50, 18, "Press Enter To Continue", this->fontColors[0]);
	}
	if (this->isGameOver){
		SDL_SetRenderDrawColor(this->ren, 0, 0, 0, 90);
		SDL_Rect overlay = {0, 0, this->width, this->height};
		SDL_RenderFillRect(this->ren, &overlay);
		this->drawTextCenter(this->width / 2, this->height / 2 - 100, 50, "Game Over!", this->fontColors[0]);
		this->drawTextCenter(this->width / 2, this->height / 2 - 10, 30, "Press Enter To Try Again", this->fontColors[0]);
	}	
	

}

void Game::update(){	
	
	this->lastRect = this->rects.size() - 1;
	
	
	
	for (unsigned int b = 0; b < this->bounds.size(); ++b){
		this->bounds[b].update();
	
	}
	
	for (unsigned int e = 0; e < this->explodes.size(); ++e){
		this->explodes[e].update();
		
		if (this->explodes[e].isComplete()){
			this->explodes.erase(this->explodes.begin() + e);
		}
	}
	
	bool lastDone = this->rects[this->lastRect].isDone();
	

	
	if (lastDone && !this->isAssembled){
		if (!this->isGameOver){
			int colorIndex = this->rect_lvl[this->current - 1];
			this->rects.push_back(Rect(this->width/2, this->height-100, this->rectColors[colorIndex], getColor(colorIndex)));
			this->isAssembled = true;
			this->current++;
		}
	}
	
	
	for (unsigned int r = 0; r < this->rects.size(); r++){
		
		
		int mx, my;
		
		if(this->rects[r].isEliminate(this->field, mx, my)){
			
			this->explodes.push_back(Explode(mx * 30 + 15, my * 30 + 15));
			this->rects.erase(this->rects.begin() + r);
			this->field[my][mx] = '.';
			this->score += 50;
		}
		
		this->rects[r].update();
		
	}
	
	
	this->rects[this->lastRect].placementOnField(this->field);
	this->rects[this->lastRect].checkMap(this->field);
	
	
	if (this->rects.size() < 2 && this->lvl < 5 && this->rect_lvl.size() - this->current >= 0){
		this->isGameDone = true;
	}
	
	if ((int)this->rect_lvl.size() < this->current && lastDone && !this->isGameDone){
		
		this->isGameOver = true;
	}	
	
	for (int z = 0; z < (int)this->rect_lvl.size(); z++){
		
		cout<<this->rect_lvl[z]<<endl;
		
	}
	cout<<endl;
	
	
	
}

void Game::clean(){
	
	SDL_DestroyRenderer(this->ren);
	SDL_DestroyWindow(this->win);
	TTF_Quit();
	SDL_Quit();

	
	
}

