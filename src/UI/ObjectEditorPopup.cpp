#include "ObjectEditorPopup.hpp"
#include <string>

using namespace geode::prelude;


void ObjectEditorPopup::onApplyButton(CCObject* sender) {
    auto xPosStr = xPosInput->getString();
    auto yPosStr = yPosInput->getString();
    auto xScaleStr = xScaleInput->getString();
    auto yScaleStr = yScaleInput->getString();
    auto rotationStr = rotationInput->getString();
    auto zOrderStr = zOrderInput->getString();

    float xPos = 0.f;
    float yPos = 0.f;
    float xScale = 0.f;
    float yScale = 0.f;
    float rotation = 0.f;
    int zOrder = 0.f;

    try {
        xPos = std::stof(xPosStr);
        yPos = std::stof(yPosStr);
        xScale = std::stof(xScaleStr);
        yScale = std::stof(xScaleStr);
        rotation = std::stof(rotationStr);
        zOrder = std::stoi(zOrderStr);

        selectedObj->setPosition({xPos, yPos});
        selectedObj->setRScaleX(xScale);
        selectedObj->m_scaleX =xScale;
        selectedObj->setRScaleX(yScale);
        selectedObj->m_scaleY= yScale;
        selectedObj->setRotation(rotation);
        selectedObj->m_zOrder = zOrder;
    } catch (...) {
        FLAlertLayer::create("Error", "Enter a valid number.", "Ok");
        return;
    }
}

bool ObjectEditorPopup::setup() {
    m_noElasticity = true;
    this->setTitle("Object Editor");

    auto objXpos = selectedObj->getPositionX();
    auto objYpos = selectedObj->getPositionY();
    auto objXscale = selectedObj->getScaleX();
    auto objYscale = selectedObj->getScaleY();
    auto objRotation = selectedObj->getObjectRotation();
    auto objZorder = selectedObj->getObjectZOrder();

    auto winSize = CCDirector::sharedDirector()->getWinSize();


    auto inputMenu = CCMenu::create();
    inputMenu->setContentSize({485.f, 150.f});
    inputMenu->setPosition(winSize / 2);

    auto inputLayout = RowLayout::create();
    inputLayout->setGap(15.f);
    inputLayout->setGrowCrossAxis(true);
    inputMenu->setLayout(inputLayout);


    CCNode* xPosNode = CCNode::create();
    xPosNode->setContentSize({100.f, 60.f});

    xPosInput = TextInput::create(100.f, "xPos", "bigFont.fnt");
    xPosInput->setString(std::to_string(objXpos));
    xPosInput->setPosition({50.f, 20.f});
    xPosNode->addChild(xPosInput);

    auto xPosLabel = CCLabelBMFont::create("x Pos", "bigFont.fnt");
    xPosLabel->setPosition({50.f, 50.f});
    xPosLabel->setScale(0.75f);
    xPosNode->addChild(xPosLabel);


    CCNode* yPosNode = CCNode::create();
    yPosNode->setContentSize({100.f, 60.f});

    yPosInput = TextInput::create(100.f, "yPos", "bigFont.fnt");
    yPosInput->setString(std::to_string(objYpos));
    yPosInput->setPosition({50.f, 20.f});
    yPosNode->addChild(yPosInput);

    auto yPosLabel = CCLabelBMFont::create("y Pos", "bigFont.fnt");
    yPosLabel->setPosition({50.f, 50.f});
    yPosLabel->setScale(0.75f);
    yPosNode->addChild(yPosLabel);


    CCNode* xScaleNode = CCNode::create();
    xScaleNode->setContentSize({100.f, 60.f});

    xScaleInput = TextInput::create(100.f, "xScale", "bigFont.fnt");
    xScaleInput->setString(std::to_string(objXscale));
    xScaleInput->setPosition({50.f, 20.f});
    xScaleNode->addChild(xScaleInput);

    auto xScaleLabel = CCLabelBMFont::create("x Scale", "bigFont.fnt");
    xScaleLabel->setPosition({50.f, 50.f});
    xScaleLabel->setScale(0.75f);
    xScaleNode->addChild(xScaleLabel);


    CCNode* yScaleNode = CCNode::create();
    yScaleNode->setContentSize({100.f, 60.f});

    yScaleInput = TextInput::create(100.f, "yScale", "bigFont.fnt");
    yScaleInput->setString(std::to_string(objYscale));
    yScaleInput->setPosition({50.f, 20.f});
    yScaleNode->addChild(yScaleInput);

    auto yScaleLabel = CCLabelBMFont::create("y Scale", "bigFont.fnt");
    yScaleLabel->setPosition({50.f, 50.f});
    yScaleLabel->setScale(0.75f);
    yScaleNode->addChild(yScaleLabel);


    CCNode* rotationNode = CCNode::create();
    rotationNode->setContentSize({100.f, 60.f});

    rotationInput = TextInput::create(100.f, "Rotation", "bigFont.fnt");
    rotationInput->setString(std::to_string(objRotation));
    rotationInput->setPosition({50.f, 20.f});
    rotationNode->addChild(rotationInput);

    auto rotationLabel = CCLabelBMFont::create("Rotation", "bigFont.fnt");
    rotationLabel->setPosition({50.f, 50.f});
    rotationLabel->setScale(0.75f);
    rotationNode->addChild(rotationLabel);


    CCNode* zOrderNode = CCNode::create();
    zOrderNode->setContentSize({100.f, 60.f});

    zOrderInput = TextInput::create(100.f, "Z Order", "bigFont.fnt");
    zOrderInput->setString(std::to_string(objZorder));
    zOrderInput->setPosition({50.f, 20.f});
    zOrderNode->addChild(zOrderInput);

    auto zOrderLabel = CCLabelBMFont::create("Z Order", "bigFont.fnt");
    zOrderLabel->setPosition({50.f, 50.f});
    zOrderLabel->setScale(0.75f);
    zOrderNode->addChild(zOrderLabel);


    inputMenu->addChild(xPosNode);
    inputMenu->addChild(yPosNode);
    inputMenu->addChild(xScaleNode);
    inputMenu->addChild(yScaleNode);
    inputMenu->addChild(rotationNode);
    inputMenu->addChild(zOrderNode);


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