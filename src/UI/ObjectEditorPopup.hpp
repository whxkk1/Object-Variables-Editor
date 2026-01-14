#pragma once
#include "Geode/ui/Popup.hpp"



class ObjectEditorPopup : public geode::Popup<> {
protected:
    geode::TextInput* xPosInput = nullptr;
    geode::TextInput* yPosInput = nullptr;
    geode::TextInput* xScaleInput = nullptr;
    geode::TextInput* yScaleInput = nullptr;
    geode::TextInput* rotationInput = nullptr;
    geode::TextInput* zOrderInput = nullptr;
    bool setup() override;

public:
    static ObjectEditorPopup* create();
    GameObject* selectedObj = LevelEditorLayer::get()->m_editorUI->m_selectedObject;
    void onApplyButton(CCObject* sender);
};