/*Copyright 2017 Onelio

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

#ifndef _UI_MANAGER_INTERFACE_HEADER
#define _UI_MANAGER_INTERFACE_HEADER

#include "Namespace.h"
#include <thread>
#include <iostream>
#include <string>

//Window Callbacks
typedef std::function<void(HWND hwnd)> wCreateCallBack;
typedef std::function<void(HWND hwnd)> wDestroyCallBack;
typedef std::function<void(HWND hwnd, bool focused)> wFocusCallBack;
typedef std::function<void(HWND hwnd, UIManager::Coordinates coord)> wLeftClickCallBack;
typedef std::function<void(HWND hwnd, UIManager::Coordinates coord)> wRightClickCallBack;
typedef std::function<void(HWND hwnd, UIManager::Coordinates coord)> wMiddleClickCallBack;
typedef std::function<void(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)> wPersonalizedCallBack;

//View Callbacks
typedef std::function<void(HWND hwnd)> vOnClick;
typedef std::function<void(HWND hwnd)> vOnDoubleClick;
typedef std::function<void(HWND hwnd, std::string text)> vOnTextChange;
typedef std::function<void(HWND hwnd)> vOnCursorEnter;
typedef std::function<void(HWND hwnd)> vOnCursorLeave;

//View Redraw
typedef std::function<void(HWND hwnd, LPDRAWITEMSTRUCT &lpDrawItem)> vOnNormalRedraw;
typedef std::function<void(HWND hwnd, LPDRAWITEMSTRUCT &lpDrawItem)> vOnHoverRedraw;
typedef std::function<void(HWND hwnd, LPDRAWITEMSTRUCT &lpDrawItem)> vOnPressRedraw;

#endif //_UI_MANAGER_INTERFACE_HEADER