//
// Created by IvanBrekman on 26.09.2022
//

#include <cstdarg>

#include "../Class_Utils/baselib.hpp"
#include "WindowView.hpp"

WindowView::WindowView(std::initializer_list<Widget*> objects)
: m_hidden(false) {
    set_objects(objects);
}

WindowView::~WindowView() {
    freeStdVector(m_objects, false);
}

// ==================== Getters ====================
size_t WindowView::size() const {
    return m_objects.size();
}

bool WindowView::hidden() const {
    return m_hidden;
}

std::vector<Widget*> WindowView::objects() const {
    return m_objects;
}
// =================================================


// ==================== Setters ====================
WindowView& WindowView::set_hidden(bool hidden) {
    m_hidden = hidden;
    
    for (Widget* object : m_objects) {
        object->set_hidden(hidden);
    }

    return *this;
}

WindowView& WindowView::set_objects(std::initializer_list<Widget*> objects) {
    m_objects.resize(0);

    for (Widget* object : objects) {
        m_objects.push_back(object);
    }

    return *this;
}
// =================================================
