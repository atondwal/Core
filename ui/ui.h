#ifndef UI_H
#define UI_H

#include "../display.h"
#include "../util.h"
#include "../mousecursor.h"

#include <vector>
#include <list>

class UIElement;

class UI {
    UIElement* selectedElement;
    std::vector<UIElement*> elements;

    float double_click_interval;
    float double_click_timer;
    
    char toChar(SDL_KeyboardEvent *e);
public:
    FXFont font;

    UI();
    ~UI();

    void clear();

    void addElement(UIElement* e);

    UIElement* getSelected();

    bool elementsByType(std::list<UIElement*>& found, int type);

    UIElement* elementAt(const vec2& pos);
    UIElement* selectElementAt(const vec2& pos);

    void deselect();
    
    bool keyPress(SDL_KeyboardEvent *e);

    virtual void click(const MouseCursor& cursor);
    virtual void drag(const MouseCursor& cursor);

    void update(float dt);

    void draw();
    void drawOutline();
};

#endif