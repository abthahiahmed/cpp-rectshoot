#ifndef _PARTICLE_H_
#define _PARTICLE_H_



class Particle{
	
private:
	int x;
	int y;
	SDL_Rect rect;
	int alpha;
	SDL_Color color;

public:
	Particle(int x, int y, SDL_Color color){
		
		this->x = x;
		this->y = y;
		
		this->alpha = 255;
		
		this->color = color;
		
		int size = 5 + rand() % 16;
		
		
		this->rect = {this->x - size / 2, this->y - size / 2, size, size};
		
	}
	
	void update(){
		
		this->alpha-=30;
		
		
	}
	
	void draw(SDL_Renderer *ren){
		
		SDL_SetRenderDrawColor(ren, this->color.r, this->color.g, this->color.b, this->alpha);
		SDL_RenderFillRect(ren, &this->rect);
		
	}
	
	bool isDone(){
		return this->alpha < 0;
	}
	
};



#endif