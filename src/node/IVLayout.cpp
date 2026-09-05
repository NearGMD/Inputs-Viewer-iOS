#include "IVLayout.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

void IVLayout::applyVerticalLayout(CCArray* nodes, const IVStyle& style) {
    if (!nodes) return;

    float y = 0.f;

    for (auto node : CCArrayExt<IVNodeBase*>(nodes)) {
        if (!node) continue;

        node->setPosition({0.f, y});
        y -= style.spacing;
    }
}

void IVLayout::applyHorizontalLayout(CCArray* nodes, const IVStyle& style) {
    if (!nodes) return;

    float x = 0.f;

    for (auto node : CCArrayExt<IVNodeBase*>(nodes)) {
        if (!node) continue;

        node->setPosition({x, 0.f});
        x += style.spacing;
    }
}

GEODE_NS_IV_END
