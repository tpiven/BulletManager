#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <algorithm>
#include <cmath>
#include "Wall.hpp"

#ifndef BULLETMANAGER_HPP
#define BULLETMANAGER_HPP

class BulletManager {
private:
	class Bullet {
	private:
		float2 _pos;
		float2 _dir;
		float _speed;
		float _time;
		float _life_time;
		float2 _cur_pos;
	public:
		Bullet() { }
		Bullet (float2 pos, float2 dir, float speed, float time, float life_time) : _pos(pos), _dir(dir), _speed(speed), _time(time), _life_time(life_time){
			_cur_pos = pos;
		}
		~Bullet() { }

		float GetSpeed(void) {
			return (_speed);
		}
		float GetLife_time(void){
			return (_life_time);
		}
		float GetTime(void){
			return (_time);
		}
		float2 GetPos(void) {
			return (_pos);
		}
		float2 GetDir(void) {
			return (_dir);
		}
		float2 GetCur_Pos(void) {
			return (_cur_pos);
		}
		void SetDir(float2 newdir) {
			_dir = newdir;
		}
		void SetCurPos(float2 curpos){
			_cur_pos = curpos;
		}
        void SetPos(float2 newpos) {
            _pos = newpos;
        }
        void SetTime(float newTime) {
           _time = newTime;
        }
        void SetLifeTime(float newTime) {
            _life_time = newTime;
        }
	};
	std::list <Wall> &Wallmanager;
	std::vector <Bullet> bm;

public:

	BulletManager(std::list <Wall> &w);
	~BulletManager();
	std:: vector <Bullet> GetManager();
	void Update (float time);
	void Fire (float2 pos, float2 dir, float speed, float time, float life_time);
};


#endif
