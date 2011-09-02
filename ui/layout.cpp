#include "layout.h"

UILayout::UILayout(bool horizontal) : horizontal(horizontal), UIElement() {
    alignment  = UI_LAYOUT_ALIGN_NONE;
    background = vec4(0.0f);
}

UILayout::~UILayout() {
    clear();
}

void UILayout::clear() {
    foreach(UIElement* e, elements) {
        delete e;
    }    
    elements.clear();
}

void UILayout::setHorizontal(bool horizontal) {
    this->horizontal = horizontal;
};

void UILayout::setUI(UI* ui) {
    this->ui = ui;
    foreach(UIElement* e, elements) {
        e->setUI(ui);
    }
}

void UILayout::addElement(UIElement* e) {
    e->parent = this;
    if(ui!=0) e->setUI(ui);
    
    elements.push_back(e);
}

void UILayout::update(float dt) {

    rect = vec2(0.0f, 0.0f);

    foreach(UIElement* e, elements) {
        e->update(dt);

        vec2 r = e->getRect();
        
        if(horizontal) {
            rect.x += r.x;
            rect.y = std::max(rect.y, r.y);
        } else {
            rect.x = std::max(rect.x, r.x);
            rect.y += r.y;
        }
    }

    if(horizontal) {
        rect.x += margin.x*2.0f + ((float)elements.size()-1.0f) * padding.x;
        rect.y += margin.y*2.0f;
    } else {
        rect.x += margin.x*2.0f;
        rect.y += margin.y*2.0f + ((float)elements.size()-1.0f) * padding.y;
    }
}

void UILayout::updatePos(const vec2& pos) {

    switch(alignment) {
        case UI_LAYOUT_ALIGN_TOP_LEFT:
            this->pos = vec2(0.0f, 0.0f);
            break;
        case UI_LAYOUT_ALIGN_BOTTOM_LEFT:
            this->pos = vec2(0.0f, display.height - rect.y);
            break;
        case UI_LAYOUT_ALIGN_TOP_RIGHT:
            this->pos = vec2(display.width-rect.x, 0.0f);
            break;
        case UI_LAYOUT_ALIGN_BOTTOM_RIGHT:
            this->pos = vec2(display.width-rect.x, display.height - rect.y);
            break;
        default:
            this->pos = pos;
            break;
    }

    bool right_align = (   alignment == UI_LAYOUT_ALIGN_TOP_RIGHT
                        || alignment == UI_LAYOUT_ALIGN_BOTTOM_RIGHT) ?
                       true : false;

    vec2 cursor;

    if(right_align) {
        cursor = this->pos + vec2(rect.x - margin.x, margin.y);
    } else {
        cursor = this->pos + margin.xy;
    }

    foreach(UIElement* e, elements) {

        vec2 r = e->getRect();

        if(right_align) {
            e->updatePos(cursor - vec2(r.x, 0.0f));
        } else {
            e->updatePos(cursor);
        }

        if(horizontal) {
            cursor.x += r.x + padding.x;
        } else {
            cursor.y += r.y + padding.y;
        }
    }

}

bool UILayout::elementsByType(std::list<UIElement*>& found, int type) {

    bool success = UIElement::elementsByType(found, type);

    foreach(UIElement* e, elements) {
        if(e->elementsByType(found, type)) success = true;
    }

    return success;
}

UIElement* UILayout::elementAt(const vec2& pos) {

    if(!UIElement::elementAt(pos)) return 0;

    UIElement* found = 0;

    foreach(UIElement* e, elements) {
        if((found = e->elementAt(pos)) != 0) return found;
    }

    return this;
}

void UILayout::drawOutline() {

    UIElement::drawOutline();

    foreach(UIElement* e, elements) {
        e->drawOutline();
    }
}

void UILayout::draw() {

    if(background.w>0.0f) {
        glDisable(GL_TEXTURE_2D);
        glColor4fv(glm::value_ptr(background));
        drawQuad(pos, rect, vec4(0.0f, 0.0f, 1.0f, 1.0f));
        glEnable(GL_TEXTURE_2D);
    }

    foreach(UIElement* e, elements) {
        e->draw();
    }

}

//UILabelledElement

UILabelledElement::UILabelledElement(const std::string text, UIElement* e, float width) : UILayout(true) {
    addElement(new UILabel(text, false, false, width));
    addElement(e);
}