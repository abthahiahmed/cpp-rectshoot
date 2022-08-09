#ifndef _RECT_H_
#define _RECT_H_

#include <iostream>
#include <vector>

#include "Particle.h"
#include "Bound.h"

using namespace std;


class Rect{
	
private:
	SDL_Color color;
	float dx, dy, d;
	float vx, vy;
	float v,a;
	SDL_FRect rect;
	char rectType;
	bool isActive;
	bool isOnMap;
	bool isMoving;
	
	vector<Particle> fire;
	
	vector<SDL_Color> colors;
	
public:
	
	float x, y;
	float size;
	
	Rect(float x, float y, SDL_Color color, char rectT){
		
		this->rectType = rectT;
		
		this->x = x;
		this->y = y;
		this->size = 28;
		
		this->color = color;
		
		this->vx = 0;
		this->vy = 0;
		this->v = 30;
		this->a = 0;
		this->d = -1;
		this->dx = 0;
		this->dy = 0;
		
		this->rect = {this->x -this->size/2, this->y -this->size/2, this->size, this->size};
	
		this->isActive = false;
		this->isOnMap = false;
		this->isMoving = true;
		
		this->colors.push_back({255, 183, 3});
		this->colors.push_back({251, 133, 0});
		
		
		
	}
	
	
	void draw(SDL_Renderer *ren){
		
		for (auto f : this->fire){
			f.draw(ren);
		}
		
		SDL_SetRenderDrawColor(ren, this->color.r, this->color.g, this->color.b, 255);
		SDL_RenderFillRectF(ren, &this->rect);
	}
	
	void shoot(float x, float y){
		
		if (this->d == -1){
			this->dx = x - this->x;
			this->dy = y - this->y;
			this->d = sqrt(pow(this->dx, 2) + pow(this->dy, 2));
		}
		
		this->vx = this->v * (this->dx / this->d);
		this->vy = this->v * (this->dy / this->d);
		
	}

	
	bool isDone(){
		if (this->vx == 0 && this->vy == 0){
			return true;
		}else{
			return false;
		}
	}
	
	
	
	void update(){

		this->x += this->vx;
		this->y += this->vy;
	
		this->rect.x = (int)this->x - this->size/2;
		this->rect.y = (int)this->y - this->size/2;	
		
		
		if (this->vx != 0 || this->vy != 0){
			
			
			this->fire.push_back(Particle(this->x, this->y, this->colors[rand() % 2]));
			
		}
		for (unsigned int i = 0;i < this->fire.size(); i++){
			this->fire[i].update();
			if (this->fire[i].isDone()){
				this->fire.erase(this->fire.begin() + i);
			}
		}
		
	}
	
	bool isEliminate(char field[23][18], int& mx, int& my){
		mx = ((int)this->x - 15) / 30;
		my = ((int)this->y - 15) / 30;
		if (field[my][mx] == '-'){
			return true;
		}else{
			return false;
		}
	}
	
	void placementOnField(char field[23][18]){
				
		int normx = ((int)this->x - 15) / 30;
		int normy = ((int)this->y - 15) / 30;



		if (this->vx < 0){
			if (field[normy][normx - 1] == '#'){
			
				this->x = (normx) * 30 + 15;
				this->vx *= -1;
			}

		}else{
			if (field[normy][normx + 1] == '#'){
				
				this->x = (normx) * 30 + 15;
				this->vx *= -1;
			}
			
		}		
		
		if (field[normy - 1][normx + 1] != '.' && field[normy - 1][normx + 1] != '#'){
			this->vx = this->vx + 1;
			this->vx = 0;
		}
		if (field[normy - 1][normx - 1] != '.' && field[normy - 1][normx - 1] != '#'){
			this->vx = this->vx - 1;
			this->vx = 0;
		}
		
		if (field[normy - 1][normx] != '.' && field[normy - 1][normx] != '#'){
			this->x = (normx) * 30 + 15;
			this->y = (normy) * 30 + 15;
			this->vy = 0;
			this->vx = 0;
			field[normy][normx] = this->rectType;
			this->isOnMap = true;
			this->isMoving = false;
		}
		if (field[normy][normx - 1] != '.' && field[normy][normx - 1] != '#'){
			this->x = (normx) * 30 + 15;
			this->y = (normy) * 30 + 15;
			this->vy = 0;
			this->vx = 0;
			field[normy][normx] = this->rectType;
			this->isOnMap = true;
			this->isMoving = false;
		}
		if (field[normy][normx + 1] != '.' && field[normy][normx + 1] != '#'){
			this->x = (normx) * 30 + 15;
			this->y = (normy) * 30 + 15;
			this->vy = 0;
			this->vx = 0;
			field[normy][normx] = this->rectType;
			this->isOnMap = true;
			this->isMoving = false;
		}
		
	
	}
	
	auto checkMap(char field[23][18]){
		
		int normx = ((int)this->x - 15) / 30;
		int normy = ((int)this->y - 15) / 30;
		
		
		if (field[normy - 1][normx] == this->rectType){
			field[normy][normx] = '-';
			field[normy - 1][normx] = '-';
			
			int checkN = 0;
			for (int c = 2; c < 18; c++){
				if (field[normy - c][normx] == this->rectType){
					checkN++;
				}else{
					break;
				}
			}
			if (checkN >= 1){
				for (int c = 2; c < checkN + 2; c++){
					field[normy - c][normx] = '-';				
				}
			}
			
		}
		if (field[normy][normx - 1] == this->rectType){
			field[normy][normx] = '-';
			field[normy][normx - 1] = '-';
			
			int checkN = 0;
			for (int c = 2; c < 18; c++){
				if (field[normy][normx - c] == this->rectType){
					checkN++;
				}else{
					break;
				}
			}
			if (checkN >= 1){
				for (int c = 2; c < checkN + 2; c++){
					field[normy][normx - c] = '-';				
				}
			}			
			
			
		}
		if (field[normy][normx + 1] == this->rectType){
			field[normy][normx] = '-';
			field[normy][normx + 1] = '-';
			
			int checkN = 0;
			for (int c = 2; c < 18; c++){
				if (field[normy][normx + c] == this->rectType){
					checkN++;
				}else{
					break;
				}
			}
			if (checkN >= 1){
				for (int c = 2; c < checkN + 2; c++){
					field[normy][normx + c] = '-';				
				}
			}				
			
		}
		
	}
	
	
};


#endif