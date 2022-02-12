#include "Controller.h"
#include <cmath>
#include <iostream>
namespace mrsd
{
	void Controller::control(const mrsd::Game& g, float t)
	{
		if (p != 0) {
			determineSafeSpots(g);
			float safe_spot = pickSafeSpot(g);

			if(safe_spot - p->x > 0) {
				p->x = std::min(p->x + g.playerSpeed, safe_spot);
			} else {
				p->x = std::max(p->x - g.playerSpeed, safe_spot);
			}
		}
	}

	void Controller::createPlayer(Game& g)
	{
		if(p == 0)
		{
			p = new Player();
			p->dead = true;
			dangerZone = new int[g.getWidth()+1];
		}
		if(p->dead)
		{
			p->dead = false;
			p->x = g.getWidth()/2;
			g.newPlayer(p);
		}
	}

	Prediction Controller::trackProjectile(const Projectile& p, const Game& g)
	{
		Prediction pred;
		float t = g.getGameTime();
		float dt = g.getTimeStep();
		float y = p.y, x = p.x, vy = p.vy;
		float grav = g.getGravity();
		
		while (y > 0) {
			x += p.vx*dt;
			y += vy*dt + 0.5*grav*dt*dt;
			vy += grav*dt;
			t += dt;
		}

		pred.x = x;
		pred.t = t;

		return pred;
	}

	void Controller::determineSafeSpots(const Game& g)
	{
		double horizon = 5.0;

		int w = g.getWidth();
		
		for(int i = 0; i <= w; i++) 
			dangerZone[i] = 0;

		std::list<Projectile> projectiles = g.getProjectiles();
		for(auto proj : projectiles) {
			Prediction pred = trackProjectile(proj,g);
			
			if(pred.t - g.getGameTime() > horizon) {
				for(int i = std::floor(pred.x - g.explosionSize); i <= std::ceil(pred.x + g.explosionSize); i++) {
					if(i >= 0 && i <= w)
						dangerZone[i] = 1;
				}
			}
		}

		std::list<Explosion> explosions = g.getExplosions();
		for(auto expl : explosions) {
			for(int i = std::floor(expl.x - g.explosionSize); i <= std::ceil(expl.x + g.explosionSize); i++) {
				if(i >= 0 && i <= w)
					dangerZone[i] = 1;
			}
		}


	}

	int Controller::pickSafeSpot(const Game& g)
	{
		int curr_x = std::floor(p->x);
		int safe_spot = std::floor(g.getWidth()/2);

		for (int i = 0; i<=g.getWidth(); i++) {
			if(curr_x-i >= 0 && !dangerZone[curr_x-i]) {
				safe_spot = curr_x-i;
				break;
			}
			if(curr_x+i <= g.getWidth() && !dangerZone[curr_x+i])
			{
				safe_spot = curr_x+i;
				break;
			}
		}

		return safe_spot;
	}
}
