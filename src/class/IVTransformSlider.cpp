#include "IVTransformSlider.hpp"
#include "IVManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

TransformSlider::TransformSlider() {}

TransformSlider* TransformSlider::create(
    LevelSettings& setting,
    NodeTransform LevelSettings::* transform,
    IVPlayerInputNode* inputNode,
    char const* text,
    std::function<NodeTransform()>&& defaultPosFunc
) {
    auto ret = new (std::nothrow) TransformSlider();

    if (ret && ret->init(
        transform,
        inputNode,
        text,
        std::move(defaultPosFunc)
    )) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool TransformSlider::init(
    NodeTransform LevelSettings::* transform,
    IVPlayerInputNode* inputNode,
    char const* text,
    std::function<NodeTransform()>&& defaultPosFunc
) {
    if (!CCLayer::init())
        return false;

    m_transform = transform;
    m_inputNode = inputNode;
    m_defaultPosFunc = std::move(defaultPosFunc);

    return true;
}

void TransformSlider::setLevelSettings(LevelSettingsType type) {
    m_currentSetting = std::ref(
        type == LevelSettingsType::Classic
            ? IVManager::get().m_settingClassic
            : IVManager::get().m_settingPlatformer
    );
}

GEODE_NS_IV_END
