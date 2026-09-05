#include "IVInputsViewLayer.hpp"
#include "node/IVNodeContainer.hpp"

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

InputsViewLayer::InputsViewLayer(LevelSettingsType type)
    : m_currentSetting(
        type == LevelSettingsType::Classic
            ? IVManager::get().m_settingClassic
            : IVManager::get().m_settingPlatformer
    ) {}

InputsViewLayer* InputsViewLayer::create(LevelSettingsType type) {
    auto ret = new (std::nothrow) InputsViewLayer(type);
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

bool InputsViewLayer::init() {
    if (!CCLayer::init())
        return false;

    auto container = IVNodeContainer::create();
    if (!container)
        return false;

    this->addChild(container);

    return true;
}

void InputsViewLayer::handleButton(
    bool down,
    PlayerButton input,
    bool isP1,
    bool updateCounters
) {
    // Input handling will be connected here.
}

LevelSettings const& InputsViewLayer::getLevelSettings() const noexcept {
    return m_currentSetting.get();
}

void InputsViewLayer::setLevelSettings(LevelSettingsType type) {
    m_currentSetting = (
        type == LevelSettingsType::Classic
            ? IVManager::get().m_settingClassic
            : IVManager::get().m_settingPlatformer
    );
}

void InputsViewLayer::releaseAllButtons() {
    if (m_p1InputNode)
        m_p1InputNode->updateInputState(false);

    if (m_p2InputNode)
        m_p2InputNode->updateInputState(false);
}

void InputsViewLayer::refreshDisplay() {
    if (m_p1InputNode)
        m_p1InputNode->refreshAppearance();

    if (m_p2InputNode)
        m_p2InputNode->refreshAppearance();
}

void InputsViewLayer::onSettingEvent(SettingEventType type) {
    switch (type) {
        case SettingEventType::BackgroundColor:
        case SettingEventType::OutlineColor:
        case SettingEventType::TextColor:
            refreshDisplay();
            break;
    }
}

GEODE_NS_IV_END
