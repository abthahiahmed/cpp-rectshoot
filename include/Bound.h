#ifndef _BOUND_H_
#define _BOUND_H_


class Bound{
	
private:
	
	SDL_FRect rect, rectI;
	
public:
	
	float x, y;
	float size;

	Bound(float x, float y){
		
		this->x = x;
		this->y = y;
		this->size = 30;
		
		this->rect = {this->x - this->size / 2, this->y - this->size / 2, this->size, this->size};
		this->rectI = {this->x - this->size / 2, this->y - this->size / 2, this->size - 5, this->size - 5};
		
	}
	void draw(SDL_Renderer *ren){
		
		SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
		SDL_RenderFillRectF(ren, &this->rect);

			
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderFillRectF(ren, &this->rectI);
	}
	void update(){
		this->rect.x = this->x - this->size / 2;
		this->rect.y = this->y - this->size / 2;
		
		this->rectI.x = this->x - this->size / 2;
		this->rectI.y = this->y - this->size / 2;
	}
	
	
};


#endif