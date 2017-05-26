#include "ViewHandler.h"

std::string vh::getView(UIManager::ViewType input)
{
	switch (input) {
	case UIManager::TextView:
		return "Static";
	case UIManager::Button:
		return "Button";
	case UIManager::EditText:
		return "Edit";
	case UIManager::PictureBox:
		return "Static";
	case UIManager::ListBox:
		return "ListBox";
	case UIManager::ComboBox:
		return "ComboBox";
	default:
		return "Static";
	}
}
