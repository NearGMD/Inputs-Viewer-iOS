#pragma once

#include "node/IVNodeBase.hpp"

GEODE_NS_IV_BEGIN

class IVNodeLabel : public IVNodeBase {
public:
    IVNodeLabel();

    static IVNodeLabel* create(const char* text);

    bool init(const char* text);

    void setText(const char* text);
    void refreshAppearance() override;

protected:
    cocos2d::CCLabelBMFont* m_label = nullptr;
};

GEODE_NS_IV_END
