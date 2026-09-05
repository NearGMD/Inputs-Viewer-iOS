#include "node/IVNodeButton.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVNodeButton::IVNodeButton() {}

IVNodeButton* IVNodeButton::create(const char* labelText) {
    auto ret = new (std::nothrow) IVNodeButton();

    if (ret && ret->init(labelText)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool IVNodeButton::init(const char* labelText) {
    if (!IVNodeBase::init())
        return false;

    m_label = CCLabelBMFont::create(
        labelText ? labelText : "",
        "chatFont.fnt"
    );

    if (m_label) {
        m_label->setScale(0.6f);
        this->addChild(m_label);
    }

    return true;
}

void IVNodeButton::setPressed(bool pressed) {
    m_pressed = pressed;

    if (m_label) {
        m_label->setOpacity(pressed ? 180 : 255);
    }

    this->setScale(pressed ? 0.95f : 1.0f);

    refreshAppearance();
}

void IVNodeButton::refreshAppearance() {
    if (!m_label)
        return;

    m_label->setColor(
        m_pressed ? ccRED : ccWHITE
    );

    m_label->setOpacity(
        m_pressed ? 180 : 255
    );
}

GEODE_NS_IV_END
