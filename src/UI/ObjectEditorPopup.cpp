#include "ObjectEditorPopup.hpp"
#include "Geode/ui/TextInput.hpp"
#include <string>

using namespace geode::prelude;

template<class OkType, class ErrType>
void checkResult(const geode::Result<OkType, ErrType>& res, std::string& errString, const std::string& fieldName) {
    if(res.isErr()) {
        errString += fieldName + " Error: " + res.err().value() + '\n';
    } else {
        if (std::isnan(res.unwrap())) errString += fieldName + " Error: NaN.\n";
        else if (std::isinf(res.unwrap())) errString += fieldName + " Error: Infinite.\n";
    }
}

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
    short layer = 0;

    auto xPosResult = geode::utils::numFromString<float>(xPosStr);
    auto yPosResult = geode::utils::numFromString<float>(yPosStr);
    auto xScaleResult = geode::utils::numFromString<float>(xScaleStr);
    auto yScaleResult = geode::utils::numFromString<float>(yScaleStr);
    auto rotationResult = geode::utils::numFromString<float>(rotationStr);
    auto zOrderResult = geode::utils::numFromString<int>(zOrderStr);
    auto layerResult = geode::utils::numFromString<short>(layerStr);

    std::string errorString;
    checkResult(xPosResult, errorString, "xPos");
    checkResult(yPosResult, errorString, "yPos");
    checkResult(xScaleResult, errorString, "xScale");
    checkResult(yScaleResult, errorString, "yScale");
    checkResult(rotationResult, errorString, "Rotation");
    checkResult(zOrderResult, errorString, "zOrder");
    checkResult(layerResult, errorString, "Layer");

    /*if(xPosResult.isErr() || yPosResult.isErr() || xScaleResult.isErr() || yScaleResult.isErr() || rotationResult.isErr() || zOrderResult.isErr() || layerResult.isErr()) {
        FLAlertLayer::create("Error", "Error setting some of the fields", "Ok")->show();
        return;
    }*/

    if(!errorString.empty()) {
        FLAlertLayer::create("Error", errorString, "Ok")->show();
        return;
    }

    selectedObj->setPosition({xPosResult.unwrap(), yPosResult.unwrap()});
    selectedObj->m_scaleX = xScaleResult.unwrap();
    selectedObj->m_scaleY = yScaleResult.unwrap(); //"real" hitbox??
    selectedObj->setScaleX(xScaleResult.unwrap());
    selectedObj->setScaleY(yScaleResult.unwrap()); //visual (?
    selectedObj->setRotation(rotationResult.unwrap());
    selectedObj->m_zOrder = zOrderResult.unwrap();
    selectedObj->m_editorLayer = layerResult.unwrap();

}

bool ObjectEditorPopup::init() {

    if(!geode::Popup::init(485.f, 230.f)) {
        return false;
    }

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    m_noElasticity = true;
    this->setTitle("Object Editor");


    auto objXpos = selectedObj->getPositionX();
    auto objYpos = selectedObj->getPositionY();
    auto objXscale = selectedObj->getScaleX();
    auto objYscale = selectedObj->getScaleY();
    auto objRotation = selectedObj->getObjectRotation();
    auto objZorder = selectedObj->getObjectZOrder();
    auto objLayer = selectedObj->m_editorLayer;


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
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}