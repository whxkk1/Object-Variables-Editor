#include "ObjectEditorPopup.hpp"
#include "Geode/ui/TextInput.hpp"
#include <stdexcept>
#include <string>

using namespace geode::prelude;

CCNode* ObjectEditorPopup::createNode(const char* labelText, const std::string& textInputMessage, const std::string& textInputContent, geode::TextInput*& textInput) { //*& looks awful
    CCNode* node = CCNode::create();
    node->setContentSize({100.f, 60.f});

    auto label = CCLabelBMFont::create(labelText, "bigFont.fnt");
    label->setPosition({50.f, 50.f});
    label->setScale(0.75f);
    node->addChild(label);

    textInput = geode::TextInput::create(100.f, textInputMessage);
    textInput->setString(textInputContent);
    textInput->setPosition(50.f, 20.f);
    node->addChild(textInput);

    return node;
}

void ObjectEditorPopup::onApplyButton(CCObject* sender) {
    /*
    a little inspiration from https://github.com/jojo989/edit-object-variables/blob/main/src/editObjectPopup.cpp
    thanks jojo
    */
    auto xPosStr = xPosInput->getString();
    auto yPosStr = yPosInput->getString();
    auto xScaleStr = xScaleInput->getString();
    auto yScaleStr = yScaleInput->getString();
    auto rotationStr = rotationInput->getString();
    auto zOrderStr = zOrderInput->getString();
    auto layerStr = editorLayerInput->getString();

    float xPos = 0.f;
    float yPos = 0.f;
    float xScale = 0.f;
    float yScale = 0.f;
    float rotation = 0.f;
    int zOrder = 0.f;
    int layer = 0;

    try {
        xPos = std::stof(xPosStr);
        yPos = std::stof(yPosStr);
        xScale = std::stof(xScaleStr);
        yScale = std::stof(yScaleStr);
        rotation = std::stof(rotationStr);
        zOrder = std::stoi(zOrderStr);
        layer = std::stoi(layerStr);

        if(layer < 0 || layer > 32767) throw std::out_of_range("Layer is out of range.");

        if(std::isnan(xPos) || std::isinf(xPos) ||
            std::isnan(yPos) || std::isinf(yPos) ||
            std::isnan(xScale) || std::isinf(xScale) ||
            std::isnan(yScale) || std::isinf(yScale) ||
            std::isnan(rotation) || std::isinf(rotation) //i hate this
        ) {
            FLAlertLayer::create("Error", "Some of the values are <cr>nan</c> or <cr>inf</c>", "Ok")->show();
            return;
        }

        selectedObj->setPosition({xPos, yPos});
        selectedObj->setRScaleX(xScale);
        selectedObj->m_scaleX = xScale;
        selectedObj->setRScaleY(yScale);
        selectedObj->m_scaleY = yScale;
        selectedObj->setRotation(rotation);
        selectedObj->m_zOrder = zOrder;
        selectedObj->m_editorLayer = layer;
    } catch (const std::out_of_range& e) {
        FLAlertLayer::create("Error", "Some of the values are either too large or too small.", "Ok")->show();
        return;
    } catch(const std::invalid_argument& e) {
        FLAlertLayer::create("Error", "Some of the values is not a number.", "Ok")->show();
        return;
    } catch(...) {
        FLAlertLayer::create("Error", "Unknown error.", "Ok")->show(); 
        return;
    }
}

bool ObjectEditorPopup::setup() {

    //if you are seeing this and have any suggestions, please let me know. i hate cocos ui
    m_noElasticity = true;
    this->setTitle("Object Editor");

    auto objXpos = selectedObj->getPositionX();
    auto objYpos = selectedObj->getPositionY();
    auto objXscale = selectedObj->getScaleX();
    auto objYscale = selectedObj->getScaleY();
    auto objRotation = selectedObj->getObjectRotation();
    auto objZorder = selectedObj->getObjectZOrder();
    auto objLayer = selectedObj->m_editorLayer;

    auto winSize = CCDirector::sharedDirector()->getWinSize();


    auto inputMenu = CCMenu::create();
    inputMenu->setContentSize({485.f, 150.f});
    inputMenu->setPosition(winSize / 2);

    auto inputLayout = RowLayout::create();
    inputLayout->setGap(15.f);
    inputLayout->setGrowCrossAxis(true);
    inputMenu->setLayout(inputLayout);


    inputMenu->addChild(createNode("X Pos", "X Pos", std::to_string(objXpos),xPosInput));
    inputMenu->addChild(createNode("Y Pos", "Y Pos", std::to_string(objYpos),yPosInput));
    inputMenu->addChild(createNode("X Scale", "X Scale", std::to_string(objXscale),xScaleInput));
    inputMenu->addChild(createNode("Y Scale", "Y Scale", std::to_string(objYscale),yScaleInput));
    inputMenu->addChild(createNode("Rotation", "Rotation", std::to_string(objRotation),rotationInput));
    inputMenu->addChild(createNode("Z Order", "Z Order", std::to_string(objZorder),zOrderInput));
    inputMenu->addChild(createNode("Layer", "Layer", std::to_string(objLayer),editorLayerInput));



    inputMenu->updateLayout();
    this->addChild(inputMenu);

    auto buttonMenu = CCMenu::create();
    auto btn = CCMenuItemSpriteExtra::create(ButtonSprite::create("Apply"),
    this, 
    menu_selector(ObjectEditorPopup::onApplyButton)
    );
    btn->setPositionY(-85.f);
    buttonMenu->addChild(btn);

    this->addChild(buttonMenu);

    return true;
}



ObjectEditorPopup* ObjectEditorPopup::create() {
    auto ret = new ObjectEditorPopup();
    if (ret->initAnchored(485.f, 230.f)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}