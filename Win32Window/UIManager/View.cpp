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

#include "View.h"

std::vector<vOnClick> UIManager::View::onClick;

UIManager::View::View()
{
	vType = UIManager::TextView;
}

UIManager::View::View(UIManager::ViewType view, int startX, int startY, int endX, int endY)
{
	vType = view;
	this->startX = startX;
	this->startY = startX;
	this->endX = endX;
	this->endY = endY;
}

void UIManager::View::setType(UIManager::ViewType view)
{
	vType = view;
}

void UIManager::View::setText(std::string text)
{
	vText = text;
}

void UIManager::View::setLocation(int xloc, int yloc)
{
	this->startX = xloc;
	this->startY = yloc;
}

void UIManager::View::setSize(int xsize, int ysize)
{
	this->endX = xsize;
	this->endY = ysize;
}

void UIManager::View::setOnClick(vOnClick callback)
{
	onClick.push_back(callback);
}
