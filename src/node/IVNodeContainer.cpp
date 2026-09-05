#include "node/IVNodeContainer.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

IVNodeContainer::IVNodeContainer() {}

IVNodeContainer* IVNodeContainer::create() {
    auto ret = new (std::nothrow) IVNodeContainer();

    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool IVNodeContainer::init() {
    if (!IVNodeBase::init())
        return false;

    return true;
}

void IVNodeContainer::addNode(IVNodeBase* node) {
    if (!node)
        return;

    this->addChild(node);
}

void IVNodeContainer::refreshAppearance() {
    for (auto child : this->getChildrenExt<IVNodeBase*>()) {
        if (child) {
            child->refreshAppearance();
        }
    }
}

GEODE_NS_IV_END
