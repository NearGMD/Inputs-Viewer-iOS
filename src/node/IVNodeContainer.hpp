#pragma once

#include "node/IVNodeBase.hpp"

GEODE_NS_IV_BEGIN

class IVNodeContainer : public IVNodeBase {
public:
    IVNodeContainer();
    static IVNodeContainer* create();

    bool init() override;

    void addNode(IVNodeBase* node);
    void refreshAppearance() override;
};

GEODE_NS_IV_END
