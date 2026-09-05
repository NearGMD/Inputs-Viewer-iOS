#include "IVTransformSlider.hpp"
#include "IVManager.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

TransformSlider::TransformSlider(LevelSettings& setting)
    : m_currentSetting(setting) {}

TransformSlider* TransformSlider::create(
    LevelSettings& setting,
    NodeTransform LevelSettings::* transform,
    IVPlayerInputNode* inputNode,
    char const* text,
    std::function<NodeTransform()>&& defaultPosFunc
) {
    auto ret = new (std::nothrow) TransformSlider(setting);

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
    if (!CCNode::init())
        return false;

    m_transform = transform;
    m_inputNode = inputNode;
    m_defaultPosFunc = std::move(defaultPosFunc);

    m_textLabel = CCLabelBMFont::create(
        text ? text : "",
        "goldFont.fnt"
    );

    if (m_textLabel) {
        m_textLabel->setAnchorPoint({0.f, 0.5f});
        this->addChild(m_textLabel);
    }

    return true;
}

void TransformSlider::setLevelSettings(LevelSettingsType type) {
    m_currentSetting = std::ref(
        type == LevelSettingsType::Classic
            ? IVManager::get().m_settingClassic
            : IVManager::get().m_settingPlatformer
    );

    updateSettingNodes();
}

void TransformSlider::onDefaultPosition(cocos2d::CCObject*) {
    if (!m_defaultPosFunc)
        return;

    auto& setting = m_currentSetting.get().*m_transform;
    setting = m_defaultPosFunc();

    updateSettingNodes();
}

void TransformSlider::onSetVisibility(cocos2d::CCObject*) {
    if (!m_visibilityCheckbox)
        return;

    auto& setting = m_currentSetting.get().*m_transform;

    setting.isVisible = !setting.isVisible;

    if (m_inputNode) {
        m_inputNode->setVisible(setting.isVisible);
    }
}

void TransformSlider::updateSettingNodes() {
    if (!m_transform)
        return;

    auto& setting = m_currentSetting.get().*m_transform;

    if (m_inputNode) {
        m_inputNode->setPosition(setting.position);
        m_inputNode->setScale(setting.scale);
        m_inputNode->setRotation(setting.rotation);
        m_inputNode->setVisible(setting.isVisible);
    }

    if (m_xPosSlider) {
        m_xPosSlider->setValue(setting.position.x);
    }

    if (m_yPosSlider) {
        m_yPosSlider->setValue(setting.position.y);
    }

    if (m_scaleSlider) {
        m_scaleSlider->setValue(setting.scale);
    }

    if (m_visibilityCheckbox) {
        m_visibilityCheckbox->toggle(setting.isVisible);
    }
}

GEODE_NS_IV_END
