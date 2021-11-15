/*
 * 2021-2023 Shigehiro Fukase
 */

#include "libdwarf.h"
#include "dd_globals.h"
#include "dd_naming.h"
#include "dd_esb.h"
#include "dd_esb_using_functions.h"
#include "dd_sanitized.h"

#include "parson.h"
#include "output_json.h"

static FILE *json_wfp = NULL;
void json_init(void **prv, const char * name) {
    if (!glflags.json_root_value) {
        JSON_Value *root_value = json_value_init_object();
        JSON_Object *root_object = json_value_get_object(root_value);

        if (name) {
            json_object_set_string(root_object, JSON_NODE_FILENAME, name);
        }
        json_object_set_empty_array(root_object, JSON_NODE_SECTION);
        glflags.json_root_value = root_value;
    }
    if (prv) {
        *prv = glflags.json_root_value;
    }
    if (glflags.output_json) {
        json_wfp = fopen(glflags.output_json, "w");
        if (!json_wfp) {
            fprintf(stderr, "%s ERROR:  "
                "can't open save file.... %s\n",
                glflags.program_name,
                glflags.output_json);
        }
    }
}
void json_term(void *rv) {
    if (rv && (rv != glflags.json_root_value)) {
        json_value_free(rv);
    }
    json_value_free(glflags.json_root_value);
    glflags.json_root_value = NULL;

    if (json_wfp) {
        fclose(json_wfp);
    }
}
void json_add_section(JSON_Value *json_sec_val) {
    JSON_Value *root_value = glflags.json_root_value;
    JSON_Object *root_object = json_value_get_object(root_value);
    JSON_Array *arr = json_object_get_array(root_object, JSON_NODE_SECTION);
    json_array_append_value(arr, json_sec_val);
}
JSON_Status json_object_set_empty_array(JSON_Object *object, const char *name) {
    JSON_Value *val = json_value_init_array();
    JSON_Array *arr = json_value_get_array(val);
    json_array_clear(arr);
    return json_object_set_value(object, name, val);
}
char * json_get_string(void *rv) {
    JSON_Value *root_value;
    JSON_Object *root_object;
    char *serialized_string = NULL;

    if (!rv) {
        rv = glflags.json_root_value;
    }
    root_value = (JSON_Value *)rv;
    root_object = json_value_get_object(root_value);
    serialized_string = json_serialize_to_string_pretty(root_value);
    return serialized_string;
}
void json_dump(void *rv) {
    char *serialized_string = json_get_string(rv);
    // puts(serialized_string);
    if (json_wfp) {
        fputs(serialized_string, json_wfp);
    }
    json_free_serialized_string(serialized_string);
}
void json_save(const char * path, void *rv) {
    if (path) {
        FILE *fp = fopen(path, "w");
        if (fp) {
            char *serialized_string = json_get_string(rv);
            fprintf(fp, "%s\n", serialized_string);
            fclose(fp);
            json_free_serialized_string(serialized_string);
        } else {
            fprintf(stderr, "%s ERROR:  "
                "can't open save file.... %s\n",
                glflags.program_name,
                path);
        }
    }
}
