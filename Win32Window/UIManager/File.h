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

#ifndef _UI_MANAGER_FILE_HEADER
#define _UI_MANAGER_FILE_HEADER

#include "Namespace.h"
#include <thread>
#include <iostream>
#include <string>

//File
HBITMAP UIManager::Bitmap(std::string url) {
	return (HBITMAP)LoadImage(NULL, url.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HICON UIManager::Icon(std::string url) {
	return (HICON)LoadImage(NULL, url.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
}

#endif //_UI_MANAGER_FILE_HEADER