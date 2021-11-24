/*
 *2021 Shigehiro Fukase
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
#define JSON_NODE_DIE_ATTR_VALUE_STRING             "Value_String"
#if defined(CONFIG_OUTPUT_JSON_DIE_ATTR_EXTRA) && (CONFIG_OUTPUT_JSON_DIE_ATTR_EXTRA != 0)
#define JSON_NODE_DIE_ATTR_EXTRA                    "Extra"
#endif /* CONFIG_OUTPUT_JSON_DIE_ATTR_EXTRA */
#define JSON_NODE_DIE_ATTR_DATA_LENGTH_STRING       "Data_Length_String"
#define JSON_NODE_DIE_ATTR_DATA_LENGTH_NUMBER       "Data_Length_Number"
#define JSON_NODE_DIE_ATTR_DATA_STRING              "Data_String"

#define JSON_NODE_DIE_ATTR_OP                       "Op"
#define JSON_NODE_DIE_ATTR_OP_NAME                  "Name"
#define JSON_NODE_DIE_ATTR_OP_VALUE_STRING          "Value_String"
#define JSON_NODE_DIE_ATTR_OP_VALUE_NUMBER          "Value_Number"

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* ___OUTPUT_JSON_H___ */
