#ifndef UI_GROUP_h
#define UI_GROUP_h

#include "label.h"
#include "solid_layout.h"

class UIGroupBar : public UISolidLayout {
public:
    UILabel* label;
    UIGroupBar(const std::string& text);
    void setText(const std::string& text);
    void click(const vec2& pos);
};

class UIGroup : public UIElement {

protected:
    UILayout* layout;
    UIAction* open_action;
    float animation;
    float speed;

    vec2 old_group_rect;
    vec2 old_label_rect;

    bool minimized;
    bool minimizable;
public:
    UIGroupBar* bar;

    UIGroup(const std::string& groupname, bool minimized = false, bool resizable = false);
    ~UIGroup();

    void setUI(UI* ui);

    bool elementsByType(std::list<UIElement*>& found, int type);
    void elementsAt(const vec2& pos, std::list<UIElement*>& elements_found);

    void setOpenAction(UIAction* action);

    int getType() const { return UI_GROUP; };

    UILayout* getLayout() { return layout; };

    void setTitle(const std::string& text);

    virtual void toggle();
    virtual void minimize();
    virtual void maximize();

    void update(float dt);
    void updatePos(const vec2& pos);

    void draw();
};

#endif
