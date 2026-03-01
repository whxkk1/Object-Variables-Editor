#pragma once
#include "Geode/ui/Popup.hpp"
#include "Geode/ui/TextInput.hpp"
#include <string>

class ObjectEditorPopup : public geode::Popup {
private:
    CCNode* createNode(const char* labelText, const std::string& textInputMessage, const std::string& textInputContent, geode::TextInput*& textInput);
    float width = 0.f;
    float height = 0.f;
protected:
    geode::TextInput* xPosInput = nullptr;
    geode::TextInput* yPosInput = nullptr;
    geode::TextInput* xScaleInput = nullptr;
    geode::TextInput* yScaleInput = nullptr;
    geode::TextInput* rotationInput = nullptr;
    geode::TextInput* zOrderInput = nullptr;
    geode::TextInput* editorLayerInput = nullptr;
    CCMenuItemSpriteExtra* infoButton = nullptr;
    bool init();

public:
    static ObjectEditorPopup* create();
    GameObject* selectedObj = LevelEditorLayer::get()->m_editorUI->m_selectedObject;
    void onApplyButton(CCObject* sender);
    void onInfoButton(CCObject* sender);
};