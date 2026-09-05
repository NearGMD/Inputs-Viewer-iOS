#include "IVSettingsLayer.hpp"
#include "IVManager.hpp"

#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

GEODE_NS_IV_BEGIN

SettingsLayer::SettingsLayer(LevelSettingsType levelType)
    : m_currentSettingType(levelType)
    , m_currentSetting(
        levelType == LevelSettingsType::Classic
            ? IVManager::get().m_settingClassic
            : IVManager::get().m_settingPlatformer
    )
{}

SettingsLayer* SettingsLayer::create(
    LevelSettingsType levelType,
    bool enableGeodeSettingButton
) {
    auto ret = new (std::nothrow) SettingsLayer(levelType);

    if (!ret)
        return nullptr;

    if (!ret->init(
        350.f,
        260.f,
        "GJ_square01.png"
    )) {
        delete ret;
        return nullptr;
    }

    IVManager::get().m_isInSetting = true;

    ret->m_enableGeodeSettingButton = enableGeodeSettingButton;

    ret->setTitle("Inputs Viewer Config");
    ret->setColor({127, 127, 127});
    ret->setOpacity(255);

    if (enableGeodeSettingButton) {
        auto modSettingsBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName(
                "GJ_optionsBtn02_001.png"
            ),
            ret,
            menu_selector(SettingsLayer::onModSettings)
        );

        if (modSettingsBtn) {
            ret->m_buttonMenu->addChildAtPosition(
                modSettingsBtn,
                Anchor::TopRight,
                ccp(-3.f, -3.f)
            );
        }
    }

    auto classicBtnSpr = ButtonSprite::create(
        "Classic",
        "bigFont.fnt",
        "GJ_button_04.png"
    );

    classicBtnSpr->setScale(0.5f);

    ret->m_classicBtn = CCMenuItemSpriteExtra::create(
        classicBtnSpr,
        ret,
        menu_selector(SettingsLayer::onClassic)
    );

    if (!ret->m_classicBtn)
        return nullptr;

    ret->m_buttonMenu->addChildAtPosition(
        ret->m_classicBtn,
        Anchor::TopLeft,
        ccp(62.f, 0.f)
    );

    auto platformerBtnSpr = ButtonSprite::create(
        "Platformer",
        "bigFont.fnt",
        "GJ_button_04.png"
    );

    platformerBtnSpr->setScale(0.5f);

    ret->m_platformerBtn = CCMenuItemSpriteExtra::create(
        platformerBtnSpr,
        ret,
        menu_selector(SettingsLayer::onPlatformer)
    );

    if (!ret->m_platformerBtn)
        return nullptr;

    ret->m_buttonMenu->addChildAtPosition(
        ret->m_platformerBtn,
        Anchor::TopLeft,
        ccp(154.f, 0.f)
    );

    ret->m_inputsLayer = InputsViewLayer::create(
        ret->m_currentSettingType
    );

    if (!ret->m_inputsLayer)
        return nullptr;

    ret->m_inputsLayer->setPosition(
        CCDirector::get()->getWinSize() * 0.5f
    );

    ret->insertBefore(
        ret->m_inputsLayer,
        ret->m_mainLayer
    );

    ret->m_p1Slider = TransformSlider::create(
        ret->m_currentSetting,
        &LevelSettings::p1Transform,
        ret->m_inputsLayer->m_p1InputNode,
        "P1 Input",
        IVManager::getDefaultP1Transform
    );

    if (!ret->m_p1Slider)
        return nullptr;

    ret->m_mainLayer->addChildAtPosition(
        ret->m_p1Slider,
        Anchor::Center,
        ccp(-80.f, 20.f)
    );

    ret->m_p2Slider = TransformSlider::create(
        ret->m_currentSetting,
        &LevelSettings::p2Transform,
        ret->m_inputsLayer->m_p2InputNode,
        "P2 Input",
        IVManager::getDefaultP2Transform
    );

    if (!ret->m_p2Slider)
        return nullptr;

    ret->m_mainLayer->addChildAtPosition(
        ret->m_p2Slider,
        Anchor::Center,
        ccp(80.f, 20.f)
    );

    ret->m_totalInputsCheckbox = ret->createCheckbox(
        &LevelSettings::showTotalInputs,
        "Show Total Inputs",
        SettingEventType::KeyAppearance,
        Anchor::Center,
        ccp(-90.f, -50.f)
    );

    ret->m_cpsCheckbox = ret->createCheckbox(
        &LevelSettings::showCPS,
        "Show Clicks per Seconds",
        SettingEventType::KeyAppearance,
        Anchor::Center,
        ccp(-90.f, -80.f)
    );

    ret->m_hideLRCheckbox = ret->createCheckbox(
        &LevelSettings::hideLeftRight,
        "Hide L&R Keys",
        SettingEventType::KeyAppearance,
        Anchor::Center,
        ccp(-90.f, -110.f),
        "Hide the left and right keys."
    );

    ret->updateSettingNodes();

    ret->autorelease();
    return ret;
}

void SettingsLayer::onClassic(CCObject*) {
    this->setLevelSettings(
        LevelSettingsType::Classic
    );
}

void SettingsLayer::onPlatformer(CCObject*) {
    this->setLevelSettings(
        LevelSettingsType::Platformer
    );
}

void SettingsLayer::setLevelSettings(
    LevelSettingsType type
) {
    m_currentSettingType = type;

    m_currentSetting = std::ref(
        type == LevelSettingsType::Classic
            ? IVManager::get().m_settingClassic
            : IVManager::get().m_settingPlatformer
    );

    if (m_inputsLayer)
        m_inputsLayer->setLevelSettings(type);

    if (m_p1Slider)
        m_p1Slider->setLevelSettings(type);

    if (m_p2Slider)
        m_p2Slider->setLevelSettings(type);

    this->updateSettingNodes();
}

void SettingsLayer::updateSettingNodes() {
    if (!m_classicBtn || !m_platformerBtn)
        return;

    switch (m_currentSettingType) {
        case LevelSettingsType::Classic:
            static_cast<ButtonSprite*>(
                m_classicBtn->getNormalImage()
            )->updateBGImage("GJ_button_01.png");

            m_classicBtn->setEnabled(false);

            static_cast<ButtonSprite*>(
                m_platformerBtn->getNormalImage()
            )->updateBGImage("GJ_button_04.png");

            m_platformerBtn->setEnabled(true);
            break;

        case LevelSettingsType::Platformer:
            static_cast<ButtonSprite*>(
                m_platformerBtn->getNormalImage()
            )->updateBGImage("GJ_button_01.png");

            m_platformerBtn->setEnabled(false);

            static_cast<ButtonSprite*>(
                m_classicBtn->getNormalImage()
            )->updateBGImage("GJ_button_04.png");

            m_classicBtn->setEnabled(true);
            break;
    }

    if (m_totalInputsCheckbox) {
        m_totalInputsCheckbox->toggle(
            m_currentSetting.get().showTotalInputs
        );
    }

    if (m_cpsCheckbox) {
        m_cpsCheckbox->toggle(
            m_currentSetting.get().showCPS
        );
    }

    if (m_hideLRCheckbox) {
        m_hideLRCheckbox->toggle(
            m_currentSetting.get().hideLeftRight
        );
    }
}

CCMenuItemToggler* SettingsLayer::createCheckbox(
    bool LevelSettings::* member,
    char const* text,
    std::optional<SettingEventType> postEvent,
    Anchor anchor,
    CCPoint const& offset,
    char const* description
) {
    auto checkbox = CCMenuItemExt::createTogglerWithStandardSprites(
        0.7f,
        [this, member, postEvent](CCMenuItemToggler* btn) {
            m_currentSetting.get().*member = !btn->isToggled();

            if (postEvent && m_inputsLayer) {
                m_inputsLayer->onSettingEvent(*postEvent);
            }
        }
    );

    if (!checkbox)
        return nullptr;

    m_buttonMenu->addChildAtPosition(
        checkbox,
        anchor,
        offset
    );

    auto label = CCLabelBMFont::create(
        text,
        "bigFont.fnt"
    );

    if (label) {
        label->limitLabelWidth(
            200.f,
            0.5f,
            0.1f
        );

        label->setAnchorPoint(
            ccp(0.f, 0.5f)
        );

        m_mainLayer->addChildAtPosition(
            label,
            anchor,
            offset + ccp(14.f, 0.f)
        );
    }

    if (description) {
        auto infoSpr =
            CCSprite::createWithSpriteFrameName(
                "GJ_infoIcon_001.png"
            );

        if (infoSpr) {
            infoSpr->setScale(0.4f);

            auto infoBtn =
                CCMenuItemExt::createSpriteExtra(
                    infoSpr,
                    [text, description](CCMenuItemSpriteExtra*) {
                        FLAlertLayer::create(
                            text,
                            description,
                            "Ok"
                        )->show();
                    }
                );

            if (infoBtn) {
                m_buttonMenu->addChildAtPosition(
                    infoBtn,
                    anchor,
                    offset + ccp(-14.f, 14.f)
                );
            }
        }
    }

    return checkbox;
}

void SettingsLayer::onModSettings(CCObject*) {
    openSettingsPopup(
        Mod::get(),
        false
    );
}

void SettingsLayer::onExit() {
    IVManager::get().m_isInSetting = false;

    if (m_inputsLayer) {
        m_inputsLayer->onSettingEvent(
            SettingEventType::RefreshView
        );
    }

    Popup::onExit();
}

GEODE_NS_IV_END
