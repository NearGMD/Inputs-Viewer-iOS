#pragma once

#include <Geode/Geode.hpp>

GEODE_NS_IV_BEGIN

enum class SettingEventType {
    BackgroundColor,
    OutlineColor,
    TextColor,
    KeyAppearance,
    RefreshView
};

// Geode 5 event
class IVSettingEvent
    : public geode::Event<IVSettingEvent, void(SettingEventType)> {
public:
    using Event::Event;
};

GEODE_NS_IV_END
