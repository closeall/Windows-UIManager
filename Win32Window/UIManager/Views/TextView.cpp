/*Copyright 2017 Ricardo Moya Mejias

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

#include "TextView.h"

UIManager::TextView::TextView()
{
}

UIManager::TextView::TextView(std::string text, int xloc, int yloc)
{
	oName = text;
	startX = xloc;
	startY = yloc;
}

void UIManager::TextView::setText(std::string text)
{
	oName = text;
}

void UIManager::TextView::setLocation(int xloc, int yloc)
{
	startX = xloc;
	startY = yloc;
}

void UIManager::TextView::setSize(int xsize, int ysize)
{
	endX = xsize;
	endY = ysize;
}

std::string UIManager::TextView::getText()
{
	return oName;
}

int UIManager::TextView::getXLoc()
{
	return startX;
}

int UIManager::TextView::getYLoc()
{
	return startY;
}

int UIManager::TextView::getXSize()
{
	return endX;
}

int UIManager::TextView::getYSize()
{
	return endY;
}
