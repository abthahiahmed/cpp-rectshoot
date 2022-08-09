#ifndef MOVINGPARTICLE_H
#define MOVINGPARTICLE_H



class MovingParticle{
	
private:
	int x;
	int y;
	SDL_Rect rect;
	int alpha;
	int size;
	int vx, vy;
	SDL_Color color;

public:
	MovingParticle(int x, int y, int vx, int vy, SDL_Color color){
		
		this->x = x;
		this->y = y;
		
		this->vx = vx;
		this->vy = vy;
		
		this->alpha = 255;
		this->size = 16;
		this->rect = {this->x - this->size / 2, this->y - this->size / 2, this->size, this->size};
		
		this->color = color;
	}
	
	void update(){
		
		this->alpha -= 12;
		this->size -= 1;
		
		this->x += this->vx;
		this->y += this->vy;
		
		this->rect.x = this->x - this->size / 2;
		this->rect.y = this->y - this->size / 2;
		
		this->rect.w = this->size;
		this->rect.h = this->size;
		
//		this->vx *= 2;
//		this->vy *= 2;
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