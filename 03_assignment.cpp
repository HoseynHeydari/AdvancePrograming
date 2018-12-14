#include <string>
#include <vector>
#include <iostream>

#include "rsdl.h"

using namespace std;

struct Position
{
    int x, y;

    Position(int x, int y)
    : x(x)
    , y(y)
    {
    }
};

class Element
{
public:
    Element(window* pl, Position loc, string type);
    void draw();
    virtual void next_turn() = 0;
protected:
    window* plan;
    Position location;
    vector<string> path;
    string attach_path();
    virtual void fulfill_path(string type);
};

Element::Element(window* pl, Position loc, string type)
    : plan(pl), location(loc)
{
}

void Element::fulfill_path(string type)
{
    path.push_back("./images");
    path.push_back("/");
    path.push_back(type);
    path.push_back("/");
}

string Element::attach_path()
{
    string current_path = "";
    for (int i = 0; i < path.size(); i++)
        current_path.append(path[i]);
    return current_path;
}

void Element::draw()
{
    plan->draw_bmp(attach_path(), location.x, location.y);
}

class Prisoner : public Element
{
public:
    Prisoner(window* pl, Position loc, string type);
    void set_situation(string stat);
    virtual void next_turn();
private:
    string status;
    virtual void fulfill_path(string type);
    string condition;
    int variants;
};

Prisoner::Prisoner(window* pl, Position loc, string type = "character")
    : Element (pl, loc, type)
    , status("run")
    , condition("1")
    , variants(8)
{
    this->fulfill_path(type);
}

void Prisoner::fulfill_path(string type)
{
    Element::fulfill_path(type);
    path.push_back(status);
    path.push_back("/");
    path.push_back(condition);
    path.push_back(".bmp");
}

void Prisoner::set_situation(string stat)
{
    status = stat;
    condition = "1";
    if (stat == "run")
        variants = 8;
    else if (stat == "jump")
        variants = 9;
    else
        variants = 6;
}

void Prisoner::next_turn()
{
    int cond_ind = path.size() - 2;
    int cond = stoi(path[cond_ind]);
    cond++;
    cond = (cond - 1) % variants + 1;
    condition = to_string(cond);
    while(!path.empty())
        path.pop_back();
    this->fulfill_path("character");
}

// TODO: change class name.
class Mover : public Element
{
public:
    Mover(window* pl, Position loc, string type, string condition);
    virtual void next_turn() {return;}
private:
    string condition;
    virtual void fulfill_path(string type);
};

Mover::Mover(window* pl, Position loc, string type, string condition)
    : Element (pl, loc, type)
    , condition(condition)
{
    this->fulfill_path(type);
}

void Mover::fulfill_path(string type)
{
    Element::fulfill_path(type);
    path.push_back(condition);
    path.push_back(".bmp");
}

void total_draw(vector<Element*> elements)
{
    for (int i = 0; i < elements.size(); i++)
        elements[i]->draw();
}

void coin_play(window* plan)
{
    vector<Element*> elements;
    Mover* back_ground = new Mover(plan, Position(0, 0), "GND", "platform");
    elements.push_back(back_ground);
    Prisoner* player = new Prisoner(plan, Position(400, 235));
    elements.push_back(player);
    total_draw(elements);
    back_ground->draw();
    player->draw();
    bool quit = false;
    while(!quit)
    {
        HANDLE(
            QUIT(quit = true);
            player->next_turn();
            total_draw(elements);
            );
        DELAY(100);
    }
}

int main(int argc, const char * argv[])
{
    window plan(900, 450);
    coin_play(&plan);
    return 0;
}
