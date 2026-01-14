#include <Geode/modify/EditorUI.hpp>
#include "UI/ObjectEditorPopup.hpp"

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
	void createMoveMenu() {
		
		EditorUI::createMoveMenu();

		auto sprite = ButtonSprite::create("Edit", "goldFont.fnt", "GJ_button_01.png", 0.25f);

		auto btn = CCMenuItemSpriteExtra::create(
			sprite,
			this,
			menu_selector(MyEditorUI::onMyButton)
		);

		m_editButtonBar->m_buttonArray->addObject(btn);
		auto rows = GameManager::sharedState()->getIntGameVariable("0049");
		auto cols = GameManager::sharedState()->getIntGameVariable("0050");
		m_editButtonBar->reloadItems(rows, cols);
	}

	void onMyButton(CCObject* sender) {
		int objCount = getSelectedObjects()->count();
		if(objCount <= 0 || objCount > 1) {
			FLAlertLayer::create("Error", "You only can edit one object", "Ok")->show();
		} else {
			ObjectEditorPopup::create()->show();
		}
	}
};