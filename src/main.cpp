#include <Geode/modify/EditorUI.hpp>
#include "UI/ObjectEditorPopup.hpp"

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
	/*
	https://github.com/matcool/geode-mods/blob/main/circle-tool/main.cpp
	code i used as a reference to add the button to the editor.
	thanks mat
	*/
	void createMoveMenu() {
		
		EditorUI::createMoveMenu();

		auto btn = this->getSpriteButton("editButton.png"_spr, menu_selector(MyEditorUI::onMyButton), nullptr, 0.9f);

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