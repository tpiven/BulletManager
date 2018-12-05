
#include "BulletManager.hpp"
#include <mutex>

std::mutex mtx;

BulletManager::BulletManager(std::list <Wall> &w) : Wallmanager(w) {}
BulletManager::~BulletManager(){}
std:: vector <BulletManager::Bullet> BulletManager::GetManager() {
    return bm;
}
void BulletManager::Update (float time){
   for (std::vector <Bullet> ::iterator i = bm.begin(); i < bm.end();) {
//видалення кулі, у якої закінчилося life_time
        if (time - (*i).GetTime() > (*i).GetLife_time()){
            bm.erase(i);
            continue ;
        }
//загальна відстань від точки пострілу до мішені
        float total = std::sqrt(std::pow(((*i).GetPos().GetX() - (*i).GetDir().GetX()), 2) + std::pow(((*i).GetPos().GetY() - (*i).GetDir().GetY()), 2));
//відстань, яку пролетіла куля за час, що минув від пострілу і точка, на якій вона зараз знаходиться
        float s = (*i).GetSpeed() * (time - (*i).GetTime());
        float k = s/total;
        (*i).SetCurPos((*i).GetPos() + (((*i).GetDir() - (*i).GetPos()) * k));
        for (std::list <Wall>::iterator j = Wallmanager.begin(); j != Wallmanager.end(); ) {
//визначення чи перетинаються траєкторія кулі і стіна, визначаємо рівняння прямих, на яких лежать ці відрізки
            float2 dir1 = (*i).GetCur_Pos() - (*i).GetPos();
            float2 dir2 = (*j).GetOne() - (*j).GetTwo();
            float a1 = -dir1.GetY();
            float b1 = +dir1.GetX();
            float d1 = -(a1*((*i).GetPos().GetX()) + b1*((*i).GetPos().GetY()));
            float a2 = -dir2.GetY();
            float b2 = +dir2.GetX();
            float d2 = -(a2*((*j).GetOne().GetX()) + b2*((*j).GetOne().GetY()));
            float seg1_line2_start = a2*((*i).GetPos().GetX()) + b2*((*i).GetPos().GetY()) + d2;
            float seg1_line2_end = a2*((*i).GetCur_Pos().GetX()) + b2*((*i).GetCur_Pos().GetY()) + d2;
            float seg2_line1_start = a1*((*j).GetOne().GetX()) + b1*((*j).GetOne().GetY()) + d1;
            float seg2_line1_end = a1*((*j).GetTwo().GetX()) + b1*((*j).GetTwo().GetY()) + d1;
//якщо кінці обох відрізків мають різні знаки, то вони перетинаються
            if (seg1_line2_start * seg1_line2_end <= 0 && seg2_line1_start * seg2_line1_end <= 0) {
                float u = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
//визначення точки перетину
                float2 out_intersection =  (*i).GetPos() + (dir1 * u);
                (*i).SetCurPos(out_intersection);
                (*i).SetLifeTime((*i).GetLife_time() - (time - (*i).GetTime()));
                (*i).SetTime(time);
//визначення нового напрямку руху кулі
                float new_x = ((*i).GetCur_Pos().GetX() - (*i).GetPos().GetX()) * std::cos((60 * M_PI) / 180) + ((*i).GetCur_Pos().GetY() - (*i).GetPos().GetY()) * std::sin((60 * M_PI) / 180) + (*i).GetCur_Pos().GetX();
                float new_y = ((*i).GetCur_Pos().GetX() - (*i).GetPos().GetX()) * std::sin((60 * M_PI) / 180) - ((*i).GetCur_Pos().GetY() - (*i).GetPos().GetY()) * std::cos((60 * M_PI) / 180) + (*i).GetCur_Pos().GetY();
//запис нових даних і видалення стіни
                (*i).SetDir(float2(new_x, new_y));
                (*i).SetPos(out_intersection);
                Wallmanager.erase(j);
                break ;
            }
            j++;
        }
       i++;
    }
}

//створення нового об'єкту класу Bullet і додавання його до вектору, який містить всі об'єти цього класу
void BulletManager::Fire (float2 pos, float2 dir, float speed, float time, float life_time){
    std::lock_guard <std::mutex> guard(mtx);
    Bullet bul(pos, dir, speed, time, life_time);
    bm.push_back(bul);
}
