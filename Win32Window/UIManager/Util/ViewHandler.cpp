#include "ViewHandler.h"

std::string vh::getView(UIManager::ViewType input)
{
	switch (input) {
	case UIManager::TextView:
		return "Static";
	case UIManager::Button:
		return "Button";
	case UIManager::ImageButton:
		return "Button";
	case UIManager::CustomButton:
		return "Button";
	case UIManager::EditText:
		return "Edit";
	case UIManager::PictureBox:
		return "Static";
	case UIManager::ProgressBar:
		return PROGRESS_CLASS;
	case UIManager::ListBox:
		return "ListBox";
	case UIManager::ComboBox:
		return WC_COMBOBOX;
	default:
		return "Static";
	}
}
