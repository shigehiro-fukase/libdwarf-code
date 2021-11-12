/*
 *2021 Shigehiro Fukase
 */

#ifndef ___OUTPUT_JSON_H___
#define ___OUTPUT_JSON_H___

#include "parson.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void json_init(void **prv);
void json_term(void *rv);
void json_add_section(JSON_Value *json_sec_val);

JSON_Status json_object_set_empty_array(JSON_Object *object, const char *name);

void json_dump(void *rv);
void json_save(const char * path, void *rv);

#define JSON_NODE_SECTION       "Section"
#define JSON_NODE_SECNAME       "Section_Name"
#define JSON_NODE_COMPILE_UNIT  "Compile_Unit"
#define JSON_NODE_DIE           "DIE"
# define    JSON_NODE_DIE_INDENT_LEVEL      "Indent_Level"
# define    JSON_NODE_DIE_GLOBAL_OFFSET     "Global_Offset"
# define    JSON_NODE_DIE_OFFSET            "Offset"
# define    JSON_NODE_DIE_OVERALL_OFFSET    "Overall_Offset"
# define    JSON_NODE_DIE_TAG_NAME          "Tag_Name"
#define JSON_NODE_ATTR          "Attr"
# define    JSON_NODE_ATTR_NAME             "Attr_Name"
# define    JSON_NODE_ATTR_VALUE            "Attr_Value"
# define    JSON_NODE_ATTR_EXTRA            "Extra"

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* ___OUTPUT_JSON_H___ */
