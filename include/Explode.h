#ifndef _EXPLODE_H_
#define _EXPLODE_H_

#include <iostream>
#include <vector>



#include "MovingParticle.h"

using namespace std;

class Explode{
	
private:
	
	int x;
	int y;
	vector<MovingParticle> particles;
	bool isDone;
	
	vector<SDL_Color> colors;

public:
	
	Explode(int x, int y){
		
		this->x = x;
		this->y = y;
		
		this->colors.push_back({255, 183, 3});
		this->colors.push_back({251, 133, 0});
		
		
		
		this->particles.push_back(MovingParticle(this->x, this->y, 0, -2, this->colors[0]));
		this->particles.push_back(MovingParticle(this->x, this->y, 0, 2, this->colors[1]));
		this->particles.push_back(MovingParticle(this->x, this->y, -2, 0, this->colors[0]));
		this->particles.push_back(MovingParticle(this->x, this->y, 2, 0, this->colors[1]));		
		
		this->isDone = false;
		
	}
	
	void update(){
		

	
		for (unsigned int i = 0; i < this->particles.size(); i++){
			
			this->particles[i].update();
			if (this->particles[i].isDone()) {
				this->particles.erase(this->particles.begin() + i);
				this->isDone = true;
			}
		}
	
	}
	
	bool isComplete(){
		return this->isDone;
	}
	
	void draw(SDL_Renderer *ren){
	
		for (auto p: this->particles){
			
			p.draw(ren);
			
		}
		
	}
	
	
};


#endif