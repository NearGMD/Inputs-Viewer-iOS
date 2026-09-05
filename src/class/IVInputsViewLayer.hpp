#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/cocos.hpp>

#include "IVEvent.hpp"
#include "IVLevelSettings.hpp"
#include "node/IVPlayerInputNode.hpp"
#include "IVManager.hpp"

GEODE_NS_IV_BEGIN

class InputsViewLayer : public cocos2d::CCLayer {
public:
    InputsViewLayer(LevelSettingsType type);
    static InputsViewLayer* create(LevelSettingsType type);

    bool init() override;

    void handleButton(
        bool down,
        PlayerButton input,
        bool isP1,
        bool updateCounters = true
    );

    LevelSettings const& getLevelSettings() const noexcept;
    void setLevelSettings(LevelSettingsType type);
    void releaseAllButtons();
    void refreshDisplay();

    void onSettingEvent(SettingEventType);

public:
    IVPlayerInputNode* m_p1InputNode = nullptr;
    IVPlayerInputNode* m_p2InputNode = nullptr;

protected:
    std::reference_wrapper<LevelSettings> m_currentSetting;

    // Geode 5 removed the old EventListener API.
    // Event listening will be handled separately.
};

GEODE_NS_IV_END
