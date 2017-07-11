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

#ifndef _UI_MANAGER_INTERFACE_ERROR
#define _UI_MANAGER_INTERFACE_ERROR

// stringised version of line number (must be done in two steps)
#define STRINGISE(N) #N
#define EXPAND_THEN_STRINGISE(N) STRINGISE(N)
#define __LINE_STR__ EXPAND_THEN_STRINGISE(__LINE__)

// MSVC-suitable routines for formatting <#pragma message>
#define __LOC__ __FILE__ "(" __LINE_STR__ ")"
#define __OUTPUT_FORMAT__(type) __LOC__ " : " type " : "

// specific message types for <#pragma message>
#define __WARN__ __OUTPUT_FORMAT__("warning")
#define __ERR__ __OUTPUT_FORMAT__("error")
#define __MSG__ __OUTPUT_FORMAT__("programmer's message")
#define __TODO__ __OUTPUT_FORMAT__("to do")

#endif //_UI_MANAGER_INTERFACE_ERROR


//#pragma message ( __ERR__ "Error, Only EditText can handle OnTextChange Callbacks")