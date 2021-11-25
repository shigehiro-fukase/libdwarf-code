/*
 SPDX-License-Identifier: MIT
 
 Copyright (c) 2021-2022 Shigehiro Fukase

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#ifndef ___OUTPUT_JSON_H___
#define ___OUTPUT_JSON_H___

#define CONFIG_OUTPUT_JSON_DIE_ATTR_EXTRA           0

#include "parson.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void json_init(void **prv, const char * name);
void json_term(void *rv);
void json_add_section(JSON_Value *json_sec_val);

JSON_Status json_object_set_empty_array(JSON_Object *object, const char *name);

void json_dump(void *rv);
void json_save(const char * path, void *rv);

#define JSON_NODE_FILENAME                          "Filename"
#define JSON_NODE_SECTION                           "Section"
#define JSON_NODE_SECNAME                           "Section_Name"
#define JSON_NODE_COMPILE_UNIT                      "Compile_Unit"
#define JSON_NODE_DIE                               "DIE"
#define JSON_NODE_DIE_INDENT_LEVEL                  "Indent_Level"
#define JSON_NODE_DIE_GLOBAL_OFFSET                 "Global_Offset"
#define JSON_NODE_DIE_OFFSET_ID                     "Offset_ID"
#define JSON_NODE_DIE_OVERALL_OFFSET                "Overall_Offset"
#define JSON_NODE_DIE_TAG_NAME                      "Tag_Name"

#define JSON_NODE_DIE_ATTR                          "Attr"
#define JSON_NODE_DIE_ATTR_NAME                     "Name"
#define JSON_NODE_DIE_ATTR_VALUE                    "Value"
#if defined(CONFIG_OUTPUT_JSON_DIE_ATTR_EXTRA) && (CONFIG_OUTPUT_JSON_DIE_ATTR_EXTRA != 0)
#define JSON_NODE_DIE_ATTR_EXTRA                    "Extra"
#endif /* CONFIG_OUTPUT_JSON_DIE_ATTR_EXTRA */
#define JSON_NODE_DIE_ATTR_DATA_LENGTH              "Data_Length"
#define JSON_NODE_DIE_ATTR_DATA_LENGTH_NUMBER       "Data_Length_Number"
#define JSON_NODE_DIE_ATTR_DATA                     "Data"

#define JSON_NODE_DIE_ATTR_OP                       "Op"
#define JSON_NODE_DIE_ATTR_OP_NAME                  "Name"
#define JSON_NODE_DIE_ATTR_OP_VALUE                 "Value"
#define JSON_NODE_DIE_ATTR_OP_VALUE_NUMBER          "Value_Number"

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* ___OUTPUT_JSON_H___ */
